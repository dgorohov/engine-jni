//
// Created by Gorohov Dmitry on 4/17/17.
//

#ifndef GAME_ENGINE_JNI_GAMEOBJECT_H
#define GAME_ENGINE_JNI_GAMEOBJECT_H

#include <vector>
#include "Transform.h"

class GameObject {
private:
    std::vector<GameObject *> children;
    Transform *transform;
protected:
    virtual ~GameObject() {
        if (numChildren() > 0) {
            dispose();
        }
    }

public:
    char *name;
    GameObject *parent;

    GameObject(char *name)
            : GameObject(name, 0) {}

    GameObject(char *name, GameObject *parent)
            : transform(new Transform()),
              children({}) {
        this->name = name;
        if (parent) {
            parent->addChildren(this);
            this->parent = parent;
        }
        initialize();
    }

    void addChildren(GameObject *object) {
        children.push_back(object);
    }

    virtual void initialize() {}

    virtual void dispose() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
            children[i] = 0;
        }
    }

    std::vector<GameObject *> &getChildren() {
        return children;
    }

    size_t numChildren() {
        return children.size();
    }

    virtual void render() {
        for (int i = 0; i < children.size(); i++) {
            children[i]->render();
        }
    }

    virtual void update() {
        for (int i = 0; i < children.size(); i++) {
            children[i]->update();
        }
    }

    Transform *getTransform() const {
        return transform;
    }
};

#endif //GAME_ENGINE_JNI_GAMEOBJECT_H
