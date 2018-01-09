#ifndef ENGINE_JNI_RECT_H
#define ENGINE_JNI_RECT_H

class Rect {
private:
    int _x, _y;
    int _width, _height;
public:
    Rect(int x, int y, int width, int height) :
        _x(x), _y(y), _width(width), _height(height) {}

    Rect() :
        _x(0), _y(0), _width(0), _height(0) {}

    int x() const {
        return _x;
    }

    int y() const {
        return _y;
    }

    int width() const {
        return _width;
    }

    int height() const {
        return _height;
    }

    Rect *ref() {
        return this;
    }

};


#endif //ENGINE_JNI_RECT_H
