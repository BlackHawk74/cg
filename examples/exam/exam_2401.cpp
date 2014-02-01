#include <cg/exam/exam_2401.h>

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
       : segment({0, 0}, {10, 10})
   {
       rasterized = cg::rasterize(segment);
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      drawer.draw_point(segment[0], 2);
      drawer.draw_point(segment[1], 2);
      drawer.draw_line(segment[0], segment[1]);

      drawer.set_color(Qt::gray);
      for (auto const& pix : rasterized)
      {
          drawer.draw_line(point_2(pix.first, pix.second), point_2(pix.first + 1, pix.second));
          drawer.draw_line(point_2(pix.first, pix.second), point_2(pix.first, pix.second + 1));
          drawer.draw_line(point_2(pix.first + 1, pix.second), point_2(pix.first + 1, pix.second + 1));
          drawer.draw_line(point_2(pix.first, pix.second + 1), point_2(pix.first + 1, pix.second + 1));
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton to move point"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f &p)
   {
      button_pressed = true;
      return set_idx(p);
   }

   bool on_release(const point_2f &)
   {
      button_pressed = false;
      rasterized = cg::rasterize(segment);
      idx.reset();
      return true;
   }

   bool on_move(const point_2f & p)
   {
       if (button_pressed && idx)
       {
          segment[*idx] = {p.x, p.y};
          return true;
       }
       return false;
   }

private:
   bool set_idx(point_2f const& p)
   {
       idx.reset();
       for (int i = 0; i < 2; i++)
       {
           if (fabs(segment[i].x - p.x) < 1.0 && fabs(segment[i].y - p.y) < 1.0)
           {
               idx = i;
               return true;
           }
       }
       return false;
   }

   bool button_pressed = false;
   boost::optional<int> idx;
   cg::segment_2 segment;
   std::vector<std::pair<int, int> > rasterized;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segments_intersect_viewer viewer;
   cg::visualization::run_viewer(&viewer, "rasterize viewer");
}

