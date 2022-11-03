# Tibbo recommended Setup
```bash
https://github.com/tibbotech/repo-manifests/tree/master/yocto-layers
```

# local.conf changes
```
MENDER_ARTIFACT_NAME = "release-1"
ARTIFACTIMG_FSTYPE = "ext4"
DISTRO_FEATURES:append += "mender-uboot"
INHERIT += "mender-uboot"

# instead of mender-vars
MENDER_FEATURES_ENABLE:append = " mender-uboot"
# build fixes
INITRAMFS_MAXSIZE = "434200"

# build fixes
INITRAMFS_MAXSIZE = "434200"

```

# Mender layer (WIP)
```bash
git clone git@gitlab.com:tibbotech/meta-mender-tibbo.git poky/meta-mender-tibbo
git clone git@github.com:mendersoftware/meta-mender.git poky/meta-mender -b dunfell
bitbake-layers add-layer <full_path>/poky/meta-mender-tibbo
bitbake-layers add-layer <full_path>/poky/meta-mender
```

# Basic build
```bash
bitbake mc::img-tst-tini
```

# Create final binary
```bash
cd /disk2/build.tibbo.dunfell.0/tmp/deploy/images/tppg2
make -f sp_make.mk -d
```

# Flash binary to board
1. Format SD card to FAT32
2. Copy /disk2/build.tibbo.dunfell.0/tmp/deploy/images/tppg2/sp_out/ISPBOOOT.BIN to the root of the SD card
3. Jump CN10 & CN11 and insert SD card
4. Powerup the board, wait until complete the Flash until `ISP all: Done`
5. Unjump CN10 & CN11 and remove the SD card

# Useful resources
- https://docs.tibbo.com/phm/ltpp3g2_firmware
- https://github.com/tibbotech/repo-manifests/tree/master/yocto-layers
