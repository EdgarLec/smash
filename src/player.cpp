#include "Include.hpp"
#include "player.hpp"
#include "Window.hpp"
#include <vector>

Player::Player():
    vector(0, 0),
    percent(50),
    jump(1),
    nb_joystick(0),
    is_fly(0)
{
    sf::Texture *img = new sf::Texture;

    can_move = 1;
    clock_anim = new sf::Clock;
    player_rect = new sf::IntRect(0, 0, 24, 24);
    img->loadFromFile("assets/fighter1.png", sf::IntRect(0, 0, 192, 240));
    rect_nb = 0;
    action_type = 0;
    busy = 0;
    sprite.setTexture(*img);
    sprite.setTextureRect(*player_rect);
    sprite.setScale(4.5, 4.5);
    sprite.setPosition(sf::Vector2f(400, 300));
    sprite.setOrigin(sf::Vector2f(12, 12));
    sprite.setColor(sf::Color(255, 255, 255, 255));
    damage.setFillColor(sf::Color::Green);
    damage.setSize(sf::Vector2f(13.5, 13.5));
    damage.setOrigin(sf::Vector2f(6.25, 6.25));
    damage.setPosition(sf::Vector2f(50, 50));
}

int Player::sprite_touch_wall(Window &win, sf::Vector2f offset)
{
    sf::FloatRect rect = sprite.getGlobalBounds();
    sf::FloatRect rect_block;
    rect_list wall = win.get_wall();

    rect.top += 10;
    rect.height -= 10;

    rect.left += 20;
    rect.width -= 40;

    rect.top += offset.y;
    rect.left += offset.x;

    for (auto &block : wall) {
        rect_block = block.getGlobalBounds();
        if (rect.intersects(rect_block))
            return 1;
    }
    return 0;
}

void Player::move_player(Window &win)
{
    contact(win);

    sprite.move((vector.x) * time, (vector.y) * time);
    sf::Vector2f vec = {0, 0};
    float tmp = sqrt(powf(vector.x, 2) + powf(vector.y, 2));
    int i = 0;

    if (tmp != 0) {
        vec.x = vector.x / tmp;
        vec.y = vector.y / tmp;
    }
    for (i = 0; sprite_touch_wall(win, {0, 0}); i++) {
        sprite.move(-vec.x / 10.0, -vec.y / 10.0);
    }
    if (is_fly && sprite_touch_wall(win, {0, 0})) {
        vector.x *= 0.7;
        vector.y *= -0.7;
        busy = 1;
        sprite.move((vector.x) * time / 10 * i, -(vector.y) * time / 10 * i);
        action_type = WAIT;
        is_fly = 0;
        return;
    }
    if (is_fly && sprite_touch_wall(win, {0, 0.1})) {
        action_type = WAIT;
        busy = 1;
        is_fly = 0;
        return;
    }
}

void Player::gravity(Window &win)
{
    time = clock.restart().asMilliseconds() / 100.0;

    if (sprite_touch_wall(win, {0, 0.1})) {
        vector.y = 0;
        jump = 2;
        return;
    }
    if (sprite_touch_wall(win, {0, -0.1})) {
        vector.y = 0;
        return;
    }
    float tmp = vector.y;
    vector.y += 10 * time;
    if ((tmp <= -15 && vector.y > -15 && jump == 2) || (tmp <= 0 && vector.y
    > 0 && jump == 2))
        jump = 1;
}

void Player::air_resistance(void)
{
    float tmp = vector.y;
    vector.x *= powf(0.5, time / 10.0);
    if (vector.x < 0.1 && vector.x > -0.1)
        vector.x = 0;
    vector.y *= powf(0.5, time / 10.0);

    if (tmp <= -15 && vector.y > -15 && jump == 2)
        jump = 1;
}

void Player::contact(Window &win)
{
    sprite.move(0.1, 0);
    if (sprite_touch_wall(win, {0.1, 0})) {
        sprite.move(-0.1, 0);
        vector.x = 0;
        return;
    }
    sprite.move(-0.2, 0);
    if (sprite_touch_wall(win, {-0.1, 0})) {
        sprite.move(0.1, 0);
        vector.x = 0;
        return;
    }
    sprite.move(0.1, 0);
}