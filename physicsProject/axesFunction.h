#pragma once

Axes::Axes(softwareRenderer* _render, float size) {

	render = _render;


	vertices = { 
		{0,0,0,1} ,
		{size,0,0,1} ,
		{0,size,0,1} ,
		{0,0,size,1} };

	faces = { 
		{0,1} ,
		{0,2} ,
		{0,3} };
}

void Axes::draw() {
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



	line[0].position = sf::Vector2f(currentVerts[faces[0][0]][0], currentVerts[faces[0][0]][1]);

	for (int i = 0; i < faces.size(); i++)
	{
		if (currentVerts[faces[0][0]][0] != render->halfRES.x && 
			currentVerts[faces[0][0]][1] != render->halfRES.y && 
			currentVerts[faces[i][1]][0] != render->halfRES.x && 
			currentVerts[faces[i][1]][1] != render->halfRES.y) {

			line[1].position = sf::Vector2f(currentVerts[faces[i][1]][0], currentVerts[faces[i][1]][1]);
			render->window->draw(line);

		}
	}

	/*for (int i = 0; i < currentVerts.size(); i++) {
		render->objects[0]->shape.setPosition({ currentVerts[i][0] - 5, currentVerts[i][1] - 5 });
		render->window->draw(render->objects[0]->shape);
	}*/
}