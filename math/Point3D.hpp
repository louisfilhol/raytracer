/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Point3D
*/

#pragma once
#include "Vector3D.hpp"

namespace math {
    class Point3D {
        public:
            double x;
            double y;
            double z;
            Point3D() = default;
            Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
            Point3D(const Point3D &other) : x(other.x), y(other.y), z(other.z) {}
            void operator=(const Point3D &other) {
                x = other.x;
                y = other.y;
                z = other.z;
            }
            Point3D operator+(const Vector3D &other) const {
                return Point3D(x + other.x, y + other.y, z + other.z);
            }
            Point3D operator-(const Vector3D &other) const {
                return Point3D(x - other.x, y - other.y, z - other.z);
            }
            Vector3D operator-(const Point3D &other) const {
                return Vector3D(x - other.x, y - other.y, z - other.z);
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
    };
}