#include <controls/ObjectContainer.h>
#include "Scene.h"

void Scene::initialize(float width, float height) {
    container = new ObjectContainer(0, this, sceneName,
                                    width, height, DEFAULT_POSITION);
}

void Scene::update() {
    container->update();
}
