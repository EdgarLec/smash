#include "Include.hpp"

void Player::choose_action(Window &win)
{
    switch (action_type) {
        case NONE: return;
        case NEUTRAL: attack_normal(win); return;
        case LEFT: left_attack(win); return;
        case RIGHT: right_attack(win); return;
        case UP:
            break;
        case DOWN: down_attack(win); return;
        case NEUTRAL_AIR: neutral_air(win); return;
        case LEFT_AIR:
            break;
        case RIGHT_AIR:
            break;
        case UP_AIR:
            break;
        case DOWN_AIR:
            break;
        default:
            break;
    }
}

void Player::attack(bool touch)
{
    sf::Joystick joy;
    int tmp = 1;
    if (!joy.isConnected(nb_joystick) || busy > 0)
        return;
    float side = joy.getAxisPosition(nb_joystick, sf::Joystick::X);
    float up = joy.getAxisPosition(nb_joystick, sf::Joystick::Y);
    if (fabs(side) <= 15.0)
        side = 0;
    if (fabs(up) <= 15.0)
        up = 0;
    if (fabs(up) > fabs(side)) {
        side = 0;
    } else
        up = 0;
    if (touch)
        tmp += 5;
    if (fabs(vector.x) > 30)
        return;
    if (up == 0) {
        if (side == 0) {
            action_type = tmp;
        } else if (side > 0) {
            action_type = tmp + 1;
        } else
            action_type = tmp + 2;
    } else if (up < 0)
        action_type = tmp + 3;
    else
        action_type = tmp + 4;
}

void Player::Joystick_move(Window &win)
{
    sf::Joystick joy;
    if (!joy.isConnected(nb_joystick))
        return;
    float side = joy.getAxisPosition(nb_joystick, sf::Joystick::X) / 100.0 * 6;
    if (fabs(side) <= 1)
        side = 0;
    if (can_move == 0) {
        if (side == 0)
            vector.x *= pow(0.005, time / 10.0);
        return;
    }
    if ((side < 0 && side * (10 / 3.0 * 2) < vector.x) ||
    (side > 0 && side * (10 / 3.0 * 2) > vector.x))
        vector.x += side * time;
    if (!sprite_touch_wall(win, {0, 0.1})) {
        if (joy.isButtonPressed(nb_joystick, 1))
            attack(1);
        choose_action(win);
        if ((joy.isButtonPressed(nb_joystick, 2) ||
        joy.isButtonPressed(nb_joystick, 3)) && jump == 1) {
            vector.x += side / 6.0 * 15;
            vector.y = -60;
            jump--;
        }
        return;
    }
    if (joy.isButtonPressed(nb_joystick, 1))
        attack(0);
    if (side == 0)
        vector.x *= pow(0.005, time / 10.0);
    if (joy.isButtonPressed(nb_joystick, 2) || joy.isButtonPressed(nb_joystick, 3))
        vector.y = -60;
    choose_action(win);
}

void Player::zqsd_move(Window &win)
{
    sf::Joystick joy;

    Joystick_move(win);
    if (joy.isConnected(0) || can_move == 0)
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        vector.y = -50 + percent / 100 * -100;
        vector.x = -50 + percent / 100 * -100;
        is_fly = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        vector.x -= vector.x < -40 ? 0 : 6 * time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        vector.x += vector.x > 40 ? 0 : 6 * time;
    if (!sprite_touch_wall(win, {0, 0.1})) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                vector.x -= 15;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                vector.x += 15;
            vector.y = -55;
            jump--;
        }
        return;
    }
    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
    || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        vector.x *= pow(0.005, time / 10.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        vector.y = -55;
}
