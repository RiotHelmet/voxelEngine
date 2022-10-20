#include <SFML/Graphics.hpp>
#include "Object_3d.h"
#include "Voxel.h"
#include "Axes.h"
#include "Camera.h"
#include "projection.h"
#include "softwareRenderer.h"
#include "classFunctions.h"
#include <iostream>
#include "matrix_functions.h"
#include "matrix_calculations.h"

int main()
{

	sf::RenderWindow window(sf::VideoMode(1280, 720), "", sf::Style::Default);
	softwareRenderer engine(&window);
	engine.run();
	return 0;
}