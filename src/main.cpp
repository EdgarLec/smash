#include "Include.hpp"
#include "player.hpp"
#include "Window.hpp"
#include <vector>

void manage_keayboard(sf::Event &ev, Window &win, Player &player)
{
    if (ev.key.code == sf::Keyboard::Escape)
        win.close();
}

void manage_mouse_release(sf::Event &ev, Window &win, Player &player)
{
}

void poll_window_events(Window &win, Player &player)
{
    sf::Event ev;

    while (win.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            win.close();
        if (ev.type == sf::Event::KeyPressed)
            manage_keayboard(ev, win, player);
        if (ev.type == sf::Event::MouseButtonReleased || ev.type == sf::Event::
        MouseButtonPressed)
            manage_mouse_release(ev, win, player);
    }
}

void get_table_light(Window &win, Player player)
{
    sf::Sprite sprite = player.get_sprite();

    win.light_render.clear(sf::Color::White);
    rect_list wall = win.get_wall();
    for (auto block : wall) {
        block.setPosition(block.getPosition().x / 4.5, block.getPosition().y / 4.5);
        block.setScale(1, 1);
        block.setFillColor(sf::Color::Black);
        win.light_render.draw(block);
    }
    sprite.setPosition(sprite.getPosition().x / 4.5, sprite.getPosition().y / 4.5);
    sprite.setScale(0.4, 0.4);
    sprite.setColor(sf::Color::Black);
    win.light_render.draw(sprite);
    win.light_render.display();
    memcpy(win.light->map, win.light_render.getTexture().copyToImage().getPixelsPtr(),
    320 * 240 * 4);
    win.light->update_wall();
    float life;
    for (std::size_t i = 0; i < win.particles.size(); i += 1) {
        life = win.particles[i].get_life_time();
        win.light->add_light(win.particles[i].pos, 10 * (life * 0.3 + 0.7), win.final,
        sf::Color(30, 20 * life + 10, 6 * life + 6, 155 * (1 - win.day) + 100));
    }
    win.light->add_light(sf::Vector2f(720, 0), 250, win.final, sf::Color(50, 50, 40));
    win.final.display();
}

void draw_window(Window &win, Player player)
{
    win.clear(sf::Color::Black);
    win.txtr.clear(sf::Color(70, 111, 117, 255));
    win.draw_fog();
    // win.txtr.draw(player.damage);
    win.draw_particle(player.get_busy(), player.damage);
    win.draw_wall();
    player.anim(win);
    win.txtr.draw(player.get_sprite());
    win.txtr.draw(win.get_damage());
    win.txtr.display();
    win.final.clear(sf::Color::Black);
    win.sprite.setTexture(win.txtr.getTexture());
    win.sprite.setColor(sf::Color(255, 255, 255, 255));
    win.final.draw(win.sprite);
    win.light->state.texture = &win.txtr.getTexture();
    get_table_light(win, player);
    win.final_sprite.setTexture(win.final.getTexture());
    win.draw_sprite(win.final_sprite);
    win.display();
}

void game_loop(Window &win, Player &player)
{
    player.gravity(win);
    player.zqsd_move(win);
    player.air_resistance();
    win.damage_pl(player);
    player.choose_action(win);
    player.move_player(win);
}

int main(void)
{
    Window window(sf::VideoMode::getDesktopMode(), "Smash", sf::Style::Default);
    Player player;

    for (int i = 0; window.isOpen(); i++) {
        game_loop(window, player);
        draw_window(window, player);
        poll_window_events(window, player);
    }
}
