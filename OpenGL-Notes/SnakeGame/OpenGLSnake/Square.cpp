#include "Square.hpp"
#include <cstdlib>

Square::Square(float x, float y, float lenght) {
	m_Position = glm::vec3(x, y, 0.0f);
	m_Color.r = (10 + std::rand() % 25) / 25.0f;
	m_Color.g = (10 + std::rand() % 25) / 25.0f;
	m_Length = lenght;
	m_Direction = DIR_RIGHT;
}

glm::vec3 Square::getPosition() {
	return this->m_Position;
}

glm::vec4 Square::getColor() {
	return this->m_Color;
}

Square::DIRECTION Square::getDirection() {
	return this->m_Direction;
}

void Square::move() {
	switch (m_Direction)
	{
	case DIR_LEFT:
		m_Position -= glm::vec3(m_Length, 0.0f, 0.0f);
		break;
	case DIR_RIGHT:
		m_Position += glm::vec3(m_Length, 0.0f, 0.0f);
		break;
	case DIR_DOWN:
		m_Position -= glm::vec3(0.0f, m_Length, 0.0f);
		break;
	case DIR_UP:
		m_Position += glm::vec3(0.0f, m_Length, 0.0f);
		break;
	}
}

void Square::setDirection(DIRECTION dir) {
	m_Direction = dir;
}