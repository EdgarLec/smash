#include "Include.hpp"
#define COO(x, y) map[(x) + (y) * 320]

sf::Vector2f norm(sf::Vector2f vector)
{
    float w = sqrt(vector.x * vector.x + vector.y * vector.y);
    vector.x /= w;
    vector.y /= w;
    return vector;
}

sf::Vector2f rotate(sf::Vector2f center, sf::Vector2f rt, float angle)
{
    float p_angle = angle * (PI / 180);
    float s = sin(p_angle);
    float c = cos(p_angle);
    float xnew;
    float ynew;

    rt.x -= center.x;
    rt.y -= center.y;
    xnew = rt.x * c - rt.y * s;
    ynew = rt.x * s + rt.y * c;
    rt.x = xnew + center.x;
    rt.y = ynew + center.y;
    return rt;
}

void Light::lunch_lines(sf::Vector2f p_pos, float intens, sf::Uint8 alpha)
{
    sf::Vector2f dir;

    for (int i = 0; i < indexs; i++) {
        if (i > 0 && i + 1 < indexs && fabs(angles[i].angle -
        angles[i + 1].angle) < 0.0001)
            continue;
        if (angles[i].is_triple == 1) {
            dir = angles[i].coo;
            find_wall(p_pos, rotate(p_pos, dir, -0.0005), intens, alpha);
            find_wall(p_pos, dir, intens, alpha);
            find_wall(p_pos, rotate(p_pos, dir, 0.0005), intens, alpha);
        } else
            find_wall(p_pos, angles[i].coo, intens, alpha);
    }
    find_wall(p_pos, rotate(p_pos, angles->coo, -0.00001), intens, alpha);
}

void Light::sort_angle(sf::Vector2f p_pos)
{
    sf::Vector2f tmp;
    float o;
    float h;

    for (int i = 0; i < indexs; i++) {
        tmp = angles[i].coo;
        o = fabs(p_pos.x - tmp.x);
        h = sqrtf(powf(p_pos.x - tmp.x, 2) + powf(p_pos.y - tmp.y, 2));
        angles[i].angle = asinf(o / h);
        if (p_pos.y < tmp.y && p_pos.x <= tmp.x) {
            angles[i].angle = PI - angles[i].angle;
            continue;
        }
        if (p_pos.y < tmp.y && p_pos.x >= tmp.x) {
            angles[i].angle += PI;
        } else if (p_pos.y >= tmp.y && p_pos.x >= tmp.x)
            angles[i].angle = 2 * PI - angles[i].angle;
    }
    size_t radix[2] = {sizeof(dir_t), size_t(indexs)};
    radix_sort(angles, radix, (size_t)&((dir_t *)0)->angle, buffer);
}

float Light::loop_find_wall(float intens, sf::Vector2f steps[3], sf::Vector2f mapcheck)
{
    float dis = 0.0;
    sf::Vector2f vstep = steps[0];
    sf::Vector2f v_ray_step = steps[1];
    sf::Vector2f v_raylen = steps[2];

    while (dis <= intens * 2) {
        if (v_raylen.x < v_raylen.y) {
            mapcheck.x += vstep.x;
            dis = v_raylen.x;
            v_raylen.x += v_ray_step.x;
        } else {
            mapcheck.y += vstep.y;
            dis = v_raylen.y;
            v_raylen.y += v_ray_step.y;
        }
        if (mapcheck.x >= 0 && mapcheck.x < 320 && mapcheck.y >= 0 && mapcheck.y < 240 && COO(
        (int)mapcheck.x, (int)mapcheck.y) != -1)
            break;
    }
    return dis;
}
