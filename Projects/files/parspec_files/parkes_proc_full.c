/*
 
Converts "gulp" (i.e. libpcap) captures from Parkes/Effelsberg spectrometer
 
Peter McMahon
Karoo Array Telescope
http://www.ska.ac.za
Center for Astronomy Signal Processing and Electronics Research, UC Berkeley
http://casper.berkeley.edu
January 2008
 
Based on pcap-format conversion code by Andrew Siemion.
 
-------------------------------------------------------------------------------------------
 
Input: file datadump.log
Output: files data-fft0.txt data-fft1.txt
 
Input format:
  - Each packet contains a single 1K channel power spectrum from the two FFTs in the FPGA.
  - Each packet starts with a 64-bit counter that counts the number of FPGA clock ticks since the ARM/1PPS was used to reset it.
  - Each packet contains 2056 bytes: 2048 bytes of FFT data, and an 8 byte counter (header)
  - This counter is followed by the binary data containing the FFT bin values.
  - FFT bin power outputs are 8-bits each.
  - The ordering of the FFT output is not obvious. It works like this, where FFT(i)-j-x is bin j from FFT i (and i = 0, 1; j = 0,..,1023) :
 
FFT(0)-0
FFT(0)-1
FFT(1)-0
FFT(1)-1
FFT(0)-2
FFT(0)-3
FFT(1)-2
FFT(1)-3
FFT(0)-4
FFT(0)-5
FFT(1)-4
FFT(1)-5
...
FFT(0)-1022
FFT(0)-1023
FFT(1)-1022
FFT(1)-1023
 
Output format:
  - The output is two text files. Each file contains the spectra of a single FFT.
  - The output files contain the data in each packet, starting with the counter value, and followed by the spectra that the packet contained
    (the first spectum is outputted to the first file, and the second spectum is outputted to the second file)
  - If the "-nocount" switch is included in the command line argument, the FPGA counter that is included in every packet is not outputted.
  - The output looks like this (the data is in text and each line is separated by a '\n' character:
 
File data-fft0.txt:
<packet_i_counter>
FFT(0)-0 FFT(0)-1 FFT(0)-2 ... FFT(0)-1023
<packet_i+1_counter>
FFT(0)-0 FFT(0)-1 FFT(0)-2 ... FFT(0)-1023
...
 
File data-fft1.txt:
<packet_i_counter>
FFT(1)-0 FFT(1)-1 FFT(1)-2 ... FFT(1)-1023
<packet_i+1_counter>
FFT(1)-0 FFT(1)-1 FFT(1)-2 ... FFT(1)-1023
...
 
*/
#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
 
#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
#endif
 
#ifndef EXIT_FAILURE
#  define EXIT_FAILURE -1
#endif
 
// Swaps bytes in an unsigned long long. Used to convert a ULL to big endian.
// Based on code by Jeff Hagen
void swap_ull(unsigned long long *pd)
{
  unsigned char t;
  unsigned char *pc;
 
  pc = (unsigned char *)pd;
  t = pc[0];
  pc[0] = pc[7];
  pc[7] = t;
 
  t = pc[1];
  pc[1] = pc[6];
  pc[6] = t;
 
  t = pc[2];
  pc[2] = pc[5];
  pc[5] = t;
 
  t = pc[3];
  pc[3] = pc[4];
  pc[4] = t;
}
 
// Swaps bytes in an unsigned int. Used to convert an unsigned to big endian.
// By Jeff Hagen.
void swap_uint(unsigned int *pi)
{
  unsigned char t;
  unsigned char *pc;
 
  pc = (unsigned char *)pi;
 
  t = pc[0];
  pc[0] = pc[3];
  pc[3] = t;
 
  t = pc[1];
  pc[1] = pc[2];
  pc[2] = t;
}
 
int main(int argc, char** argv)
{
  int x, i, j=0, k=0;
  char c;
  unsigned char payload[5050];
 
  char filename[50];
  int totalerror=0;
 
  unsigned int ip=0;
  unsigned int packet_len;
  unsigned int bump = 533;
 
  int include_counter = 1;
  if (argc == 2)
  {
    if (strcmp(argv[1], "-nocount"))
      include_counter = 0;
  }
 
 
  /* packet headers */
  /* the 21 byte UDP data packets look like this: */
  /* 8 bytes (double) time */
  /* 1 byte x engine number */
  /* 4 bytes (unsigned int) vector number within an integration */
  /*   (ie if you want to send 10MB every integration and you break it up into 1MB packets, this */
  /*    number will range from 0 to 9) */
  /* 4 bytes (unsigned int) flags (not used atm - foresee use to flag bad data) */
  /* 4 bytes (unsigned int) data length (in bytes) (payload length) */
 
 
  // PCAP global header -- SEE: http://wiki.wireshark.org/Development/LibpcapFileFormat
  //typedef struct pcap_hdr_s {
  //     4  guint32 magic_number;   /* magic number */
  //     2  guint16 version_major;  /* major version number */
  //     2  guint16 version_minor;  /* minor version number */
  //     4  gint32  thiszone;       /* GMT to local correction */
  //     4  guint32 sigfigs;        /* accuracy of timestamps */
  //     4  guint32 snaplen;        /* max length of captured packets, in octets */
  //     4  guint32 network;        /* data link type */
  //} pcap_hdr_t;  //24 bytes total
 
 
  // Open output textfiles
  sprintf(filename, "data-fft0.txt");    
  FILE *f_out_fft0 = fopen64(filename, "w");
  if (!f_out_fft0)
    printf("\nError: Cannot open the file %d\n", x); 
  printf("Opened: %s\n", filename);
 
  sprintf(filename, "data-fft1.txt");
  FILE *f_out_fft1 = fopen64(filename, "w");
  if (!f_out_fft1)
    printf("\nError: Cannot open the file %d\n", x);
  printf("Opened: %s\n", filename);
 
 
  //Open the raw data file...
  sprintf(filename, "datadump.log");    
  FILE *fp = fopen64(filename, "r");
  if (!fp)
    printf("\nError: Cannot open the file %d\n", x); 
  printf("Opened: %s\n", filename);
 
  //initialize a couple of variables
  bump=533;
  j = 0;
 
  //bump past pcap global header
  bump = fread(&payload, sizeof(char), 24, fp); 		
 
  printf("Reading packet data...\n");
 
 
  // Variables to hold contents of a data packet
  unsigned long long last_fpga_counter; // store counter from previous packet to find packet losses
  unsigned long long fpga_counter; // unsigned 64 bit integer
 
  unsigned long long packets_read = 0ULL;
 
  do {
 
    //PCAP per packet header
    //typedef struct pcaprec_hdr_s {
    //        guint32 ts_sec;         /* timestamp seconds */
    //        guint32 ts_usec;        /* timestamp microseconds */
    //        guint32 incl_len;       /* number of octets of packet saved in file */
    //        guint32 orig_len;       /* actual length of packet */
    //} pcaprec_hdr_t;
 
    //Bump past pcap per-packet header
    bump = fread(&payload, sizeof(char), 16, fp); 		
 
    packet_len = (((unsigned int) payload[12])%256);
    packet_len += (((unsigned int) payload[13])%256) * 256;
    packet_len += (((unsigned int) payload[14])%256) * 65536;
    packet_len += (((unsigned int) payload[15])%256) * 16777216;
 
    if (packet_len == 2098) { // our UDP packets are 2098 bytes long (Ethernet header=14 bytes; IP header=20 bytes; UDP header=8 bytes; data=2056 bytes)
      packets_read = packets_read + 1ULL;
      //printf("Data packet %llu\n", packets_read);
 
      //Process this packet
 
      // Ethernet header is from bytes 0 -> 13
      // IP protocol header is from 14 -> 33
      // UDP header is from 34 -> 41
      // data is from 42 -> 2097
 
      // data format is: counter fft(0)-0 fft(0)-1 fft(1)-0 fft(1)-1 ... fft(0)-1022 fft(0)-1023 fft(1)-1022 fft(1)-1023
      //   counter is 8-bytes; all fft bins are 4 bytes
      // i.e. counter is in 42 -> 49
      //      fft bins are in 50 -> 2097
 
      bump = fread(&payload, sizeof(char), 42, fp); // read Ethernet, IP and UDP headers (42 bytes in all)
 
      ip = (((unsigned int) payload[29])%256); // "from" IP address (extracted from IP header) (actually only the last part of the IP address)
 
      // read the 8 bytes that store the FPGA counter
 
      bump = fread(&fpga_counter, sizeof(unsigned long long), 1, fp);
 
      swap_ull(&fpga_counter); // this assumes BIG ENDIAN architecture (e.g. Intel) - if not, remove!
 
      // Write counter out to both files (unless a command line option is used to disable this)
      if (include_counter) {
        fprintf(f_out_fft0, "%llu\n", fpga_counter);
        fprintf(f_out_fft1, "%llu\n", fpga_counter);
      }
 
      if (fpga_counter != (last_fpga_counter+6656ULL)) // 6656 = acclen * 512clks/spectrum = 13*512; 15360 = 30 * 512; 30720 = 60 * 512
      {
        // packet loss
	printf("Packet loss! Packet number: %llu, New counter: %llu, Old counter: %llu, Counter diff = %llu, implied packet loss: %llu\n", packets_read, fpga_counter, last_fpga_counter, fpga_counter-last_fpga_counter, (fpga_counter-last_fpga_counter)/6656ULL);
      }
      last_fpga_counter = fpga_counter;
 
      // Read the data
      bump = fread(&payload, sizeof(char), 2048, fp);
 
      // Read data and write to disk
      for (j = 0; j < 512; j++)
      {
        // Read and write two bins from first FFT, then two bins from second FFT
	fprintf(f_out_fft0, "%d ", payload[(4*j)+0]);
	fprintf(f_out_fft0, "%d ", payload[(4*j)+1]);
	fprintf(f_out_fft1, "%d ", payload[(4*j)+2]);
	fprintf(f_out_fft1, "%d ", payload[(4*j)+3]);
      }
 
      fprintf(f_out_fft0, "\n");
      fprintf(f_out_fft1, "\n");
 
 
    } else {
      if(bump != 0) {
        //do not process this packet
        printf("skipping packet with len: %d\n", packet_len);
        bump = fread(&payload, sizeof(char), packet_len, fp);
      }
    }
  } while ((bump != 0) && (packets_read < 100ULL));
 
  printf("Packets read: %llu\n", packets_read);
 
  printf("closing input file\n");
  fclose(fp);
 
  printf("closing output files\n");
  fclose(f_out_fft0);
  fclose(f_out_fft1);
 
}