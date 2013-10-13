#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/contour.h>
#include <cg/operations/orientation.h>
#include "visibility_graph.h"

using cg::point_2;
using cg::segment_2;
using cg::contour_2;
using cg::point_2f;
using cg::vector_2f;

struct visibility_graph_viewer : cg::visualization::viewer_adapter
{
   visibility_graph_viewer()
      : polygon({contour_2({})}), current_poly(0), start(-10, 0), finish(10, 0)
   {
      visibility_graph = cg::visibility_graph_simple(start, finish, polygon.begin(), polygon.end());
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (auto const& contour : polygon)
      {
         for (size_t lp = contour.size() - 1, l = 0; l != contour.size(); lp = l++)
         {
            drawer.draw_line(contour[lp], contour[l], 1.5);
         }
      }

      drawer.set_color(Qt::green);
      for (auto const& segment : visibility_graph)
      {
         drawer.draw_line({segment[0], segment[1]});
      }

      drawer.set_color(Qt::red);
      drawer.draw_point(start, 3);

      drawer.set_color(Qt::blue);
      drawer.draw_point(finish, 3);
   }

   void print(cg::visualization::printer_type & p) const
   {
      auto s = current_poly == -2 ? "finish point" : current_poly == -1 ? "start point" : "polygon #" + std::to_string(current_poly);
      p.corner_stream() << "double-click to clear." << cg::visualization::endl
                        << "press mouse rbutton to add vertex. Press j/k to switch between polygons and points of start and finish" << cg::visualization::endl
                        << "Current polygon: " << s << cg::visualization::endl;
   }

   bool on_double_click(const point_2f &)
   {
      polygon.clear();
      polygon.push_back(contour_2({}));
      visibility_graph.clear();
      current_poly = 0;
      return true;
   }

   bool on_press(const point_2f & p)
   {
      switch (current_poly) {
      case -2:
         finish = p;
         break;
      case -1:
         start = p;
         break;
      default:
         {
            polygon[current_poly].add_point(p);

            if (cg::counterclockwise(polygon[current_poly]))
            {
               polygon[current_poly].reverse();
            }
         }

         break;
      }


      visibility_graph = cg::visibility_graph_simple(start, finish, polygon.begin(), polygon.end());
      return true;
   }


      bool on_key(int key_t) override
      {
         switch (key_t) {
         case Qt::Key_K:
            current_poly++;
            if (current_poly == (int)polygon.size())
               polygon.push_back(contour_2({}));

            return true;
         case Qt::Key_J:
            if (current_poly > -2)
               current_poly--;
            return true;
         default:
            break;
         }
         return false;
      }

   private:
      std::vector<contour_2> polygon;
      std::vector<segment_2> visibility_graph;
      int current_poly;
      point_2 start, finish;
   };

   int main(int argc, char ** argv)
   {
      QApplication app(argc, argv);
      visibility_graph_viewer viewer;
      cg::visualization::run_viewer(&viewer, "visibility graph viewer");
}
