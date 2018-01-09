#ifndef GAME_ENGINE_JNI_TRANSFORM_H
#define GAME_ENGINE_JNI_TRANSFORM_H

class vector2d {
public:
    int x, y;

    vector2d(int x, int y) {
        this->x = x;
        this->y = y;
    }

    vector2d() : x(0), y(0) {}

    vector2d(const vector2d &v) {
        this->x = v.x;
        this->y = v.y;
    }

    vector2d &operator=(const vector2d &v) {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    vector2d operator+(const vector2d &v) {
        return vector2d(this->x + v.x, this->y + v.y);
    }

    vector2d operator-(const vector2d &v) {
        return vector2d(this->x - v.x, this->y - v.y);
    }

    vector2d &operator*=(const vector2d &v) {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    vector2d &operator+=(const vector2d &v) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    vector2d &operator-=(const vector2d &v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    bool operator==(const vector2d &v) {
        return (this->x == v.x && this->y == v.y);
    }

    bool operator!=(const vector2d &v) {
        return (this->x != x || this->y != y);
    }
};

#endif //GAME_ENGINE_JNI_TRANSFORM_H
