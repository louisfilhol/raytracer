/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** Scene
*/

#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../objects/IShape.hpp"
#include "../lights/ILight.hpp"
#include "../lights/DirectionalLight.hpp"
#include "../lights/AmbientLight.hpp"
#include "../RayTracer.hpp"

namespace RayTracer {
    class Scene {
        private:
            std::vector<std::unique_ptr<shapes::IShape>> _shapes;
            std::vector<std::unique_ptr<ILight>> _lights;
            Camera _camera;
            std::pair<double, double> _resolution;
            Color3 _backgroundColor;
            
        public:
            Scene(Camera camera, std::pair<double, double> resolution);
            ~Scene() = default;
            
            void addShape(std::unique_ptr<shapes::IShape> shape);
            void addLight(std::unique_ptr<ILight> light);
            
            void setBackgroundColor(const Color3& color);
            const Color3& getBackgroundColor() const;
            
            Camera& getCamera();
            std::pair<double, double> getResolution() const;
            
            const std::vector<std::unique_ptr<ILight>>& getLights() const;
            
            Color3 traceRay(const Ray& ray, double min_t, double max_t, int depth = 0) const;

            bool isShadowed(const RayTracer::Ray& shadowRay, double distanceToLight) const;

            void render(sf::RenderWindow& window, bool liveRender = false);
    };
}
