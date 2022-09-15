#include "Include.hpp"
#include "player.hpp"
#include "Window.hpp"
#include <vector>

void Window::draw_sprite(sf::Sprite sprite)
{
    sf::Vector2u size = getSize();
    float offset = (size.x - (size.y / 1080.0) * 1440.0) / 2.0;
    const sf::Vector2f factor = sprite.getScale();
    const sf::Vector2f pos = sprite.getPosition();

    sprite.setScale(size.y / 1080.0 * factor.x, size.y / 1080.0 * factor.y);
    sprite.setPosition(offset + (pos.x * size.y / 1080.0), pos.y * size.y / 1080.0);
    draw(sprite);
    sprite.setScale(factor);
    sprite.setPosition(pos);
}

void Window::draw_rect(sf::RectangleShape rect)
{
    sf::Vector2u size = getSize();
    float offset = (size.x - (size.y / 1080.0) * 1440.0) / 2;
    const sf::Vector2f factor = rect.getScale();
    const sf::Vector2f pos = rect.getPosition();

    rect.setScale(size.y / 1080.0 * factor.x, size.y / 1080.0 * factor.y);
    rect.setPosition(offset + (pos.x * size.y / 1080.0), pos.y * size.y / 1080.0);
    draw(rect);
    rect.setScale(factor);
    rect.setPosition(pos);
}
