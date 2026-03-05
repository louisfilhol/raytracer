/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** FlatColor
*/

#pragma once
#include "IMaterial.hpp"
#include "Color3.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"
#include "../scene/Scene.hpp"
#include "../lights/AmbientLight.hpp"
#include "../lights/DirectionalLight.hpp"
#include <limits>
#include <algorithm>

namespace RayTracer {
    class FlatColor : public IMaterial {
        private:
            Color3 _color;
            
        public:
            FlatColor() : _color(Color3(1, 1, 1)) {}
            FlatColor(const Color3& color) : _color(color) {}
            FlatColor(double r, double g, double b) : _color(Color3(r, g, b)) {}

            const Color3& getColor() const { return _color; }
            void setColor(const Color3& color) { _color = color; }

            Color3 shade(const Ray& ray, const HitRecord& rec, const Scene& scene) const override {
                (void)ray;
                Color3 accumulatedColor(0, 0, 0);
                Color3 baseObjectColor = _color;

                for (const auto& light_ptr : scene.getLights()) {
                    Color3 lightIntensity = light_ptr->getIntensity();

                    if (dynamic_cast<const AmbientLight*>(light_ptr.get())) {
                        accumulatedColor += baseObjectColor * lightIntensity;
                    } else if (dynamic_cast<const DirectionalLight*>(light_ptr.get())) {
                        math::Vector3D lightVector = light_ptr->getDirection(rec.point);
                        
                        math::Vector3D vector_towards_light = lightVector.normalized();

                        math::Point3D shadowRayOrigin = rec.point + rec.normal * 1e-4;
                        RayTracer::Ray shadowRay(shadowRayOrigin, vector_towards_light);

                        if (!scene.isShadowed(shadowRay, std::numeric_limits<double>::infinity())) {
                            double NdotL = std::max(0.0, rec.normal.dot(vector_towards_light));
                            accumulatedColor += baseObjectColor * lightIntensity * NdotL;
                        }
                    }
                }
                return accumulatedColor.clamp();
            }
    };
}
