#ifndef PARTICLE_H
    #define PARTICLE_H
    #include <utility>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>

class Particle
{
private:
    sf::Vector2f scale;
    float life_time;
    sf::Vector2f vector;
    int random_seed;

public:
    sf::Vector2f pos;
    bool was_busy;

    Particle(sf::Vector2f pos, sf::Vector2f dir, float speed, int random);
    void move(float time);

    sf::Vector2f get_pos() {return pos;}
    sf::Vector2f get_scale() {
        if (life_time < 0.25)
            return sf::Vector2f(scale.x / 3.0, scale.y / 3.0);
        if (life_time < 0.5)
            return sf::Vector2f(scale.x / 3.0 * 2, scale.y / 3.0 * 2);
        return scale;
    }
    void set_scale(sf::Vector2f scale) {this->scale = scale;}
    float get_life_time() {return life_time;}
};

#endif