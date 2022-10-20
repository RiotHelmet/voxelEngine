#pragma once
#include <iostream>
#include "matrix_calculations.h"
#include "matrix_functions.h"
#include <array>
#include <SFML/Graphics.hpp>

struct softwareRenderer;

struct Camera {
	vector<vector<float>> pos;
	vector<vector<float>> forward;
	vector<vector<float>> up;
	vector<vector<float>> right;
	float h_fov;
	float v_fov;
	float near_plane;
	float far_plane;
	softwareRenderer* render;

	Camera(softwareRenderer*, sf::Vector3f);

	void setupCamera();

	void camera_yaw(float deg) {
		forward = matrixMult(forward, rotate_yMatrix(deg));
		right = matrixMult(right, rotate_yMatrix(deg));
		up = matrixMult(up, rotate_yMatrix(deg));
	}

	void camera_pitch(float deg) {
		forward = matrixMult(forward, rotate_xMatrix(deg));
		right = matrixMult(right, rotate_xMatrix(deg));
		up = matrixMult(up, rotate_xMatrix(deg));
	}

	vector<vector<float>> translate_matrix() {
		float x, y, z, w;
		x = pos[0][0];
		y = pos[0][1];
		z = pos[0][2];
		w = pos[0][3];
		vector<vector<float>> returnMatrix = { {
			{ 1,0,0,0 },
			{ 0,1,0,1 },
			{ 0,0,1,0 },
			{ -x,-y,-z,1 } } };
		return returnMatrix;
	}

	vector<vector<float>> rotate_matrix() {
		float rx, ry, rz, w;
		rx = right[0][0];
		ry = right[0][1];
		rz = right[0][2];
		w = right[0][3];
		float fx, fy, fz;
		fx = forward[0][0];
		fy = forward[0][1];
		fz = forward[0][2];
		float ux, uy, uz;
		ux = up[0][0];
		uy = up[0][1];
		uz = up[0][2];
		vector<vector<float>> returnMatrix = { {
			{ rx,ux,fx,0 },
			{ ry,uy,fy,0 },
			{ rz,uz,fz,0 },
			{ 0,0,0,1 } } };
		return returnMatrix;
	}


	vector<vector<float>> camera_matrix() {
		return matrixMult(translate_matrix(), rotate_matrix());
	}
};