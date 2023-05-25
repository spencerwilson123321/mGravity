#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

// CONSTANTS
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

// CLASSES
class Ball {
    public:
        sf::CircleShape shape;
        sf::Vector2f position;
        float radius;
        float yVelocity = 5.0;
        float xVelocity = 5.0;
        float timestep = 1.0f;
        float acceleration = 1.2f;
        Ball(float x, float y, float r) {
            position.x = x;
            position.y = y;
            radius = r;
            shape.setPosition(position);
            shape.setRadius(radius);
        };
        void update() {
            if (position.y+radius >= WINDOW_HEIGHT || position.y-radius <= 0) {
                yVelocity *= -1;
            }
            if (position.x+radius >= WINDOW_WIDTH || position.x-radius <= 0) {
                xVelocity *= -1;
            }
            position.y += timestep*(yVelocity + timestep*acceleration / 2);
            yVelocity += timestep*acceleration;
            position.x += xVelocity;
            shape.setPosition(position);
        }
        void draw(sf::RenderWindow &window) {
            window.draw(shape);
        }
};

int main() {
    
    // WINDOW OBJECT
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncy Ball");
    window.setFramerateLimit(60);

    // BALL OBJECT
    Ball ball(600, 350, 30.0f);

    // GAME LOOP
    while (window.isOpen()) {

        // EVENT PROCESSING
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        ball.update();
        
        // RENDER
        window.clear();
        ball.draw(window);
        window.display();
    }
    return 0;
}
