#include "perlinNoise.hpp"
#include <math.h>





float interpolate(float a0, float a1, float w) {
    // cubic interpolation method
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}



// hashing function
vector2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float dotGridGradient(int ix, int iy, float x, float y) {
	// get gradient from integer coordinates
	vector2 gradient = randomGradient(ix, iy);

    // compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // return dot-product
    return (dx * gradient.x + dy * gradient.y);

}


float perlin(float x, float y) {

    // finding grid cell corner values
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // compute interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // compute and interpolate top two corners
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    //compute and interpolate bottom two corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    float value = interpolate(ix0, ix1, sy);

    return value;

}
