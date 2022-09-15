#include "Include.hpp"
#include "player.hpp"
#include "Window.hpp"
#include <vector>

void change_day(Window &win, sf::Joystick &joy, int nb_joystick)
{
    if (joy.isButtonPressed(nb_joystick, 5) && win.am)
        win.day += 0.01;
    if (joy.isButtonPressed(nb_joystick, 5) && !win.am)
        win.day -= 0.01;
    if (win.day > 1) {
        win.day = 1;
        win.am = false;
    }
    if (win.day < 0) {
        win.day = 0;
        win.am = true;
    }
}

void Player::anim(Window &win)
{
    sf::Joystick joy;

    sprite.setColor(sf::Color(80 + 175 * win.day, 80 + 175 * win.day, 100 + 155 * win.day));
    if (!joy.isConnected(nb_joystick))
        return;
    float side = joy.getAxisPosition(nb_joystick, sf::Joystick::X) / 100.0 * 6;
    change_day(win, joy, nb_joystick);
    rect_nb = 0;
    if (fabs(side) <= 1)
        side = 0;
    if (side == 0) {
        player_rect->top = player_rect->top >= 120 ? 120 : 0;
    } else if (side < 0)
        player_rect->top = 0;
    else
        player_rect->top = 120;
    if (fabs(vector.x) > 1.5 && sprite_touch_wall(win, {0, 0.1})) {
        rect_nb = 2;
        player_rect->top += 48;
        if (fabs(vector.x) > 13)
            player_rect->top += 24;
    } else if (!sprite_touch_wall(win, {0, 0.1})) {
        rect_nb = 4;
        player_rect->top += 96;
    }
    if (action_type == 1) {
        player_rect->top = player_rect->top >= 120 ? 144 : 24;
        rect_nb = 1;
    }
    if (clock_anim->getElapsedTime().asMilliseconds() / 1000.0 >= 0.10) {
        player_rect->left += 24;
        player_rect->left %= player_lim[rect_nb] * 24;
        clock_anim->restart();
    }
    player_rect->left %= player_lim[rect_nb] * 24;
    sprite.setTextureRect(*player_rect);
}