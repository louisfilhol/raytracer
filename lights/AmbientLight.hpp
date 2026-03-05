/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** AmbientLight
*/

#pragma once
#include "ILight.hpp"

namespace RayTracer {
    class AmbientLight : public ILight {
        private:
            Color3 _intensity;
            
        public:
            AmbientLight(const Color3& intensity)
                : _intensity(intensity) {}
            
            Color3 getIntensity() const override {
                return _intensity;
            }
            
            math::Vector3D getDirection(const math::Point3D& point) const override {
                (void)point;
                return math::Vector3D(0, 0, 0);
            }
    };
}
