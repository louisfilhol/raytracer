/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include <iostream>
#include <stdexcept>
#include "../objects/Sphere.hpp"
#include "../objects/Plane.hpp"
#include "../objects/Cylinder.hpp"
#include "../objects/Cone.hpp"

namespace RayTracer {
    SceneParser::SceneParser(const std::string& configFile)
        : _configFile(configFile)
    {
    }
    
    math::Point3D SceneParser::parsePoint3D(const libconfig::Setting& setting)
    {
        double x = 0.0, y = 0.0, z = 0.0;
        try {
            if (setting.exists("x"))
                x = setting["x"];
            if (setting.exists("y"))
                y = setting["y"];
            if (setting.exists("z"))
                z = setting["z"];
        } catch (const libconfig::SettingTypeException& e) {
            std::cerr << "Type error in point coordinates: " << e.what() << std::endl;
        }
        return math::Point3D(x, y, z);
    }
    
    math::Vector3D SceneParser::parseVector3D(const libconfig::Setting& setting)
    {
        double x = 0.0, y = 0.0, z = 0.0;
        try {
            if (setting.exists("x"))
                x = setting["x"];
            if (setting.exists("y"))
                y = setting["y"];
            if (setting.exists("z"))
                z = setting["z"];
        } catch (const libconfig::SettingTypeException& e) {
            std::cerr << "Type error in vector coordinates: " << e.what() << std::endl;
        }
        return math::Vector3D(x, y, z);
    }
    
    Color3 SceneParser::parseColor3(const libconfig::Setting& setting)
    {
        double r = 0.0, g = 0.0, b = 0.0;
        try {
            if (setting.exists("r"))
                r = static_cast<double>(static_cast<int>(setting["r"])) / 255.0;
            if (setting.exists("g"))
                g = static_cast<double>(static_cast<int>(setting["g"])) / 255.0;
            if (setting.exists("b"))
                b = static_cast<double>(static_cast<int>(setting["b"])) / 255.0;
        } catch (const libconfig::SettingTypeException& e) {
            std::cerr << "Type error in color values: " << e.what() << std::endl;
        }
        return Color3(r, g, b);
    }

    std::shared_ptr<IMaterial> SceneParser::parseMaterial(const libconfig::Setting& setting)
    {
        if (setting.exists("color")) {
            Color3 color = parseColor3(setting["color"]);
            return std::make_shared<FlatColor>(color.r, color.g, color.b);
        }
        return std::make_shared<FlatColor>(1.0, 1.0, 1.0);
    }
    
    std::unique_ptr<shapes::IShape> SceneParser::parseSphere(const libconfig::Setting& setting)
    {
        try {
            math::Point3D center = parsePoint3D(setting);
            double radius = setting.exists("r") ? static_cast<double>(setting["r"]) : 1.0;
            std::shared_ptr<IMaterial> material = parseMaterial(setting);
            
            return std::make_unique<shapes::Sphere>(center, radius, material);
        } catch (const libconfig::SettingNotFoundException& nfex) {
            std::cerr << "Missing setting in sphere: " << nfex.getPath() << std::endl;
            throw;
        }
    }
    
    std::unique_ptr<shapes::IShape> SceneParser::parsePlane(const libconfig::Setting& setting)
    {
        try {
            math::Point3D point(0, 0, 0);
            math::Vector3D normal(0, 0, 1);
            
            if (setting.exists("axis") && setting.exists("position")) {
                std::string axisStr;
                try {
                    const char* axisChar = setting["axis"];
                    axisStr = std::string(axisChar);
                    axisStr = axisStr.substr(0, 1);
                    double position = setting["position"];
                    
                    if (axisStr == "X" || axisStr == "x") {
                        point = math::Point3D(position, 0, 0);
                        normal = math::Vector3D(1, 0, 0);
                    } else if (axisStr == "Y" || axisStr == "y") {
                        point = math::Point3D(0, position, 0);
                        normal = math::Vector3D(0, 1, 0);
                    } else if (axisStr == "Z" || axisStr == "z") {
                        point = math::Point3D(0, 0, position);
                        normal = math::Vector3D(0, 0, 1);
                    } else {
                        std::cerr << "Invalid axis for plane: " << axisStr << ", defaulting to Z" << std::endl;
                        point = math::Point3D(0, 0, position);
                        normal = math::Vector3D(0, 0, 1);
                    }
                } catch (const libconfig::SettingTypeException& e) {
                    std::cerr << "Error parsing plane axis or position: " << e.what() << std::endl;
                }
            } else {
                if (setting.exists("point"))
                    point = parsePoint3D(setting["point"]);
                if (setting.exists("normal"))
                    normal = parseVector3D(setting["normal"]);
            }
            
            std::shared_ptr<IMaterial> material = parseMaterial(setting);
            return std::make_unique<shapes::Plane>(point, normal, material);
        } catch (const std::exception& ex) {
            std::cerr << "Error parsing plane: " << ex.what() << std::endl;
            return std::make_unique<shapes::Plane>(
                math::Point3D(0, 0, -10), 
                math::Vector3D(0, 0, 1), 
                std::make_shared<FlatColor>(0.5, 0.5, 0.5)
            );
        }
    }
    
    std::unique_ptr<shapes::IShape> SceneParser::parseCylinder(const libconfig::Setting& setting)
    {
        try {
            math::Point3D axisPoint(0, 0, 0);
            math::Vector3D axisDirection(0, 1, 0);
            double radius = 1.0;

            if (setting.exists("axisPoint"))
                axisPoint = parsePoint3D(setting["axisPoint"]);
            if (setting.exists("axisDirection"))
                axisDirection = parseVector3D(setting["axisDirection"]);
            if (setting.exists("radius"))
                radius = setting["radius"];
            
            std::shared_ptr<IMaterial> material = parseMaterial(setting);
            return std::make_unique<shapes::Cylinder>(axisPoint, axisDirection.normalized(), radius, material);
        } catch (const std::exception& ex) {
            std::cerr << "Error parsing cylinder: " << ex.what() << std::endl;
            throw;
        }
    }

    std::unique_ptr<shapes::IShape> SceneParser::parseCone(const libconfig::Setting& setting)
    {
        try {
            math::Point3D tip(0, 0, 0);
            math::Vector3D axisDirection(0, 1, 0);
            double angle = 30.0;

            if (setting.exists("tip"))
                tip = parsePoint3D(setting["tip"]);
            if (setting.exists("axisDirection"))
                axisDirection = parseVector3D(setting["axisDirection"]);
            if (setting.exists("angle"))
                angle = setting["angle"];
            
            std::shared_ptr<IMaterial> material = parseMaterial(setting);
            return std::make_unique<shapes::Cone>(tip, axisDirection.normalized(), angle, material);
        } catch (const std::exception& ex) {
            std::cerr << "Error parsing cone: " << ex.what() << std::endl;
            throw;
        }
    }
    
    void SceneParser::parsePrimitives(Scene& scene, const libconfig::Setting& primitives)
    {
        if (primitives.exists("spheres")) {
            const libconfig::Setting& spheres = primitives["spheres"];
            for (int i = 0; i < spheres.getLength(); i++) {
                try {
                    std::unique_ptr<shapes::IShape> sphere = parseSphere(spheres[i]);
                    scene.addShape(std::move(sphere));
                } catch (const std::exception& ex) {
                    std::cerr << "Error parsing sphere at index " << i << ": " << ex.what() << std::endl;
                }
            }
        }
        
        if (primitives.exists("planes")) {
            const libconfig::Setting& planes = primitives["planes"];
            for (int i = 0; i < planes.getLength(); i++) {
                try {
                    std::unique_ptr<shapes::IShape> plane = parsePlane(planes[i]);
                    scene.addShape(std::move(plane));
                } catch (const std::exception& ex) {
                    std::cerr << "Error parsing plane at index " << i << ": " << ex.what() << std::endl;
                }
            }
        }

        if (primitives.exists("cylinders")) {
            const libconfig::Setting& cylinders = primitives["cylinders"];
            for (int i = 0; i < cylinders.getLength(); i++) {
                try {
                    std::unique_ptr<shapes::IShape> cylinder = parseCylinder(cylinders[i]);
                    scene.addShape(std::move(cylinder));
                } catch (const std::exception& ex) {
                    std::cerr << "Error parsing cylinder at index " << i << ": " << ex.what() << std::endl;
                }
            }
        }

        if (primitives.exists("cones")) {
            const libconfig::Setting& cones = primitives["cones"];
            for (int i = 0; i < cones.getLength(); i++) {
                try {
                    std::unique_ptr<shapes::IShape> cone = parseCone(cones[i]);
                    scene.addShape(std::move(cone));
                } catch (const std::exception& ex) {
                    std::cerr << "Error parsing cone at index " << i << ": " << ex.what() << std::endl;
                }
            }
        }
    }
    
    void SceneParser::parseLights(Scene& scene, const libconfig::Setting& lights)
    {
        try {
            if (lights.exists("ambient")) {
                double ambient = lights["ambient"];
                scene.addLight(std::make_unique<AmbientLight>(Color3(ambient, ambient, ambient)));
                std::cout << "Added ambient light with intensity: " << ambient << std::endl;
            } else {
                scene.addLight(std::make_unique<AmbientLight>(Color3(0.2, 0.2, 0.2)));
                std::cout << "Added default ambient light" << std::endl;
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error parsing ambient light: " << ex.what() << std::endl;
            scene.addLight(std::make_unique<AmbientLight>(Color3(0.2, 0.2, 0.2)));
        }
        
        double diffuseIntensity = 0.8;
        try {
            if (lights.exists("diffuse")) {
                diffuseIntensity = lights["diffuse"];
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error parsing diffuse intensity: " << ex.what() << std::endl;
        }
        
        bool addedDirectionalLight = false;
        if (lights.exists("directional")) {
            std::cout << "DEBUG: Found 'directional' light section." << std::endl;
            try {
                const libconfig::Setting& dirLights = lights["directional"];
                if (dirLights.isList()) {
                    std::cout << "DEBUG: 'directional' is a List with length: " << dirLights.getLength() << std::endl;
                    for (int i = 0; i < dirLights.getLength(); i++) {
                        std::cout << "DEBUG: Processing directional light item #" << i << std::endl;
                        try {
                            const libconfig::Setting& light = dirLights[i];
                            if (light.isGroup()) {
                                math::Vector3D direction = parseVector3D(light);
                                direction = direction.normalized();
                                Color3 color(diffuseIntensity, diffuseIntensity, diffuseIntensity);
                                if (light.exists("color")) {
                                    color = parseColor3(light["color"]);
                                    color = color * diffuseIntensity;
                                }
                                scene.addLight(std::make_unique<DirectionalLight>(direction, color));
                                addedDirectionalLight = true;
                                std::cout << "Added directional light from direction: (" 
                                        << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
                            } else {
                                std::cerr << "DEBUG: Item #" << i << " in 'directional' list is NOT a group." << std::endl;
                            }
                        } catch (const std::exception& ex) {
                            std::cerr << "Error parsing directional light at index " << i << ": " << ex.what() << std::endl;
                        }
                    }
                } else {
                    std::cout << "DEBUG: 'directional' is NOT a List. Type is: " << dirLights.getType() << std::endl;
                }
            } catch (const libconfig::SettingException &lcex) {
                std::cerr << "DEBUG: Libconfig setting exception in directional lights: " << lcex.what() << " Path: " << lcex.getPath() << std::endl;
            } catch (const std::exception& ex) {
                std::cerr << "Error processing directional lights array: " << ex.what() << std::endl;
            }
        } else {
            std::cout << "DEBUG: Did NOT find 'directional' light section." << std::endl;
        }
        
        if (!addedDirectionalLight) {
            scene.addLight(std::make_unique<DirectionalLight>(
                math::Vector3D(1, -1, -1).normalized(), 
                Color3(diffuseIntensity, diffuseIntensity, diffuseIntensity)
            ));
            std::cout << "Added default directional light" << std::endl;
        }
        
        if (lights.exists("point")) {
        }
    }
    
    void SceneParser::parseCamera(Scene& scene, const libconfig::Setting& cameraSetting)
    {
        math::Point3D position(0, 0, 0);
        math::Vector3D rotation(0, 0, 0);
        double fov = 72.0;
        std::pair<double, double> resolution = {1920, 1080};
        
        try {
            if (cameraSetting.exists("position")) {
                position = parsePoint3D(cameraSetting["position"]);
                std::cout << "Camera position set to: (" << position.x << ", " 
                         << position.y << ", " << position.z << ")" << std::endl;
            } else {
                std::cout << "Using default camera position (0, 0, 0)" << std::endl;
            }
            
            if (cameraSetting.exists("rotation")) {
                rotation = parseVector3D(cameraSetting["rotation"]);
                std::cout << "Camera rotation set to: (" << rotation.x << ", " 
                         << rotation.y << ", " << rotation.z << ")" << std::endl;
            } else {
                std::cout << "Using default camera rotation (0, 0, 0)" << std::endl;
            }
            
            if (cameraSetting.exists("fieldOfView")) {
                fov = cameraSetting["fieldOfView"];
                if (fov < 10.0) {
                    std::cout << "Warning: FOV too small, clamping to 10 degrees" << std::endl;
                    fov = 10.0;
                } else if (fov > 170.0) {
                    std::cout << "Warning: FOV too large, clamping to 170 degrees" << std::endl;
                    fov = 170.0;
                }
                std::cout << "Camera FOV set to: " << fov << " degrees" << std::endl;
            } else {
                std::cout << "Using default FOV of 72 degrees" << std::endl;
            }
            
            if (cameraSetting.exists("resolution")) {
                const libconfig::Setting& res = cameraSetting["resolution"];
                if (res.exists("width") && res.exists("height")) {
                    int width = res["width"];
                    int height = res["height"];
                    
                    if (width < 320) {
                        std::cout << "Warning: Width too small, clamping to 320" << std::endl;
                        width = 320;
                    } else if (width > 7680) {
                        std::cout << "Warning: Width too large, clamping to 7680" << std::endl;
                        width = 7680;
                    }
                    
                    if (height < 240) {
                        std::cout << "Warning: Height too small, clamping to 240" << std::endl;
                        height = 240;
                    } else if (height > 4320) {
                        std::cout << "Warning: Height too large, clamping to 4320" << std::endl;
                        height = 4320;
                    }
                    
                    resolution = {static_cast<double>(width), static_cast<double>(height)};
                    std::cout << "Resolution set to: " << width << "x" << height << std::endl;
                } else {
                    std::cout << "Incomplete resolution settings, using default 1920x1080" << std::endl;
                }
            } else {
                std::cout << "Using default resolution 1920x1080" << std::endl;
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error parsing camera settings: " << ex.what() << std::endl;
            std::cerr << "Using default camera settings" << std::endl;
        }
        
        math::Vector3D direction(0, 0, -1);
        
        scene.getCamera() = Camera(position, direction, fov, resolution.first / resolution.second);
    }
    
    std::unique_ptr<Scene> SceneParser::parse()
    {
        std::cout << "Parsing scene file: " << _configFile << std::endl;
        
        try {
            _config.readFile(_configFile.c_str());
            std::cout << "Scene file loaded successfully" << std::endl;
        } catch(const libconfig::FileIOException &fioex) {
            std::cerr << "Error: Cannot read configuration file " << _configFile << std::endl;
            std::cerr << "Please check file permissions and path." << std::endl;
            throw std::runtime_error("Cannot read configuration file");
        } catch(const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                      << " - " << pex.getError() << std::endl;
            std::cerr << "Please check the syntax of your scene file." << std::endl;
            throw std::runtime_error("Parse error in configuration file");
        }
        
        math::Point3D origin(0, 0, 0);
        math::Vector3D direction(0, 0, -1);
        double fov = 72.0;
        double aspect_ratio = 16.0 / 9.0;
        Camera cam(origin, direction, fov, aspect_ratio);
        std::pair<double, double> resolution = {1920, 1080};
        auto scene = std::make_unique<Scene>(cam, resolution);
        
        scene->setBackgroundColor(Color3(0.1, 0.1, 0.2));
        
        if (_config.exists("camera")) {
            std::cout << "\n[Camera Settings]" << std::endl;
            try {
                parseCamera(*scene, _config.lookup("camera"));
            } catch (const std::exception& ex) {
                std::cerr << "Error parsing camera section: " << ex.what() << std::endl;
                std::cerr << "Using default camera settings" << std::endl;
            }
        } else {
            std::cout << "No camera section found, using default settings" << std::endl;
        }
        
        if (_config.exists("primitives")) {
            std::cout << "\n[Primitives]" << std::endl;
            try {
                parsePrimitives(*scene, _config.lookup("primitives"));
            } catch (const std::exception& ex) {
                std::cerr << "Error parsing primitives section: " << ex.what() << std::endl;
                std::cerr << "Using default primitives (none)" << std::endl;
            }
        } else {
            std::cout << "No primitives section found - scene will be empty" << std::endl;
            std::cout << "Consider adding some shapes to your scene file" << std::endl;
        }
        
        if (_config.exists("lights")) {
            std::cout << "\n[Lights]" << std::endl;
            try {
                parseLights(*scene, _config.lookup("lights"));
            } catch (const std::exception& ex) {
                std::cerr << "Error parsing lights section: " << ex.what() << std::endl;
                std::cerr << "Using default lighting (ambient + directional)" << std::endl;
                
                scene->addLight(std::make_unique<AmbientLight>(Color3(0.2, 0.2, 0.2)));
                scene->addLight(std::make_unique<DirectionalLight>(
                    math::Vector3D(1, -1, -1).normalized(), 
                    Color3(0.8, 0.8, 0.8)
                ));
            }
        } else {
            std::cout << "No lights section found, adding default lighting" << std::endl;
            
            scene->addLight(std::make_unique<AmbientLight>(Color3(0.2, 0.2, 0.2)));
            scene->addLight(std::make_unique<DirectionalLight>(
                math::Vector3D(1, -1, -1).normalized(), 
                Color3(0.8, 0.8, 0.8)
            ));
        }
        
        std::cout << "\nScene parsing complete" << std::endl;
        
        return scene;
    }
}
