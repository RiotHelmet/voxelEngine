#pragma once
#include "matrix_functions.h"
#include "matrix_calculations.h"
#include <fstream>
#include <string>
#include <iostream>
//#include "softwareRenderer.h"

struct softwareRenderer;
struct Axes;

using namespace std;

struct Voxel {

	vector<vector<float>> vertices = { {-1,-1,-1,1}, {-1,1,-1,1}, {1,1,-1,1} ,{1,-1,-1,1}, {-1,-1,1,1}, {-1,1,1,1}, {1,1,1,1} ,{1,-1,1,1} };
	vector<vector<float>> faces = { {1,2,3,4}, {8,7,6,5}, {5,6,2,1}, {4,3,7,8}, {5,1,4,8}, {2,6,7,3} };
	softwareRenderer* render;
	sf::CircleShape shape;

	sf::Vector3f pos{ 0, 0, 0 };

	Voxel(softwareRenderer*, sf::Vector3f _pos);
	vector<sf::Color> colors;


	void draw();

	bool backfaceCulling(std::vector<float> _vertices);


	void translate(sf::Vector3f t) {
		vertices = matrixMult(vertices, translateMatrix(t));
	}

	void scale(float scale_to) {
		vertices = matrixMult(vertices, scaleMatrix(scale_to));
	}

	void rotate_x(float deg) {
		vertices = matrixMult(vertices, rotate_xMatrix(deg));
	}

	void rotate_y(float deg) {
		vertices = matrixMult(vertices, rotate_yMatrix(deg));
	}

	void rotate_z(float deg) {
		vertices = matrixMult(vertices, rotate_zMatrix(deg));
	}

};
