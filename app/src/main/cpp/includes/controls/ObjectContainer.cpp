#include "ObjectContainer.h"

Layout::Layout(ObjectContainer *container, int flags) :
        _container(container),
        _positionFlags(flags) {}

Layout::Layout(ObjectContainer *container) : _container(container) {}

void Layout::layoutChildren() {
    float parentWidth = _container->width();
    float parentHeight = _container->height();
    if (_container->getParent() != 0) {
        parentWidth = _container->getParent()->width();
        parentHeight = _container->getParent()->height();
    }
    float dx = 0;
    float dy = 0;

    if (_container && _container->haveChildren()) {
        for (int i = 0; i < _container->getChildren().size(); i++) {}
    }
}

ObjectContainer::ObjectContainer(ObjectContainer *parent,
                                 Scene *scene,
                                 const char *name,
                                 float width, float height,
                                 int positionFlags)
        : parent(parent), children({}),
          _relativePosition(vector2d(DEFAULT_PADDING, DEFAULT_PADDING)),
          name(name), _width(width), _height(height),
          scene(scene), stateDirty(true) {
    layout = new Layout(this, positionFlags);
    initialize();
}

void ObjectContainer::update() {
    if (stateDirty) {
        getLayout()->layoutChildren();
        stateDirty = false;
    }
    for (int i = 0; i < children.size(); i++) {
        children[i]->update();
    }
}

ObjectContainer::~ObjectContainer() {
    if (numChildren() > 0) {
        dispose();
    }
    delete layout;
    layout = 0;
}

ObjectContainer::ObjectContainer(Scene *scene, const char *name,
                                 float width, float height,
                                 int positionFlags)
        : ObjectContainer(this, scene, name, width, height, positionFlags) {}
