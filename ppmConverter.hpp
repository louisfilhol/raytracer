/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** ppmConverter
*/

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class convert_to_ppm
{
    public:
        static void save(const sf::RenderWindow& window, const std::string& filename);

};

void convert_to_ppm::save(const sf::RenderWindow& window, const std::string& filename)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(window);
    sf::Image screenshot = texture.copyToImage();

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    outFile << "P3" << std::endl;
    outFile << windowSize.x << " " << windowSize.y << std::endl;
    outFile << "255" << std::endl;

    for (unsigned int y = 0; y < windowSize.y; ++y) {
        for (unsigned int x = 0; x < windowSize.x; ++x) {
            sf::Color pixel = screenshot.getPixel(x, y);
            outFile << static_cast<int>(pixel.r) << " "
                   << static_cast<int>(pixel.g) << " "
                   << static_cast<int>(pixel.b) << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
    std::cout << "Image saved to " << filename << std::endl;
}