#include <managers/AudioManager.h>
#include <scenes/MenuScene.h>

void MenuScene::initialize(int width, int height) {
    Scene::initialize(width, height);
    audioEffect = AudioManager::makeInstance()->createSFX("music/game.ogg");
    AudioManager::makeInstance()->playSFX(audioEffect, true);
}

void MenuScene::dispose() {
    if (audioEffect) {
        AudioManager::makeInstance()->deleteSFX(audioEffect);
    }
}
