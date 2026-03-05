/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Rectangle3D
*/

#pragma once
#include "math/Point3D.hpp"

namespace RayTracer {
    class Rectangle3D {
        public:
            Rectangle3D() = default;
            Rectangle3D(math::Point3D origin, math::Vector3D bottom_side, math::Vector3D left_side) : origin(origin), bottom_side(bottom_side), left_side(left_side) {}
            math::Point3D origin;
            math::Vector3D bottom_side;
            math::Vector3D left_side;
            math::Point3D pointAt(double u, double v) {
                math::Point3D point;
                point.x = origin.x + (bottom_side.x * u) + (left_side.x * v);
                point.y = origin.y + (left_side.y * v) + (bottom_side.y * u);
                point.z = origin.z + (left_side.z * v) + (bottom_side.z * u);
                return point;
            }
    };
}