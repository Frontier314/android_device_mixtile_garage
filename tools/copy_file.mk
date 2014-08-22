LLOCAL_PATH := device/mixtile/garage/tools

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/other/gator.ko:system/bin/gator.ko \
	$(LOCAL_PATH)/other/busybox:root/sbin/busybox \
	$(LOCAL_PATH)/other/picocom:root/sbin/picocom \
	$(LOCAL_PATH)/other/remount_rw:root/sbin/remount_rw \
	$(LOCAL_PATH)/other/remount_ro:root/sbin/remount_ro \
	$(LOCAL_PATH)/other/su:system/xbin/su \
  $(LOCAL_PATH)/preinstall/preinstall.sh:system/bin/preinstall.sh
