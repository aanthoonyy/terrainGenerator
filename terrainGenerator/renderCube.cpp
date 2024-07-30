#include "renderCube.hpp"
#include "perlinNoise.hpp"
#include <iostream>
#include <random>
#include <ctime>
sf::VertexArray drawIsometricCube(float isoX, float isoY, float size, int color[])
{
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

    cube[16].position = vertices[4];
    cube[17].position = vertices[5];
    cube[18].position = vertices[6];
    cube[19].position = vertices[7];

    cube[20].position = vertices[3];
    cube[21].position = vertices[2];
    cube[22].position = vertices[1];
    cube[23].position = vertices[0];

    sf::Color topColor(color[0] * .95, color[1] * .95, color[2] * .95);
    sf::Color frontColor(color[0], color[1], color[2]);
    sf::Color sideColor(color[0] * .85, color[1] * .85, color[2] * .85);
    sf::Color alpha(150, 150, 150);
    alpha.a = 0;

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

    return cube;
}

void renderMap() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "idk");
    const int gridSize = 16;
    const float cubeSize = 20.0f;
    const float isoXStart = 350.0f;
    const float isoYStart = 100.0f;

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> distribution(3, 6); 
    std::uniform_int_distribution<int> treeDistribution(1, 100); 

    int seed = static_cast<int>(std::time(nullptr));

    int ran = distribution(gen);
    seed *= ran;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    
        window.clear();
        float isoX = 1250;
        float isoY = -1080;
        int color[3] = { 66, 135, 245 };
        

        float multiplyer = 0;
        int yAdjustment = 0;

        for (int x = 0; x < 1990; x+=5)
        {
            for (int y = 0; y < 1080; y+=5)
            {
                float normalizedX = (float)x / gridSize;
                float normalizedY = (float)y / gridSize;
                if (perlin(normalizedX, normalizedY, seed) > -0.35 + multiplyer) {

                    float offsetX = y * cubeSize * 0.25f;
                    float offsetY = x * cubeSize * 0.5f;
                    float isoPosX = isoX + offsetX - offsetY;
                    float isoPosY = isoY + offsetY + offsetX;
                    window.draw(drawIsometricCube(1920 - x, 1100 - y, cubeSize, color));
                }

            }
        }
        
        for (int i = 0; i < 6; i++) {
            if (i == 0) {
                color[0] = 219;
                color[1] = 255;
                color[2] = 110;
            }
            if(i >0 && i < 3) {
                color[0] = 16;
                color[1] = 160;
                color[2] = 75;
            }
            for (int x = 0; x < gridSize * 20; x++)
            {
                for (int y = 0; y < gridSize * 20; y++)
                {
                    float normalizedX = (float)x / gridSize;
                    float normalizedY = (float)y / gridSize;
                    if (perlin(normalizedX, normalizedY, seed) > -0.35 + multiplyer) {

                        float offsetX = y * cubeSize * 0.25f;
                        float offsetY = x * cubeSize * 0.5f;
                        float isoPosX = isoX + offsetX - offsetY;
                        float isoPosY = isoY + offsetY + offsetX;
                        window.draw(drawIsometricCube(isoPosX, isoPosY - yAdjustment, cubeSize, color));
                        if (treeDistribution(gen) == 10 && i >= 3) {
                            drawTrees(window, isoPosX, isoPosY, 100.f);
                        }
                        
                    }

                }
            }
            multiplyer += 0.2;
            yAdjustment -= 20;
            
        }
        window.display();
    }

    return;
}

void drawTrees(sf::RenderWindow& window, float isoX, float isoY, float treeHeight) {
    int brown[3] = { 120,84,48 };
    int leaves[3] = { 33,69,35 };
    window.draw(drawIsometricCube(isoX, isoY, 20, brown));
    window.draw(drawIsometricCube(isoX, isoY -=20, 20, brown));
    window.draw(drawIsometricCube(isoX, isoY -=20, 20, brown));
    window.draw(drawIsometricCube(isoX, isoY -=20, 20, leaves));
    window.draw(drawIsometricCube(isoX - 10, isoY, 20, leaves));
    window.draw(drawIsometricCube(isoX + 10, isoY, 20, leaves));
    window.draw(drawIsometricCube(isoX + 15, isoY - 5, 20, leaves));
    window.draw(drawIsometricCube(isoX - 15, isoY - 5, 20, leaves));
    window.draw(drawIsometricCube(isoX - 20, isoY - 10, 20, leaves));
    window.draw(drawIsometricCube(isoX + 20, isoY + 10, 20, leaves));
    window.draw(drawIsometricCube(isoX , isoY -= 20, 20, leaves));
}