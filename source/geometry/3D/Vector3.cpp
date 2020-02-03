//
//  Vector3.cpp
//  geometry
//
//  Created by Vladas Zakrevskis on 9/13/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <cmath>
#include <string>

#include "Vector3.hpp"
#include "Matrix4.hpp"

using namespace gm;

const Point& Vector3::point() const {
    return reinterpret_cast<const Point&>(x);
}

float Vector3::length() const {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::set_length(float _length) {
    *this *= _length / length();
}

Vector3 Vector3::with_length(float _length) const  {
    return *this * _length / length();
}

Vector3 Vector3::with_x(float x) const { auto result = *this; result.x = x; return result; }
Vector3 Vector3::with_y(float y) const { auto result = *this; result.y = y; return result; }
Vector3 Vector3::with_z(float z) const { auto result = *this; result.z = z; return result; }

Vector3 Vector3::adding_x(float x) const { auto result = *this; result.x += x; return result; }
Vector3 Vector3::adding_y(float y) const { auto result = *this; result.y += y; return result; }
Vector3 Vector3::adding_z(float z) const { auto result = *this; result.z += z; return result; }

Vector3 Vector3::rotated_x(float angle) const { return Matrix4::transform::rotation_x(angle) * *this; }
Vector3 Vector3::rotated_y(float angle) const { return Matrix4::transform::rotation_y(angle) * *this; }
Vector3 Vector3::rotated_z(float angle) const { return Matrix4::transform::rotation_z(angle) * *this;}

float Vector3::xy_angle() const {
    return std::atan2(y, x);
}

float Vector3::xz_angle() const {
    return std::atan2(z, x);
}

Vector3 Vector3::cross(const Vector3& vec) const {
    return {
        y * vec.z - z * vec.y,
        z * vec.x - x * vec.z,
        x * vec.y - y * vec.x
	};
}

float Vector3::dot(const Vector3& vec) const {
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3& Vector3::normalize() {
    return *this *= 1 / length();
}

Vector3 Vector3::normalized() const {
    Vector3 result = *this;
    return result *= 1 / length();
}

Vector3& Vector3::flip_height() {
    std::swap(y, z);
    return *this;
}

Vector3 Vector3::operator + (const Vector3& vec) const {
	return {
		x + vec.x,
		y + vec.y,
		z + vec.z
	};
}

Vector3& Vector3::operator += (const Vector3& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3 Vector3::operator - (const Vector3& vec) const {
	return {
		x - vec.x,
		y - vec.y,
		z - vec.z
	};
}

Vector3& Vector3::operator -= (const Vector3& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3 Vector3::operator * (const Vector3& vec) const {
    return {
        x * vec.x,
        y * vec.y,
        z * vec.z
    };
}

Vector3& Vector3::operator *= (const Vector3& vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector3 Vector3::operator * (float value) const {
	return {
		x * value,
		y * value,
		z * value
	};
}

Vector3& Vector3::operator *= (float value) {
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3 Vector3::operator / (float value) const {
    return {
        x / value,
        y / value,
        z / value
    };
}

Vector3& Vector3::operator /= (float value) {
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

Vector3 Vector3::operator + (float value) const {
    return {
        x + value,
        y + value,
        z + value
    };
}

Vector3& Vector3::operator += (float value) {
    x += value;
    y += value;
    z += value;
    return *this;
}

Vector3 Vector3::operator - (float value) const {
    return {
        x - value,
        y - value,
        z - value
    };
}

Vector3& Vector3::operator -= (float value) {
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

void Vector3::orbit_shift(const Point& shift) {
    *this = Matrix4::transform::rotation_z(shift.x) * *this;
    const auto _length = length();
    const auto step = _length * 2;
    z += shift.y * step;
    set_length(_length);
}

std::string Vector3::to_string() const {
    return std::string() + "{ " + std::to_string(x) + "f, " + std::to_string(y) + "f, " + std::to_string(z) + "f }";
}
