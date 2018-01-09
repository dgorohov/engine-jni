#include <controls/HorizontalLayout.h>

void HorizontalLayout::layoutChildren() {
    ObjectContainer *container = getContainer();
    if (container && container->haveChildren()) {
        Rect *rect = getRect();
        int dx, dy = 0;
        if (_centered) {
            dx = (container->width() - rect->width()) / 2;
            dy = (container->height() - rect->height()) / 2;
        } else {
            ObjectContainer *parent = container->getParent();
            dx = parent->relativePosition().x;
            dy = parent->relativePosition().y;
        }

        for (int i = 0; i < container->getChildren().size(); i++) {
            ObjectContainer *currentChild = container->getChildAt(i);
            updateChild(currentChild,
                        Rect(dx, dy, currentChild->width(), currentChild->height()).ref());
            dx += currentChild->width();
        }
    }
}
