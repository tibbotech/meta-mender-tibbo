# Tibbo recommended Setup
https://github.com/tibbotech/repo-manifests/tree/master/yocto-layers
```bash
curl https://raw.githubusercontent.com/tibbotech/repo-manifests/master/clone.sh > ./clone.sh && chmod 0755 ./clone.sh && ./clone.sh
repo3 sync
TEMPLATECONF=`pwd`/layers/meta-tibbo/build.tppg2/conf . layers/openembedded-core/oe-init-build-env ./build.tppg2
install -m 0644 ../layers/meta-tibbo/build.all/site.conf conf/

```

# Mender layer (WIP)
```bash
git clone https://github.com/tibbotech/meta-mender-tibbo.git ../layers/meta-mender-tibbo
git clone https://github.com/mendersoftware/meta-mender.git ../layers/meta-mender -b dunfell
MACHINE=tppg2 bitbake-layers add-layer ../layers/meta-mender/meta-mender-core/
MACHINE=tppg2 bitbake-layers add-layer ../layers/meta-mender-tibbo/
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

# ISPE definitions

# images of this type is the part of ISP. should be built first
IMAGE_TYPEDEP_isp += "ext4"
IMAGE_TYPEDEP_isp += "dataimg"

# the ISP set subfolder/image ID
ISP_CONFIG += "emmcM"

# to boot from EMMC
ISP_BOOTYP[emmcM] = "emmc"

# partition name;binary contents;offset (512byte blocks)
ISP_CONFIG[emmcM] += "xboot1;../${MACHINE}-arm5/xboot-emmc.img;0x0"
ISP_CONFIG[emmcM] += "uboot1;u-boot.bin-a7021_ppg2.img;0x22"
ISP_CONFIG[emmcM] += "uboot2;u-boot.bin-a7021_ppg2.img;0x822"
ISP_CONFIG[emmcM] += "env;;0x1022"
ISP_CONFIG[emmcM] += "env_redund;;0x1422"
ISP_CONFIG[emmcM] += "nonos;../${MACHINE}-arm5/a926-empty.img;0x1822"
ISP_CONFIG[emmcM] += "dtb;sp7021-ltpp3g2revD.dtb;0x2022"
ISP_CONFIG[emmcM] += "kernel;${KERNEL_IMAGETYPE}-initramfs-${MACHINE}.img;0x2222"
ISP_CONFIG[emmcM] += "rootfs;${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4;0x12222"
# offset=(3.8GB - 1GB)
ISP_CONFIG[emmcM] += "rootB;${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4;0x600000"
# offset= (3.8GB - 200MB)
ISP_CONFIG[emmcM] += "data;${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.dataimg;0x700000"

# ISPBOOOT.BIN boot area
ISP_SETBOO[emmcM] += "../${MACHINE}-arm5/xboot-emmc.img;0x0"
ISP_SETBOO[emmcM] += "u-boot.bin-a7021_ppg2.img;0x10000"
```

# Basic build
```bash
MACHINE=tppg2 bitbake mc:tppg2:img-tst-tini
```

# Create final binary (old way)
```bash
cd /disk2/build.tibbo.dunfell.1/tmp/deploy/images/tppg2
make -f sp_make.mk -d
```

# Final binary (new way)
Placed at /disk2/build.tibbo.dunfell.1/tmp/deploy/images/tppg2/emmcM/

# Flash binary to board
1. Format SD card to FAT32
2. Copy /disk2/build.tibbo.dunfell.0/tmp/deploy/images/tppg2/sp_out/ISPBOOOT.BIN to the root of the SD card
3. Jump CN10 & CN11 and insert SD card
4. Powerup the board, wait until complete the Flash until `ISP all: Done`
5. Unjump CN10 & CN11 and remove the SD card

# Useful resources
- https://docs.tibbo.com/phm/ltpp3g2_firmware
- https://github.com/tibbotech/repo-manifests/tree/master/yocto-layers
