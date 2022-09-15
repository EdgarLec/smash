#include "Include.hpp"
#include "player.hpp"
#include "Window.hpp"
#include <vector>


sf::Vector2f angle_to_vector(float angle)
{
    sf::Vector2f vector;

    vector.x = cos(angle / 180.0 * PI);
    vector.y = sin(angle / 180.0 * PI);
    return (vector);
}