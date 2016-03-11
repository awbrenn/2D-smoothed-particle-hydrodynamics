//
// Created by awbrenn on 3/11/16.
//

#include "vector2.h"
#include <cmath>

vector2::vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

vector2::vector2(const vector2& src) {
    this->x = src.x;
    this->y = src.y;

}

const vector2& vector2::operator=(const vector2& rhs) {
    this->x = rhs.x;
    this->y = rhs.y;

    return *this;
}

vector2::~vector2() {}

vector2 vector2::operator+(const vector2& rhs) const {
    return vector2(this->x + rhs.x, this->y + rhs.y);
}

vector2 vector2::operator-(const vector2& rhs) const {
    return vector2(this->x - rhs.x, this->y - rhs.y);
}

vector2 vector2::operator*(const vector2& rhs) const {
    return vector2(this->x * rhs.x, this->y * rhs.y);
}

vector2 vector2::operator/(const vector2& rhs) const {
    return vector2(this->x / rhs.x, this->y / rhs.y);
}

const vector2& vector2::operator+=(const vector2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}

const vector2& vector2::operator-=(const vector2& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

const vector2& vector2::operator*=(const vector2& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;

    return *this;
}

const vector2& vector2::operator/=(const vector2& rhs) {
    this->x /= rhs.x;
    this->y /= rhs.y;
    return *this;
}

float vector2::length() const {
    return sqrtf(x*x + y*y);
}

void vector2::scale(const float factor) {
    this->x *= factor;
    this->y *= factor;
}

vector2 vector2::unit() const {
    vector2 toReturn = *this;
    toReturn.scale(1/toReturn.length());
    return toReturn;
}
