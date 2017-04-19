#ifndef GAME_ENGINE_JNI_SCENE_H
#define GAME_ENGINE_JNI_SCENE_H

#include <vector>
#include <controls/ObjectContainer.h>

class ObjectContainer;

class Scene {
private:
    ObjectContainer *container;
    const char *sceneName;

    virtual void dispose() {};
public:
    Scene(const char *sceneName) : sceneName(sceneName) {}

    virtual ~Scene() {
        dispose();
    }

    virtual void initialize(float width, float height);

    virtual void update();

    ObjectContainer *getContainer() const {
        return container;
    }
};

#endif //GAME_ENGINE_JNI_SCENE_H
