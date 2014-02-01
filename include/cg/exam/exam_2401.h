#pragma once
#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>
#include <cg/operations/orientation.h>
#include <cg/primitives/contour.h>
#include <cg/primitives/triangle.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/intersection/segment_segment.h>
#include <cg/convex_hull/jarvis.h>
#include <cmath>

namespace cg
{

inline std::vector<std::pair<int, int> > rasterize(segment_2 s)
{
    std::vector<std::pair<int, int> > result;
    if (s[0] > s[1])
        std::swap(s[0], s[1]);

    auto cur = std::make_pair((int)floor(s[0].x), (int)floor(s[0].y));

    result.push_back(cur);

    auto end = std::make_pair((int)floor(s[1].x), (int)floor(s[1].y));
    bool move_up = s[0].y <= s[1].y;
    while (cur != end)
    {
        if (move_up)
        {
            point_2 p(cur.first + 1, cur.second + 1);
            auto o = orientation(s[0], s[1], p);
            if (o == CG_RIGHT)
                cur.second++;
            else if (o == CG_LEFT)
                cur.first++;
            else
            {
                cur.first++;
                cur.second++;
            }
        } else
        {
            point_2 p(cur.first + 1, cur.second);
            auto o = orientation(s[0], s[1], p);
            if (o == CG_RIGHT)
                cur.first++;
            else if (o == CG_LEFT)
                cur.second--;
            else
            {
                cur.first++;
                cur.second--;
            }
        }
        result.push_back(cur);
    }
    return result;
}

struct intersection_visitor : public boost::static_visitor<>
{
    std::vector<point_2>& points;
    intersection_visitor(std::vector<point_2>& points)
        :points(points)
    {

    }

    void operator() (boost::none_t const&)
    {

    }

    void operator() (point_2 const& p)
    {
        points.push_back(p);
    }

    void operator() (segment_2 const& s)
    {
        points.push_back(s[0]);
        points.push_back(s[1]);
    }
};

inline std::vector<point_2> intersection(triangle_2 const& a, triangle_2 const& b)
{
    std::vector<point_2> points;
    intersection_visitor visitor(points);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            segment_2 s {a[i], a[(i+1)%3]};
            segment_2 t {b[j], b[(j+1)%3]};
            auto pt = intersection(s, t, -10);
            boost::apply_visitor(visitor, pt);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (contains(a, b[i]))
            points.push_back(b[i]);
        if (contains(b, a[i]))
            points.push_back(a[i]);
    }

    auto it = jarvis_hull(points.begin(), points.end());

    return std::vector<point_2>(points.begin(), it);
}
}
