#include "Include.hpp"

sf::Vector2f step(sf::Vector2f *vstep, sf::Vector2f vraydir
, sf::Vector2f p_pos, sf::Vector2f v_ray_step)
{
    sf::Vector2f v_raylen;

    if (vraydir.x < 0) {
        vstep->x = -1;
        v_raylen.x = ((p_pos.x) - (int)p_pos.x) * v_ray_step.x;
    } else {
        vstep->x = 1;
        v_raylen.x = ((int)(p_pos.x + 1.0) - p_pos.x) * v_ray_step.x;
    }
    if (vraydir.y < 0) {
        vstep->y = -1;
        v_raylen.y = ((p_pos.y) - (int)p_pos.y) * v_ray_step.y;
    } else {
        vstep->y = 1;
        v_raylen.y = ((int)(p_pos.y + 1.0) - p_pos.y) * v_ray_step.y;
    }
    return v_raylen;
}

void Light::draw_line(sf::Vector2f p_pos, sf::Vector2f vraydir, float dis)
{
    sf::Vector2f vinter = sf::Vector2f(p_pos.x + vraydir.x * dis, p_pos.y + vraydir.y *
    dis);
    vinter.x *= 4.5;
    vinter.y *= 4.5;
    vrtx.position = vinter;
    vrtx.texCoords = vinter;
    arr_vrtx->append(vrtx);
}

void Light::find_wall(sf::Vector2f p_pos, sf::Vector2f p_dir, float intens, sf::Uint8 alpha)
{
    sf::Vector2f r_dir = norm(p_dir - p_pos);
    sf::Vector2f v_ray_step = {sqrt(1 + (r_dir.y / r_dir.x) * (r_dir.y /
    r_dir.x)), sqrt(1 + (r_dir.x / r_dir.y) * (r_dir.x / r_dir.y))};
    sf::Vector2f mapcheck = p_pos;
    sf::Vector2f vstep;
    sf::Vector2f v_raylen = step(&vstep, r_dir, p_pos, v_ray_step);
    sf::Vector2f tmp[3] = {vstep, v_ray_step, v_raylen};
    float dis = loop_find_wall(intens, tmp, mapcheck);

    dis = (dis > intens * 2) ? intens * 2 : dis;
    vrtx.color.a = (alpha - (dis / 2) / intens * alpha);
    draw_line(p_pos, r_dir, dis);
}

void Light::add_light(sf::Vector2f pos, float intens, sf::RenderTexture &win, sf::Color clr)
{
    sf::Vector2f p_pos = sf::Vector2f((float)(pos.x) / 4.5, (float)(pos.y) / 4.5);

    vrtx.position = pos;
    vrtx.texCoords = pos;
    vrtx.color = clr;
    arr_vrtx->append(vrtx);
    sort_angle(p_pos);
    lunch_lines(p_pos, intens, clr.a);
    win.draw(*arr_vrtx, state);
    arr_vrtx->clear();
}

void Light::update_wall(void)
{
    indexs = 0;
    for (int i = 0; i < 320; i++)
        for (int j = 0; j < 240; j++)
            find_angles(i, j);
    wall_light();
}