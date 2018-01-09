#include "ObjectContainer.h"

Layout::Layout(ObjectContainer *container) : _container(container) {}

void Layout::layoutChildren() {
    if (_container && _container->haveChildren()) {
        for (int i = 0; i < _container->getChildren().size(); i++) {
            ObjectContainer *object = _container->getChildAt(i);
            layoutChild(object);
        }
    }
}

void Layout::layoutChild(ObjectContainer *object) {
    int parentX = object->getParent() != 0
                  ? object->getParent()->relativePosition().x
                  : 0;

    int parentY = object->getParent() != 0
                  ? object->getParent()->relativePosition().y
                  : 0;

    int controlWidth = object->width() + object->relativePosition().x * 2;
    if (object->getParent() != 0
        && controlWidth > object->getParent()->width()) {
        controlWidth = object->getParent()->width();
    }

    int controlHeight = object->height() + object->relativePosition().y * 2;
    if (object->getParent() != 0 && controlHeight > object->getParent()->height()) {
        controlHeight = object->getParent()->height();
    }

    updateChild(object, Rect(
        parentX + object->relativePosition().x,
        parentY + object->relativePosition().y,
        controlWidth, controlHeight).ref());
}

void Layout::updateChild(ObjectContainer *object, Rect *rect) {
    object->draw(rect);
    object->getLayout()->layoutChildren();
}

ObjectContainer::ObjectContainer(ObjectContainer *parent,
                                 Scene *scene,
                                 const char *name,
                                 int width, int height)
    : parent(parent), children({}),
      _relativePosition(vector2d(DEFAULT_PADDING, DEFAULT_PADDING)),
      name(name), _width(width), _height(height),
      scene(scene), stateDirty(true) {
    layout = new Layout(this);
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

void ObjectContainer::draw(Rect *rect) {}

ObjectContainer *Layout::getContainer() const {
    return _container;
}

Rect *Layout::getRect() const {
    ObjectContainer *container = getContainer();
    if (container && container->haveChildren()) {
        int totalWidth = 0, totalHeight = 0;
        size_t n = container->getChildren().size();
        for (int i = 0; i < n; i++) {
            ObjectContainer *object = container->getChildAt(i);
            totalWidth += object->width();
            totalHeight += object->height();
        }
        return Rect(0, 0, totalWidth, totalHeight).ref();
    }
    return Rect().ref();
}
