LLOCAL_PATH := device/mixtile/garage/wifi

ifeq ($(WIFI_RTL8188),true)
PRODUCT_COPY_FILES += \
  	$(LLOCAL_PATH)/rtl8188/8192cu.ko:system/lib/modules/8192cu.ko \
  	$(LLOCAL_PATH)/rtl8188/8188eu.ko:system/lib/modules/8188eu.ko
endif

#  	frameworks/base/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
