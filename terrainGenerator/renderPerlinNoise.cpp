//const int windowWidth = 1920;
//const int windowHeight = 1080;
//
//sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "perlin");
//
//sf::Uint8* pixels = new sf::Uint8[windowWidth * windowHeight * 4];
//
//const int GRID_SIZE = 400;
//
//
//for (int x = 0; x < windowWidth; x++) {
//
//    for (int y = 0; y < windowHeight; y++) {
//        int index = (y * windowWidth + x) * 4;
//
//        float val = 0;
//
//        float freq = 1;
//
//        float amp = 1;
//
//        for (int i = 0; i < 12; i++) {
//            val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;
//
//            freq *= 2;
//            amp /= 2;
//        }
//        // contrast value
//        val *= 1.2;
//
//        // because perlin values are usually between -1 and 1, we need to clip between those values
//        if (val > 1.0f) {
//            val = 1.0f;
//        }
//        else if (val < -1.0f) {
//            val = -1.0f;
//        }
//
//        // convert 1 to -1 into 255 to 0
//        int color = (int)(((val + 1.0f) * 0.5f) * 255);
//
//        // set pixel color
//        pixels[index] = color;
//        pixels[index + 1] = (136, 200, 56);
//        pixels[index + 2] = color;
//        pixels[index + 3] = 255;
//
//    }
//}
//sf::Texture texture;
//sf::Sprite sprite;
//
//texture.create(windowWidth, windowHeight);
//
//texture.update(pixels);
//
//sprite.setTexture(texture);
//
//while (window.isOpen()) {
//    sf::Event event;
//    while (window.pollEvent(event)) {
//        if (event.type == sf::Event::Closed) {
//            window.close();
//        }
//    }
//    window.clear();
//    window.draw(sprite);
//
//    window.display();
//}