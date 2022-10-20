#pragma once

bool pressing(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key)) { return true; }
	return false;
}

// mouse button pressed
bool pressing(sf::Mouse::Button button)
{
	if (sf::Mouse::isButtonPressed(button)) { return true; }
	return false;
}
