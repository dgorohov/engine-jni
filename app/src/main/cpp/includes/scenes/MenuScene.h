//
// Created by Gorohov Dmitry on 4/17/17.
//

#ifndef GAME_ENGINE_JNI_MENUSCENE_H
#define GAME_ENGINE_JNI_MENUSCENE_H

#include <scenes/Scene.h>
#include <managers/AudioManager.h>

class MenuScene : public Scene {
private:
    AudioEffect* audioEffect;
    virtual void dispose() override;
public:
    ~MenuScene() {}
    virtual void initialize() override;
    virtual void render() override;
};

#endif //GAME_ENGINE_JNI_MENUSCENE_H
