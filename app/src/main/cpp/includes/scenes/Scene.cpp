#include <controls/ObjectContainer.h>
#include "Scene.h"

void Scene::initialize(int width, int height) {
    container = new ObjectContainer(0, this, sceneName,
                                    width, height);
}

void Scene::update() {
    container->update();
}
