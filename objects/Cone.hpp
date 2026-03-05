#pragma once

#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"
#include "../RayTracer.hpp"
#include "../HitRecord.hpp"
#include "IShape.hpp"
#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace shapes {
    class Cone : public IShape {
    public:
        math::Point3D tip;
        math::Vector3D axisDirection;
        double angle;
        double cos_angle;
        double cos_sq_angle;

        Cone() = default;
        Cone(math::Point3D t, math::Vector3D dir, double ang_degrees, std::shared_ptr<RayTracer::IMaterial> mat = nullptr)
            : IShape(mat), tip(t), axisDirection(dir.normalized()), angle(ang_degrees) {
            double angle_rad = angle * M_PI / 180.0;
            cos_angle = std::cos(angle_rad);
            cos_sq_angle = cos_angle * cos_angle;
        }

        bool hits(const RayTracer::Ray& ray, double tMin, double tMax, RayTracer::HitRecord& rec) const override {
            math::Vector3D co = ray.origin - tip;

            double co_dot_axis = co.dot(axisDirection);
            double ray_dir_dot_axis = ray.direction.dot(axisDirection);

            double a = ray_dir_dot_axis * ray_dir_dot_axis - cos_sq_angle * ray.direction.dot(ray.direction);
            double b = 2.0 * (co_dot_axis * ray_dir_dot_axis - cos_sq_angle * co.dot(ray.direction));
            double c = co_dot_axis * co_dot_axis - cos_sq_angle * co.dot(co);

            double discriminant = b * b - 4.0 * a * c;

            if (discriminant < 0) {
                return false;
            }

            double sqrt_discriminant = std::sqrt(discriminant);
            double t0 = (-b - sqrt_discriminant) / (2.0 * a);
            double t1 = (-b + sqrt_discriminant) / (2.0 * a);

            double t_smallest = std::numeric_limits<double>::infinity();
            bool hit_found = false;

            if (t0 >= tMin && t0 <= tMax) {
                if ((co_dot_axis + t0 * ray_dir_dot_axis) >= 0) {
                    t_smallest = t0;
                    hit_found = true;
                }
            }
            if (t1 >= tMin && t1 <= tMax) {
                if ((co_dot_axis + t1 * ray_dir_dot_axis) >= 0) {
                     if (!hit_found || t1 < t_smallest) {
                        t_smallest = t1;
                        hit_found = true;
                    }
                }
            }

            if (!hit_found) {
                return false;
            }

            rec.t = t_smallest;
            rec.point = ray.at(rec.t);

            math::Vector3D U = rec.point - tip;
            double m = U.dot(axisDirection);
            math::Vector3D outwardNormal = ( axisDirection * U.dot(axisDirection) - U * cos_sq_angle ).normalized();
            rec.setFaceNormal(ray, outwardNormal); 
            rec.material = _material;
            return true;
        }
    };
} 