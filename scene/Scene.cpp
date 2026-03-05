/*
** EPITECH PROJECT, 2025
** B-OOP-400-MPL-4-1-raytracer-louis.filhol-valantin
** File description:
** Scene
*/

#include "Scene.hpp"
#include "../HitRecord.hpp"

namespace RayTracer {
    Scene::Scene(Camera camera, std::pair<double, double> resolution)
        : _camera(camera), _resolution(resolution), _backgroundColor(Color3(0, 0, 0))
    {
    }

    void Scene::addShape(std::unique_ptr<shapes::IShape> shape)
    {
        _shapes.push_back(std::move(shape));
    }

    void Scene::addLight(std::unique_ptr<ILight> light)
    {
        _lights.push_back(std::move(light));
    }

    void Scene::setBackgroundColor(const Color3& color)
    {
        _backgroundColor = color;
    }

    const Color3& Scene::getBackgroundColor() const
    {
        return _backgroundColor;
    }

    Camera& Scene::getCamera()
    {
        return _camera;
    }

    std::pair<double, double> Scene::getResolution() const
    {
        return _resolution;
    }

    const std::vector<std::unique_ptr<ILight>>& Scene::getLights() const
    {
        return _lights;
    }

    Color3 Scene::traceRay(const Ray& ray, double min_t, double max_t, int depth) const
    {
        (void)depth;

        HitRecord final_rec;
        bool hit_anything = false;
        double closest_so_far = max_t;

        for (const auto& shape_ptr_unique : _shapes) {
            HitRecord current_rec;
            if (shape_ptr_unique->hits(ray, min_t, closest_so_far, current_rec)) {
                hit_anything = true;
                closest_so_far = current_rec.t;
                final_rec = current_rec;
            }
        }

        if (hit_anything) {
            if (final_rec.material) {
                return final_rec.material->shade(ray, final_rec, *this);
            } else {
                return Color3(1.0, 0.0, 1.0);
            }
        } else {
            return _backgroundColor;
        }
    }

    bool Scene::isShadowed(const RayTracer::Ray& shadowRay, double distanceToLight) const
    {
        HitRecord tempShadowRec;
        for (const auto& shape : _shapes) {
            if (shape->hits(shadowRay, 1e-4, distanceToLight, tempShadowRec)) {
                return true;
            }
        }
        return false;
    }

    void Scene::render(sf::RenderWindow& window, bool liveRender)
    {
        auto windowSize = window.getSize();
        
        sf::Image image;
        image.create(windowSize.x, windowSize.y, sf::Color::Black);
        
        sf::Texture texture;
        texture.create(windowSize.x, windowSize.y);
        sf::Sprite sprite;
        
        const int BATCH_SIZE = 20;
        
        for (unsigned int j = 0; j < windowSize.y; j += BATCH_SIZE) {
            for (unsigned int i = 0; i < windowSize.x; i++) {
                for (unsigned int batchJ = j; batchJ < std::min(j + BATCH_SIZE, windowSize.y); batchJ++) {
                    double u = static_cast<double>(i) / windowSize.x;
                    double v = static_cast<double>(batchJ) / windowSize.y;
                    Ray r = _camera.ray(u, v);
                    Color3 pixelColor = traceRay(r, 0.001, INFINITY);
                    Color3 color8bit = pixelColor.to8bit();
                    sf::Color color(color8bit.r, color8bit.g, color8bit.b);
                    image.setPixel(i, batchJ, color);
                }
            }
            texture.update(image);
            sprite.setTexture(texture, true);
            
            window.clear();
            window.draw(sprite);

            if (liveRender) {
                window.display();

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                        window.close();
                }
                if (!window.isOpen()) {
                    return;
                }
            }
        }

        texture.update(image);
        sprite.setTexture(texture, true);
        window.clear();
        window.draw(sprite);
    }
}
