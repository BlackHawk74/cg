#include <cg/exam/exam_0102.h>

#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/triangle.h>
#include <cg/primitives/point.h>

#include <cg/operations/contains/contour_point.h>
#include <vector>
#include <cstdlib>

using cg::point_2f;
using cg::point_2;


struct contour_contains_point_viewer : cg::visualization::viewer_adapter
{
   contour_contains_point_viewer()
      : contour(std::vector<point_2>({point_2(0, 0), point_2(100, 100), point_2(200, 0)}))
   {
       splitted = cg::split(contour, x);
       for (int i = 0; i < 100; i++) {
          QColor color(50 + rand() % 200, 50 + rand() % 200, 58 + 2 * i);
          colors.push_back(color);
       }
   }

   void draw(cg::visualization::drawer_type & drawer) const override
   {
      drawer.set_color(Qt::white);
      drawer.draw_line(point_2(x, -200), point_2(x, 200));

      int j = 0;
      for (auto const& contour : splitted)
      {
          drawer.set_color(colors[j++]);

          for (size_t l = 0, lp = contour.size() - 1; l != contour.size(); lp = l++)
             drawer.draw_line(contour[lp], contour[l]);
      }

   }

   void print(cg::visualization::printer_type & p) const override
   {
      p.corner_stream() << "press mouse lbutton with CTRL key near contour vertex to move it"
                        << cg::visualization::endl
                        << "if triangle is green contour contains cursor point"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p) override
   {
      for (size_t l = 0; l != contour.size(); ++l)
      {
         if (fabs(p.x - contour[l].x) < 4 && fabs(p.y - contour[l].y) < 4)
         {
            idx_ = l;
            return true;
         }
      }

      contour.add_point(p);
      splitted = cg::split(contour, x);

      return false;
   }

   bool on_double_click(const cg::point_2f &p)
   {
       x = p.x;
       splitted = cg::split(contour, x);
       for (auto& i : splitted)
       {
           for (auto& j : i)
               std::cout << j << "\n";
           std::cout << "------------" << std::endl;
       }
       std::cout << "@@@@@@@@" << std::endl;
       return true;
   }

   bool on_release(const point_2f & p) override
   {
      idx_.reset();
      splitted = cg::split(contour, x);
      return false;
   }

   bool on_move(const point_2f & p) override
   {
      if (!idx_)
         return true;

      contour[*idx_] = p;
      return true;
   }

private:
   cg::contour_2 contour;
   double x = 0.0;
   std::vector<QColor> colors;
   std::vector<cg::contour_2> splitted;
   boost::optional<size_t> idx_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   contour_contains_point_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Contour contains point");
}
