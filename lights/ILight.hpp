/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** ILight
*/

#pragma once
#include "../math/Vector3D.hpp"
#include "../materials/Color3.hpp"

namespace RayTracer {
    class ILight {
        public:
            virtual ~ILight() = default;
            
            virtual Color3 getIntensity() const = 0;
            virtual math::Vector3D getDirection(const math::Point3D& point) const = 0;
    };
}
