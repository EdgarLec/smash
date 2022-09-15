#ifndef LIGHT_T
    #define LIGHT_T
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <math.h>

typedef struct dir_t {
    float angle;
    sf::Vector2f coo;
    int is_triple;
} dir_t;

class Light
{
private:
    sf::Vertex vrtx;
    sf::VertexArray *arr_vrtx;
    dir_t *angles;
    dir_t *buffer;
    int indexs;
    void draw_line(sf::Vector2f p_pos, sf::Vector2f vraydir, float dis);
    void find_wall(sf::Vector2f p_pos, sf::Vector2f p_dir, float intens, sf::Uint8 alpha);
    void lunch_lines(sf::Vector2f p_pos, float intens, sf::Uint8 alpha);
    void sort_angle(sf::Vector2f p_pos);
    float loop_find_wall(float intens, sf::Vector2f steps[3], sf::Vector2f mapcheck);
    void find_angles(int i, int j);
    void find_angle_n(int i, int j, int l);
    void wall_light(void);

public:
    Light();
    ~Light();
    sf::RenderStates state;
    int map[320 * 240];
    void add_light(sf::Vector2f pos, float intens, sf::RenderTexture &win, sf::Color clr);
    void update_wall(void);

};

sf::Vector2f norm(sf::Vector2f vector);
sf::Vector2f rotate(sf::Vector2f center, sf::Vector2f rt, float angle);

void radix_sort(void *toSort2, size_t sizes[2],
size_t offset_in_struct, void *buffer2);

#endif