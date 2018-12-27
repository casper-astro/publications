## Starting the ROACH2's

    Commands to be typed are shown after "$ " and the representative output is shown after it.
    
    # Program the "frb1" ROACH2 with the s6 gateware design
    $ adc16_init.rb --demux=4 --gain=2 frb1 s6_195_MHz
    Connecting to frb1...
    Programming frb1 with s6_195_MHz...
    Design built for ROACH2 rev2 with 8 ADCs (ZDOK rev2)
    Gateware supports demux modes (using demux by 4)
    For demux by 4, will point all channels to input 2
    Will set ADC register 0x31 to 0x0001
    Will set ADC register 0x3a to 0x0404
    Will set ADC register 0x3b to 0x0404
    Resetting ADC, setting registers, power cycling ADC, and reprogramming FPGA...
    ZDOK0 clock OK, ZDOK1 clock OK
    Calibrating SERDES blocks...ABCDEFGH
    SERDES calibration successful.
    Selecting analog inputs...
    Setting digital gain to 2...
    Setting demux by 4 mode...
    Done!
    
    # Program the "frb2" ROACH2 with the s6 gateware design
    $ adc16_init.rb --demux=4 --gain=2 frb2 s6_195_MHz
    Connecting to frb2...
    Programming frb2 with s6_195_MHz...
    Design built for ROACH2 rev2 with 8 ADCs (ZDOK rev2)
    Gateware supports demux modes (using demux by 4)
    For demux by 4, will point all channels to input 2
    Will set ADC register 0x31 to 0x0001
    Will set ADC register 0x3a to 0x0404
    Will set ADC register 0x3b to 0x0404
    Resetting ADC, setting registers, power cycling ADC, and reprogramming FPGA...
    ZDOK0 clock OK, ZDOK1 clock OK
    Calibrating SERDES blocks...ABCDEFGH
    SERDES calibration successful.
    Selecting analog inputs...
    Setting digital gain to 2...
    Setting demux by 4 mode...
    Done!
    
    # Initialize the S6 registers in the now programmed frb1 and frb2 ROACH2s:
    $ s6_init.rb --gain=300 --schan=0 --nchan=160 frb1 frb2
    initializing frb1 with SIDs 0 to 3
    initializing frb2 with SIDs 4 to 7
    connecting to frb1
    frb1 s6 app/lib revision 9d1b557/01ff4b5
    connecting to frb2
    frb2 s6 app/lib revision 9d1b557/01ff4b5
    disabling network transmission
    setting frb1 SIDs to 0..3
    setting frb2 SIDs to 4..7
    setting fftshift to 0
    setting gain to 300/1
    setting schan to 0
    setting nchan to 160
    setting 10 GbE destination IPs
    configuring 10 GbE interfaces
    arming sync generator(s)
    storing sync time in redis on redishost
    seeding noise generators
    arming noise generator(s)
    resetting 10 GbE network interfaces
    enable 10 GbE transmission
    all done
    
    The adc16_init.rb command lines will change slightly as new versions of the gateware are built
    (i.e. the "s6_195_MHz" name will change).  The s6_init.rb command lines shown are functionally
    correct, but the actual values to use for "gain" and "schan" and "nchan" are TBD.
    
    If you want to see the current status of the s6 gateware, you can use the s6_ifconfig.rb script
    (which might get renamed at some point to s6_status.rb):
    
    $ s6_ifconfig.rb frb2 
    frb2:ip_dest_N
        0 : 10.10.10.2
        1 : 10.10.10.4
        2 : 10.10.10.12
        3 : 10.10.10.14
        4 : 10.10.10.22
        5 : 10.10.10.24
        6 : 10.10.10.32
        7 : 10.10.10.34
    frb2:eth0  MAC 02:02:0a:0a:0a:cc  IP 10.10.10.204
        Counter reset  : off
        10 GbE reset   : off
        Transmit enable: ON
        Transmit oflows: 0
        Receive oruns  : 0
        Receive bframes: 0
    frb2:eth1  MAC 02:02:0a:0a:0a:cd  IP 10.10.10.205
        Counter reset  : off
        10 GbE reset   : off
        Transmit enable: ON
        Transmit oflows: 0
        Receive oruns  : 0
        Receive bframes: 0
    frb2:eth2  MAC 02:02:0a:0a:0a:ce  IP 10.10.10.206
        Counter reset  : off
        10 GbE reset   : off
        Transmit enable: ON
        Transmit oflows: 0
        Receive oruns  : 0
        Receive bframes: 0
    frb2:eth3  MAC 02:02:0a:0a:0a:cf  IP 10.10.10.207
        Counter reset  : off
        10 GbE reset   : off
        Transmit enable: off
        Transmit oflows: 0
        Receive oruns  : 0
        Receive bframes: 0

## Programming the Valon Synthesizers

The valon box contains 2 synthesizers, 'A' and 'B'. The valon is
connected to the s6 head node via USB, thus the following commands are
issued on the head node.

To set the synthesizer A to, for example, 790MHz :

` $ valon -a 790`  
` INFO:    Synth A set to 790.0`  
` INFO:    Frequencies written to non-volatile memory`  
` INFO:    All flags handled. Exiting successfully.`

To see the frequency setting of both synthesizers:

` $ valon`  
` Synth A: 790.0 MHz`  
` Synth B: 896.0 MHz`

## Output File Format

Output files will follow the [FITS
standard](http://fits.gsfc.nasa.gov/fits_home.html) along with any
needed keyword additions. This format is dubbed ETFITS.

The header data units (HDUs) are arrayed as follows:

The primary header contains items that will remain constant throughout a
given file. This includes things like receiver name, telescope location,
and constants needed to resolve pointing coordinates.

At each integration (time slice) there will be an metadata header
followed by a number of ETHITS HDUs.

The metadata header contains items that change throughout the file. This
includes things like oscillator settings and other engineering data. The
metadata header also includes items that normally do not (or should not)
change during a file but for which we need to know when exactly a change
does occur. This includes the system clock and birdie frequencies. The
metadata headers differ considerably (and are named differently) between
observatories (see the Arecibo and Green Bank templates below). The
Arecibo metadata header is called AOSCRAM and the Green Bank metadata
header is call GBTSTATUS. The metadata header has no data portion.

Immediately following a metadata header is the first of several ETHITS
HDUs. A small ETHITS header is followed by a variable length binary
table containing the actual hits. The ETHITS header contains information
concerning the hits in the data portion. This information includes time,
sky coordinates, and an indication of which subset of data is contained
in this HDU.

For Arecibo, data subsets are determined by beam and polarization. Thus
for ALFA there are 7 beams x 2 pols = 14 ETHITS HDUs per integration.
For single pixel dual pol receivers (eg the 327MHz receiver), there are
two useful ETHITS HDUs (beampols 0 and 1) with the remaining beampol
delineated HDUs containing unspecified data.

For Green Bank, data subsets are determined by subspectra and
polarization. There are eight subspectra and two pols, thus 16 ETHITS
HDUs per integration.

The data portion format of an ETHITS HDU is identical across Arecibo and
Green Bank. See the definition in the templates, below.

## Output File Template : Arecibo

    ##################################################################
    # FITS Primary Header Block
    ##################################################################
    #
    SIMPLE  =                    T  / file does conform to FITS standard
    BITPIX  =                    8  / number of bits per data pixel
    NAXIS   =                    0  / number of data axes
    EXTEND  =                    T  / FITS dataset may contain extensions
    BLOCKED =                    T  / Blocks of 2880 bytes
    ORIGIN  ='SERENDIP VI'          / File was created by the guppi_daq sw
    DATE    =                    *  / Date (dd/mm//yy) this file was written
    #
    ### Core ETFITS header fields ###
    #
    HDRVER  = 1.0                   / Header version
    S6HPCVER= '0.7.2'               / version of serendip6.so
    LBGPUVER= '0.7.2'               / version of libS6GPU.so
    HASHPVER= '0.1.0'               / version of hashpipe lib/app
    FPGAVER = '0.1.0'               / version of FPGA code
    TELESCOP=                    *  / Telescope name
    DATE-OBS=                    *  / Date of observation (YYYY-MM-DDThh:mm:ss UTC)
    TSYS    =                    *  / System temperature
    PROJID  =                    *  / Project name
    FRONTEND=                    *  /   Rx and feed ID
    OBSFREQ =                    *  / [MHz] Centre frequency for observation
    SITELONG= -66.7552222           / Antenna longitude (degrees, float)
    SITELAT = 18.3538056            / Antenna latitude (degrees, float)
    SITEELEV= 497                   / Antenna elevation (metres, float)
    EQUINOX = 2000.0                / Equinox of coords (e.g. 2000.0)
    FITSTYPE= 'ETFITS'              / FITS definition for pulsar data files
    INSTRUME= 'SERENDIP VI'         / Backend ID
    COORD_MD= 'J2000'               / Coordinate mode (J2000, GAL, ECLIP, etc.)
    NINPUTS =                    *  / Number of beampols
    BANDWID =                    *  / Bandwidth of entire backend
    FREQRES =                    *  / Width of each original spectral channel
    NSUBBAND=                    *  / number of subbands
    NCHAN   =                    *  / Number of spectral bins per sub-band
    CHAN_BW =                    *  / bandwidth of each spectral bin (resolution)
    
    #
    ### multibeam pointing calcualtion fields ###
    #
    # per beam pointing ellipse zenith angle offsets
    ZELLIPS0=   0.0                 / (TDOUBLE)
    ZELLIPS1= 384.005               / (TDOUBLE)
    ZELLIPS2= 384.005               / (TDOUBLE)
    ZELLIPS3= 384.005               / (TDOUBLE)
    ZELLIPS4= 384.005               / (TDOUBLE)
    ZELLIPS5= 384.005               / (TDOUBLE)
    ZELLIPS6= 384.005               / (TDOUBLE)
    # per beam pointing ellipse asimuth offsets
    AELLIPS0=   0.0                 / (TDOUBLE)
    AELLIPS1= 329.06                / (TDOUBLE)
    AELLIPS2= 329.06                / (TDOUBLE)
    AELLIPS3= 329.06                / (TDOUBLE)
    AELLIPS4= 329.06                / (TDOUBLE)
    AELLIPS5= 329.06                / (TDOUBLE)
    AELLIPS6= 329.06                / (TDOUBLE)
    # per beam pointing ellipse array angle offsets
    ARRANGL0=    0.0                / (TDOUBLE)
    ARRANGL1=  120.0                / (TDOUBLE)
    ARRANGL2=  180.0                / (TDOUBLE)
    ARRANGL3= -120.0                / (TDOUBLE)
    ARRANGL4=  -60.0                / (TDOUBLE)
    ARRANGL5=    0.0                / (TDOUBLE)
    ARRANGL6=   60.0                / (TDOUBLE)
    END
    ##################################################################
    # ETFITS Binary Table Header Block - 1 per integration - no data
    ##################################################################
    ### Mandatory ETFITS header fields ###
    #
    XTENSION= BINTABLE              / FITS binary table
    BITPIX  =                    8  / Binary data
    NAXIS   =                    2  / 2-dimensional binary table
    NAXIS1  =                    *  / width of table in bytes
    NAXIS2  =                    *  / Number of rows in table
    PCOUNT  =                    0  / size of special data area
    GCOUNT  =                    1  / one data group (required keyword)
    TFIELDS =                    *  / Number of fields per row
    EXTNAME = 'AOSCRAM'             / name of this binary table extension
    NMATRIX =                    1  / 1 dataset per row
    #
    COARCHID=                    *  / coarse channel ID
    #
    ### PNT SCRAM fields ###
    PNTSTIME=                    *  / unix time of this PNT data (TINT)
    PNTRA   =                    *  / latest requested pointing (TDOUBLE)
    PNTDEC  =                    *  / latest requested pointing (TDOUBLE)
    PNTMJD  =                    *  / (TDOUBLE)
    PNTAZCOR=                    *  / center beam azimuth correction (TDOUBLE)
    PNTZACOR=                    *  / center beam zenith angle correction (TDOUBLE)
    ### AGC SCRAM fields ###
    AGCSTIME=                    *  / unix time of this AGC data (TINT)
    AGCTIME =                    *  / millisec past local midnight.  A time stamp for Az/Za (TINT)
    AGCAZ   =                    *  / uncorrected Az as of AGCTIME (TDOUBLE)
    AGCZA   =                    *  / uncorrected ZA as of AGCTIME (TDOUBLE)
    AGCLST  =                    *  / (TDOUBLE)
    ### ALFA SHMEM SCRAM fields ###
    ALFSTIME=                    *  / unix time of this ALFA SHMEM data (TINT)
    ALFBIAS1=                    *  / AlfaFirstBias bitmap   (TINT)
    ALFBIAS2=                    *  / AlfaSecondBias bitmap  (TINT)
    ALFMOPOS=                    *  / AlfaMotorPosition      (TDOUBLE)
    ### IF1 SCRAM fields ###
    IF1STIME=                    *  / unix time of this IF1 data  (TINT)
    IF1SYNHZ=                    *  / synI_freqHz_0 (LO, right?)          (TDOUBLE)
    IF1SYNDB=                    *  / synI_ampDB_0           (TINT)
    IF1RFFRQ=                    *  / rfFreq                 (TDOUBLE)
    IF1IFFRQ=                    *  / if1FrqMhz              (TDOUBLE)
    IF1ALFFB=                    *  / alfaFb                 (TINT)
    ### IF2 SCRAM fields ###
    IF2STIME=                    *  / unix time of this IF2 data  (TINT)
    IF2ALFON=                    *  / useAlfa 1 = ALFA is on (TINT)
    IF2SYNHZ=                    *  / synI_freqHz_0 (LO, right?)          (TDOUBLE)
    IF2SIGSR=                    *  / signal source 0=gr,1=ch,2=noise     (TINT)
    ### TT SCRAM fields ###
    TTSTIME =                    *  / unix time of this TT data   (TINT)
    TTTURENC=                    *  / TurretEncoder               (TINT)
    TTTURDEG=                    *  / TurretDegrees          (TDOUBLE)
    ### Sample clock synth fields ###
    CLOCKTIM=                    *  / unix time of this clock data (TINT)
    CLOCKFRQ=                    *  / clock frequency - the sample rate of the instrument (TDOUBLE)
    CLOCKDBM=                    *  / clock power level in dBm (TDOUBLE)
    CLOCKLOC=                    *  / 1 = synth is locked, 0 = synth is not locked (TINT)
    ### Birdie frequency synth fields ###
    BIRDITIM=                    *  / unix time of this birdie data (TINT)
    BIRDIFRQ=                    *  / birdie frequency (TDOUBLE)
    BIRDIDBM=                    *  / birdie power level in dBm (TDOUBLE)
    BIRDILOC=                    *  / 1 = synth is locked, 0 = synth is not locked (TINT)
    ### ADC RMS Values ###
    ADCRMSTM=                    *  / unix time of this ADC data (TINT)
    ADCRMS01=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS02=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS03=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS04=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS05=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS06=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS07=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS08=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS09=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS10=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS11=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS12=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS13=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS14=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS15=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    ADCRMS16=                    *  / a value of -1 indicates a NaN return from the ADC (TDOUBLE)
    #
    END
    ##################################################################
    # ETFITS Coarse Channel Powers Binary Table Header Block - 1 per per integration
    ##################################################################
    #
    ### Mandatory ETFITS header fields ###
    #
    XTENSION= BINTABLE             / FITS binary table
    BITPIX  =                    8  / Binary data
    NAXIS   =                    2 / 2-dimensional binary table
    NAXIS1  =                    * / width of table in bytes
    NAXIS2  =                    * / Number of rows in table
    PCOUNT  =                    0 / size of special data area
    GCOUNT  =                    1 / one data group (required keyword)
    TFIELDS =                    * / Number of fields per row
    EXTNAME = 'CCPWRS'             / name of this binary table extension
    NMATRIX =                    1 / 1 dataset per row
    #
    ### ETFITS hits metadata ###
    #
    TIME    =                    * / unix time of this integration - is this fine enough res? (TINT)
    RA      =                    * / derived from corrected scram azza (TDOUBLE)
    DEC     =                    * / derived from corrected scram azza (TDOUBLE)
    #
    END
    ##################################################################
    # Data table rows
    #####################################################################
    #
    ### ETFITS coarse channel power columns ###
    #
    TTYPE#  = 'POLX    '           / coarse channel powers for X polarization
    TFORM#  = '1E      '           / 4-byte real
    TTYPE#  = 'POLY    '           / coarse channel powers for Y polarization
    TFORM#  = '1E      '           / 4-byte real
    #
    END
    ##################################################################
    # ETFITS Binary Table Header Block - 1 per beam/pol per integration
    ##################################################################
    #
    ### Mandatory ETFITS header fields ###
    #
    XTENSION= BINTABLE             / FITS binary table
    BITPIX  =                    8 / Binary data
    NAXIS   =                    2 / 2-dimensional binary table
    NAXIS1  =                    * / width of table in bytes
    NAXIS2  =                    * / Number of rows in table
    PCOUNT  =                    0 / size of special data area
    GCOUNT  =                    1 / one data group (required keyword)
    TFIELDS =                    * / Number of fields per row
    EXTNAME = 'ETHITS'             / name of this binary table extension
    NMATRIX =                    1 / 1 dataset per row
    #
    ### ETFITS hits metadata ###
    #
    TIME    =                    * / unix time of this integration - is this fine enough res? (TINT)
    RA      =                    * / derived from corrected scram azza (TDOUBLE)
    DEC     =                    * / derived from corrected scram azza (TDOUBLE)
    BORSPOL =                    * / 0-13 beam/pols or 0-15 spectra/pols  (TINT)
    NHITS   =                    * / (TINT)
    MISSEDPK=                    * / missed packets this beam/pol this integration (TINT)
    #
    END
    ##################################################################
    # Data table columns
    #####################################################################
    #
    ### ETFITS hits columns ###
    #
    TTYPE#  = 'DETPOW  '           / detected power in units of mean power
    TFORM#  = '1E      '           / 4-byte real
    TTYPE#  = 'MEANPOW '           / mean power
    TFORM#  = '1E      '           / 4-byte real
    TTYPE#  = 'COARCHAN'           / coarse channel bin number
    TFORM#  = '1I      '           / 16-bit integer
    TTYPE#  = 'FINECHAN'           / fine channel bin number
    TFORM#  = '1J      '           / 32-bit integer
    #
    END

## Output File Template : Green Bank Telescope

    ##################################################################
    # FITS Primary Header Block
    ##################################################################
    #
    SIMPLE  =                    T  / file does conform to FITS standard
    BITPIX  =                    8  / number of bits per data pixel
    NAXIS   =                    0  / number of data axes
    EXTEND  =                    T  / FITS dataset may contain extensions
    BLOCKED =                    T  / Blocks of 2880 bytes
    ORIGIN  ='SERENDIP VI'          / File was created by the guppi_daq sw
    DATE    =                    *  / Date (dd/mm//yy) this file was written
    #
    ### Core ETFITS header fields ###
    #
    HDRVER  = 1.0                   / Header version 
    S6HPCVER= '0.7.2'               / version of serendip6.so
    LBGPUVER= '0.7.2'               / version of libS6GPU.so
    HASHPVER= '0.1.0'               / version of hashpipe lib/app
    FPGAVER = '0.1.0'               / version of FPGA code
    TELESCOP=                    *  / Telescope name
    DATE-OBS=                    *  / Date of observation (YYYY-MM-DDThh:mm:ss UTC)
    TSYS    =                    *  / System temperature
    PROJID  =                    *  / Project name
    FRONTEND=                    *  /   Rx and feed ID
    OBSFREQ =                    *  / [MHz] Centre frequency for observation
    SITELONG= 79.839835             / Antenna longitude (degrees, float)
    SITELAT = 38.433121             / Antenna latitude (degrees, float)
    SITEELEV= 807.43                / Antenna elevation (metres, float)
    EQUINOX = 2000.0                / Equinox of coords (e.g. 2000.0) 
    FITSTYPE= 'ETFITS'              / FITS definition for pulsar data files
    INSTRUME= 'SERENDIP VI'         / Backend ID
    COORD_MD= 'J2000'               / Coordinate mode (J2000, GAL, ECLIP, etc.)
    NINPUTS =                    *  / Number of pols * number of subbands
    BANDWID =                    *  / Bandwidth of entire backend
    FREQRES =                    *  / Width of each original spectral channel
    NSUBBAND=                    *  / number of subbands
    NCHAN   =                    *  / Number of spectral bins per sub-band
    CHAN_BW =                    *  / bandwidth of each spectral bin (resolution)
    #
    END
    ##################################################################
    # ETFITS Binary Table Header Block - 1 per integration - no data
    ##################################################################
    ### Mandatory ETFITS header fields ###
    #
    XTENSION= BINTABLE              / FITS binary table
    BITPIX  =                    8  / Binary data
    NAXIS   =                    2  / 2-dimensional binary table
    NAXIS1  =                    *  / width of table in bytes 
    NAXIS2  =                    *  / Number of rows in table
    PCOUNT  =                    0  / size of special data area
    GCOUNT  =                    1  / one data group (required keyword)
    TFIELDS =                    *  / Number of fields per row
    EXTNAME = 'GBTSTATUS'           / name of this binary table extension
    NMATRIX =                    1  / 1 dataset per row
    #
    COARCHID=                    *  / coarse channel ID
    #
    ### GBT_STATUS fields ###
    LASTUPDT=                    *  / time string when gbt_status was last updated (TSTRING)
    LST     =                    *  / local sidereal time HH:MM:SS (TSTRING)
    UTC     =                    *  / universal time HH:MM:SS (TSTRING)
    MJD     =                    *  / modified julian date (TDOUBLE)
    EPOCH   =                    *  / epoch (TSTRING)
    MAJTYPE =                    *  / major type (TSTRING)
    MINTYPE =                    *  / minor type (TSTRING)
    MAJOR   =                    *  / major (TSTRING)
    MINOR   =                    *  / minor (TSTRING)
    AZCOMM  =                    *  / az commanded (TDOUBLE)
    ELCOMM  =                    *  / el commanded (TDOUBLE)
    AZACTUAL=                    *  / az actual (TDOUBLE) (used in deriving ra/dec)
    ELACTUAL=                    *  / el actual (TDOUBLE)
    AZERROR =                    *  / az error (TDOUBLE)
    ELERROR =                    *  / el error (TDOUBLE)
    LPCS    =                    *  / lpcs (TSTRING)
    FOCUSOFF=                    *  / focus offset (TSTRING)
    ANTMOT  =                    *  / antenna motion (TSTRING)
    RECEIVER=                    *  / receiver (TSTRING)
    IFFRQ1ST=                    *  / first IF freq (TDOUBLE)
    IFFRQRST=                    *  / IF rest freq (TDOUBLE)
    DCRSCFRQ=                    *  / dcr_sky_center_freq (TDOUBLE)
    SPRCSFRQ=                    *  / spectral_processor_sky_freq (TDOUBLE)
    FREQ    =                    *  / frequency (TDOUBLE)
    VELFRAME=                    *  / velocity frame (TSTRING)
    VELDEF  =                    *  / velocity defintion (TSTRING)
    J2000MAJ=                    *  / J2000 major (TDOUBLE)
    J2000MIN=                    *  / J2000 minor (TDOUBLE)
    ### GBTstatus Derived fields ###
    LSTH_DRV=                    *  / local sidereal time in decimal hours (TDOUBLE)
    RA_DRV  =                    *  / RA in hours (taken from az/el actual, precessed to J2000)
    RADG_DRV=                    *  / RA in degrees (taken from az/el actual, precessed to J2000)
    DEC_DRV =                    *  / DEC in degrees (taken from az/el actual, precessed to J2000)
    ### Cleo fields ###
    CLEOREV =                    *  / Cleo server revision #
    ATMCRAJ2=                    *  / RA in degrees (as computed by cleo, precessed to J2000)
    ATMCDCJ2=                    *  / DEC in degrees (as computed by cleo, precessed to J2000)
    IFV1CSFQ=                    *  / server-derived center freq in MHz
    IFV1BW  =                    *  / MHz - estimate of useful BW
    IFV1LVL =                    *  / (unreliable) system set to low of high intensity noise diode
    IFV1IFFQ=                    *  / IF freq corresponding to CorrectedSkyFrequency (MHz)
    IFV1SSB =                    *  / lower/upper - if upper sky freqs increase as IF freqs increase
    IFV1SKFQ=                    *  / sky freq at IF in MHz at start of obs, not correct during a scan if doppler tracking
    IFV2CSFQ=                    *  / server-derived center freq in MHz
    IFV2BW  =                    *  / MHz - estimate of useful BW
    IFV2LVL =                    *  / (unreliable) system set to low of high intensity noise diode
    IFV2IFFQ=                    *  / IF freq corresponding to CorrectedSkyFrequency (MHz)
    IFV2SSB =                    *  / lower/upper - if upper sky freqs increase as IF freqs increase
    IFV2SKFQ=                    *  / sky freq at IF in MHz at start of obs, not correct during a scan if doppler tracking
    LO1APSFQ=                    *  / Hz, used to determine Doppler tracking altering center sky freq
    LO1BPSFQ=                    *  / Hz, used to determine Doppler tracking altering center sky freq
    VEGSFBW1=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW2=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW3=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW4=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW5=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW6=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW7=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSFBW8=                    *  / analog filger BW (MHz) just in front of VEGAS inputs
    VEGSSBAM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank A
    VEGSSBBM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank B
    VEGSSBCM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank C
    VEGSSBDM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank D
    VEGSSBEM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank E
    VEGSSBFM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank F
    VEGSSBGM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank G
    VEGSSBHM=                    *  / if == 1 and ScanCoordinator == "Running" then observer collecting data with bank H
    BAMMPWR1=                    *  / power levels in (dBn) of VEGAS samplers (polarization 1)
    BAMMPWR2=                    *  / power levels in (dBn) of VEGAS samplers (polarization 2)
    ### Cleo derived fields ###
    LCUDSECS=                    *  / seconds since last update of any cleo values from server
    ### Sample clock synth fields ###
    CLOCKTIM=                    *  / unix time of this clock data (TINT)  
    CLOCKFRQ=                    *  / clock frequency - the sample rate of the instrument (TDOUBLE)
    CLOCKDBM=                    *  / clock power level in dBm (TDOUBLE)
    CLOCKLOC=                    *  / 1 = synth is locked, 0 = synth is not locked (TINT)
    ### Birdie frequency synth fields ###
    BIRDITIM=                    *  / unix time of this birdie data (TINT)  
    BIRDIFRQ=                    *  / birdie frequency (TDOUBLE)
    BIRDIDBM=                    *  / birdie power level in dBm (TDOUBLE)
    BIRDILOC=                    *  / 1 = synth is locked, 0 = synth is not locked (TINT)
    ### ADC RMS Values ###
    # Not yet implemented
    #
    END
    
    ##################################################################
    # ETFITS Coarse Channel Powers Binary Table Header Block - 1 per per integration
    ##################################################################
    #
    ### Mandatory ETFITS header fields ###
    #
    XTENSION= BINTABLE             / FITS binary table
    BITPIX  =                    8  / Binary data
    NAXIS   =                    2 / 2-dimensional binary table
    NAXIS1  =                    * / width of table in bytes
    NAXIS2  =                    * / Number of rows in table
    PCOUNT  =                    0 / size of special data area
    GCOUNT  =                    1 / one data group (required keyword)
    TFIELDS =                    * / Number of fields per row
    EXTNAME = 'CCPWRS'             / name of this binary table extension
    NMATRIX =                    1 / 1 dataset per row
    #
    ### ETFITS hits metadata ###
    #
    TIME    =                    * / unix time of this integration - is this fine enough res? (TINT)
    RA      =                    * / derived from corrected scram azza (TDOUBLE)
    DEC     =                    * / derived from corrected scram azza (TDOUBLE)
    #
    END
    ##################################################################
    # Data table rows
    #####################################################################
    #
    ### ETFITS coarse channel power columns ###
    #
    TTYPE#  = 'POLX    '           / coarse channel powers for X polarization
    TFORM#  = '1E      '           / 4-byte real
    TTYPE#  = 'POLY    '           / coarse channel powers for Y polarization
    TFORM#  = '1E      '           / 4-byte real
    #
    END
    ##################################################################
    # ETFITS Binary Table Header Block - 1 per bors/pol per integration
    ##################################################################
    #
    ### Mandatory ETFITS header fields ###
    #
    XTENSION= BINTABLE             / FITS binary table
    BITPIX  =                    8 / Binary data
    NAXIS   =                    2 / 2-dimensional binary table
    NAXIS1  =                    * / width of table in bytes 
    NAXIS2  =                    * / Number of rows in table
    PCOUNT  =                    0 / size of special data area
    GCOUNT  =                    1 / one data group (required keyword)
    TFIELDS =                    * / Number of fields per row
    EXTNAME = 'ETHITS'             / name of this binary table extension
    NMATRIX =                    1 / 1 dataset per row
    #
    ### ETFITS hits metadata ###
    #
    TIME    =                    * / unix time of this integration - is this fine enough res? (TINT)
    RA      =                    * / derived from corrected scram azza (TDOUBLE)
    DEC     =                    * / derived from corrected scram azza (TDOUBLE)
    BORSPOL =                    * / 0-13 beam/pols or 0-15 spectra/pols  (TINT)
    NHITS   =                    * / (TINT)
    MISSEDPK=                    * / missed packets this beam/pol this integration (TINT)
    #
    END
    ##################################################################
    # Data table columns
    #####################################################################
    #
    ### ETFITS hits columns ###
    #
    TTYPE#  = 'DETPOW  '           / detected power in units of mean power
    TFORM#  = '1E      '           / 4-byte real 
    TTYPE#  = 'MEANPOW '           / mean power
    TFORM#  = '1E      '           / 4-byte real 
    TTYPE#  = 'COARCHAN'           / coarse channel bin number
    TFORM#  = '1I      '           / 16-bit integer
    TTYPE#  = 'FINECHAN'           / fine channel bin number
    TFORM#  = '1J      '           / 32-bit integer
    #
    END

## Block Diagram (and installation photographs)

  - [block diagram Rev. 3
    (pdf)](https://casper.berkeley.edu/wiki/images/5/58/S6alfaburst_blockdiagram_rev3.pdf)
  - [rack layout Rev. 0
    (jpg)](https://casper.berkeley.edu/wiki/images/2/2e/S6alfaburst_rack_diagram_0.jpg)
  - [photos of Arecibo installation as of 2014feb28
    (pdf)](https://casper.berkeley.edu/wiki/images/2/20/S6_Arecibo_photos.pdf)

## IF Splitter / Beam Selector

  - [block diagram
    (pdf)](https://casper.berkeley.edu/wiki/images/3/34/S6_beamsplitter_block.pdf)
  - Vin input voltage +9 to +12 VDC
  - Iin input current 1.43 Amps when Vin = +10 VDC.
      - The Iin input current will increase, like the IF signal gain,
        with increasing Vin.
  - The input power is supplied by a manually controlled Circuit
    Specialties CS11802x 0-18V, 0-2A lab PSU.
      - The CS11802x is powered off the network controlled power strip
        described below.
  - This chassis has a MC7805P +5VDC regulator which is used to supply
    the Vin for the Sample Clock generator discussed below.
  - datasheets
      - The data sheet for the Circuit Specialties CS11802x 0-18V, 0-2A
        lab PSU has not been found.
      - [MiniCircuits ZKL-1R5+ amplifier
        (pdf)](http://www.minicircuits.com/pdfs/ZKL-1R5+.pdf)
          - 10 to 1500 MHz. 40 dB typical gain. 36 dB minimum gain. 3 dB
            NF. VSWR \~ 1.5. output P1dB = +15 dBm. max input power +13
            dBm.
      - [MiniCircuits ZX10-2-12+ splitter
        (pdf)](http://www.minicircuits.com/pdfs/ZX10-2-12+.pdf)
          - 2 way 0 deg 2 to 1200 MHz IL .5 to 1.5 dB, phase unbalance 3
            deg, amp unbalance .5 dB Isolation 21 dB typ, 16 dB min
      - [1 Amp 5V regulator MC7805CP
        (pdf)](https://casper.berkeley.edu/wiki/images/4/4f/Motorola_MC7805CP.pdf)

<!-- end list -->

  -   - reverse input VDC protection diode
      - chassis

  - lab measurements
    
      - 2014feb16 all 16 paths were checked 1 circuit at a time.
      - Only channel 0 data is plotted because all the other 13
        channels, numbers 0..13, are functionally identical.
      - The second or spare un-amplified SMA outputs of channels 14 and
        15 were also test and match the primary corresponding primary
        BNC outputs.
      - [channel 0 S11
        (pdf)](https://casper.berkeley.edu/wiki/images/e/e9/S6_IF_splitter_S11.pdf)
      - [channel 0 passive output S21
        (pdf)](https://casper.berkeley.edu/wiki/images/3/39/S6_IF_splitter_passive_S21.pdf)
      - [channel 0 amplified output S21
        (pdf)](https://casper.berkeley.edu/wiki/images/2/24/S6_IF_splitter_amp_S21.pdf)

  - photos
    
      - [IF picture collection
        (pdf)](https://casper.berkeley.edu/wiki/images/3/31/S6_IP_splitter_pict.pdf)

## IF Mapping Table

  - [IF mapping table as of 2014feb23
    (pdf)](https://casper.berkeley.edu/wiki/images/e/e3/SERENDIP6_IF_mapping.pdf)

## IF levels

dBm to rms counts

  - [dBm to ADC rms count table and notes
    (txt)](https://casper.berkeley.edu/wiki/images/0/0e/S6_dBm_to_rms.txt)
  - with ADC IC digital gain = 2, input 50-450 MHz noise, 700 MHz clock
    :
      - full scale noise = -2.5 dBm rms = 29.5
      - typical operating point : -8.5 dBm rms = 14.7
      - near the minimum linear level : -17.6 dBm rms = 5.2
  - TBD: table with full clock rate of 896 MHz.

Arecibo IF

  - [birdie test results
    (txt)](https://casper.berkeley.edu/wiki/images/7/7d/S6_birdie_testing.txt)
  - [raw notes of initial setting 2014feb26
    (txt)](https://casper.berkeley.edu/wiki/images/6/68/S6_IF_levels_testnotes.txt)
  - [day 1 partial IF level summary table
    (txt)](https://casper.berkeley.edu/wiki/images/d/d3/S6_IF_level_summary.txt)
  - [day 2 complete IF level summary table
    (txt)](https://casper.berkeley.edu/wiki/images/3/30/S6_IF_summary_table_day2.txt)
  - On the rack mounted shelf above the IF Splitter is a small bag with
    2 of each of 3 dB, 6 dB and 10 dB SMA attenuators should additional
    level tweaking be required.

Evans Hall Digital Lab IF

  - [Digital Lab IF setup and measurements
    (txt)](https://casper.berkeley.edu/wiki/images/3/36/S6_Dig_Lab_IF_setup.txt)

## Sample Clock

  - The sample clock is generated by a [Valon 5008
    synthesizer](http://www.valontechnology.com/5008.html) locked to the
    observatory 10 MHz reference.
      - The two programmable tones are generated by two on board [Analog
        Devices ADF4350
        (URL)](http://www.analog.com/en/rfif-components/pll-synthesizersvcos/adf4350/products/product.html)
        wideband synthesizers with integrated VCO components. The
        datasheet is [ADF4350
        (pdf)](http://www.analog.com/static/imported-files/data_sheets/ADF4350.pdf).
      - The synthesizers are programmed by an on board [TI MSP430
        (URL)](http://www.ti.com/lsds/ti/microcontrollers_16-bit_32-bit/msp/overview.page?DCMP=MCU_other&HQS=msp430)
        low power microcontroller. This implements a UART-SPI bridge.
  - The +5 VDC input power is supplied by the MC7805CP regulator mounted
    on the IF Splitter described above. The Valon synthesizer is powered
    on and off at the same times as the IF Splitter.
  - Channel 1 is programmed to be 700 MHz to ease initial FPGA design
    testing. The output level is +7 dBm.
  - Channel 2 is programmed to be 896 MHz to sample the full IF
    passband. The output level is +7 dBm.
  - New frequencies may be programmed via the USB cable connected to the
    back of the SERENDIP6 head node computer.
  - The output of the sample clock synthesizer feeds an Anzac DS-409-4
    10 to 2000 MHz 4 way 0 degree splitter.
  - Each of the 4 outputs of the splitter are about 0.5 dBm due to the
    6dB loss for 4 copies and 0.5 dB for insertion and cable losses.
  - The net clock input to the ADC16x250-8 rev2 boards will be about 0
    dBm due to losses in the various cables to deliver the signal from
    the synthesizer and within the Roach2 chassis and to ADC16x250-8
    rev2 boards.
  - [Sample clock harmonic measurements
    (pdf)](https://casper.berkeley.edu/wiki/images/6/60/SERENDIP6_sample_clocks.pdf)

## 1PPS distribution

  - In the Evans Hall Dig Lab
      - The 1PPS is 0 to 3.4V measured into a 50 ohm load to GND as
        supplied by the [16 way 1PPS
        driver](https://casper.berkeley.edu/wiki/16_way_1PPS_driver)
      - The active high pulse is about 20 to 25 usec wide
      - This has passed \~ weekend long lab test using 1 16 way 1PPS
        driver output and all 4 outputs loaded.
      - If a 3dB BNC attenuator was included on the input side the
        Roach2s did detect the pulse but the jitter was unacceptably
        high. We must cable the 16 way 1PPS driver directly into the 4
        way AC coupled split.
  - At Arecibo
      - The 1PPS reference is 0 to 2.8 V measured into a 50 ohm load to
        GND.
      - The active high pulse is about 20 to 25 usec wide
      - 4 copies of the 1PPS are generated using a [4 way AC coupled
        splitter
        (pdf)](https://casper.berkeley.edu/wiki/images/2/2a/1PPS_4way_passive_split.pdf).
      - At Arecibo only 3 of the 4 way AC coupled splitter outputs may
        be used to drive 50 ohm loads. The 4th input may be used to
        drive an high impedance oscilloscope input or something along
        those lines.
      - To monitor the received 1PPS, and other signals, each F chassis
        has a sync\_out SMA connector on the upper left hand corner of
        the back of the chassis. These outputs feed a SMA plug to BNC
        plug cable to a BNC-tee. One leg of the BNC-tee has a 50 ohm
        load. The other end is a plug connector which can be directly
        mated to an oscilloscope. A common measurement is to measure the
        time difference between the internal versions of the 1PPS signal
        from the two F Chassis to see if they are still synchronized.

## SERENDIP 6 Head Nodes

  - [computer block diagram
    (pdf)](https://casper.berkeley.edu/wiki/images/9/97/S6_headnode_block.pdf)
  - [BOM and serial number spreadsheet
    (pdf)](https://casper.berkeley.edu/wiki/images/b/b4/S6_headnodes_BOM_SN.pdf)
  - the above spreadsheet has the details of the following systems:
      - RAL Digital Lab, Berkeley, California
      - Arecibo, Puerto Rico
      - Green Bank, West Virginia (See the RAL Dig Lab unit above)

## SERENDIP 6 Compute Nodes

  - [computer block diagram
    (pdf)](https://casper.berkeley.edu/wiki/images/f/f0/S6_computenode_block.pdf)
  - [BOM and serial number spreadsheet
    (pdf)](https://casper.berkeley.edu/wiki/images/0/05/S6_computenodes_BOM_SN.pdf)
  - the above spreadsheet has the details of the following systems:
      - RAL Digital Lab, Berkeley, California
      - Arecibo, Puerto Rico

## ALFABURST Head Nodes

  - [computer block diagram
    (pdf)](https://casper.berkeley.edu/wiki/images/3/39/AB_headnode_block.pdf)
  - [BOM and serial number spreadsheet
    (pdf)](https://casper.berkeley.edu/wiki/images/c/c8/AB_headnodes_BOM_SN.pdf)
  - the above spreadsheet has the details of the following systems:
      - Arecibo, Puerto Rico

## ALFABURST Compute Nodes

  - [computer block diagram
    (pdf)](https://casper.berkeley.edu/wiki/images/c/c1/AB_computenode_block.pdf)
  - [BOM and serial number spreadsheet
    (pdf)](https://casper.berkeley.edu/wiki/images/d/dc/AB_compuenodes_BOM_SN.pdf)
  - the above spreadsheet has the details of the following systems:
      - Arecibo, Puerto Rico

## F Chassis

2 F Chassis are required. Each F Chassis has :

  - 1 of [Roach2
    Rev2](https://casper.berkeley.edu/wiki/ROACH-2_Revision_2)
  - 2 of [ADC16x250-8 coax rev 2 wired for 4
    inputs](https://casper.berkeley.edu/wiki/ADC16x250-8_coax_rev_2)
  - 2 of [SFP+ 10 Gbps Mezzanine
    card](https://casper.berkeley.edu/wiki/SFP%2B)
  - [photos
    (pdf)](https://casper.berkeley.edu/wiki/images/5/59/SERENDIP6_F_Chassis_photos.pdf)
  - The lids of the F Chassis are held in place with at most 1 or 2
    screws for easy access. Additional lid screws may be found in a
    small clear plastic bag on the rack mounted shelf just above the F
    Chassis.

## 1 Gbps Networking

[DLink DGS-1224T Hardware Rev
D1](http://support.dlink.com/ProductInfo.aspx?m=DGS-1224T)

  - [datasheet
    (pdf)](ftp://ftp2.dlink.com/PRODUCTS/DGS-1224T/REVD/DGS-1224T_REVD_DATASHEET_1.00_EN.PDF)
  - [install guide
    (pdf)](ftp://ftp2.dlink.com/PRODUCTS/DGS-1224T/REVD/DGS-1224T_REVD_QIG_1.01_EN.PDFcquick)
  - [user manual
    (pdf)](ftp://ftp2.dlink.com/PRODUCTS/DGS-1224T/REVD/DGS-1224T_REVD_MANUAL_3.10_EN.PDF)

## 10 Gbps Networking

[SFP+ cable mapping table
(pdf)](https://casper.berkeley.edu/wiki/images/6/65/S6_10Gbps_networking.pdf)

Primary SFP+ switch: Juniper EX4500-LB

  - [complete hardware guide
    (pdf)](https://www.juniper.net/techpubs/en_US/release-independent/junos/information-products/topic-collections/hardware/ex-series/ex4500/book-hw-ex4500.pdf)
  - [quick start guide
    (pdf)](https://www.juniper.net/techpubs/en_US/release-independent/junos/information-products/topic-collections/hardware/ex-series/ex4500/quick-start-ex4500.pdf)
  - warning lights
      - the front upper right corner red Alarm LED will be asserted and
        the LCD display will show "SPD ALARM 01" if the management port
        is not connected.
  - measured power consumption
      - idle with no SFP+ connections of any kind: 2.32 Amps, power
        factor = 0.98, 265 Watts

Alternative 24 port SFP+ switch: Dell
    8024F

  - [Dell 8024F](https://www.dell.com/us/business/p/powerconnect-8024f/pd)
  - [getting started guide
    (pdf)](ftp://ftp.dell.com/Manuals/all-products/esuprt_ser_stor_net/esuprt_powerconnect/powerconnect-8024f_setup%20guide_en-us.pdf)
  - [reference guide
    (pdf)](http://downloads.dell.com/Manuals/all-products/esuprt_ser_stor_net/esuprt_powerconnect/powerconnect-8024f_reference%20guide_en-us.pdf?c=us&l=en&cs=04&s=bsd)
  - [Users guide
    (pdf)](http://downloads.dell.com/Manuals/all-products/esuprt_ser_stor_net/esuprt_powerconnect/powerconnect-8024f_user%27s%20guide_en-us.pdf?c=us&l=en&cs=04&s=bsd)

SFP+ cables

  - FCI part number: 10110818-2030LF
      - Non Halogen Free
      - 3m
      - 30AWG
      - connectors (at both ends): 20 positions SFP
  - [datasheet
    (pdf)](http://download.siliconexpert.com/pdfs/2012/2/4/0/56/24/324/fci_/manual/10110818.pdf)
  - Vendor
        sites
      - [Digikey](http://www.digikey.com/product-search/en?x=0&y=0&lang=en&site=us&KeyWords=+10110818-2030LF)
      - [Arrow](http://components.arrow.com/part/detail/48968078S8458037N8314)

## Shipping

  - 2014feb07 - 2014feb18(scheduled) 2014feb22(actual) shipment
      - [shipping notes (revised Feb 23)
        (txt)](https://casper.berkeley.edu/wiki/images/a/ad/SERENDIP6_ship_2014feb07.txt)

## Components to be brought on flights to and from Arecibo

  - Flying to Arecibo 2014feb22
      - [checked cases
        (txt)](https://casper.berkeley.edu/wiki/images/5/58/S6_checkedbags_2014feb22.txt)
      - [hand carry list
        (txt)](https://casper.berkeley.edu/wiki/images/8/88/SERENDIP6_handcarry_2014feb07.txt)
  - Flying from Arecibo 2014mar01
      - [checked cases
        (txt)](https://casper.berkeley.edu/wiki/images/3/31/S6_checkedbags_2014feb28.txt)
      - [hand carry list
        (txt)](https://casper.berkeley.edu/wiki/images/0/0a/S6_handcarry_2014mar01.txt)

## VAC Power

  - UPS 1
      - VACin : circuit breaker phase 1
      - [APC SmartUPS 3000XL 2400 Watt, 3000
        Volt-Amps](http://www.apc.com/resource/include/techspec_index.cfm?base_sku=su3000rmxl3u)
      - power strip A (vertical mount back left of compute server rack)
          - SERENDIP6 head node aka asa10 aka s6h1
          - ALFABURST head node aka asa3 aka abh0
      - power strip B (vertical mount back left of the compute server
        rack)
          - SERENDIP6 compute node 0 aka s6c0
          - wire shelf mounted LCD monitor
      - Dlink DGS-1224t 1G switch
  - UPS 2
      - VACin : circuit breaker phase 2
      - [APC SmartUPS 3000XL 2400 Watt, 3000
        Volt-Amps](http://www.apc.com/resource/include/techspec_index.cfm?base_sku=su3000rmxl3u)
      - power strip C (vertical mount back right of the compute server
        rack)
          - SERENDIP6 compute node 1 aka s6c1
          - SERENDIP6 compute node 2 aka s6c2
      - power strip D (sitting on the bottom of the back side of the
        compute server rack)
          - [Tripp-Lite Isobar8 ultra 8 way 12 amp
            strip](http://www.tripplite.com/sku/ISOBAR8ULTRA/)
          - SERENDIP6 compute node 3 aka s6c3
          - wall wart for the SETI@Home LO Plate (front of the IF/F
            Chassis rack)
          - Rohde & Schwarz ZVL Network Analyzer for temporarily test
            use only. See test equipment section below.
  - UPS 3
      - VACin : circuit breaker phase 3
    
      - [APC SmartUPS 3000XL 2400 Watt, 3000
        Volt-Amps](http://www.apc.com/resource/include/techspec_index.cfm?base_sku=su3000rmxl3u)
    
      - 
      - WARNING \!\!\! the battery in this UPS has failed. Replacement
        will be installed ASAP.
    
      - This unit is effectively a power strip. Only.
    
      - 
      - power strip F (vertical mount below midway on back right of the
        compute server rack)
        
          - ALFABURST compute node 1 aka abc1
          - ALFABURST compute node 0 aka abc0
    
      - power strip G (vertical mount above midway on back right of the
        compute server rack)
        
          - ALFABURST compute node 2 aka abc2
    
      - wall wart for the 4 way AO network 1GbE switch
  - UPS 4
      - VACin : circuit breaker phase : TBD
      - VAC supply from quadplex outlet on the floor shown below
      - [APC BackupPro 1400 950 Watts, 1400
        Volt-Amps](http://www.apc.com/resource/include/techspec_index.cfm?base_sku=BP1400I)
          - small Sceptre white LCD screen - monitor for the Dell
            "SETI@HOME recorder" computer
          - [Masscool UHB-340U/PS external USB2/SATAI/II disk drive
            enclosure](http://www.masscool.com/product_detail.php?pid=180&id=75)
          - network controlled power strip Bus A (Bus B is not on UPS)
              - [Digital Loggers Inc EPRC2 network controlled power
                strip datasheet
                (pdf)](https://casper.berkeley.edu/wiki/images/d/df/S6_network_controlled_power_strip.pdf)
              - [power strip channel to load map
                (txt)](https://casper.berkeley.edu/wiki/images/a/aa/S6_power_strip_table.txt)
              - magic incantations to manage this power strip go here.
  - UPS 5
      - VACin : circuit breaker phase : TBD
      - [APC Back-UPS 500 300 Watt, 500
        Volt-Amps](http://www.apc.com/products/resource/include/techspec_index.cfm?base_sku=BK500&total_watts=200)
          - Centrecoom FS709FE 100MbE switch (with no used RJ45 ports)
  - 20 amp duplex outlet on the floor to the back right of the IF/F
    Chassis rack
      - VACin : circuit breaker phase : TBD
      - power strip E (sitting on the floor of the IF/F Chassis rack)
          - [Tripp-Lite Isobar4 4 way 12 amp
            strip](http://www.tripplite.com/sku/IBAR4/)
          - ALFABURST compute node 3 aka abc3
      - Juniper EX4500-LB 40 port 10 GbE SFP+ switch
  - 20? amp quadplex outlet on the floor underneath the wire mesh
    shelving unit
      - VACin : circuit breaker phase : TBD
      - UPS 4 as described above
      - UPS 5 as described above
      - power strip H (vertical mount back right of the IF/F Chassis
        rack)
          - Bus B of the network controlled power strip described above
            (in the UPS 4 section)
          - [PTS500 CW generator for
            SETI@Home](http://www.programmedtest.com/pts500.html)
          - SETI@Home Quadrature Downconverter

## Test Equipment

  - Arecibo Observatory
      - [R\&S ZVL network and spectrum analyzer
        (pdf)](http://cdn.rohde-schwarz.com/dl_downloads/dl_common_library/dl_manuals/gb_1/z/zvl_1/ZVL_Operating_008_V3_20.pdf)

## SCRAM Info

SCRAM packets are dumped to disk on the S6 head node, in
/data/serendip6/, with files named with Unix time timestamps. To view
one of these files, copy it elsewhere, uncompress it and run the
following command:

/usr/local/bin/s6\_observatory -nodb -stdout -infile <scramdump-file>

Every line should have an xxxSTIME, which is the Unix time when those
values were obtained from SCRAM (+/- a second or so). For SCRAM:DERIVED,
the field is DERTIME.
