#include "Include.hpp"
#define COO(x, y) map[(x) + (y) * 320]

void Light::find_angle_n(int i, int j, int l)
{
    for (int k = -1; k != 3; k += 2) {
        if (i + l < 320 && i + l >= 0 && j + k < 240 && j + k >= 0 &&
        COO(i + l, j) == COO(i, j + k)) {
            angles[indexs].coo = sf::Vector2f((i + (l == 1)),
            (j + (k == 1)));
            angles[indexs].is_triple = 1;
            indexs++;
        }
    }
}

void Light::find_angles(int i, int j)
{
    if (COO(i, j) == -1)
        return;
    for (int l = -1; l != 3; l += 2)
        find_angle_n(i, j, l);
}

void Light::wall_light(void)
{
    sf::Vector2f first = {18, 1000};
    sf::Vector2f center = {320 / 2.0, 240 / 2.0};

    for (float i = 0; i < 360; i += 15) {
        angles[indexs].coo = rotate(center, first, i);
        angles[indexs].is_triple = 0;
        indexs++;
    }
}