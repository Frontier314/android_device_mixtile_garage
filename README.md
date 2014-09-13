How to build Android Kitkat 4.4.2 for Mixtile Garage and (possibly) Hyundai T7s:

- Get Android branch android-4.4.2_r2 (KVT49L).
- After syncing, perform the following changes:

- File: hardware/libhardware/include/gralloc.h

  Add:
    GRALLOC_USAGE_HW_FIMC1        = 0x01000000,
    GRALLOC_USAGE_HW_ION          = 0x02000000,
    GRALLOC_USAGE_YUV_ADDR        = 0x04000000,
    /* SEC Private usage , for Overlay path at HWC */
    GRALLOC_USAGE_HWC_HWOVERLAY     = 0x20000000,

    Add after GRALLOC_USAGE_PROTECTED:
    
    /* SEC Private usage , for HWC to set HDMI S3D format */
    /* HDMI should display this buffer as S3D SBS LR/RL*/
    GRALLOC_USAGE_PRIVATE_SBS_LR       = 0x00100000,
    GRALLOC_USAGE_PRIVATE_SBS_RL       = 0x00200000,
    /* HDMI should display this buffer as 3D TB LR/RL*/
    GRALLOC_USAGE_PRIVATE_TB_LR       = 0x00400000,
    GRALLOC_USAGE_PRIVATE_TB_RL       = 0x00800000,

    Add near the end:
    
    #if !defined(VITHAR_HACK)
    int (*getphys)(struct gralloc_module_t const* module,
            buffer_handle_t handle, void** paddr);
    #endif


- File: system/core/include/system/graphics.h

  Add:
    HAL_PIXEL_FORMAT_RGBA_5551          = 6,
    HAL_PIXEL_FORMAT_RGBA_4444          = 7,
    
- Remove all device folders inside device (e.g lg, samsung, asus, etc) except google and common
- mkdir device/mixtile
- Inside device/mixtile git clone git@github.com:Frontier314/android_device_mixtile_garage.git
- Rename the resulting folder to 'garage', e.g device/mixtile/garage contains all device files
- Inside hardware/samsung_slsi git clone git@github.com:Frontier314/android_hardware_samsung_slsi.git
- Make sure the path hardware/samsung_slsi/Exynos4 exists and contains HAL source (i.e libaudio, libump etc).
- mkdir hardware/realtek and inside git clone git@github.com:Frontier314/android_hardware_realtek.git
- Make sure the path hardware/realtek/wlan exists and contains WLAN HAL files.

To build:

- cd to the root android source tree
- . build/envsetup.sh
- lunch (select garage-eng)
- make
