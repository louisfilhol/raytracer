#pragma once

#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"
#include "IShape.hpp"
#include <cmath>
#include <limits>

namespace shapes {
    class Cylinder : public IShape {
    public:
        math::Point3D axisPoint;
        math::Vector3D axisDirection;
        double radius;

        Cylinder() = default;
        Cylinder(math::Point3D p, math::Vector3D dir, double r, std::shared_ptr<RayTracer::IMaterial> mat = nullptr)
            : IShape(mat), axisPoint(p), axisDirection(dir.normalized()), radius(r) {}

        bool hits(const RayTracer::Ray& ray, double tMin, double tMax, RayTracer::HitRecord& rec) const override {
            math::Vector3D co = ray.origin - axisPoint;

            math::Vector3D a_prime = ray.direction - axisDirection * ray.direction.dot(axisDirection);
            math::Vector3D b_prime = co - axisDirection * co.dot(axisDirection);

            double a = a_prime.dot(a_prime);
            double b = 2.0 * a_prime.dot(b_prime);
            double c = b_prime.dot(b_prime) - radius * radius;

            double discriminant = b * b - 4.0 * a * c;

            if (discriminant < 0) {
                return false;
            }

            double sqrt_discriminant = std::sqrt(discriminant);
            double t0 = (-b - sqrt_discriminant) / (2.0 * a);
            double t1 = (-b + sqrt_discriminant) / (2.0 * a);

            double t_hit = -1.0;

            if (t0 > tMin && t0 < tMax) {
                t_hit = t0;
            }
            if (t1 > tMin && t1 < tMax) {
                if (t_hit < 0 || t1 < t_hit) {
                    t_hit = t1;
                }
            }
            
            double root = -1.0;
            if (t0 > tMin && t0 < tMax) {
                root = t0;
            }
            if (t1 > tMin && t1 < tMax) {
                if (root < 0 || t1 < root) {
                    root = t1;
                }
            }

            if (root < 0) {
                if (t0 > tMin && t0 < tMax) root = t0;
                else if (t1 > tMin && t1 < tMax) root = t1;
                else return false;
            }


            if (root < tMin || root > tMax) {
                if (t0 > tMin && t0 < tMax && (t1 < tMin || t1 > tMax || t0 < t1) ) root = t0;
                else if (t1 > tMin && t1 < tMax && (t0 < tMin || t0 > tMax || t1 < t0) ) root = t1;
                else return false;
            }
            
            double t_smallest = std::numeric_limits<double>::infinity();
            bool hit_found = false;

            if (t0 >= tMin && t0 <= tMax) {
                t_smallest = t0;
                hit_found = true;
            }
            if (t1 >= tMin && t1 <= tMax) {
                if (t1 < t_smallest) {
                    t_smallest = t1;
                    hit_found = true;
                }
            }

            if (!hit_found) {
                return false;
            }
            
            if (std::abs(a) < 1e-8) {
                if (c > 0) return false;
            }


            rec.t = t_smallest;
            rec.point = ray.at(rec.t);

            math::Vector3D hit_to_axis_point = rec.point - axisPoint;
            double projection = hit_to_axis_point.dot(axisDirection);
            math::Point3D point_on_axis = axisPoint + axisDirection * projection;
            math::Vector3D outwardNormal = (rec.point - point_on_axis).normalized();
            
            rec.setFaceNormal(ray, outwardNormal);
            rec.material = _material;
            return true;
        }
    };
} 