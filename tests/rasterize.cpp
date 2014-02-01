#include <cg/exam/exam_2401.h>
#include <gtest/gtest.h>

TEST(rasterize_segment, test1)
{
    auto res = cg::rasterize({{0.5, 0.5}, {1.5, 0.5}});
    std::vector<std::pair<int, int> > t{{0, 0}, {1, 0}};
    ASSERT_EQ(t, res);
}

TEST(rasterize_segment, test2)
{
    auto res = cg::rasterize({{0.5, 0.5}, {1.5, 1.5}});
    std::vector<std::pair<int, int> > t{{0, 0}, {1, 1}};
    ASSERT_EQ(t, res);
}

TEST(rasterize_segment, test3)
{
    auto res = cg::rasterize({{0.5, 0.5}, {2.5, -1.7}});
    std::vector<std::pair<int, int> > t{{0, 0}, {0, -1}, {1, -1}, {1, -2}, {2, -2}};
    ASSERT_EQ(t, res);
}
