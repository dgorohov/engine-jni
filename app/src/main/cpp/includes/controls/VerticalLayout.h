#ifndef ENGINE_JNI_VERTICALLAYOUT_H
#define ENGINE_JNI_VERTICALLAYOUT_H

#include <controls/ObjectContainer.h>

class VerticalLayout : public Layout {
    bool _centered;
public:
    VerticalLayout::VerticalLayout(ObjectContainer *container, bool center)
        : Layout(container),
          _centered(center) {}

    void layoutChildren() override;
};

#endif //ENGINE_JNI_VERTICALLAYOUT_H
