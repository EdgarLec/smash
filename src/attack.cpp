#include "Include.hpp"
#include "player.hpp"
#include "Window.hpp"
#include <vector>

void Player::attack_normal(Window &win)
{
    sf::Vector2f ori;
    if (busy < 0) {
        can_move = 0;
        busy = 3;
        damage.setOrigin(6.25, 6.25);
        damage.setPosition(sprite.getPosition());
        relative_pos = {0, 0};
    }
    busy -= time;
    damage.setPosition(sprite.getPosition());
    ori = damage.getOrigin();
    if (player_rect->top >= 120) {
        ori.x -= time * 20;
    } else {
        ori.x = fabs(ori.x) + time * 20;
    }
    damage.setOrigin(ori);

    if (busy < 0) {
        can_move = 1;
        action_type = NONE;
    }
}

void Player::neutral_air(Window &win)
{
    sf::Vector2f ori;
    float angle = 70;

    if (busy < 0)
        busy = 8;
    busy -= time;
    if (busy < 0) {
        action_type = 0;
    }
    if (busy > 7.5 || busy < 4.5)
        return;
    damage.setOrigin(6.25, 6.25);
    damage.setPosition(sprite.getPosition());
    relative_pos = {0, 0};
    ori = angle_to_vector(angle + (7.5 - busy) / 3.0 * 360);
    ori.x = ori.x * 50 + 8;
    ori.y = ori.y * 50 + 8;
    damage.setOrigin(ori);
}

void Player::left_attack(Window &win)
{
    if (busy < 0) {
        can_move = 0;
        busy = 7;
        damage.setScale(1, 1);
        damage.setOrigin(60, 6.25);
        damage.setPosition(sprite.getPosition());
        relative_pos = {0, 0};
    }
    busy -= time;
    if (busy >= 3) {
        damage.setScale(1, 5);
        if (is_fly == 0)
            vector.x = -40;
        damage.setPosition(sprite.getPosition());
    } else {
        vector.x *= pow(0.7, time);
        damage.setScale(1, 1);
    }
    if (busy < 0 || is_fly == 1) {
        busy = -1;
        damage.setScale(1, 1);
        can_move = 1;
        action_type = NONE;
    }
}

void Player::right_attack(Window &win)
{
    if (busy < 0) {
        can_move = 0;
        busy = 7;
        damage.setScale(1, 1);
        damage.setOrigin(-60 + 6.25, 6.25);
        damage.setPosition(sprite.getPosition());
        relative_pos = {0, 0};
    }
    busy -= time;
    if (busy >= 3) {
        vector.x *= pow(0.7, time);
        damage.setScale(1, 5);
        if (is_fly == 0)
            vector.x = 40;
        damage.setPosition(sprite.getPosition());
    } else {
        vector.x *= pow(0.7, time);
        damage.setScale(1, 1);
    }
    if (busy < 0 || is_fly == 1) {
        busy = -1;
        damage.setScale(1, 1);
        can_move = 1;
        action_type = NONE;
    }
}


void Player::down_attack(Window &win)
{
    sf::Vector2f coo;

    if (busy < 0) {
        can_move = 0;
        busy = 10;
        damage.setScale(1, 1);
        damage.setOrigin(6.25, 50);
        damage.setPosition(sprite.getPosition());
        relative_pos = {0, 0};
    }
    busy -= time;
    if (busy >= 5) {
        damage.setScale((5 - (busy - 5)) * 1.3 + 1, 1);
        coo = sprite.getPosition();
        coo.y += 90;
        damage.setPosition(coo);
    } else {
        vector.x *= pow(0.7, time);
        damage.setScale(1, 1);
    }
    if (busy < 0 || is_fly == 1) {
        busy = -1;
        damage.setScale(1, 1);
        can_move = 1;
        action_type = NONE;
    }
}