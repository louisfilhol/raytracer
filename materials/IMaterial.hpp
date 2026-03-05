/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** IMaterial
*/

#pragma once
#include "Color3.hpp"

namespace RayTracer {
    struct HitRecord;
    class Ray;
    class Scene;

    class IMaterial {
        public:
            virtual ~IMaterial() = default;
            virtual Color3 shade(const Ray& ray, const HitRecord& rec, const Scene& scene) const = 0;
    };
}
