/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** Color3
*/

#pragma once

namespace RayTracer {
    class Color3 {
        public:
            double r, g, b;

            Color3() : r(0), g(0), b(0) {}
            Color3(double r, double g, double b) : r(r), g(g), b(b) {}
            Color3(const Color3& other) : r(other.r), g(other.g), b(other.b) {}

            Color3& operator=(const Color3& other) {
                if (this == &other)
                    return *this;
                r = other.r;
                g = other.g;
                b = other.b;
                return *this;
            }

            Color3 operator+(const Color3& other) const {
                return Color3(r + other.r, g + other.g, b + other.b);
            }

            Color3 operator*(const Color3& other) const {
                return Color3(r * other.r, g * other.g, b * other.b);
            }

            Color3 operator*(double scalar) const {
                return Color3(r * scalar, g * scalar, b * scalar);
            }

            void operator+=(const Color3& other) {
                r += other.r;
                g += other.g;
                b += other.b;
            }

            void operator*=(const Color3& other) {
                r *= other.r;
                g *= other.g;
                b *= other.b;
            }

            void operator*=(double scalar) {
                r *= scalar;
                g *= scalar;
                b *= scalar;
            }

            Color3 clamp() const {
                return Color3(
                    r < 0 ? 0 : (r > 1 ? 1 : r),
                    g < 0 ? 0 : (g > 1 ? 1 : g),
                    b < 0 ? 0 : (b > 1 ? 1 : b)
                );
            }

            Color3 to8bit() const {
                return Color3(r * 255, g * 255, b * 255);
            }
    };
}
