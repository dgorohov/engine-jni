#ifndef GAME_ENGINE_JNI_GAMEOBJECT_H
#define GAME_ENGINE_JNI_GAMEOBJECT_H

#include <vector>
#include <scenes/Scene.h>
#include "Vector2d.h"

#define DEFAULT_PADDING     2
#define DEFAULT_WIDTH       10
#define DEFAULT_HEIGHT      10

static uint8_t POSITION_NORMAL = 0x0;
static uint8_t POSITION_VERTICAL = 0x1;
static uint8_t POSITION_HORIZONTAL = 0x2;
static uint8_t POSITION_CENTER_BOTH = 0x4;
static uint8_t POSITION_CENTER_VERTICAL = 0x8;
static uint8_t POSITION_CENTER_HORIZONTAL = 0x10;
static uint8_t DEFAULT_POSITION = POSITION_VERTICAL | POSITION_CENTER_VERTICAL;

class ObjectContainer;

class Layout {
    int _positionFlags;
    ObjectContainer *_container;
public:
    Layout(ObjectContainer *container, int flags);

    Layout(ObjectContainer *container);

    virtual void layoutChildren();
};

class Scene;

class ObjectContainer {
private:
    std::vector<ObjectContainer *> children;
    vector2d _relativePosition;
    float _width, _height;
    Layout *layout;
    Scene *scene;
    ObjectContainer *parent;
    bool stateDirty;

    ObjectContainer(Scene *scene, const char *name,
                    float width, float height,
                    int positionFlags);
protected:
    virtual ~ObjectContainer();

public:
    const char *name;

    ObjectContainer(ObjectContainer *parent,
                    Scene *scene, const char *name,
                    float width, float height,
                    int positionFlags);

    ObjectContainer *addChildren(char *name, float width, float height) {
        ObjectContainer *childContainer = new ObjectContainer(
                this->scene, name, width, height, DEFAULT_POSITION);
        children.push_back(childContainer);
        return childContainer;
    }

    virtual void initialize() {}

    virtual void dispose() {
        for (int i = 0; i < children.size(); i++) {
            children[i]->dispose();
            delete children[i];
            children[i] = 0;
        }
        children.clear();
    }

    std::vector<ObjectContainer *> &getChildren() {
        return children;
    }

    size_t numChildren() {
        return children.size();
    }

    bool haveChildren() {
        return children.size() > 0;
    }

    virtual void update();

    Layout *getLayout() const {
        return layout;
    }

    ObjectContainer *getParent() const {
        return parent;
    }

    const vector2d &relativePosition() const {
        return _relativePosition;
    }

    float width() const {
        return _width;
    }

    float height() const {
        return _height;
    }
};

#endif //GAME_ENGINE_JNI_GAMEOBJECT_H
