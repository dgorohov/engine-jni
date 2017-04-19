#include <jni.h>
#include <MainEngine.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define JNI_METHOD(name)        Java_com_smartpoint_android_gameengine_GameEngine_##name
#define EXPORTED(type, name)    JNIEXPORT type JNICALL JNI_METHOD(name)

static MainEngine *mainEngine = 0;

extern "C" {

EXPORTED(void, nativeOnStart)(JNIEnv *env, jobject /* this */) {
    mainEngine = MainEngine::makeInstance();
}

EXPORTED(void, nativeOnSurfaceCreated)(JNIEnv *env, jobject /* this */,
                                       int width, int height) {
    if (mainEngine) {
        mainEngine->initialize(width, height);
    }
}

EXPORTED(void, nativeOnRender)(JNIEnv *env, jobject /* this */) {
    if (mainEngine) {
        mainEngine->update();
    }
}

EXPORTED(void, nativeOnDestroy)(JNIEnv *env, jobject /* this */) {
    if (mainEngine) {
        mainEngine->dispose();
        delete mainEngine;
        mainEngine = 0;
    }
}

EXPORTED(void, nativeOnAssetManagerReady)(JNIEnv *env,
                                          jobject /* this */ obj,
                                          jobject assetManager) {
    if (mainEngine) {
        AAssetManager *manager = AAssetManager_fromJava(env, assetManager);
        mainEngine->setAssetManager(manager);
    }

}

}
