/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** RayTracer
*/

#pragma once
#include "math/Point3D.hpp"
#include "Rectangle3D.hpp"
#include <iostream>

namespace RayTracer {
    class Ray {
        public:
            math::Point3D origin;
            math::Vector3D direction;
            Ray() = default;
            Ray(math::Point3D origin, math::Vector3D direction) : origin(origin), direction(direction) {}
            Ray(const Ray &other) : origin(other.origin), direction(other.direction) {}
            void operator=(const Ray &other) {
                origin = other.origin;
                direction = other.direction;
            }

            math::Point3D at(double t) const {
                return origin + direction * t;
            }
            
            math::Vector3D normalized() {
                double length = direction.length();
                return math::Vector3D(direction.x / length, direction.y / length, direction.z / length);
            }
    };
    class Camera {
        public:
            math::Point3D origin;
            math::Vector3D direction;
            double fov;
            double aspect_ratio;
            Rectangle3D screen;

            Camera(math::Point3D origin, math::Vector3D direction, double fov, double aspect_ratio) : origin(origin), direction(direction), fov(fov), aspect_ratio(aspect_ratio) {
                double viewport_height = 2.0 * tan((fov * M_PI / 180.0) / 2.0);
                double viewport_width = viewport_height * aspect_ratio;

                math::Vector3D forward = direction.normalized();
                math::Vector3D up = math::Vector3D(0, 1, 0);
                math::Vector3D right = forward.cross(up).normalized();
                up = right.cross(forward);

                math::Point3D screen_center = origin + forward;
                math::Vector3D horizontal = right * viewport_width;
                math::Vector3D vertical = up * viewport_height;
                math::Point3D screen_origin = screen_center - horizontal * 0.5 - vertical * 0.5;

                screen = Rectangle3D{screen_origin, horizontal, vertical};
            }

            RayTracer::Ray ray(double u, double v) {
                RayTracer::Ray ray;
                ray.origin = origin;
                math::Point3D point = screen.pointAt(u, v);
                math::Vector3D direction = point - origin;
                ray.direction = direction;
                return ray;
            }
    };
    
}
