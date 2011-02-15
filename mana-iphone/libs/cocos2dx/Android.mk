LOCAL_PATH := $(call my-dir)

# compile cocos2d.so
include $(CLEAR_VARS)
LOCAL_MODULE := libcocos2d

LOCAL_SRC_FILES := \
CCConfiguration.cpp \
CCDrawingPrimitives.cpp \
CCScheduler.cpp \
CCamera.cpp \
actions/CCAction.cpp \
actions/CCActionCamera.cpp \
actions/CCActionEase.cpp \
actions/CCActionGrid.cpp \
actions/CCActionGrid3D.cpp \
actions/CCActionInstant.cpp \
actions/CCActionInterval.cpp \
actions/CCActionManager.cpp \
actions/CCActionPageTurn3D.cpp \
actions/CCActionProgressTimer.cpp \
actions/CCActionTiledGrid.cpp \
base_nodes/CCAtlasNode.cpp \
cocoa/CGAffineTransform.cpp \
cocoa/CGGeometry.cpp \
cocoa/NSAutoreleasePool.cpp \
cocoa/NSData.cpp \
cocoa/NSObject.cpp \
cocoa/NSSet.cpp \
cocoa/NSZone.cpp \
cocos2d.cpp \
effects/CCGrabber.cpp \
event_dispatcher/CCEventDispatcher.cpp \
event_dispatcher/CCKeyboardEventDelegate.cpp \
event_dispatcher/CCMouseEventDelegate.cpp \
keypad_dispatcher/CCKeypadDelegate.cpp \
keypad_dispatcher/CCKeypadDispatcher.cpp \
label_nodes/CCLabelAtlas.cpp \
label_nodes/CCLabelBMFont.cpp \
label_nodes/CCLabelTTF.cpp \
layers_scenes_transitions_nodes/CCScene.cpp \
layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
layers_scenes_transitions_nodes/CCTransitionRadial.cpp \
menu_nodes/CCMenuItem.cpp \
misc_nodes/CCMotionStreak.cpp \
misc_nodes/CCProgressTimer.cpp \
misc_nodes/CCRenderTexture.cpp \
misc_nodes/CCRibbon.cpp \
particle_nodes/CCParticleExamples.cpp \
particle_nodes/CCParticleSystem.cpp \
particle_nodes/CCParticleSystemQuad.cpp \
platform/CCDirector_mobile.cpp \
platform/CCGrid_mobile.cpp \
platform/CCLayer_mobile.cpp \
platform/CCMenu_mobile.cpp \
platform/CCNode_mobile.cpp \
platform/CCParticleSystemPoint_mobile.cpp \
platform/CCTransition_mobile.cpp \
platform/android/CCNS_android.cpp \
platform/android/CCTime.cpp \
platform/android/CCXApplication_android.cpp \
platform/android/CCXBitmapDC.cpp \
platform/android/CCXEGLView_android.cpp \
platform/android/CCXFileUtils_android.cpp \
platform/android/CCXUIAccelerometer_android.cpp \
platform/android/CCXUIImage_android.cpp \
platform/android/Cocos2dJni.cpp \
platform/android/NSLock.cpp \
platform/android/ccxCommon_android.cpp \
sprite_nodes/CCAnimation.cpp \
sprite_nodes/CCAnimationCache.cpp \
sprite_nodes/CCSprite.cpp \
sprite_nodes/CCSpriteBatchNode.cpp \
sprite_nodes/CCSpriteFrame.cpp \
sprite_nodes/CCSpriteFrameCache.cpp \
sprite_nodes/CCSpriteSheet.cpp \
support/CCProfiling.cpp \
support/CGPointExtension.cpp \
support/TransformUtils.cpp \
support/base64.cpp \
support/ccUtils.cpp \
support/file_support/FileUtils.cpp \
support/image_support/TGAlib.cpp \
support/opengl_support/glu.cpp \
support/zip_support/ZipUtils.cpp \
support/zip_support/ioapi.cpp \
support/zip_support/unzip.cpp \
textures/CCTexture2D.cpp \
textures/CCTextureAtlas.cpp \
textures/CCTextureCache.cpp \
tileMap_parallax_nodes/CCParallaxNode.cpp \
tileMap_parallax_nodes/CCTMXLayer.cpp \
tileMap_parallax_nodes/CCTMXObjectGroup.cpp \
tileMap_parallax_nodes/CCTMXTiledMap.cpp \
tileMap_parallax_nodes/CCTMXXMLParser.cpp \
tileMap_parallax_nodes/CCTileMapAtlas.cpp \
touch_dispatcher/CCTouchDispatcher.cpp \
touch_dispatcher/CCTouchHandler.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/platform/android/third_party/iconv \
                    $(LOCAL_PATH)/platform/android/third_party/libpng \
                    $(LOCAL_PATH)/platform/android/third_party/libxml2 \
                    $(LOCAL_PATH)/platform/android/third_party/libjpeg \
                    $(LOCAL_PATH)/platform/android/third_party/skia/core \
                    $(LOCAL_PATH)/platform/android/third_party/skia/animator \
                    $(LOCAL_PATH)/platform/android/third_party/skia/config \
                    $(LOCAL_PATH)/platform/android/third_party/skia/effects \
                    $(LOCAL_PATH)/platform/android/third_party/skia/images \
                    $(LOCAL_PATH)/platform/android/third_party/skia/pdf \
                    $(LOCAL_PATH)/platform/android/third_party/skia/ports \
                    $(LOCAL_PATH)/platform/android/third_party/skia/svg \
                    $(LOCAL_PATH)/platform/android/third_party/skia/text \
                    $(LOCAL_PATH)/platform/android/third_party/skia/utils \
                    $(LOCAL_PATH)/platform/android/third_party/skia/views \
                    $(LOCAL_PATH)/platform/android/third_party/skia/ xml
                    
#it is used for ndk-r4
LOCAL_LDLIBS := -L$(LOCAL_PATH)/platform/android/third_party/libs \
                -lGLESv1_CM -llog -lz \
                -lpng \
                -lxml2 \
                -ljpeg \
                -lskia

# it is used for ndk-r5    
# because the new Windows toolchain doesn't support Cygwin's drive
# mapping (i.e /cygdrive/c/ instead of C:/)  
#LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/platform/android/third_party/libs) \
#                -lGLESv1_CM -llog -lz \
#                -lpng \
#                -lxml2 \
#                -ljpeg \
#                -lskia

# define the macro to compile through support/zip_support/ioapi.c                
LOCAL_CFLAGS := -DUSE_FILE32API
                                 
include $(BUILD_SHARED_LIBRARY)