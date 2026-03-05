/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** IShape
*/

#pragma once
#include "../math/Matrix4x4.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"
#include "../materials/IMaterial.hpp"
#include <memory>

namespace shapes {
    class IShape {
        protected:
            std::shared_ptr<RayTracer::IMaterial> _material;
            
        public:
            IShape() : _material(nullptr) {}
            IShape(std::shared_ptr<RayTracer::IMaterial> material) : _material(material) {}
            virtual ~IShape() = default;

            std::shared_ptr<RayTracer::IMaterial> getMaterial() const { return _material; }
            void setMaterial(std::shared_ptr<RayTracer::IMaterial> material) { _material = material; }
            virtual bool hits(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &rec) const = 0;
    };
}
