#ifndef INCLUDE_H
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <math.h>
    #include "player.hpp"
    #include "Window.hpp"
    #include "light.hpp"
    #include "particle.hpp"
    #include <iostream>
    #define INCLUDE_H


    #define PI 3.14159265

sf::Vector2f angle_to_vector(float angle);

void PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float fBias
, float *fOutput);
float perlin_noise(int seed, int x, int y);
double interpolated_noise(int i, double x, double y);
double ValueNoise_2D(int rand, double x, double y, int num_octaves);

static const int player_lim[6] {
    4,
    3,
    8,
    8,
    4
};

#endif