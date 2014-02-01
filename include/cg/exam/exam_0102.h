#pragma once

#include <cg/primitives/contour.h>
#include <cg/operations/intersection/segment_segment.h>
#include <algorithm>

namespace cg
{

struct contour_intersection
{
    size_t idx;
    point_2 p;

    contour_intersection(size_t idx, point_2 const& p)
        : idx(idx), p(p)
    {}
};

bool operator <(contour_intersection const& a, contour_intersection const& b)
{
    return a.p.y > b.p.y;
}

bool operator ==(contour_intersection const& a, contour_intersection const& b)
{
    return a.idx == b.idx;
}

size_t pair(size_t i)
{
    return i % 2 ? i - 1 : i + 1;
}

std::vector<contour_2> split(contour_2 contour, double x)
{
    if (!counterclockwise(contour))
    {
        contour.reverse();
    }

    std::vector<contour_intersection> intersections;

    for (size_t l = 0, lp = contour.size() - 1; l != contour.size(); lp = l++)
    {
        segment_2 s(contour[lp], contour[l]);
        if (min(s).x <= x && max(s).x >= x)
        {
            double t = (x - s[1].x) / (s[0].x - s[1].x);
            point_2 int_pt = s[1] + t * (s[0] - s[1]);
            intersections.push_back(contour_intersection(lp, int_pt));
        }
    }

    auto cmp = [](contour_intersection const& a, contour_intersection const& b)
    {
        return a.p.y > b.p.y;
    };

    std::sort(intersections.begin(), intersections.end(), cmp);
    std::vector<int> idx_backref(contour.size(), -1);
    for (size_t i = 0; i < intersections.size(); i++)
    {
        idx_backref[intersections[i].idx] = i;
    }

    std::vector<contour_2> contours;
    {
        std::vector<point_2> v;
        contour_2 c(v);
        contours.push_back(c);
    }

    std::vector<int> crossbacks(1, -1);
    size_t cur = 0;
    for (size_t l = 0, lp = contour.size() - 1; l != contour.size(); lp = l++)
    {
        contours[cur].add_point(contour[lp]);
        segment_2 s(contour[lp], contour[l]);
        if (min(s).x <= x && max(s).x >= x)
        {
            if (idx_backref[lp] != -1)
            {
                contour_intersection ci = intersections[idx_backref[lp]];
                contours[cur].add_point(ci.p);
                crossbacks[cur] = pair(idx_backref[lp]);
                contours[cur].add_point(intersections[crossbacks[cur]].p);
                auto it2 = std::find_if(crossbacks.begin(), crossbacks.end(), [&ci,&intersections] (int i) {
                    return i != -1 && intersections[i].idx == ci.idx;
                });
                if (it2 != crossbacks.end())
                {
                    cur = it2 - crossbacks.begin();
//                    contours[cur].add_point(intersections[*it2].p);
                } else
                {
                    std::vector<point_2> v;
                    v.push_back(ci.p);
                    contour_2 c(v);
                    contours.push_back(c);
                    crossbacks.push_back(-1);

                    cur = contours.size() - 1;
                }
             }
        }
    }
    return contours;
}

}
