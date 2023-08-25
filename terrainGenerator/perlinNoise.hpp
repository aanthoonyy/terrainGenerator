#pragma once
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
typedef struct {
    float x, y;
} vector2;

vector2 randomGradient(int ix, int iy);

float interpolate(float a0, float a1, float w);
float dotGridGradient(int ix, int iy, float x, float y);
float perlin(float x, float y);
void renderPerlin();
void returnPerlin();