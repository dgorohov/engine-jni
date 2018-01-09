#ifndef GAME_ENGINE_JNI_MENUSCENE_H
#define GAME_ENGINE_JNI_MENUSCENE_H

#include <scenes/Scene.h>
#include <managers/AudioManager.h>

class MenuScene : public Scene {
private:
    AudioEffect *audioEffect;

    virtual void dispose() override;

public:
    MenuScene() : Scene("Menu") {}

    ~MenuScene() {}

    virtual void initialize(int width, int height) override;
};

#endif //GAME_ENGINE_JNI_MENUSCENE_H
