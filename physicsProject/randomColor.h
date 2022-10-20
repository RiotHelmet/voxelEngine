#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

sf::Color getRandomColor(std::mt19937& rng)
{
	static std::vector<sf::Color> colorsToChooseFrom = {
		sf::Color(255,   0,   0, 63),
		sf::Color(255, 255,   0, 63),
		sf::Color(255,   0, 255, 63),
		sf::Color(0, 255,   0, 63),
		sf::Color(0, 255, 255, 63),
		sf::Color(0,   0, 255, 63)
	};

	static std::uniform_int_distribution<> color_dist(0, colorsToChooseFrom.size() - 1);

	return colorsToChooseFrom.at(color_dist(rng));
}
