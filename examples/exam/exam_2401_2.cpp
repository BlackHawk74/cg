#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/segment.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/point.h>

#include <cg/operations/has_intersection/triangle_segment.h>
#include <cg/exam/exam_2401.h>

using cg::point_2;
using cg::point_2f;

struct triangle_intersects_triangle_viewer : cg::visualization::viewer_adapter
{
   triangle_intersects_triangle_viewer()
       : s_(point_2(-100, -100), point_2(50, 50), point_2(0, 50)),
        t_(point_2(-50, -50), point_2(50, -50), point_2(-50, 50)),
         rbutton_pressed_(false),
         int_({})
   {
       int_ = cg::intersection(s_, t_);
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);

//      drawer.draw_line(s_[0], s_[1]);
      for (size_t l = 0, lp = 2; l != 3; lp = l++)
      {
         drawer.draw_line(t_[lp], t_[l]);
         drawer.draw_line(s_[lp], s_[l]);
      }

      drawer.set_color(Qt::green);
      for (size_t l = 0, lp = int_.size() - 1; l != int_.size(); lp = l++)
      {
          drawer.draw_line(int_[lp], int_[l]);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near segment vertex to move it"
                        << cg::visualization::endl
                        << "if lines are green there is intersection"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
       rbutton_pressed_ = true;
      return set_idx(p);
   }

   bool on_release(const point_2f & p)
   {
      rbutton_pressed_ = false;
      int_ = cg::intersection(s_, t_);
      return true;
   }

   bool on_move(const point_2f & p)
   {
      if (!rbutton_pressed_)
         set_idx(p);
      if (!idx_)
         return true;

      if (rbutton_pressed_) {
         if((*idx_).first)
            s_[(*idx_).second] = p;
         else
            t_[(*idx_).second] = p;

         int_ = cg::intersection(s_, t_);
      }
      return true;
   }

private:
   bool set_idx (const point_2f & p)
   {
      idx_.reset();
      float max_r;
      for (size_t l = 0; l != 3; ++l)
      {
         float current_r = (p.x - t_[l].x) * (p.x - t_[l].x) + (p.y - t_[l].y) * (p.y - t_[l].y);
         if ((idx_ && current_r < max_r) || (!idx_ && current_r < 100))
         {
            idx_ = std::make_pair(false, l);
            max_r = current_r;
         }
      }
      for (size_t l = 0; l != 3; ++l)
      {
         float current_r = (p.x - s_[l].x) * (p.x - s_[l].x) + (p.y - s_[l].y) * (p.y - s_[l].y);
         if ((idx_ && current_r < max_r) || (!idx_ && current_r < 100))
         {
            idx_ = std::make_pair(true, l);
            max_r = current_r;
         }
      }

      return idx_;
   }

   cg::triangle_2 s_;
   cg::triangle_2 t_;
   boost::optional< std::pair<bool, size_t> > idx_;
   bool rbutton_pressed_;
   std::vector<point_2> int_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   triangle_intersects_triangle_viewer viewer;
   cg::visualization::run_viewer(&viewer, "triangle intersects triangle");
}
