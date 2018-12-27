## People

[Andrew Siemion](User:siemion "wikilink")

The pocket spectrometer is a PFB based spectrometer that runs on a
single IBOB.

## Making a pocket spectrometer

How to make your own Pocket Spectrometer:

  - Get the MSSGE Tools (including the libraries):
    <http://bee2.eecs.berkeley.edu/wiki/MssgeFaq.html>
  - Download
    [pocketspec\_v307d.mdl](http://casper.berkeley.edu/projects/pocketspec/pocketspec_v307d.mdl)
    (forgive my naming convention) and the three files it references:
    [pocketspec\_library.mdl](http://casper.berkeley.edu/projects/pocketspec/pocketspec_library.mdl),
    [vacc\_mask.m](http://casper.berkeley.edu/projects/pocketspec/vacc_mask.m)
    and
    [acc\_core\_mask.m](http://casper.berkeley.edu/projects/pocketspec/acc_core_mask.m).
    Make sure these files are in the same directory as
    pocketspec\_v307d.mdl.
  - Compile pocketspec\_v307d.mdl using bee\_xps. This step may take a
    matter of hours. Keep in mind that the more channels your
    spectrometer has (which is a parameter in the pocketspec design),
    the longer it takes to compile.
  - Note that the compile created a project directory with the same name
    as the project name: pocketspec\_v307d/
  - Copy the source files from here:
    [src.tar.gz](http://casper.berkeley.edu/projects/pocketspec/src.tar.gz)
    into pocketspec\_v307d/src/
  - Run a software compile - this should only take a minute or two. You
    can do this by selecting "Software Only" from the dropdown menu in
    bee\_xps. Be careful: if you accidentally check any of the boxes
    that aren't necessary for the software compile, you may have to sit
    through the entire thing again.
  - Download pocketspec's backend software,
    [walletmac.tar.gz](http://casper.berkeley.edu/projects/pocketspec/walletmac.tar.gz).
    Installation instructions are included. Once installed, run
    pocketplot with no flags (or -h) for instructions on use. If you
    have include LWIP in your pocketspec design, use [this
    version](http://casper.berkeley.edu/projects/pocketspec/walletmac_tcpip.tar.gz)

## Pocket Spec Graphics

  

Image:tN63tOhb\_adc.png|adc.png
Image:tN63tOhb\_histogram.png|histogram.png
Image:tN63tOhb\_pocketspec-2.png|pocketspec-2.png
Image:tN63tOhb\_tvg.png|tvg.png
