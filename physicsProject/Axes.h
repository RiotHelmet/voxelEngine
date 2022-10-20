#pragma once

using namespace std;

struct Axes {
	softwareRenderer* render;
	vector<vector<float>> vertices;
	vector<vector<float>> faces;

	Axes(softwareRenderer* _render, float size);

	void draw();
};