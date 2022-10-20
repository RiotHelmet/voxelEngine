#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "matrix_functions.h"
#include "matrix_calculations.h"
#include "movement.h"

//#include "Object_3d.h"
//#include "Camera.h"
//#include "Camera.h"
using namespace std;
//struct Object3d;

//struct Camera;

struct softwareRenderer {

	sf::Vector2f RES = { 1280, 720 };
	sf::Vector2f halfRES = { RES.x / 2, RES.y / 2 };
	int targetFPS = 60;
	sf::RenderWindow* window;
	sf::Clock clock;
	float deltaT;
	int fps = 60;
	Camera* camera;
	std::vector<Voxel*> objects;
	Object3d* obj;
	softwareRenderer* render;
	Projection* projection;
	sf::Vector2f mouseDelta = {0,0};
	sf::Vector2f mouseposition;
	softwareRenderer(sf::RenderWindow* _window) {
		window = _window;
		deltaT = clock.restart().asSeconds();
	}

	void createNewVoxel(sf::Vector3f _pos) {
		objects.push_back(new Voxel(this, _pos));
	}

	void create_objects() {
		for (float i = 0; i < 3; i++)
		{
			for (float j = 0; j < 3; j++)
			{
				createNewVoxel(sf::Vector3f{ i * 2, 0.01, j * 2});
			}
		}
		//createNewObject(sf::Vector3f{ 0.2, 0.01, 0.2 });

		camera = new Camera(this, sf::Vector3f{ 0.0001 ,1, -3 });
		projection = new Projection(this);
	}

	void draw() {
		window->clear();
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->draw();
			//objects[i]->rotate_x(0.01);
		}
		window->display();
	}


	void run() {
		create_objects();
		sf::Event event;
		window->setFramerateLimit(targetFPS);
		while (window->isOpen())
		{

			mouseposition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			mouseDelta = mouseposition - halfRES + sf::Vector2f{328,211};
			sf::Mouse::setPosition(sf::Vector2i(halfRES.x, halfRES.y));
			window->setMouseCursorVisible(false);

			if (pressing(sf::Keyboard::Escape)) {
				window->close();
			}

			if (pressing(sf::Keyboard::W)) {
				camera->pos[0][0] += camera->forward[0][0] * 0.05;
				camera->pos[0][1] += camera->forward[0][1] * 0.05;
				camera->pos[0][2] += camera->forward[0][2] * 0.05;
			}
			if (pressing(sf::Keyboard::S)) {
				camera->pos[0][0] -= camera->forward[0][0] * 0.05;
				camera->pos[0][1] -= camera->forward[0][1] * 0.05;
				camera->pos[0][2] -= camera->forward[0][2] * 0.05;
			}
			if (pressing(sf::Keyboard::D)) {
				camera->pos[0][0] += camera->right[0][0] * 0.05;
				camera->pos[0][1] += camera->right[0][1] * 0.05;
				camera->pos[0][2] += camera->right[0][2] * 0.05;
			}
			if (pressing(sf::Keyboard::A)) {
				camera->pos[0][0] -= camera->right[0][0] * 0.05;
				camera->pos[0][1] -= camera->right[0][1] * 0.05;
				camera->pos[0][2] -= camera->right[0][2] * 0.05;
			}

			if (pressing(sf::Keyboard::Right)) {
				camera->camera_yaw(0.01);
			}
			if (pressing(sf::Keyboard::Left)) {
				camera->camera_yaw(-0.01);
			}


			if (pressing(sf::Keyboard::Up)) {
				camera->camera_pitch(-0.01);
			}
			if (pressing(sf::Keyboard::Down)) {
				camera->camera_pitch(0.01);
			}


			//camera->camera_yaw(mouseDelta.x / 1000);
			//camera->camera_pitch(mouseDelta.y / 1000);


			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
				}
			}
			//camera->pos[2] -= 0.1;
			//obj->rotate_x(3.145 / 100);
			//obj->rotate_y(3.145 / 100);
			//obj->rotate_z(3.145 / 100);
			deltaT = clock.restart().asSeconds();
			fps = 1 / deltaT;
			draw();
			window->setTitle(std::to_string(fps));

		}
	}
};
