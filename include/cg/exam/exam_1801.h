#include <cg/primitives/point.h>
#include <vector>
#include <set>

namespace cg
{
struct y_comparator
{
    bool operator() (point_2 const a, point_2 const& b)
    {
        return a.y < b.y;
    }
};

std::vector<point_2> find_maximums(std::vector<point_2> points)
{
    std::sort(points.begin(), points.end());
    std::set<point_2, y_comparator> current;
    std::vector<point_2> result;
    for (auto i = points.rbegin(); i != points.rend(); ++i)
    {
        if (current.lower_bound(*i) == current.end())
        {
            result.push_back(*i);
        }
        current.insert(*i);
    }
    return result;
}

}
