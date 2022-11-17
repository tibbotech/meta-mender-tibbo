# Tibbo recommended Setup
https://github.com/tibbotech/repo-manifests/tree/master/yocto-layers
```bash
curl https://raw.githubusercontent.com/tibbotech/repo-manifests/master/clone.sh > ./clone.sh && chmod 0755 ./clone.sh && ./clone.sh
repo3 sync
TEMPLATECONF=`pwd`/layers/meta-tibbo/build.tppg2/conf . layers/openembedded-core/oe-init-build-env ./build.tppg2
install -d conf/multiconfig
install -D ../layers/meta-tibbo/build.tppg2/conf/multiconfig/* conf/multiconfig/
install -m 0644 ../layers/meta-tibbo/build.all/site.conf conf/

```

# Mender layer (WIP)
```bash
git clone https://github.com/tibbotech/meta-mender-tibbo.git ../layers/meta-mender-tibbo
git clone https://github.com/mendersoftware/meta-mender.git ../layers/meta-mender -b dunfell
bitbake-layers add-layer ../layers/meta-mender/meta-mender-core/
bitbake-layers add-layer ../layers/meta-mender-tibbo/
```

# local.conf changes
```
# Mender variables
MENDER_ARTIFACT_NAME = "release-1"
ARTIFACTIMG_FSTYPE = "ext4"
INHERIT:append:tppg2 = " mender-uboot"
MENDER_FEATURES_ENABLE:append:tppg2 = " mender-uboot"

MENDER_BOOT_PART=""
MENDER_BOOT_PART_NUMBER="3"
MENDER_DATA_PART = "${MENDER_STORAGE_DEVICE_BASE}10"
MENDER_ROOTFS_PART_A="${MENDER_STORAGE_DEVICE_BASE}8"
MENDER_ROOTFS_PART_B="${MENDER_STORAGE_DEVICE_BASE}9"

# build fixes
INITRAMFS_MAXSIZE = "443200"
```

# Basic build
```bash
bitbake mc::img-tst-tini
```

# Create final binary
```bash
cd /disk2/build.tibbo.dunfell.1/tmp/deploy/images/tppg2
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
