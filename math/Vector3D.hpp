/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Vector3D
*/

#pragma once
#include <math.h>

namespace math {
    class Vector3D {
        public:
            double x;
            double y;
            double z;
            Vector3D() = default;
            Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
            Vector3D(const Vector3D &other) : x(other.x), y(other.y), z(other.z) {}
            double length() const {
                return sqrt(x * x + y * y + z * z);
            }
            void operator+=(const Vector3D &other) {
                x += other.x;
                y += other.y;
                z += other.z;
            }
            void operator-=(const Vector3D &other) {
                x -= other.x;
                y -= other.y;
                z -= other.z;
            }
            Vector3D operator+(const Vector3D &other) const {
                return Vector3D(x + other.x, y + other.y, z + other.z);
            }
            Vector3D operator-(const Vector3D &other) const {
                return Vector3D(x - other.x, y - other.y, z - other.z);
            }
            
            Vector3D operator-() const {
                return Vector3D(-x, -y, -z);
            }
            Vector3D operator*(const Vector3D &other) const {
                return Vector3D(x * other.x, y * other.y, z * other.z);
            }
            Vector3D operator/(const Vector3D &other) const {
                return Vector3D(x / other.x, y / other.y, z / other.z);
            }
            void operator*=(const Vector3D &other) {
                x *= other.x;
                y *= other.y;
                z *= other.z;
            }
            void operator/=(const Vector3D &other) {
                x /= other.x;
                y /= other.y;
                z /= other.z;
            }
            void operator=(const Vector3D &other) {
                x = other.x;
                y = other.y;
                z = other.z;
            }
            Vector3D operator*(double scalar) const {
                return Vector3D(x * scalar, y * scalar, z * scalar);
            }
            Vector3D operator/(double scalar) const {
                return Vector3D(x / scalar, y / scalar, z / scalar);
            }
            void operator*=(double scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
            }
            void operator/=(double scalar) {
                x /= scalar;
                y /= scalar;
                z /= scalar;
            }
            double dot(const Vector3D &other) const {
                return x * other.x + y * other.y + z * other.z;
            }
            Vector3D normalized() const {
                double len = this->length();
                return Vector3D(x / len, y / len, z / len);
            }
            Vector3D cross(const Vector3D &other) const {
                return Vector3D(
                    y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x
                );
            }
    };
}