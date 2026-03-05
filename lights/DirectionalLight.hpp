/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** DirectionalLight
*/

#pragma once
#include "ILight.hpp"

namespace RayTracer {
    class DirectionalLight : public ILight {
        private:
            math::Vector3D _direction;
            Color3 _intensity;
            
        public:
            DirectionalLight(const math::Vector3D& direction, const Color3& intensity)
                : _direction(direction.normalized()), _intensity(intensity) {}
            
            Color3 getIntensity() const override {
                return _intensity;
            }
            
            math::Vector3D getDirection(const math::Point3D& point) const override {
                (void)point;
                return -_direction;
            }
    };
}
