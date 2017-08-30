#include "..\include\cgBasic.h"

namespace cg
{
	int area2(const Point &p, const Point &q, const Point &s)
	{
		return p.x * q.y + p.y * s.x + q.x * s.y
			- q.y * s.x - p.y * q.x - p.x * s.y;
	}

	bool toLeft(const Point &p, const Point &q, const Point &s)
	{
		int sq = area2(p, q, s);
		if (sq > 0) return true;
		if (sq < 0) return false;
		return between(p, q, s);
	}

	bool toRight(const Point &p, const Point &q, const Point &s)
	{
		int sq = area2(p, q, s);
		if (sq < 0) return true;
		if (sq > 0) return false;
		return between(p, q, s);
	}

	bool between(const Point &p, const Point &k, const Point &q)
	{
		return (p.x - k.x) * (k.x - q.x) + (p.y - k.y) * (k.y - q.y) > 0;
	}

	bool inTriangle(const Point &p, const Point &q, const Point &r, const Point &s)
	{
		return toLeft(p, q, s) &&
			toLeft(q, r, s) &&
			toLeft(r, p, s);
	}

	size_t lowestThenLeftmost(const std::vector<Point> &vp)
	{
		size_t r = 0;
		for (size_t i = 1; i < vp.size(); ++i)
		{
			if (vp[i].y < vp[r].y) r = i;
			else if (vp[i].y == vp[r].y)
				if (vp[i].x < vp[r].x) r = i;
		}

		return r;
	}

	void polarAngleSort(std::vector<Point> &vp)
	{
		//find the ltl first
		size_t ltl = lowestThenLeftmost(vp);
		using std::swap;
		swap(vp[0], vp[ltl]);

		std::sort(vp.begin() + 1, vp.end(), [vp](const Point &p1, const Point &p2)
		{return toLeft(vp[0], p1, p2); });
	}

	bool inConvexPolygonSorted(const std::vector<Point> &vp, const Point &p)
	{
		//pay attention that the lo is start from 1
		size_t lo = 1, hi = vp.size() - 1;
		size_t mid = (lo + hi) >> 1;
		while (hi - lo > 1)
		{
			if (toLeft(vp[0], vp[mid], p))
				lo = mid;
			else if (area2(vp[0], vp[mid], p) == 0 && between(vp[0], p, vp[mid]))
				return true;
			else
				hi = mid;

			mid = (lo + hi) >> 1;
		}

		return inTriangle(vp[0], vp[lo], vp[hi], p);
	}
}