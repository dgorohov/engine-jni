#ifndef GAME_ENGINE_JNI_GAMEOBJECT_H
#define GAME_ENGINE_JNI_GAMEOBJECT_H

#include <vector>
#include <scenes/Scene.h>
#include <controls/Vector2d.h>
#include <controls/Rect.h>

#define DEFAULT_PADDING     2

class ObjectContainer;

class Layout {
    ObjectContainer *_container;
protected:
    virtual void layoutChild(ObjectContainer *childContainer);

    virtual void updateChild(ObjectContainer *childContainer, Rect *rect);

public:
    Layout(ObjectContainer *container);

    virtual void layoutChildren();

    ObjectContainer *getContainer() const;

    Rect *getRect() const;
};

class Scene;

class ObjectContainer {
private:
    std::vector<ObjectContainer *> children;
    vector2d _relativePosition;
    int _width, _height;
    Layout *layout;
    Scene *scene;
    ObjectContainer *parent;
    bool stateDirty;

protected:
    virtual ~ObjectContainer();

public:
    const char *name;

    ObjectContainer(ObjectContainer *parent,
                    Scene *scene, const char *name,
                    int width, int height);

    ObjectContainer *addChildren(char *name, int width, int height) {
        ObjectContainer *childContainer = new ObjectContainer(
            this, this->scene, name, width, height);
        children.push_back(childContainer);
        return childContainer;
    }

    virtual void initialize() {}

    virtual void draw(Rect *rect);

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

    ObjectContainer *getChildAt(int num) {
        return children[num];
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

    int width() const {
        return _width;
    }

    int height() const {
        return _height;
    }
};

#endif //GAME_ENGINE_JNI_GAMEOBJECT_H
