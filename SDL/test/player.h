#pragma once
#include "object.h"

class Player : public Object {
public:
	float dir;

	void dirUpdate();
};