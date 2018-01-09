#ifndef ENGINE_JNI_HORIZONTALLAYOUT_H
#define ENGINE_JNI_HORIZONTALLAYOUT_H

#include <controls/ObjectContainer.h>

class HorizontalLayout : public Layout {
    bool _centered;
public:
    HorizontalLayout::HorizontalLayout(ObjectContainer *container, bool center)
        : Layout(container),
          _centered(center) {}

    void layoutChildren() override;

};


#endif //ENGINE_JNI_HORIZONTALLAYOUT_H
