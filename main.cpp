#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace sf;

int randomGenerator() {
	return rand() % 600;
}

void generateRandomNumbers(std::vector<int>& numbers);

int main() {
	Clock clock;

	float fps = 0;
	Text text;
	Font font;
	font.loadFromFile("font.ttf");


	text.setFont(font);
	text.setPosition(Vector2f(0.f, 0.f));
	text.setCharacterSize(20);

	std::srand(int(time(NULL)));
	RectangleShape line;
	line.setFillColor(Color::White);
	
	std::vector<int> numbers(401);
	generateRandomNumbers(numbers);
	std::vector<int> first(401);
	first = numbers;
	std::vector<int> second(401);

	int loop = 0;
	RenderWindow window(VideoMode(800, 600), "Bobble Sort", Style::Close);

	std::string string;
	std::fstream stream;
	stream.open("frameratelimit.txt");
	stream >> string;
	stream.close();
	window.setFramerateLimit(atoi(string.c_str()));

	while (window.isOpen()) {

		fps = 1.f/clock.getElapsedTime().asSeconds();

		clock.restart();
		text.setString(std::to_string(int(fps)));

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
				break;
			}
			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					generateRandomNumbers(numbers);
					first = numbers;
					loop = 0;
				}
			}
		}
		window.clear(Color::Black);

		for (int i = 0; i < 400; i++) {
			line.setSize(Vector2f(2.f, first[i] * 1.f));
			line.setPosition(Vector2f(i*2.f, 600.f - first[i]));
			window.draw(line);
		}

		window.draw(text);

		window.display();

		second = first;
		for (int i = 1; i < 400 - loop; i++) {

			float a = second[i - 1];
			float b = second[i];
			if (a > b) {
				second[i] = a;
				second[i - 1] = b;
			}
		}
		if(loop < 400)loop += 1;

		first = second;

	}
}

void generateRandomNumbers(std::vector<int>& numbers) {
	for (int i = 0; i < 400; i++) {
		numbers[i] = randomGenerator();
	}
}