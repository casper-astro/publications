### BEE2 Interchip Interconnects ###

[Interchip pcore from the BEE2 Repository](http://repository.eecs.berkeley.edu/viewvc/Projects/BEE/trunk/2/hardware/pcores/interchip_block_v1_00_a/)

In the gen directory is a perl script for generating VHDL files for a pcore that in theory will correctly clock and delay the interconnect so that all the data arrives synchronously.
The perl script is called ''gen_chip2chip.pl'' It requires an input file to tell it what to do. The input file should look like this:

```
# interchip.info - input file for gen_chip2chip.pl
# 
# All entries seem to be required.
# Each variable is defined with an equals sign

# CHIP_A indicates the first FPGA, CHIP_B is the second FPGA
# Value 0 means the CTRL FPGA
# Values 1-4 mean FPGA1 - 4 (I hope they correspond to the labeling on the PCB)
CHIP_A=1   #FPGA1
CHIP_B=2   #FPGA2

#A2B indicates how many lines to assign FROM chip_A TO chip_B
#B2A indicates how many lines to assign FROM chip_B TO chip_A
# The sum of A2B + B2A must be less than 138 for between user FPGAs and less than 64 for between user and ctrl
A2B=138
B2A=0

#CLKFREQ is the clock frequency in MHz
CLKFREQ=200

#DDR should be 1 if DDR is to be used, 0 otherwise.
DDR=0

#CHIP_A_FILENAME indicates the filename prefix for the core that will reside in chip A
# Similarly for CHIP_B_FILENAME
# The output file will be <CHIP_A_FILENAME>.vhd etc
CHIP_A_FILENAME=FPGA1_TO_FPGA2
CHIP_B_FILENAME=FPGA2_FROM_FPGA1

#DELAY_CYCLE seems to only be important for DDR. I haven't found any change in the output when DDR is disabled
#Allowed values seem to be 0 or 1
DELAY_CYCLE=0
```

#### Notes about gen_chip2chip.pl ####

This program requires two other files which are in the ''gen'' directory as well: ''2vp70_ff1704_flytime.csv'' and ''trace_timing.txt''
The program seems reasonably sane.
The total delay for an interconnect is the sum of:
- **setup time**: Fixed at 0.84ns, seems to be from V2P datasheet Table 32: Setup and Hold times with Respect to Clock at IOB Input Register. Pad, no delay, T_IOPICK
- **clock to data**: Fixed at 1.67ns, seems to be from V2P datasheet Table 34: Sequential Delays Clock CLK to valid data on Pad (synchronous) T_IOCKON. Comments state it's T_IOCKP
- **pad to register**: Fixed at 0.84ns, seems to be from V2P datasheet Table 32: Propagation Delays Pad to I output, no delay T_IOPI
- **Pad to Trace**: Extracted from ''2vp70_ff1704_flytime.csv''
- **Trace length**: Extracted from ''trace_timing.txt''
- **Trace to Pad**: Extracted from ''2vp70_ff1704_flytime.csv''

The program uses a total of 4 possible clock phases: -clk270, clk, clk90, clk180, clk270. If these clock phases are indexed from -1 for -clk270 to 3 for clk270, the program calculates a "quality factor" as follows:
Q = (T_cycle*(1+i/4) - T_total) / T_eye
where T_cycle is the cycle time (1/CLK), T_total is the total delay as calculated above, i is the clock phase index, and T_eye = T_cycle if DDR is disabled, otherwise, T_cycle/2
This quality factor should be 0.5 ideally, and a value of 0 means the data will just barely be sampled and a value of 1 means the data came too late. 

The output VHDL files start with a table which lists all the requested IO pins, the Pad to Trace, Trace Length, and Trace to Pad measurements, and the quality factors for each possible clock phase. Finally, the clock phase with the best quality factor is chosen and listed along with the difference between the quality factor and the ideal quality of 0.5. This number indicates the sample time error as a fraction of the valid data window.

### Table of Delays @ 200 MHz##
Calculated using gen_chip2chip.pl. USER FPGA links tested as indicated in next section.

| FPGA A | FPGA B | IO Range | Clk Phase |
|--------|--------|----------|-----------|
| CTRL | USR1 | 0:39 | 270 |
| CTRL | USR1 | 40:63 | 180 |
| CTRL | USR2 | 0:39 | 270 |
| CTRL | USR2 | 40:63 | 180 |
| CTRL | USR3 | 0:39 | 180 |
| CTRL | USR3 | 40:63 | 270 |
| CTRL | USR4 | 0:39 | 180 |
| CTRL | USR4 | 40:63 | 270 |
| USR1 | USR2 | 0:137 | 180 |
| USR2 | USR3 | 0:137 | 270 |
| USR3 | USR4 | 0:137 | 180 |
| USR4 | USR1 | 0:137 | 270 |

### Reliability ###
On my BEE2 I implemented a design with LFSRs driving the "RIGHTLINK" ports and compared the result recieved on "LEFTLINK" to another synchronized LFSR and found that I had accumulated no errors in 48 hours of continuous running using the delays specified in this table at 200 MHz. The models used for this test are [here](https://casper.ssl.berkeley.edu/svn/trunk/caltech/designs/bee2interchiptests/)