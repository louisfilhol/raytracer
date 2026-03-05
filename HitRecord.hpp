/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** HitRecord
*/

#pragma once
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"
#include <memory>

namespace RayTracer {
    class IMaterial;
    struct HitRecord {
        double t;
        math::Point3D point;
        math::Vector3D normal;
        std::shared_ptr<IMaterial> material;
        bool frontFace;

        HitRecord() : t(0), point(), normal(), material(nullptr), frontFace(false) {}

        inline void setFaceNormal(const RayTracer::Ray& ray, const math::Vector3D& outwardNormal) {
            frontFace = ray.direction.dot(outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
    };
}
