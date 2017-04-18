#ifndef GAME_ENGINE_JNI_MAINENGINE_H
#define GAME_ENGINE_JNI_MAINENGINE_H

#include <scenes/Scene.h>
#include <managers/FileLoader.h>
#include <managers/AudioManager.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class MainEngine {
private:
    Scene *currentScene;
    Scene *nextScene;
    AAssetManager *assetManager;
    void setScene(Scene *scene);

    int width;
    int height;
public:
    void changeScene(Scene *scene) {
        nextScene = scene;
    }

    void initialize(int width, int height);

    void update();

    void render();

    void dispose() {
        if (currentScene) {
            delete currentScene;
            currentScene = 0;
        }

        AudioManager::makeInstance()->destroy();
        FileLoader::makeInstance()->destroy();
    }

    void setAssetManager(AAssetManager* manager) {
        this->assetManager = manager;
        FileLoader::makeInstance()->initialize(manager);
    }

    static MainEngine *makeInstance() {
        static MainEngine *mainEngine;

        if (mainEngine == 0) {
            mainEngine = new MainEngine();
        }
        return mainEngine;
    }
};

#endif //GAME_ENGINE_JNI_MAINENGINE_H
