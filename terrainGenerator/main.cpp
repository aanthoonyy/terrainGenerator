#include <SFML/Graphics.hpp>
#include "renderCube.hpp"
#include "perlinNoise.hpp"
#include <iostream>







int main()
{
	//renderMap();
    const int GRID_SIZE = 16;

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            float normalizedX = (float)x / GRID_SIZE;
            float normalizedY = (float)y / GRID_SIZE;

            float val = perlin(normalizedX, normalizedY); 

            std::cout << "value at (" << normalizedX << ", " << normalizedY << "): " << val << std::endl;
        }
    }


    renderMap();
}

