#ifndef WINDOW_h
    #define WINDOW_h
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <math.h>
typedef std::vector<sf::RectangleShape> rect_list;

class Player;
class Particle;
class Light;

class Window : public sf::RenderWindow
{
private:
    sf::Vertex vrtx;
    sf::VertexArray *arr_vrtx;
    rect_list wall;
    sf::RectangleShape damage;
    sf::RectangleShape ptcl;
    sf::Clock *clock;
    float time_clk;
    int random_seed;
    int last_fog;
    float *fog;
    int off;
    std::vector<float> move;
    sf::Sprite *back;

public:
    Window(sf::VideoMode mode, std::string name, sf::Uint8 style);
    ~Window();

    float day;
    bool am;
    Light *light;

    std::vector<Particle> particles;
    sf::RenderTexture txtr;
    sf::RenderTexture final;
    sf::RenderTexture light_render;
    sf::Sprite sprite;
    sf::Sprite final_sprite;
    sf::RenderWindow win;
    rect_list get_wall() {return wall;}
    sf::RectangleShape get_damage() {return damage;}
    void draw_sprite(sf::Sprite sprite);
    void draw_rect(sf::RectangleShape rect);
    void draw_wall(void);
    void up_next(int i, bool up);
    void damage_pl(Player &player);
    void draw_fog(void);

    void draw_particle(float busy, sf::RectangleShape dammage);
};

#endif
