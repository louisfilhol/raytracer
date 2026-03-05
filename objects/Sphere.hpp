/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Sphere
*/

#include "IShape.hpp"
#include "../math/Point3D.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"

namespace shapes {
    class Sphere : public IShape {
        public:
            math::Point3D center;
            double radius;

            Sphere() = default;
            Sphere(math::Point3D center, double radius) : center(center), radius(radius) {}
            Sphere(math::Point3D center, double radius, std::shared_ptr<RayTracer::IMaterial> material) 
                : IShape(material), center(center), radius(radius) {}

            double getdistance(math::Point3D &point) {
                return sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2) + pow(point.z - center.z, 2));
            }

            bool hits(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &rec) const override {
                math::Vector3D oc = ray.origin - center;
                double a = ray.direction.dot(ray.direction);
                double half_b = oc.dot(ray.direction);
                double c = oc.dot(oc) - radius * radius;

                double discriminant = half_b*half_b - a*c;
                if (discriminant < 0)
                    return false;

                double sqrtd = sqrt(discriminant);

                double root = (-half_b - sqrtd) / a;
                if (root < tMin || root > tMax) {
                    root = (-half_b + sqrtd) / a;
                    if (root < tMin || root > tMax)
                        return false;
                }

                rec.t = root;
                rec.point = ray.at(rec.t);
                math::Vector3D outwardNormal = (rec.point - center) / radius;
                rec.setFaceNormal(ray, outwardNormal);
                rec.material = _material;

                return true;
            }
    };
}
