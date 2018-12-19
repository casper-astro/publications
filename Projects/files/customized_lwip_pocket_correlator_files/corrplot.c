#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <grace_np.h>
 
#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
#endif
 
#ifndef EXIT_FAILURE
#  define EXIT_FAILURE -1
#endif
 
void my_error_function(const char *msg)
{
    fprintf(stderr, "library message: \"%s\"\n", msg);
}
 
 
main()
{
FILE *fp;
short int myshortint;
//int myint;
//long mylong;
//long int mylongint;
//unsigned int someint;
int i, j, k, bytesread;
char c;
char payload[5050];
char temppayload[1045];
 
char labelstrings[]="AAABBBACBCCCBDCDDDAD";
 
long value[1024];
 
 
unsigned int real, imag;
unsigned int accumulation_number;
unsigned int vector_number;
unsigned int vector_order;
unsigned int first_accumulation = 0;
unsigned int bump = 1045;
unsigned int baseline_number = 0;
int colors[10]={2, 3, 4, 8, 9, 10, 11, 12, 13, 14};
char placeholder[4];
struct baseline {
double real[1024];
double imag[1024];
};
double phase=0;
struct baseline baselines[10];
 
 
 
/* packet headers */
/* the 21 byte UDP data packets look like this: */
/* 8 bytes (double) time */
/* 1 byte x engine number */
/* 4 bytes (unsigned int) vector number within an integration */
/*   (ie if you want to send 10MB every integration and you break it up into 1MB packets, this */
/*    number will range from 0 to 9) */
/* 4 bytes (unsigned int) flags (not used atm - foresee use to flag bad data) */
/* 4 bytes (unsigned int) data length (in bytes) (payload length) */
 
    GraceRegisterErrorFunction(my_error_function);
 
    /* Start Grace with a buffer size of 2048 and open the pipe */
    if (GraceOpen(16768) == -1) {
        fprintf(stderr, "Can't run Grace. \n");
        exit(EXIT_FAILURE);
    }
 
 
 
   /* Send some initialization commands to Grace */
    GracePrintf("arrange(2, 2, 0.1, 0.15, 0.5)");
 
	GracePrintf("Legend ON");
	GracePrintf("Legend loctype view");
	GracePrintf("Legend 1.1, 0.9");
 
 
    GracePrintf("view ymax 0.002");
    GracePrintf("view ymin 0.001");
    GracePrintf("view xmax 0.002");
    GracePrintf("view xmin 0.001");
    GracePrintf("xaxis tick off");
    GracePrintf("yaxis tick off");
 
 
    GracePrintf("with g1");
	GracePrintf("yaxis TICKLABEL APPEND \"\\x p\"");
 
 
    GracePrintf("xaxis tick major 256");
    GracePrintf("xaxis tick minor 128");
    GracePrintf("yaxis tick major 1");
    GracePrintf("yaxis tick minor off");
 
	GracePrintf("view ymax 0.9");
    GracePrintf("view ymin .50");
    GracePrintf("view xmax 1.05");
    GracePrintf("view xmin 0.1");
 
	GracePrintf("SUBTITLE FONT 1");
	GracePrintf("SUBTITLE SIZE 1");
 
    GracePrintf("SUBTITLE \"Phase\"");
 
    GracePrintf("world xmax 1024");
    GracePrintf("world ymax 3.15");
    GracePrintf("world ymin -3.15");
 
        GracePrintf("with g2");
 
    GracePrintf("xaxis tick major 256");
    GracePrintf("xaxis tick minor 128");
    GracePrintf("yaxis tick major 1");
    GracePrintf("yaxis tick minor off");
 
	GracePrintf("view ymax 0.4");
    GracePrintf("view ymin .1");
    GracePrintf("view xmax 1.05");
    GracePrintf("view xmin 0.1");
 
	GracePrintf("SUBTITLE FONT 1");
	GracePrintf("SUBTITLE SIZE 1");
 
    GracePrintf("SUBTITLE \"Amplitude\"");    
    GracePrintf("world xmax 1024");
    GracePrintf("world ymax 100");
    GracePrintf("world ymin 0");
 
    GracePrintf("yaxis tick major 25");
    GracePrintf("yaxis tick minor off");
    GracePrintf("G3 HIDDEN TRUE");
 
    /* Display sample data */
    for (j=1;j<11;j=j+1){
	GracePrintf("g0.s%d color %d", j, colors[j-1]);
    GracePrintf("g0.s%d legend \"%c%c\"", j, labelstrings[((j*2) - 2)], labelstrings[((j*2) - 1)]  );
 
    for (i = 0; i < 1024 && GraceIsOpen(); i++) {
        GracePrintf("g0.s%d point %d, %d",j, i, j);
        //GracePrintf("g0.s1 point %d, %d", i, ((i * i) + j));
        /* Update the Grace display after every ten steps */
 
    }
    	printf("1\n");
    	GracePrintf("redraw");
    }
 
if ((fp = fopen("blah.log", "r")) == NULL) printf("\nError: Cannot open the file\n"); 
 
 
while(1)
{
 
 
	//read to end of file   
	while(bump == 1045)
	{
		bump = fread(&payload, sizeof(char), 1045, fp); 
	}
 
 
	//look for vector 0, start of newest data
	vector_number = 99;
	baseline_number = 0;
	while(vector_number != 0)
	{
		bytesread = fread(&payload[bump], sizeof(char), (size_t) (1045 - bump), fp);
		//printf("got: %d and %08x and %d \n", bytesread+bump, payload, 1045-bump);
 
		if((bytesread + bump) == 1045){			
 
 
			vector_number = (((unsigned int) payload[12])%256);
			vector_number += (((unsigned int) payload[11])%256) * 256;
			vector_number += (((unsigned int) payload[10])%256) * 65536;
			vector_number += (((unsigned int) payload[9])%256) * 16777216;
			//printf("Vector Number: %d\n", vector_number);
			bump = 0;
		} else {
			bump = bump + bytesread;			
		}
	}
 
 
	//GracePrintf("plot");
 
	while(vector_number <= 63)
	{
	//at this point we know that we are on a packet boundry and at vector 0.
	//now we continue reading until we have a complete spectra
		accumulation_number = (((unsigned int) payload[4])%256);
		accumulation_number += (((unsigned int) payload[5])%256) * 256;
		accumulation_number += (((unsigned int) payload[6])%256) * 65536;
		accumulation_number += (((unsigned int) payload[7])%256) * 16777216;
 
 
 
		vector_order = (((vector_number + 4)%4) * 256);
		 //printf("vector order is: %i, bump: %d vector_number: %d acc_num: %d\n", vector_order, bump, vector_number, accumulation_number);
		 //printf("Vector Order: %d\n", vector_order);
/*		 
dumpbrams[0] = XPAR_PE_LWIP_1K_DIR_X_AA_BRAM_BASEADDR; 3
dumpbrams[1] = XPAR_PE_LWIP_1K_DIR_X_AB_REAL_BASEADDR; 7
dumpbrams[2] = XPAR_PE_LWIP_1K_DIR_X_AB_IMAG_BASEADDR; 11
dumpbrams[3] = XPAR_PE_LWIP_1K_DIR_X_BB_BRAM_BASEADDR; 15
dumpbrams[4] = XPAR_PE_LWIP_1K_DIR_X_AC_REAL_BASEADDR; 19
dumpbrams[5] = XPAR_PE_LWIP_1K_DIR_X_AC_IMAG_BASEADDR; 23
dumpbrams[6] = XPAR_PE_LWIP_1K_DIR_X_BC_REAL_BASEADDR; 27
dumpbrams[7] = XPAR_PE_LWIP_1K_DIR_X_BC_IMAG_BASEADDR; 31
dumpbrams[8] = XPAR_PE_LWIP_1K_DIR_X_CC_BRAM_BASEADDR; 35
dumpbrams[9] = XPAR_PE_LWIP_1K_DIR_X_BD_REAL_BASEADDR; 39
dumpbrams[10] = XPAR_PE_LWIP_1K_DIR_X_BD_IMAG_BASEADDR; 43
dumpbrams[11] = XPAR_PE_LWIP_1K_DIR_X_CD_REAL_BASEADDR; 47
dumpbrams[12] = XPAR_PE_LWIP_1K_DIR_X_CD_IMAG_BASEADDR; 51
dumpbrams[13] = XPAR_PE_LWIP_1K_DIR_X_DD_BRAM_BASEADDR; 55
dumpbrams[14] = XPAR_PE_LWIP_1K_DIR_X_AD_REAL_BASEADDR; 59
dumpbrams[15] = XPAR_PE_LWIP_1K_DIR_X_AD_IMAG_BASEADDR; 63
*/
 
		 for(j =0;j <256;j += 1)
		 {
			 placeholder[0] = payload[21 + (j*4)];
			 placeholder[1] = payload[21 + (j*4) + 1];
			 placeholder[2] = payload[21 + (j*4) + 2];
			 placeholder[3] = payload[21 + (j*4) + 3];
			 value[vector_order + j] = *(long*) placeholder;	 
 
 
	  		value[vector_order + j] =   value[vector_order + j] / 64;   //scale back fixed point
//			 value[vector_order + j] = (((unsigned int) payload[21 + (j*4)])%256);
//			 value[vector_order + j] += (((unsigned int) payload[21 + (j*4) + 1])%256) * 256; 
//			 value[vector_order + j] += (((unsigned int) payload[21 + (j*4) + 2])%256) * 65536;	
//			 value[vector_order + j] += (((unsigned int) payload[21 + (j*4) + 3])%256) * 16777216;
 
		//	 printf("Real: %d Imag: %d Power: %f\n", real, imag, power);
		 }
 
 
		 if(vector_order == 768 )
		 {
			//process auto correlations
			if(vector_number == 3 || vector_number == 15 || vector_number == 35 || vector_number == 55) {
				for(j=0;j<1024;j++){
					baselines[baseline_number].real[j] = value[j];
					baselines[baseline_number].imag[j] = 0;
				}
				baseline_number++;
			}
			//process real cross correlations
			if(vector_number == 7 || vector_number == 19 || vector_number == 27 || vector_number == 39 || vector_number == 47 || vector_number == 59) {
				for(j=0;j<1024;j++){
					baselines[baseline_number].real[j] = value[j];
				}
			}
			//process imag cross correlations
			if(vector_number == 11 || vector_number == 23 || vector_number == 31 || vector_number == 43 || vector_number == 51 || vector_number == 63) {
				for(j=0;j<1024;j++){
					baselines[baseline_number].imag[j] = value[j];
				}
				baseline_number++;			
			}
 
 
 
		 }	
		 if(vector_number < 63){
		 	vector_number = 99;
		 } else {
 
		 	for(baseline_number = 0;baseline_number<10;baseline_number++){
				   GracePrintf("kill g2.s%d", baseline_number);			 
				   GracePrintf("kill g1.s%d", baseline_number);			 
 
				   GracePrintf("g2.s%d color %d", baseline_number, colors[baseline_number]);			 
				   GracePrintf("g1.s%d color %d", baseline_number, colors[baseline_number]);			 
 
				   for (j=512;j<1024;j++){
						GracePrintf("g2.s%d point %d, %f", baseline_number, j-512, sqrt((baselines[baseline_number].real[j] * baselines[baseline_number].real[j]) + (baselines[baseline_number].imag[j] * baselines[baseline_number].imag[j])));
/*
						if(baselines[baseline_number].real[j] == 0.0) phase = 10.0;
						if(baselines[baseline_number].real[j] > 0.0 && baselines[baseline_number].imag[j] > 0.0) phase = atan((baselines[baseline_number].imag[j] / baselines[baseline_number].real[j]));
						if(baselines[baseline_number].real[j] < 0.0 && baselines[baseline_number].imag[j] > 0.0) phase = ((((3.1415/2.0) + atan((baselines[baseline_number].imag[j]) / baselines[baseline_number].real[j]))) + (3.1415/2.0));
						if(baselines[baseline_number].real[j] < 0.0 && baselines[baseline_number].imag[j] < 0.0) phase = ( (atan((baselines[baseline_number].imag[j] / baselines[baseline_number].real[j])) - (3.1415/2.0)) - (3.1415/2.0));
						if(baselines[baseline_number].real[j] > 0.0 && baselines[baseline_number].imag[j] < 0.0) phase = atan((baselines[baseline_number].imag[j] / baselines[baseline_number].real[j]));
*/
 
						phase = atan2(baselines[baseline_number].imag[j] , baselines[baseline_number].real[j]);
						GracePrintf("g1.s%d point %d, %f", baseline_number, j-512, phase);
 
				   }
 
				   for (j=0;j<512;j++){
						GracePrintf("g2.s%d point %d, %f", baseline_number, j+512, sqrt((baselines[baseline_number].real[j] * baselines[baseline_number].real[j]) + (baselines[baseline_number].imag[j] * baselines[baseline_number].imag[j])));
/*						
						if(baselines[baseline_number].real[j] == 0.0) phase = 10.0;
						if(baselines[baseline_number].real[j] > 0.0 && baselines[baseline_number].imag[j] > 0.0) phase = atan((baselines[baseline_number].imag[j] / baselines[baseline_number].real[j]));
						if(baselines[baseline_number].real[j] < 0.0 && baselines[baseline_number].imag[j] > 0.0) phase = ((((3.1415/2.0) + atan((baselines[baseline_number].imag[j]) / baselines[baseline_number].real[j]))) + (3.1415/2.0));
						if(baselines[baseline_number].real[j] < 0.0 && baselines[baseline_number].imag[j] < 0.0) phase = ( (atan((baselines[baseline_number].imag[j] / baselines[baseline_number].real[j])) - (3.1415/2.0)) - (3.1415/2.0));
						if(baselines[baseline_number].real[j] > 0.0 && baselines[baseline_number].imag[j] < 0.0) phase = atan((baselines[baseline_number].imag[j] / baselines[baseline_number].real[j]));
*/
						phase = atan2(baselines[baseline_number].imag[j] , baselines[baseline_number].real[j]);						
						GracePrintf("g1.s%d point %d, %f", baseline_number, j+512, phase);
 
				   }
 
 
 
				 GracePrintf("redraw");
			}
 
 
		 	vector_number = 98;
 
		 }
		 while(vector_number == 99){
			  bytesread = fread(&payload[bump], sizeof(char), 1045 - bump, fp);
			  if((bytesread + bump) == 1045){			
				  vector_number = (((unsigned int) payload[12])%256);
				  vector_number += (((unsigned int) payload[11])%256) * 256;
				  vector_number += (((unsigned int) payload[10])%256) * 65536;
				  vector_number += (((unsigned int) payload[9])%256) * 16777216;
				  bump = 0;
			  } else {
				  bump = bump + bytesread;			
			  }
		 }
 
	}	
	bump = 1045;
	usleep(500000);
} 
 
 
	fclose(fp);
 
}