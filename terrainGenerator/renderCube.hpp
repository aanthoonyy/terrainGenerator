#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

sf::VertexArray drawIsometricCube(float isoX, float isoY, float size, int color[]);
void renderMap();
void drawTrees(sf::RenderWindow& window, float isoX, float isoY, float treeHeight);