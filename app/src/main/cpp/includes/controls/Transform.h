//
// Created by Gorohov Dmitry on 4/18/17.
//

#ifndef GAME_ENGINE_JNI_TRANSFORM_H
#define GAME_ENGINE_JNI_TRANSFORM_H

class vector2d {
public:
    float x, y;

    vector2d(float x, float y) {
        this->x = x;
        this->y = y;
    }

    vector2d() : x(0), y(0) {}

    vector2d(const vector2d& v) {
        this->x = v.x;
        this->y = v.y;
    }

    vector2d& operator =(const vector2d& v) {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    vector2d operator +(const vector2d& v) {
        return vector2d(this->x + v.x, this->y + v.y);
    }

    vector2d operator -(const vector2d& v) {
        return vector2d(this->x - v.x, this->y - v.y);
    }

    vector2d& operator *=(const vector2d& v) {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    vector2d& operator +=(const vector2d& v) {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    vector2d& operator -=(const vector2d& v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    bool operator ==(const vector2d& v) {
        return (this->x == v.x && this->y == v.y);
    }

    bool operator !=(const vector2d& v) {
        return (this->x != x || this->y != y);
    }
};

class Transform {
public:
    Transform() {
        _position = vector2d();
        _scale = vector2d(1, 1);
        _rotate = 0;
    }
private:
    vector2d _position, _scale;
    float _rotate;
public:

    void moveTo(int dx, int dy) {
        _position += vector2d(dx, dy);
    };

    void moveTo(const vector2d& v) {
        _position += v;
    };

    void setPosition(const vector2d& v) {
        _position = v;
    };

    void x(float x) {
        _position.x += x;
    }

    void setX(float x) {
        _position.x = x;
    }

    void y(float y) {
        _position.y += y;
    }

    void setY(float y) {
        _position.y = y;
    }

    void scaleX(float dx) {
        _scale.x *= dx;
    };

    void scaleY(float dy) {
        _scale.y *= dy;
    };

    void scale(float dx, float dy) {
        _scale *= vector2d(dx, dy);
    };

    void scale(const vector2d& v) {
        _scale *= v;
    };

    void setScale(const vector2d& v) {
        _scale = v;
    };

    void rotate(float angle) {
        _rotate += angle;
    };

    void setRotation(float angle) {
        _rotate = angle;
    };
};


#endif //GAME_ENGINE_JNI_TRANSFORM_H
