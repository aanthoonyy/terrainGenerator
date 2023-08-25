#include "renderCube.hpp"
#include "perlinNoise.hpp"

sf::VertexArray drawIsometricCube(float isoX, float isoY, float size, int color[])
{
    // Define the cube's vertices in isometric coordinates
    sf::Vector2f vertices[8] = {
        sf::Vector2f(isoX, isoY),
        sf::Vector2f(isoX + size, isoY),
        sf::Vector2f(isoX + size * 0.5f, isoY - size * 0.5f),
        sf::Vector2f(isoX - size * 0.5f, isoY - size * 0.5f),

        sf::Vector2f(isoX, isoY - size),
        sf::Vector2f(isoX + size, isoY - size),
        sf::Vector2f(isoX + size * 0.5f, isoY - size * 1.5f),
        sf::Vector2f(isoX - size * 0.5f, isoY - size * 1.5f)
    };

    // Define the cube's faces using vertex indices
    sf::VertexArray cube(sf::Quads, 24);
    cube[0].position = vertices[0];
    cube[1].position = vertices[1];
    cube[2].position = vertices[5];
    cube[3].position = vertices[4];

    cube[4].position = vertices[1];
    cube[5].position = vertices[2];
    cube[6].position = vertices[6];
    cube[7].position = vertices[5];

    cube[8].position = vertices[2];
    cube[9].position = vertices[3];
    cube[10].position = vertices[7];
    cube[11].position = vertices[6];

    cube[12].position = vertices[3];
    cube[13].position = vertices[0];
    cube[14].position = vertices[4];
    cube[15].position = vertices[7];

    // top of the cube
    cube[16].position = vertices[4];
    cube[17].position = vertices[5];
    cube[18].position = vertices[6];
    cube[19].position = vertices[7];
    // bottom of cube
    cube[20].position = vertices[3];
    cube[21].position = vertices[2];
    cube[22].position = vertices[1];
    cube[23].position = vertices[0];

    // Set cube color

    sf::Color topColor(color[0] * .95, color[1] * .95, color[2] * .95);
    sf::Color frontColor(color[0], color[1], color[2]);
    sf::Color sideColor(color[0] * .85, color[1] * .85, color[2] * .85);
    sf::Color alpha(150, 150, 150);
    alpha.a = 0;

    // set top color

    cube[0].color = frontColor;
    cube[1].color = frontColor;
    cube[2].color = frontColor;
    cube[3].color = frontColor;

    cube[4].color = frontColor;
    cube[5].color = frontColor;
    cube[6].color = frontColor;
    cube[7].color = frontColor;

    cube[8].color = frontColor;
    cube[9].color = frontColor;
    cube[10].color = frontColor;
    cube[11].color = frontColor;

    cube[12].color = sideColor;
    cube[13].color = sideColor;
    cube[14].color = sideColor;
    cube[15].color = sideColor;

    cube[16].color = topColor;
    cube[17].color = topColor;
    cube[18].color = topColor;
    cube[19].color = topColor;

    cube[20].color = alpha;
    cube[21].color = alpha;
    cube[22].color = alpha;
    cube[23].color = alpha;




    //window.draw(cube);
    return cube;
}

void renderMap() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "idk");
    const int gridSize = 16;
    const float cubeSize = 20.0f;
    const float isoXStart = 350.0f;
    const float isoYStart = 100.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        float isoX = 950;
        float isoY = 0;
        int color[3] = { 16, 160, 55 };



        for (int x = 0; x < gridSize * 4; x++)
        {
            for (int y = 0; y < gridSize * 8; y++)
            {
                float normalizedX = (float)x / gridSize;
                float normalizedY = (float)y / gridSize;
                if (perlin(normalizedX, normalizedY) < 0) {
                    float offsetX = y * cubeSize * 0.25f;
                    float offsetY = x * cubeSize * 0.5f;
                    float isoPosX = isoX + offsetX - offsetY;
                    float isoPosY = isoY + offsetY + offsetX;

                    window.draw(drawIsometricCube(isoPosX, isoPosY, cubeSize, color));
                }

            }
        }

        //drawIsometricCube(isoX - 0, isoY -20, cubeSize, color); /// Every row subtract - 20 from the Y
        window.display();
    }

    return;
}