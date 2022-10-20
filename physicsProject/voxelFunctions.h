#pragma once

Voxel::Voxel(softwareRenderer* _render, sf::Vector3f _pos) {
	render = _render;
	shape.setRadius(2.5);
	pos = _pos;
	scale(0.2);

	for (int i = 0; i < faces.size(); i++)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		colors.push_back(sf::Color(r, g, b));
	}
}


bool Voxel::backfaceCulling(std::vector<float> _vertices) {
	vector<vector<float>> currentVerts;

	sf::Vector3f centre = { 0,0,0 };
	sf::Vector3f nVector;
	//sf::Vector3f viewPoint = { 0,0,0 };
	sf::Vector3f viewPoint = { render->camera->forward[0][0] , render->camera->forward[0][1], render->camera->forward[0][2] };

	currentVerts = matrixMult(vertices, translateMatrix({ pos.x * 0.2f, pos.y * 0.2f, pos.z * 0.2f }));

	for (int i = 0; i < _vertices.size(); i++)
	{
		centre +=
			sf::Vector3f{ currentVerts[_vertices[i] - 1][0],
							currentVerts[_vertices[i] - 1][1] ,
							currentVerts[_vertices[i] - 1][2]
		};

	}
	centre = { centre.x / _vertices.size(), centre.y / _vertices.size() , centre.z / _vertices.size() };



	sf::Vector3f U = {
		(currentVerts[_vertices[1] - 1][0] - currentVerts[_vertices[0] - 1][0]),
		(currentVerts[_vertices[1] - 1][1] - currentVerts[_vertices[0] - 1][1]),
		(currentVerts[_vertices[1] - 1][2] - currentVerts[_vertices[0] - 1][2]) };

	sf::Vector3f V = {
		(currentVerts[_vertices[2] - 1][0] - currentVerts[_vertices[0] - 1][0]),
		(currentVerts[_vertices[2] - 1][1] - currentVerts[_vertices[0] - 1][1]),
		(currentVerts[_vertices[2] - 1][2] - currentVerts[_vertices[0] - 1][2]) };

	nVector = crossProduct(U, V);

	//float nMagnitude = sqrt(pow(nVector.x, 2) + pow(nVector.y, 2) + pow(nVector.z, 2));
	float nMagnitude = 1;


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

	if ((viewPoint.x * nVector.x + viewPoint.y * nVector.y + viewPoint.z * nVector.z)  <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Voxel::draw() {
	sf::ConvexShape convex;
	convex.setPointCount(faces[0].size());
	sf::VertexArray line(sf::LinesStrip, 2);
	vector<vector<float>> currentVerts;
	currentVerts = matrixMult(vertices, translateMatrix({pos.x * 0.2f, pos.y * 0.2f, pos.z * 0.2f}));
	currentVerts = matrixMult(currentVerts, render->camera->camera_matrix());
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


	//for (int i = 0; i < faces.size(); i++) {
	//	if (backfaceCulling(faces[i]))
	//	{
	//		for (int j = 0; j < faces[i].size() - 1; j++)
	//		{
	//			if (currentVerts[faces[i][j] - 1][0] != render->halfRES.x && currentVerts[faces[i][j] - 1][1] != render->halfRES.y && currentVerts[faces[i][j + 1] - 1][0] != render->halfRES.x && currentVerts[faces[i][j + 1] - 1][1] != render->halfRES.y)
	//			{
	//				line[0].position = sf::Vector2f(currentVerts[faces[i][j] - 1][0], currentVerts[faces[i][j] - 1][1]);
	//				line[1].position = sf::Vector2f(currentVerts[faces[i][j + 1] - 1][0], currentVerts[faces[i][j + 1] - 1][1]);
	//				render->window->draw(line);
	//			}
	//		}
	//		if (currentVerts[faces[i][faces[i].size() - 1]-1][0] != render->halfRES.x && currentVerts[faces[i][faces[i].size() - 1] - 1][1] != render->halfRES.y && currentVerts[faces[i][0] - 1][0] != render->halfRES.x && currentVerts[faces[i][0] - 1][1] != render->halfRES.y)
	//		{
	//			line[0].position = sf::Vector2f(currentVerts[faces[i][faces[i].size() - 1] - 1][0], currentVerts[faces[i][faces[i].size() - 1] - 1][1]);
	//			line[1].position = sf::Vector2f(currentVerts[faces[i][0] - 1][0], currentVerts[faces[i][0] - 1][1]);
	//			render->window->draw(line);
	//		}
	//	}
	//}


	for (int i = 0; i < faces.size(); i++) {
		if (backfaceCulling(faces[i])) 
		{
			 {
				for (int j = 0; j < faces[i].size(); j++)
				{
					convex.setFillColor(colors[i]);

					convex.setPoint(j, sf::Vector2f(currentVerts[faces[i][j] - 1][0], currentVerts[faces[i][j] - 1][1]));
				}
				render->window->draw(convex);
			}
		}
	}

	/*for (int i = 0; i < currentVerts.size(); i++) {
		shape.setPosition({ currentVerts[i][0] - 2.5f, currentVerts[i][1] - 2.5f });
		render->window->draw(shape);
	}*/
}

