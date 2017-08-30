#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <ctime>

namespace cg
{
	//A point in 2D space
	struct Point
	{
		int x;
		int y;

		Point(int a = 0, int b = 0) : x(a), y(b) {}
		Point(int a) : x(a), y(a) {}
	};

	//the double area of the triangle which is consist of p, q and s.
	//if p, q and s is CCW(counterclockwise), the value is positive, otherwise is negtive!
	int area2(const Point &p, const Point &q, const Point &s);
	//detect s locate on which side of the line pq.
	bool toLeft(const Point &p, const Point &q, const Point &s);
	bool toRight(const Point &p, const Point &q, const Point &s);
	//if p, k and q is collinear, detect whether k is locate on between p and q.
	bool between(const Point &p, const Point &k, const Point &q);
	//detect whether s is locate in the triangle which is consist of p, q and r.
	bool inTriangle(const Point &p, const Point &q, const Point &r, const Point &s);
	//find the lowest then leftmost point in point set vp.
	size_t lowestThenLeftmost(const std::vector<Point> &vp);

	//sort the point by polar angle.
	void polarAngleSort(std::vector<Point> &vp);

	//detect whether p is locate in the convex polygon vp
	bool inConvexPolygonSorted(const std::vector<Point> &vp, const Point &p);

}//namespace cg end