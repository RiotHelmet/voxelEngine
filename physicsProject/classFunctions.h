#pragma once
#include "axesFunction.h"
#include "voxelFunctions.h"

Projection::Projection(softwareRenderer* render)
{
	NEAR = render->camera->near_plane;
	FAR = render->camera->far_plane;
	RIGHT = tan(render->camera->h_fov / 2);
	LEFT = -RIGHT;
	TOP = tan(render->camera->v_fov / 2);
	BOTTOM = -TOP;

	m00 = 2 / (RIGHT - LEFT);
	m11 = 2 / (TOP - BOTTOM);
	m22 = (FAR + NEAR) / (FAR - NEAR);
	m32 = -2 * NEAR * FAR / (FAR - NEAR);

	projection_matrix = {
		{
		{m00,0,0,0},
		{0,m11,0,0},
		{0,0,m22,1},
		{0,0,m32,0},
		} };

	to_screen_matrix = {
		{
		{render->halfRES.x,0,0,0},
		{0,-render->halfRES.y,0,0},
		{0,0,1,0},
		{render->halfRES.x,render->halfRES.y,0,1},
		} };
}


Camera::Camera(softwareRenderer* _render, sf::Vector3f _pos) {
	render = _render;

	pos = {{ _pos.x,_pos.y,_pos.z,1 }};
	forward = { { 0,0,1,1 } };
	up = {{ 0,1,0,1 }};
	right = { { 1,0,0,1 } };
	h_fov = 3.1415f / 3;
	v_fov = h_fov * (render->RES.y / render->RES.x);
	near_plane = 0.1f;
	far_plane = 100;

}

Object3d::Object3d(softwareRenderer* _render) {
	render = _render;
	objectAxes = new Axes(render, 1);
	shape.setPosition({0,0});
	shape.setRadius(5);
	//shape.setFillColor(sf::Color::Red);
	vertices = { {{0,0,0,1},{0,1,0,1},{1,1,0,1},{1,0,0,1},{0,0,1,1},{0,1,1,1},{1,1,1,1},{1,0,1,1}} };
	faces = { {{0,1,2,3},{7,6,5,4}, {0,4,5,1},{2,6,7,3},{0,3,7,4}, {5,6,2,1}} };

	//openObj();
	for (int i = 0; i < faces.size(); i++)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		colors.push_back(sf::Color(r, g, b));
	}
}


void Object3d::draw() {
	//vertices = matrixMult(vertices, translateMatrix(sf::Vector3f(0.001, 0, 0)));
	screen_projection();
	//objectAxes->draw();
}

bool Object3d::backfaceCulling(std::vector<float> _vertices) {
	sf::Vector3f centre = {0,0,0};
	sf::Vector3f nVector;
	//sf::Vector3f viewPoint = { 0,0,0 };
	sf::Vector3f viewPoint = { render->camera->forward[0][0] , render->camera->forward[0][1], render->camera->forward[0][2] };

	for (int i = 0; i < _vertices.size(); i++)
	{
		centre +=
			sf::Vector3f{ vertices[_vertices[i]][0],
							vertices[_vertices[i]][1] ,
							vertices[_vertices[i]][2]
	};

	}
	centre = { centre.x / _vertices.size(), centre.y / _vertices.size() , centre.z / _vertices.size() };



	sf::Vector3f U = { 
		(vertices[_vertices[1]][0] - vertices[_vertices[0]][0]),
		(vertices[_vertices[1]][1] - vertices[_vertices[0]][1]),
		(vertices[_vertices[1]][2] - vertices[_vertices[0]][2]) };

	sf::Vector3f V = { 
		(vertices[_vertices[2]][0] - vertices[_vertices[0]][0]),
		(vertices[_vertices[2]][1] - vertices[_vertices[0]][1]),
		(vertices[_vertices[2]][2] - vertices[_vertices[0]][2]) };
	
	nVector = crossProduct(U, V);

	float nMagnitude = sqrt(pow(nVector.x, 2) + pow(nVector.y, 2) + pow(nVector.z, 2));

	nVector = { nVector.x / nMagnitude ,nVector.y / nMagnitude ,nVector.z / nMagnitude };

	nVector += {centre.x,
		centre.y,
		centre.z, };



	vector<vector<float>> vectorVertices = { {
		centre.x,
		centre.y,
		centre.z,
		1},
		{nVector.x, nVector.y, nVector.z, 1}
	//{U.}
	};

	
	sf::VertexArray line(sf::LinesStrip, 2);
	vector<vector<float>> currentVerts;

	currentVerts = matrixMult(vectorVertices, render->camera->camera_matrix());
	currentVerts = matrixMult(currentVerts, render->projection->projection_matrix);
	for (int i = 0; i < currentVerts.size(); i++) {
		for (int j = 0; j < 4; j++) {
			currentVerts[i][j] /= currentVerts[i][3];
		}
	}
	for (int i = 0; i < currentVerts.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (currentVerts[i][j] > 2 | currentVerts[i][j] < -2) {
				currentVerts[i][j] = 0;
			}
		}
	}



	currentVerts = matrixMult(currentVerts, render->projection->to_screen_matrix);


	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;

	line[0].position = sf::Vector2f(currentVerts[0][0], currentVerts[0][1]);
	line[1].position = sf::Vector2f(currentVerts[1][0], currentVerts[1][1]);
	render->window->draw(line);

	shape.setRadius(3);
	shape.setPosition({ currentVerts[0][0] - 3, currentVerts[0][1] - 3 });
	render->window->draw(shape);


	if ((viewPoint.x * nVector.x + viewPoint.y * nVector.y + viewPoint.z * nVector.z) <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Object3d::screen_projection() {
	sf::ConvexShape convex;
	convex.setPointCount(faces[0].size());
	sf::VertexArray line(sf::LinesStrip, 2);
	vector<vector<float>> currentVerts;

	currentVerts = matrixMult(vertices, render->camera->camera_matrix());
	currentVerts = matrixMult(currentVerts, render->projection->projection_matrix);
	for (int i = 0; i < currentVerts.size(); i++) {
		for (int j = 0; j < 4; j++) {
			currentVerts[i][j] /= currentVerts[i][3];
		}
	}
	for (int i = 0; i < currentVerts.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (currentVerts[i][j] > 2 | currentVerts[i][j] < -2) {
				currentVerts[i][j] = 0;
			}
		}
	}



	currentVerts = matrixMult(currentVerts, render->projection->to_screen_matrix);

	
	for (int i = 0; i < faces.size(); i++) {
		if (backfaceCulling(faces[i])) 
		{
			for (int j = 0; j < faces[i].size() - 1; j++)
			{
				if (currentVerts[faces[i][j]][0] != render->halfRES.x && currentVerts[faces[i][j]][1] != render->halfRES.y && currentVerts[faces[i][j + 1]][0] != render->halfRES.x && currentVerts[faces[i][j + 1]][1] != render->halfRES.y)
				{
					line[0].position = sf::Vector2f(currentVerts[faces[i][j]][0], currentVerts[faces[i][j]][1]);
					line[1].position = sf::Vector2f(currentVerts[faces[i][j + 1]][0], currentVerts[faces[i][j + 1]][1]);
					render->window->draw(line);
				}
			}
			//if (currentVerts[faces[i][faces[i].size() - 1]][0] != render->halfRES.x && currentVerts[faces[i][faces[i].size() - 1]][1] != render->halfRES.y && currentVerts[faces[i][0]][0] != render->halfRES.x && currentVerts[faces[i][0]][1] != render->halfRES.y)
			//{
			//	line[0].position = sf::Vector2f(currentVerts[faces[i][faces[i].size() - 1] - 1][0], currentVerts[faces[i][faces[i].size() - 1] - 1][1]);
			//	line[1].position = sf::Vector2f(currentVerts[faces[i][1] - 1][0], currentVerts[faces[i][1] - 1][1]);
			//	render->window->draw(line);
			//}
		}
	}
	

	for (int i = 0; i < faces.size(); i++) {
		//if (backfaceCulling(faces[i])) 
		{
			// {
			//	for (int j = 0; j < faces[i].size(); j++)
			//	{
			//		convex.setFillColor(colors[i]);

			//		convex.setPoint(j, sf::Vector2f(currentVerts[faces[i][j]][0], currentVerts[faces[i][j]][1]));
			//	}
			//	render->window->draw(convex);
			//}
		}
	}

	/*for (int i = 0; i < currentVerts.size(); i++) {
		shape.setPosition({ currentVerts[i][0] - 5, currentVerts[i][1] - 5 });
		render->window->draw(shape);
	}*/
}

