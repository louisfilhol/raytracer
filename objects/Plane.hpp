/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Plane
*/

#pragma once
#include "../math/Point3D.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"
#include "IShape.hpp"

namespace shapes {
    class Plane : public IShape {
        public:
            math::Point3D point;
            math::Vector3D normal;

            Plane() = default;
            Plane(math::Point3D point, math::Vector3D normal) : point(point), normal(normal.normalized()) {}
            Plane(math::Point3D point, math::Vector3D normal, std::shared_ptr<RayTracer::IMaterial> material) 
                : IShape(material), point(point), normal(normal.normalized()) {}

            bool hits(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &rec) const override {
                double denom = normal.dot(ray.direction);

                if (fabs(denom) < 1e-8)
                    return false;
                    
                double t = normal.dot(point - ray.origin) / denom;

                if (t < tMin || t > tMax)
                    return false;

                rec.t = t;
                rec.point = ray.at(t);
                rec.setFaceNormal(ray, normal);
                rec.material = _material;
                
                return true;
            }
    };
}
