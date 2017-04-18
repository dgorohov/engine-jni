#ifndef GAME_ENGINE_JNI_SCENE_H
#define GAME_ENGINE_JNI_SCENE_H

#include <vector>
#include <controls/GameObject.h>

class Scene {
private:
    std::vector<GameObject *> gameObjects;
    virtual void dispose() {};
public:
    virtual ~Scene() {
        dispose();
    }

    virtual void initialize() = 0;

    virtual void render() {
        for (int i = 0; i < gameObjects.size(); i++) {
            gameObjects[i]->render();
        }
    }
};

#endif //GAME_ENGINE_JNI_SCENE_H
