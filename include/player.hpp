#ifndef PLAYER_H
    #define PLAYER_H
    #include <utility>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>

class Window;

    #define WAIT RIGHT
enum action_type {
    NONE, NEUTRAL, RIGHT, LEFT, UP, DOWN, NEUTRAL_AIR, LEFT_AIR, RIGHT_AIR, UP_AIR, DOWN_AIR
};

class Player
{
private:
    sf::Vector2f vector;
    sf::Vector2f relative_pos;
    sf::Sprite sprite;

    sf::Clock clock;
    sf::Clock *clock_anim;

    int can_move;
    int action_type;
    float time;
    float percent;
    int jump;
    int nb_joystick;
    int attack_type;
    int rect_nb;
    sf::IntRect *player_rect;
    float busy;

public:
    Player();
    int is_fly;
    sf::RectangleShape damage;

    sf::Vector2f get_vector() {return vector;}
    void set_vector(sf::Vector2f coo) {vector = coo;}
    float get_percent() {return percent;}
    sf::Sprite get_sprite() {return sprite;}

    // physic on player
    void gravity(Window &win);
    void air_resistance(void);
    void contact(Window &win);
    int sprite_touch_wall(Window &win, sf::Vector2f offset);

    // move player
    void zqsd_move(Window &win);
    void Joystick_move(Window &win);
    void move_player(Window &win);

    // attack handler
    void attack(bool touch);
    void choose_action(Window &win);

    // diff attack
    void attack_normal(Window &win);
    void neutral_air(Window &win);
    void left_attack(Window &win);
    void right_attack(Window &win);
    void down_attack(Window &win);

    float get_busy() {return busy;}

    // animation
    void anim(Window &win);
};

#endif
