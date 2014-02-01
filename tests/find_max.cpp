#include <gtest/gtest.h>
#include <algorithm>
#include <cg/exam/exam_1801.h>
#include "random_utils.h"
using cg::point_2;

bool check_answer(std::vector<point_2>& v, std::vector<point_2>& ans)
{
    std::vector<point_2> dumb_ans;
    for (auto const& p : v) {
        if (std::all_of(v.begin(), v.end(), [p](point_2 const& q) {
                        if (q.x > p.x && q.y >= p.y) return false;
                        return true;
        }))
        {
            dumb_ans.push_back(p);
        }
    }
    std::sort(ans.begin(), ans.end());
    std::sort(dumb_ans.begin(), dumb_ans.end());
    if (ans.size() != dumb_ans.size())
        return false;

    for (size_t i = 0; i < ans.size(); i++)
    {
        if (ans[i] != dumb_ans[i])
            return false;
    }
    return true;
}

TEST(find_max, test1)
{


    std::vector<point_2> points {
        {0, 0},
        {1, 0},
        {0, 1}
    };

    auto ans = cg::find_maximums(points);
    ASSERT_TRUE(check_answer(points, ans));
}

TEST(find_max, test2)
{
    std::vector<point_2> points {
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 1}
    };

    auto ans = cg::find_maximums(points);
    ASSERT_TRUE(ans.size() == 2);
    ASSERT_TRUE(check_answer(points, ans));
}

TEST(find_max, test3)
{
    for (int i = 0; i < 10; i++)
    {
        auto points = uniform_points(100000);
        auto ans = cg::find_maximums(points);
        ASSERT_TRUE(check_answer(points, ans));
    }
}
