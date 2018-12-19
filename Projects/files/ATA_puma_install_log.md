# ATA PuMa NodeInstLog
Installed on pulsar-1:

## MACHINE
```
server=supermicro 6015V-T/TLP
  http://www.supermicro.com/products/system/1U/6015/SYS-6015V-TLP.cfm
motherboard = sudo dmidecode | more # =X7DVL-E
  http://www.supermicro.com/products/motherboard/Xeon1333/5000V/X7DVL-E.cfm
Re 10GE
 chip set like http://www.myri.com/scs/performance/PCIe_motherboards/results.driver-1_1_0/X7DB8.html
 but PCI-E x8 in middle. no riser. There is only a PCI-X riser
  http://www.compsource.com/pn/CSERR1UEL/Supermicro_428
  x8 ribbon riser a la http://www.plinkusa.net/webR1PCI-E1-1R.htm not easy to find
```

## SETUP
```
Modified firewall to allow external access:
Edit /etc/sysconfig/SuSEfirewall2 and add ssh to allowed services (from examples)
Start firewall:
>SuSEfirewall2 start
```

## PACKAGES
```
grace, emacs, locate, kdebase, gfortran, gv, through yast2
removed beagle* (was 100% CPU)
installed gulp from source at http://staff.washington.edu/corey/gulp/
added repo: ftp.gwdg.de/pub/linux/misc/suser-guru/rpm/10.2/RPMS/x86_64/
for libpcap-0.9.7, pbzip2
```

## FFTW3
```
remove package and included source install to optimise for CPUs
wget "http://www.fftw.org/fftw-3.1.2.tar.gz"
./configure --prefix=/usr ; make ; make install
./configure --prefix=/usr --enable-float --enable-sse ; make ; make install
(using /usr to make sure to stay in same place as earlier package)
(not sure if you actually need to run _both_ cmds to get double + float versions)
```

## PGPLOT
```
wget "ftp://ftp.astro.caltech.edu/pub/pgplot/pgplot5.2.tar.gz"
tar -zxvf pgplot5.2.tar.gz
cd  /usr/local/src/pgplot/
more aaaread.me 
more install-unix.txt
mkdir /usr/local/include/pgplot//
cd /usr/local/include/pgplot/
> read http://www.lorene.obspm.fr/pgplot_quick.txt (for gfortran)

perl -pi~ -e 's/  GIDRIV/\! GIDRIV/g;' drivers.list
/usr/local/src/pgplot/makemake /usr/local/src/pgplot linux g77_gcc

perl -pi~ -e 's/FFLAGC=-u -Wall -fPIC -O/FFLAGC=-ffixed-form -ffixed-line-length-none -u -Wall -fPIC -O/g;; s/=g77/=gfortran/; s#pndriv.o : ./png.h ./pngconf.h ./zlib.h ./zconf.h#pndriv.o : #;' makefile

make
make cpg

cd /usr/local/lib
ln -s /usr/local/include/pgplot/libpgplot.a libpgplot.a
ln -s /usr/local/include/pgplot/libcpgplot.a libcpgplot.a
cp /usr/local/include/pgplot/libpgplot.so .
ln -s /usr/local/include/pgplot/cpgplot.h /usr/local/include/cpgplot.h
/sbin/ldconfig -v	

cd /etc/profile.d/
scp -pr root@oak.phas.ubc.ca://etc/profile.d/custom\* .
edit for local setup.
```

## TEMPO
```
scp-ed from oak.phas.ubc.ca
scp-ed bigendian.f from flytrap (my custum gfortran version)
src/Makefile -> FC = gfortran -ffixed-line-length-none
```

## SIGPROC
```
cd /usr/local/src/
wget "http://prdownloads.sourceforge.net/sigproc/sigproc-3.7.tar.gz?download"
 
change makefile.linux to 
FC = gfortran  -ffixed-line-length-none
LFFTW = -L/usr/lib64 -lfftw3 -lfftw3f

scp-ed help.c filterbank-ata-02.c swap_bytes.c makefile

having some strange issues. perhaps the 64-bit architecture playing up
getenv("OSTYPE") returns an int, not a (char *)
Installed valguard (but to no use)
 wget "http://www.valgrind.org/downloads/valgrind-3.3.0.tar.bz2"
Changed swap_bytes.c to include at line 177
  #include <stdlib.h>
  int little_endian() /*includefile*/
```