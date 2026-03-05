/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** SceneParser
*/

#pragma once
#include <string>
#include <memory>
#include <libconfig.h++>
#include "Scene.hpp"
#include "../RayTracer.hpp"

namespace shapes {
    class IShape;
    class Sphere;
    class Plane;
    class Cube;
    class Cylinder;
    class Cone;
}
#include "../materials/Color3.hpp"
#include "../materials/FlatColor.hpp"

namespace RayTracer {
    class SceneParser {
        private:
            libconfig::Config _config;
            std::string _configFile;
            
            math::Point3D parsePoint3D(const libconfig::Setting& setting);
            math::Vector3D parseVector3D(const libconfig::Setting& setting);
            Color3 parseColor3(const libconfig::Setting& setting);
            std::unique_ptr<shapes::IShape> parseSphere(const libconfig::Setting& setting);
            std::unique_ptr<shapes::IShape> parsePlane(const libconfig::Setting& setting);
            std::unique_ptr<shapes::IShape> parseCylinder(const libconfig::Setting& setting);
            std::unique_ptr<shapes::IShape> parseCone(const libconfig::Setting& setting);
            std::shared_ptr<IMaterial> parseMaterial(const libconfig::Setting& setting);
            void parsePrimitives(Scene& scene, const libconfig::Setting& primitives);
            void parseLights(Scene& scene, const libconfig::Setting& lights);
            void parseCamera(Scene& scene, const libconfig::Setting& camera);
            
        public:
            SceneParser(const std::string& configFile);
            ~SceneParser() = default;
            
            std::unique_ptr<Scene> parse();
    };
}
