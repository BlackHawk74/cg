#include <gtest/gtest.h>
#include <cg/operations/intersections.h>
#include <initializer_list>
#include <vector>

using namespace cg;

// -- START point in convex contour --
TEST(convex_contour_point, t1)
{
   contour_2 contour( {{0, 0}, {2, 2}, {2, 0}});
   point_2 p {1, 0.5};
   EXPECT_EQ(point_in_convex_contour(contour, p), true);
}

TEST(convex_contour_point, t2)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 2}, {2, 0}});
   point_2 p {1, 1};
   EXPECT_EQ(point_in_convex_contour(contour, p), true);
}


TEST(convex_contour_point, t3)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 2}, {2, 0}});
   point_2 p {-1, 1};
   EXPECT_EQ(point_in_convex_contour(contour, p), false);
}

TEST(convex_contour_point, t4)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 4}, {4, 5}, {5, 3}, {4, 1}, {2, 0}});
   point_2 p {4, 4};
   EXPECT_EQ(point_in_convex_contour(contour, p), true);
}

TEST(convex_contour_point, t5)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 4}, {4, 5}, {5, 3}, {4, 1}, {2, 0}});
   point_2 p {1, 3};
   EXPECT_EQ(point_in_convex_contour(contour, p), true);
}

TEST(convex_contour_point, t6)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 4}, {4, 5}, {5, 3}, {4, 1}, {2, 0}});
   point_2 p {1, 4};
   EXPECT_EQ(point_in_convex_contour(contour, p), false);
}

TEST(convex_contour_point, t7)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 0}});
   point_2 p {1, 0};
   EXPECT_EQ(point_in_convex_contour(contour, p), true);
}

TEST(convex_contour_point, t8)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 0}});
   point_2 p {0, 1};
   EXPECT_EQ(point_in_convex_contour(contour, p), true);
}
// -- END point in convex contour --

// -- START point in arbitrary contour --
TEST(contour_point, t1)
{
   contour_2 contour( {{0, 0}, {2, 2}, {2, 0}});
   point_2 p {1, 0.5};
   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t2)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 2}, {2, 0}});
   point_2 p {1, 1};
   EXPECT_EQ(point_in_contour(contour, p), true);
}


TEST(contour_point, t3)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 2}, {2, 0}});
   point_2 p {-1, 1};
   EXPECT_EQ(point_in_contour(contour, p), false);
}

TEST(contour_point, t4)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 4}, {4, 5}, {5, 3}, {4, 1}, {2, 0}});
   point_2 p {4, 4};
   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t5)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 4}, {4, 5}, {5, 3}, {4, 1}, {2, 0}});
   point_2 p {1, 3};
   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t6)
{
   contour_2 contour( {{0, 0}, {0, 2}, {2, 4}, {4, 5}, {5, 3}, {4, 1}, {2, 0}});
   point_2 p {1, 4};
   EXPECT_EQ(point_in_contour(contour, p), false);
}

TEST(contour_point, t7)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {1, 0};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t8)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {3, 0};

   EXPECT_EQ(point_in_contour(contour, p), false);
}

TEST(contour_point, t9)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {0, 0};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t10)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {5, 1};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t11)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {3, 1};

   EXPECT_EQ(point_in_contour(contour, p), false);
}


TEST(contour_point, t12)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {0, 1};

   EXPECT_EQ(point_in_contour(contour, p), false);
}

TEST(contour_point, t13)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {7, 3};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t14)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {7, 2};

   EXPECT_EQ(point_in_contour(contour, p), false);
}

TEST(contour_point, t15)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {7.00001, 3};

   EXPECT_EQ(point_in_contour(contour, p), false);
}

TEST(contour_point, t16)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {3, 2};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t17)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {3.00001, 2};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t18)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 3}});
   point_2 p {2.9999, 2};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t19)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 4}});
   point_2 p {3, 4};

   EXPECT_EQ(point_in_contour(contour, p), true);
}

TEST(contour_point, t20)
{
   contour_2 contour( {{0, 0}, {2, 0}, {3, 2}, {4, 0}, {6, 0}, {7, 3}, {3, 4}});
   point_2 p {3.00001, 4};

   EXPECT_EQ(point_in_contour(contour, p), false);
}
// -- END point in arbitrary contour --
