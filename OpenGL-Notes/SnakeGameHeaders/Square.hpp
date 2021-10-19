#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Square {
public:
	Square(float x, float y, float lenght);

	enum DIRECTION {
		DIR_RIGHT = 1,
		DIR_LEFT = -1,
		DIR_UP = 2,
		DIR_DOWN = -2
	};
	
	glm::vec3 getPosition();
	glm::vec4 getColor();
	void move();
	DIRECTION getDirection();
	void setDirection(DIRECTION dir);

private:
	glm::vec4 m_Color;
	glm::vec3 m_Position;
	float m_Length;
	DIRECTION m_Direction;
};

#endif // !SQUARE_HPP
