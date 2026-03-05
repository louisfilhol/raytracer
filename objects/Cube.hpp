/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Cube
*/

#pragma once
#include "../math/Point3D.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"
#include "IShape.hpp"

namespace shapes {
    class Cube : public IShape {
        public:
            math::Point3D center;
            double size;

            Cube() = default;
            Cube(math::Point3D center, double size) : center(center), size(size) {}
            Cube(math::Point3D center, double size, std::shared_ptr<RayTracer::IMaterial> material) 
                : IShape(material), center(center), size(size) {}

            bool hits(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &rec) const override {
                double tmin = tMin, tmax = tMax;
                double half = size / 2.0;
                double bounds[2][3] = {
                    {center.x - half, center.y - half, center.z - half},
                    {center.x + half, center.y + half, center.z + half}
                };
                
                int hitAxis = -1;
                bool hitPositiveFace = false;

                for (int i = 0; i < 3; ++i) {
                    double origin = (&ray.origin.x)[i];
                    double dir = (&ray.direction.x)[i];
                    
                    if (fabs(dir) < 1e-8) {
                        if (origin < bounds[0][i] || origin > bounds[1][i])
                            return false;
                        continue;
                    }
                    
                    double invD = 1.0 / dir;
                    double t0 = (bounds[0][i] - origin) * invD;
                    double t1 = (bounds[1][i] - origin) * invD;
                    
                    if (invD < 0.0) std::swap(t0, t1);

                    if (t0 > tmin) {
                        tmin = t0;
                        hitAxis = i;
                        hitPositiveFace = (dir < 0);
                    }
                    
                    tmax = t1 < tmax ? t1 : tmax;
                    
                    if (tmax <= tmin)
                        return false;
                }
                
                if (tmin < tMin || tmin > tMax)
                    return false;
                
                rec.t = tmin;
                rec.point = ray.at(tmin);
                
                math::Vector3D outwardNormal(0, 0, 0);
                if (hitAxis == 0) {
                    outwardNormal.x = hitPositiveFace ? 1 : -1;
                } else if (hitAxis == 1) {
                    outwardNormal.y = hitPositiveFace ? 1 : -1;
                } else {
                    outwardNormal.z = hitPositiveFace ? 1 : -1;
                }
                
                rec.setFaceNormal(ray, outwardNormal);
                rec.material = _material;
                
                return true;
            }
    };
}
