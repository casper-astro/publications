# ATA PuMa FlyEye

Joeri's FlyEye ATA PuMa node log

## SIGPROC
```
Installed sigproc 3.7, killed a bug (cf. install page)
filterbank-ata-02 runs fast (
 30-min crab data dedispersed to 20 dm's 50-70, fg'd over 6 procs: 1m23
 tee'd over 20 processes: 1m22 (75% use, over 8 procs), so appears CPU bound, not IO.
 from ddplan below there are 44 x 250 trials per obs = 10.000/obs
 if 20=1m22 then 10.000 = ~1hr = ~2x realtime
```

## DDPLAN
```
(oak/FlyEye:)
/export/home/local/src/presto/bin/DDplan.py -l 100 -d 2000 -n 128 -t 0.000625 -f 1430 -b 208 -o ddplan.out.dm100-2000.128chan.625us.1430MHz.208MHz.eps

Minimum total smearing     : 0.997 ms
--------------------------------------------
Minimum channel smearing   : 0.461 ms
Minimum smearing across BW : 0.00295 ms
Minimum sample time        : 0.625 ms

Setting the new 'best' resolution to : 0.625 ms
Best guess for optimal initial dDM is 2.118 

  Low DM    High DM     dDM  DownSamp   #DMs  WorkFract
  100.000    462.000    2.00       1     181   0.6925
  462.000    720.000    3.00       2      86   0.1645
  720.000   1290.000    5.00       4     114   0.109
 1290.000   2000.000   10.00       8      71   0.03396
```

## NOTES
```
currently no web access from machine so more notes kept local at
joeri@pulsar-1:~/notes.txt
```