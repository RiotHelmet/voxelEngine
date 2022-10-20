#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

using namespace std;

vector<vector<float>> translateMatrix(sf::Vector3f t) {
	vector<vector<float>> returnMatrix = { { { 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ t.x,t.y,t.z,1 } } };
	return returnMatrix;
}

vector<vector<float>> rotate_xMatrix(float deg) {
	vector<vector<float>> returnMatrix = { {
		{ 1,0,0,0 },
		{ 0,cos(deg),sin(deg),0 },
		{ 0,-sin(deg),cos(deg),0 },
		{ 0,0,0,1 } } };
	return returnMatrix;
}

vector<vector<float>> rotate_yMatrix(float deg) {
	vector<vector<float>> returnMatrix = { {
		{ cos(deg),0,-sin(deg),0 },
		{ 0,1,0,0 },
		{ sin(deg),0,cos(deg),0 },
		{ 0,0,0,1 } } };
	return returnMatrix;
}

vector<vector<float>> rotate_zMatrix(float deg) {
	vector<vector<float>> returnMatrix = { {
		{ cos(deg),sin(deg),0,0 },
		{ -sin(deg),cos(deg),0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 } } };
	return returnMatrix;
}

vector<vector<float>> scaleMatrix(float n) {
	vector<vector<float>> returnMatrix = { {
		{ n,0,0,0 },
		{ 0,n,0,0 },
		{ 0,0,n,0 },
		{ 0,0,0,1 } } };
	return returnMatrix;
}
