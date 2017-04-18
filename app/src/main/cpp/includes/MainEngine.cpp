#include <scenes/MenuScene.h>
#include "MainEngine.h"

void MainEngine::initialize(int width, int height) {
    this->width = width;
    this->height = height;
    AudioManager::makeInstance()->initialize();
    changeScene(new MenuScene());
}

void MainEngine::update() {
    if (nextScene) {
        setScene(nextScene);
        nextScene = 0;
    }
}

void MainEngine::render() {
    if (currentScene) {
        currentScene->render();
    }
}

void MainEngine::setScene(Scene *scene) {
    if (scene) {
        if (currentScene) {
            delete currentScene;
            currentScene = 0;
        }
        currentScene = scene;
        currentScene->initialize();
    }
}
