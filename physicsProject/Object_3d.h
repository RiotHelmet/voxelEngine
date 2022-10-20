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

struct Object3d {

	vector<vector<float>> vertices;
	vector<vector<float>> faces;
	softwareRenderer* render;
	sf::CircleShape shape;
	Object3d(softwareRenderer*);
    vector<sf::Color> colors;

    Axes* objectAxes;

	void draw();

	void screen_projection();

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