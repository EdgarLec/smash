#include "Include.hpp"
#include "Window.hpp"
#include "player.hpp"
#include "particle.hpp"
#include <vector>

Particle::Particle(sf::Vector2f pos, sf::Vector2f dir, float speed, int random)
{
    this->pos = pos;
    this->pos.x += ((rand() / (float)RAND_MAX) * 2 - 1) * 5;
    this->pos.y += ((rand() / (float)RAND_MAX) * 2 - 1) * 5;
    this->life_time = (rand() / (float)RAND_MAX) * 0.3 + 0.7;
    dir.x = rand() / (float)RAND_MAX - 0.5;
    dir.y = rand() / (float)RAND_MAX - 0.5;
    this->vector = dir * speed;
}

void Particle::move(float time)
{
    float tmp = fabs(vector.x / 20.0);

    pos -= vector * float(time * 10.0);
    if (vector.x > 0)
        vector.x -= tmp;
    else
        vector.x += tmp;
    vector.y += tmp;
    tmp = fabs(vector.y / 20.0);
    if (vector.y > 0)
        vector.y -= tmp;
    else
        vector.y += tmp;
    scale.x -= scale.x > 1 ? time * 20.0 : scale.x - 1;
    scale.y -= scale.y > 1 ? time * 20.0 : scale.y - 1;
    vector.y += tmp;
    life_time -= time;
}

void Window::draw_particle(float busy, sf::RectangleShape dammage)
{
    sf::Vector2f pos = dammage.getPosition() - dammage.getOrigin() +
    sf::Vector2f(6.25, 6.25);
    int i = 0;
    static float tmp = 0;
    tmp += time_clk * 30;

    ptcl.setSize(sf::Vector2f(3, 3));
    ptcl.setOrigin(1.5, 1.5);

    for (int i = 0; i < (int)tmp; i++) {
        particles.push_back(Particle(pos, sf::Vector2f(0, 1), 15, random_seed));
        if (busy > 0) {
            particles.back().was_busy = true;
            particles.back().set_scale(dammage.getScale());
        } else {
            particles.back().was_busy = false;
            particles.back().set_scale(sf::Vector2f(1, 1));
        }
    }
    tmp -= int(tmp);
    for (auto &particle : particles) {
        ptcl.setPosition(particle.get_pos());
        ptcl.setFillColor(sf::Color(200, 90 * particle.get_life_time() + 90,
        40 * particle.get_life_time() + 40, 255));
        ptcl.setScale(particle.get_scale());
        ptcl.scale(4.5, 4.5);
        particle.move(time_clk);
        txtr.draw(ptcl);
        if (particle.get_life_time() < 0)
            particles.erase(particles.begin() + i--);
        i++;
    }
}