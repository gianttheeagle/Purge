# Purge
Purge is an Interactive Gentoo system maintenance utility for cleaning distfiles, binary packages, dependencies, and kernels.

## Dependencies
- gentoolkit
- eclean-kernel

To install all dependencies at once:
```sh
emerge --ask app-portage/gentoolkit app-admin/eclean-kernel
```

## Installation
To install Purge itself run:
```sh
gcc -o purge purge.c
sudo mv purge /usr/local/bin/
```
