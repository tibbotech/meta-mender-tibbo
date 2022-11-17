FILESEXTRAPATHS_prepend := "${THISDIR}/patches:"

# no automatic patching
MENDER_UBOOT_AUTO_CONFIGURE = "0"

SRC_URI:append:mender-uboot = " file://sp7021_dsxe_defconfig.mender.patch"
SRC_URI:append:mender-uboot = " file://sp7021_emmc_c_defconfig.mender.patch"
SRC_URI:append:mender-uboot = " file://sp7021_nand_c_defconfig.mender.patch"
SRC_URI:append:mender-uboot = " file://sp7021_romter_c_defconfig.mender.patch"
SRC_URI:append:mender-uboot = " file://sp7021_tppg2_defconfig.mender.patch"
# run mender_setup before defining root and running bootcmd
SRC_URI:append:mender-uboot = " file://pentagram_common.h.mender1.patch"


BOOTENV_SIZE ?= "0x80000"
MENDER_PARTITION_ALIGNMENT = "1"
# = BOOTENV_SIZE * 2
MENDER_RESERVED_SPACE_BOOTLOADER_DATA = "0x100000"
MENDER_UBOOT_ENV_STORAGE_DEVICE_OFFSET = "0x204400"

CONFIG_ENV_UBI_VOLUME = "env"
CONFIG_ENV_UBI_VOLUME_REDUND = "env_redund"

UBOOT_CONFIG = "a7021_emmc a7021_ppg2 a7021_dsxe"
