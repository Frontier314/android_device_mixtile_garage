#!/sbin/busybox sh

echo "do preinstall job"

if [ ! -e /data/system.notfirstrun ]; then		
	/system/bin/sh /system/bin/pm preinstall /system/preinstall
	/system/bin/sh /system/bin/pm preinstall /sdcard/preinstall
	/sbin/busybox touch /data/system.notfirstrun	
fi

echo "preinstall ok"

