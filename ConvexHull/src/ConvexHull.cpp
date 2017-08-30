#include "..\include\ConvexHull.h"

namespace cg
{
	void jarvisMarch(std::vector<Point> &pointSet, std::vector<Point> &ch)
	{	
		if (pointSet.size() <= 3)
		{
			ch = pointSet;
			return;
		}

		int ltl = lowestThenLeftmost(pointSet);
		int k = ltl;
		ch.push_back(pointSet[k]);

		do
		{
			int s = -1;
			for (size_t i = 0; i < pointSet.size(); ++i)
			{
				if (i != k && (s == -1 || toRight(pointSet[k], pointSet[s], pointSet[i])))
					s = i;	
			}
			k = s;
			ch.push_back(pointSet[k]);
		} while (k != ltl);
	}

	void grahamScan(std::vector<Point> &pointSet, std::vector<Point> &ch)
	{
		if (pointSet.size() <= 3)
		{
			ch = pointSet;
			return;
		}
		//preprocessing
		polarAngleSort(pointSet);
		std::vector<Point> t;
		ch.push_back(pointSet[0]);
		ch.push_back(pointSet[1]);
		for (size_t i = pointSet.size() - 1; i >= 2; --i)
			t.push_back(pointSet[i]);
		//scan
		while (!t.empty())
		{
			if (toLeft(ch[ch.size() - 2], ch.back(), t.back()))
			{
				ch.push_back(t.back());
				t.pop_back();
			}	
			else
			{
				ch.pop_back();
			}
		}
		//insert the start point to the end of ch to make the convex hull closed
		ch.push_back(ch[0]);
	}
}