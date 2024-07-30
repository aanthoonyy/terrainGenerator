#include "perlinNoise.hpp"
#include <math.h>

float interpolate(float a0, float a1, float w) {
    return (a1 - a0) * (3 - w * 2.0) * w * w + a0;
}

vector2 randomGradient(int ix, int iy, int seed) {
    
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix + seed, b = iy + seed;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); 

    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float dotGridGradient(int ix, int iy, float x, float y, int seed) {
	vector2 gradient = randomGradient(ix, iy, seed);

    float dx = x - (float)ix;
    float dy = y - (float)iy;

    return (dx * gradient.x + dy * gradient.y);

}


float perlin(float x, float y, int seed) {

    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0 = dotGridGradient(x0, y0, x, y, seed);
    float n1 = dotGridGradient(x1, y0, x, y, seed);
    float ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y, seed);
    n1 = dotGridGradient(x1, y1, x, y, seed);
    float ix1 = interpolate(n0, n1, sx);

    float value = interpolate(ix0, ix1, sy);

    return value;

}

void renderPerlin() {
    const int windowWidth = 1920;
    const int windowHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "perlin");

    sf::Uint8* pixels = new sf::Uint8[windowWidth * windowHeight * 4];

    const int GRID_SIZE = 16;

    for (int x = 0; x < windowWidth; x++) {

        for (int y = 0; y < windowHeight; y++) {
            int index = (y * windowWidth + x) * 4;

            float val = 0;

            float freq = 0.01;

            float amp = 3;

            for (int i = 0; i < 12; i++) {
                val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE, 999999) * amp;

                freq *= 1.5;
                amp /= 2;
            }
            val *= 1.2;

            if (val > 1.0f) {
                val = 1.0f;
            }
            else if (val < -1.0f) {
                val = -1.0f;
            }

            int color = (int)(((val + 1.0f) * 0.5f) * 255);

            pixels[index] = color;
            pixels[index + 1] = (136, 200, 56);
            pixels[index + 2] = color;
            pixels[index + 3] = 255;

        }
    }
    sf::Texture texture;
    sf::Sprite sprite;

    texture.create(windowWidth, windowHeight);

    texture.update(pixels);

    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);

        window.display();
    }
}
