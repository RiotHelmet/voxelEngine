#pragma once

#include "matrix_calculations.h"

using namespace std;

struct Projection {
	float NEAR;
	float FAR;
	float RIGHT;
	float LEFT;
	float TOP;
	float BOTTOM;

	float m00;
	float m11;
	float m22;
	float m32;

	vector<vector<float>> projection_matrix;
	vector<vector<float>> to_screen_matrix;

	Projection(softwareRenderer*);
};