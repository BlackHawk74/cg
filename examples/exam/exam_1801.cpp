#include <cg/exam/exam_1801.h>
#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>

#include <cg/operations/has_intersection/segment_segment.h>

using cg::point_2;
using cg::point_2f;

struct segments_intersect_viewer : cg::visualization::viewer_adapter
{
   segments_intersect_viewer()
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (auto const& p : points)
      {
          drawer.draw_point(p, 2);
      }
      drawer.set_color(Qt::green);
      for (auto const& p : answer) {
          drawer.draw_point(p, 2);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton to add point"
                        << cg::visualization::endl
                        << "if point is green, it is in answer"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      points.push_back(p);
      answer = cg::find_maximums(points);
      return true;
   }

   bool on_release(const point_2f & p)
   {
      return false;
   }

   bool on_move(const point_2f & p)
   {
        return false;
   }

private:
    std::vector<point_2> points;
    std::vector<point_2> answer;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segments_intersect_viewer viewer;
   cg::visualization::run_viewer(&viewer, "max viewer");
}

