#include "Include.hpp"
#include "Window.hpp"
#include "player.hpp"
#include <vector>

#define NORMALIZE(vector) (vector.x /= sqrtf(pow(vector.x, 2) + pow(vector.y, 2)), vector.y /= sqrtf(pow(vector.x, 2) + pow(vector.y, 2)))

typedef std::pair<int, int> move_t;
typedef std::vector<move_t> move_list;

Window::Window(sf::VideoMode mode, std::string name, sf::Uint8 style):
    sf::RenderWindow(mode, name, style)
{
    srand(time(NULL));
    setFramerateLimit(144);
    setVerticalSyncEnabled(true);

    wall.assign(1, sf::RectangleShape(sf::Vector2f(280, 20)));
    damage.setSize(sf::Vector2f(30, 30));
    damage.setFillColor(sf::Color(255, 0, 0, 255));
    damage.setPosition(200, 410);
    damage.setOrigin(30, 15);

    move.assign(340, -20);
    arr_vrtx = new sf::VertexArray();
    arr_vrtx->setPrimitiveType(sf::Quads);
    vrtx.color = sf::Color(255, 255, 255, 50);
    random_seed = rand();
    day = 0.5;
    std::string assets[4] = {
        "assets/back/back_color.png",
        "assets/back/big_back.png",
        "assets/back/medium_back.png",
        "assets/back/small_back.png"
    };
    light = new Light();
    sf::Texture *back_txt = new sf::Texture[4];
    back = new sf::Sprite[4];
    for (int i = 0; i < 4; i++) {
        back_txt[i].loadFromFile(assets[i]);
        back[i].setTexture(back_txt[i]);
        back[i].setScale(4.5, 4.5);
    }
    am = true;
    txtr.create(1440, 1080);
    final.create(1440, 1080);
    light_render.create(320, 240);
    fog = new float[340];
    clock = new sf::Clock;
    for (last_fog = 0; last_fog < 340; last_fog++) {
        fog[339 - last_fog] = last_fog;
        move[last_fog] = last_fog * 4.5;
    }
    for (auto &block : wall) {
        block.setFillColor(sf::Color(15, 20, 5, 255));
        block.setPosition(100, 850);
        block.setScale(4.5, 4.5);
    }
}

Window::~Window()
{
}

void Window::damage_pl(Player &player)
{
    sf::Sprite sprite = player.get_sprite();
    sf::FloatRect rect = sprite.getGlobalBounds();
    static int i = 0;
    sf::FloatRect rect_block;

    rect.top += 10;
    rect.height -= 10;

    rect.left += 20;
    rect.width -= 40;

    rect_block = damage.getGlobalBounds();
    sf::Vector2f vector = sprite.getPosition() - damage.getPosition();
    NORMALIZE(vector);
    sf::Vector2f vector_tmp = vector * player.get_percent();

    vector.x = vector.x * 10;
    vector.y = vector.y * 10;

    if (i == 2) {
        i = 0;
        return;
    } else
        i++;
    if (rect.intersects(rect_block)) {
        player.set_vector(vector + vector_tmp);
        player.is_fly = 1;
    }
}

void Window::draw_wall(void)
{
    for (auto &block : wall)
        txtr.draw(block);
}

void Window::draw_fog(void)
{
    static float x = 0;
    double value;
    int tmp = 45;

    txtr.draw(back[0]);
    time_clk = clock->restart().asSeconds();
    x += time_clk / 2.0;
    for (int j = 3; j >= 0; j--) {
        arr_vrtx->clear();
        for (int i = 339; i >= 0; i--) {
            move[i] += int(time_clk * (7.5));
            if (move[i] > 1450) {
                move[i] -= 340 * 4.5;
                fog[i] = last_fog++;
            }
            value = (ValueNoise_2D(random_seed, fog[i] / 10.0, x + j / 10.0, 4) * 15);
            vrtx.position = sf::Vector2f(move[i], 240 * 4.5);
            arr_vrtx->append(vrtx);
            vrtx.position = sf::Vector2f(move[i] + 4.5, 240 * 4.5);
            arr_vrtx->append(vrtx);
            vrtx.position = sf::Vector2f(move[i] + 4.5, 4.5 * int(240 - (65 + value * (j + 1) + tmp)));
            arr_vrtx->append(vrtx);
            vrtx.position = sf::Vector2f(move[i], 4.5 * int(240 - (65 + value * (j + 1) + tmp)));
            arr_vrtx->append(vrtx);
        }
        back[3 - j].setColor(sf::Color(50 + 205 * day, 50 + 205 * day, 80 + 175 * day));
        txtr.draw(back[03 - j]);
        txtr.draw(*arr_vrtx);
        tmp = tmp - 6 * j;
    }
}

void Window::up_next(int i, bool up)
{
    int tmp = rand() % 10;

    for (int j = 0; j < tmp; j++)
        fog[(i + j) % 340] += up == 1 ? 1 : -1;
}
