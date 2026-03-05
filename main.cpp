/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include "RayTracer.hpp"
#include "objects/Sphere.hpp"
#include "objects/Cube.hpp"
#include "objects/Plane.hpp"
#include "objects/Cylinder.hpp"
#include "objects/Cone.hpp"
#include "objects/IShape.hpp"
#include "materials/FlatColor.hpp"
#include "materials/Color3.hpp"
#include "HitRecord.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneParser.hpp"
#include "ppmConverter.hpp"

void printUsage(const char* programName)
{
    std::cerr << "USAGE: " << programName << " <SCENE_FILE> [--liverender]" << std::endl;
    std::cerr << "SCENE_FILE: scene configuration" << std::endl;
    std::cerr << "--liverender: optional flag to display rendering progress live" << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 2 || ac > 3) {
        printUsage(av[0]);
        return 84;
    }

    std::string sceneFilePath;
    bool liveRender = false;

    for (int i = 1; i < ac; ++i) {
        std::string arg = av[i];
        if (arg == "--liverender") {
            liveRender = true;
        } else if (sceneFilePath.empty()) {
            sceneFilePath = arg;
        } else {
            printUsage(av[0]);
            return 84;
        }
    }

    if (sceneFilePath.empty()) {
        std::cerr << "Error: Scene file not specified." << std::endl;
        printUsage(av[0]);
        return 84;
    }
    
    if (!std::filesystem::exists(sceneFilePath)) {
        std::cerr << "Error: File '" << sceneFilePath << "' does not exist." << std::endl;
        return 84;
    }

    std::unique_ptr<RayTracer::Scene> scene;
    try {
        RayTracer::SceneParser parser(sceneFilePath);
        scene = parser.parse();
    } catch (const std::exception& e) {
        std::cerr << "Error parsing scene file: " << e.what() << std::endl;
        return 84;
    }
    
    auto resolution = scene->getResolution();
    unsigned int windowWidth = static_cast<unsigned int>(resolution.first);
    unsigned int windowHeight = static_cast<unsigned int>(resolution.second);
    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "RayTracer", sf::Style::Default);
    window.setFramerateLimit(30);
    window.setPosition(sf::Vector2i((desktopMode.width - windowWidth) / 2, (desktopMode.height - windowHeight) / 2));
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Rendering scene..." << std::endl;
    } else {
        sf::Text loadingText("Rendering scene... (Press ESC to exit)", font, 24);
        loadingText.setFillColor(sf::Color::White);
        loadingText.setPosition(20, 20);
        window.clear();
        window.draw(loadingText);
        window.display();
    }
    scene->render(window, liveRender);
    window.display();

    std::string inputFilename(sceneFilePath);
    std::string outputFilename = "raytracer_output.ppm";
    
    size_t lastSlash = inputFilename.find_last_of("/\\");
    size_t lastDot = inputFilename.find_last_of(".");
    if (lastSlash != std::string::npos && lastDot != std::string::npos && lastDot > lastSlash) {
        std::string baseName = inputFilename.substr(lastSlash + 1, lastDot - lastSlash - 1);
        outputFilename = baseName + ".ppm";
    }
    
    convert_to_ppm::save(window, outputFilename);

    std::cout << "Rendering complete. Press ESC to exit." << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        sf::sleep(sf::milliseconds(50));
    }

    return 0;
}