# FlyEye Node

**LOF EXT2 Support**
```
joeri Feb 6-13 2008

downloaded ext2fsx 1.3
mounted .dmg with hdid
root# /usr/sbin/installer  -verbose -pkg Ext2FS.pkg  -target /
works fine but suggests restart   

root# mount_ext2 /dev/disk9s1 /Volumes/ehd1
(..)
kextload: kld_load_from_memory() failed for module /System/Library/Extensions/ext2fs.kext/Contents/MacOS/ext2fs
kextload: a link/load error occured for kernel extension /System/Library/Extensions/ext2fs.kext
load failed for extension /System/Library/Extensions/ext2fs.kext
(run kextload with -t for diagnostic output)
mount_ext2: ext2 filesystem is not available

Uninstalled semi-gracefully with
cd /
rm `lsbom -s -f /Library/Receipts/Ext2FS.pkg/Contents/Archive.bom`

Donwloaded 1.4_devel:
hdid Ext2FS_1.4d4.dmg
cd /Volumes/Ext2\ Filesystem\ 1.4d4/
lordoftheflies:/Volumes/Ext2 Filesystem 1.4d4 root# /usr/sbin/installer  -verbose -pkg Ext2FS.pkg  -target / 
(..)
installer: The software was successfully installed.....
installer: The upgrade was successful.
installer: The install recommends restarting now.
--rebooted

tested with:
dd if=/dev/zero of=tst.img bs=1k count=8k
/usr/local/sbin/mke2fs tst.img 
hdid -nomount tst.img
mount -t ext2 /dev/disk9 mnt/
 (checked and worked!)
umount  mnt/
hdiutil detach  /dev/disk9

so that appears solved.

USB disk was attached to flytrap. 
diskutil list 
mount -t ext2 /dev/disk9 /media/JOERI_FLYEYE_1
if fails, try "fsck_ext2 -c -y /dev/disk9s1" first [link badblocks to path
USB1.0 very slow, firewire much faster. Don't do both FW local copy + nfs copy from flytrap; slows down both
```