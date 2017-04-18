//
// Created by Gorohov Dmitry on 4/17/17.
//

#include <managers/AudioManager.h>
#include "MenuScene.h"

void MenuScene::initialize() {
    audioEffect = AudioManager::makeInstance()->createSFX("music/game.ogg");
    AudioManager::makeInstance()->playSFX(audioEffect, true);
}

void MenuScene::dispose() {
    if (audioEffect) {
        AudioManager::makeInstance()->deleteSFX(audioEffect);
    }
}

void MenuScene::render() {
    Scene::render();
}
