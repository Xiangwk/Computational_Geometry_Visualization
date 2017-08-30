#pragma once

#include "cgBasic.h"

#include <vector>

namespace cg
{
	void jarvisMarch(std::vector<Point> &pointSet, std::vector<Point> &ch);

	void grahamScan(std::vector<Point> &pointSet, std::vector<Point> &ch);
}