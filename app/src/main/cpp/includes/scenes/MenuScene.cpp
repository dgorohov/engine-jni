#include <managers/AudioManager.h>
#include "MenuScene.h"

void MenuScene::initialize(float width, float height) {
    Scene::initialize(width, height);
    audioEffect = AudioManager::makeInstance()->createSFX("music/game.ogg");
    AudioManager::makeInstance()->playSFX(audioEffect, true);
}

void MenuScene::dispose() {
    if (audioEffect) {
        AudioManager::makeInstance()->deleteSFX(audioEffect);
    }
}
