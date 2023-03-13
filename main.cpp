#include <SFML/Graphics.hpp>
#include <Windows.h>
#define height 900
#define width 1200
#define pi 3.14159f

class Pendulum {
public:
	sf::CircleShape anchor, bob;
	sf::Vector2f anchor_pos, bob_pos;
	sf::Vertex line[2];
	float length = 0, alpha = 0, omega = 0, angle = 0, g = 5;
	Pendulum() {
		anchor_pos = sf::Vector2f(width / 2, 20);
		length = 500;
		angle = pi/4;
		bob_pos.x = length * sin(angle) + anchor_pos.x;
		bob_pos.y = length * cos(angle) + anchor_pos.y;
		bob.setRadius(30);
		anchor.setFillColor(sf::Color::Blue);
		bob.setFillColor(sf::Color::Red);
		update_anchor();
		update_bob();
		line[0] = anchor_pos;
		line[1] = bob_pos;
	}
	Pendulum(sf::Vector2f a_pos, float len, float ang) {
		anchor_pos = a_pos;
		length = len;
		angle = ang * pi / 180.f;
		bob_pos.x = length * sin(angle) + anchor_pos.x;
		bob_pos.y = length * cos(angle) + anchor_pos.y;
		bob.setRadius(30);
		anchor.setFillColor(sf::Color::Blue);
		bob.setFillColor(sf::Color::Red);
		update_anchor();
		update_bob();
		line[0] = anchor_pos;
		line[1] = bob_pos;
	}
	void update() {
		alpha = -(g * sin(angle)) / length;
		omega = omega + alpha;
		angle = angle + omega;
		bob_pos.x = length * sin(angle) + anchor_pos.x;
		bob_pos.y = length * cos(angle) + anchor_pos.y;

		bob.setPosition(bob_pos);
		bob.setOrigin(bob.getRadius(), bob.getRadius());
		line[1] = bob_pos;
	}
	void update_anchor() {
		anchor.setRadius(10);
		anchor.setPosition(anchor_pos);
		anchor.setOrigin(anchor.getRadius(), anchor.getRadius());
	}
	void update_bob() {
		bob.setPosition(bob_pos);
		bob.setOrigin(bob.getRadius(), bob.getRadius());
		line[1] = bob_pos;
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
	Pendulum pendulum;
	Pendulum p1(sf::Vector2f(width / 3, 20), 500, 60);
	Pendulum p2(sf::Vector2f(width * 5 / 6, 20), 500, -60);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		Sleep(30);
		window.clear(sf::Color::Black);

		window.draw(pendulum.line, 2, sf::Lines);
		window.draw(pendulum.anchor);
		window.draw(pendulum.bob);

		window.draw(p1.line, 2, sf::Lines);
		window.draw(p1.anchor);
		window.draw(p1.bob);

		window.draw(p2.line, 2, sf::Lines);
		window.draw(p2.anchor);
		window.draw(p2.bob);
		
		window.display();
		pendulum.update();

		p1.update();

		p2.update();
	}
}
