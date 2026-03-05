/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin [WSL: Ubuntu]
** File description:
** Matrix4x4
*/

#pragma once
#include <array>
#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace math {
    class Matrix4x4 {
    public:
        std::array<std::array<double, 4>, 4> m;

        Matrix4x4() {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = (i == j) ? 1.0 : 0.0;
        }

        static Matrix4x4 translation(double tx, double ty, double tz) {
            Matrix4x4 mat;
            mat.m[0][3] = tx;
            mat.m[1][3] = ty;
            mat.m[2][3] = tz;
            return mat;
        }

        static Matrix4x4 scale(double sx, double sy, double sz) {
            Matrix4x4 mat;
            mat.m[0][0] = sx;
            mat.m[1][1] = sy;
            mat.m[2][2] = sz;
            return mat;
        }

        static Matrix4x4 rotationY(double angleRad) {
            Matrix4x4 mat;
            double c = cos(angleRad);
            double s = sin(angleRad);
            mat.m[0][0] = c;
            mat.m[0][2] = s;
            mat.m[2][0] = -s;
            mat.m[2][2] = c;
            return mat;
        }

        Point3D apply(const Point3D& p) const {
            double x = m[0][0]*p.x + m[0][1]*p.y + m[0][2]*p.z + m[0][3];
            double y = m[1][0]*p.x + m[1][1]*p.y + m[1][2]*p.z + m[1][3];
            double z = m[2][0]*p.x + m[2][1]*p.y + m[2][2]*p.z + m[2][3];
            double w = m[3][0]*p.x + m[3][1]*p.y + m[3][2]*p.z + m[3][3];
            if (w != 0.0) {
                x /= w; y /= w; z /= w;
            }
            return Point3D(x, y, z);
        }

        Vector3D apply(const Vector3D& v) const {
            double x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z;
            double y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z;
            double z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z;
            return Vector3D(x, y, z);
        }
    };
}
