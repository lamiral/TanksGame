#pragma once

#include <iostream>
#include <vector>
#include "Section.h"


class Map
{
public:

	std::vector<Section*> sections;

	void draw();
};