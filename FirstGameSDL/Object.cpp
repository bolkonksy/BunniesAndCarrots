#include "Object.h"

bool Object::collideWith(Object* other)
{
	if (other->_x + other->_sizeX < _x)	return false;
	if (other->_x > _x + _sizeX)		return false;
			
	if (other->_y + other->_sizeY < _y)	return false;
	if (other->_y > _y + _sizeY)		return false;

	return true;
}