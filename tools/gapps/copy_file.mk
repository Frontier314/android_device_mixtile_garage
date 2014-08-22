LLOCAL_PATH := device/mixtile/garage/tools/gapps

PRODUCT_COPY_FILES += \
	$(LLOCAL_PATH)/etc/permissions/com.google.android.maps.xml:system/etc/permissions/com.google.android.maps.xml \
	$(LLOCAL_PATH)/etc/permissions/com.google.android.media.effects.xml:system/etc/permissions/com.google.android.media.effects.xml \
	$(LLOCAL_PATH)/etc/permissions/com.google.widevine.software.drm.xml:system/etc/permissions/com.google.widevine.software.drm.xml \
	$(LLOCAL_PATH)/etc/permissions/features.xml:system/etc/permissions/features.xml \
	$(LLOCAL_PATH)/framework/com.google.android.maps.jar:system/framework/com.google.android.maps.jar \
	$(LLOCAL_PATH)/framework/com.google.android.media.effects.jar:system/framework/com.google.android.media.effects.jar \
	$(LLOCAL_PATH)/framework/com.google.widevine.software.drm.jar:system/framework/com.google.widevine.software.drm.jar \
	$(LLOCAL_PATH)/lib/libfilterpack_facedetect.so:system/lib/libfilterpack_facedetect.so \
	$(LLOCAL_PATH)/lib/libflint_engine_jni_api.so:system/lib/libflint_engine_jni_api.so \
	$(LLOCAL_PATH)/lib/libfrsdk.so:system/lib/libfrsdk.so \
	$(LLOCAL_PATH)/lib/libgcomm_jni.so:system/lib/libgcomm_jni.so \
	$(LLOCAL_PATH)/lib/libpicowrapper.so:system/lib/libpicowrapper.so \
	$(LLOCAL_PATH)/lib/libspeexwrapper.so:system/lib/libspeexwrapper.so \
	$(LLOCAL_PATH)/lib/libvideochat_jni.so:system/lib/libvideochat_jni.so \
	$(LLOCAL_PATH)/lib/libvideochat_stabilize.so:system/lib/libvideochat_stabilize.so \
	$(LLOCAL_PATH)/lib/libvoicesearch.so:system/lib/libvoicesearch.so \
	$(LLOCAL_PATH)/tts/lang_pico/de-DE_gl0_sg.bin:system/tts/lang_pico/de-DE_gl0_sg.bin \
	$(LLOCAL_PATH)/tts/lang_pico/de-DE_ta.bin:system/tts/lang_pico/de-DE_ta.bin \
	$(LLOCAL_PATH)/tts/lang_pico/es-ES_ta.bin:system/tts/lang_pico/es-ES_ta.bin \
	$(LLOCAL_PATH)/tts/lang_pico/es-ES_zl0_sg.bin:system/tts/lang_pico/es-ES_zl0_sg.bin \
	$(LLOCAL_PATH)/tts/lang_pico/fr-FR_nk0_sg.bin:system/tts/lang_pico/fr-FR_nk0_sg.bin \
	$(LLOCAL_PATH)/tts/lang_pico/fr-FR_ta.bin:system/tts/lang_pico/fr-FR_ta.bin \
	$(LLOCAL_PATH)/tts/lang_pico/it-IT_cm0_sg.bin:system/tts/lang_pico/it-IT_cm0_sg.bin \
	$(LLOCAL_PATH)/tts/lang_pico/it-IT_ta.bin:system/tts/lang_pico/it-IT_ta.bin
