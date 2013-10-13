#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/point.h>
#include <cg/operations/has_intersection/segment_segment.h>
#include <vector>

namespace cg
{
   namespace detail
   {
      template<class Iterator>
      bool segment_in_visibility_graph(segment_2 const& segment, Iterator begin, Iterator end)
      {
         for (auto i = begin; i != end; ++i)
         {
            contour_2 const& contour = *i;
            if (contour.size() == 0) continue;

            for (size_t lp = contour.size() - 1, l = 0; l != contour.size(); lp = l++)
            {
               segment_2 test_segment { contour[lp], contour[l] };
               if (min(segment) == min(test_segment)
                   && max(segment) == max(test_segment))
                  // Polygon has no self-intersections, so we can always go along its border
                  return true;

               if (!(segment[0] == test_segment[0]
                     || segment[1] == test_segment[0]
                     || segment[0] == test_segment[1]
                     || segment[1] == test_segment[1])
                   && has_intersection(segment, test_segment))
                  return false;
            }
         }
         return true;
      }

      contour_circulator next_circulator(contour_circulator i)
      {
         return ++i;
      }

      contour_circulator prev_circulator(contour_circulator i)
      {
         return --i;
      }

      bool check_angle(point_2 const& p, point_2 const& q, point_2 const& prev, point_2 const& next)
      {
         return orientation(prev, p, q) != CG_RIGHT || orientation(p, next, q) != CG_RIGHT;
      }

      template<class Iterator>
      void process_contour(std::vector<segment_2>& result, point_2 const& p,
                           contour_2 const& contour, Iterator begin, Iterator end,
                           point_2 const& p_prev, point_2 const& p_next)
      {
         for (auto it = contour.begin(); it != contour.end(); ++it)
         {
            auto const& q = *it;
            auto circulator = contour.circulator(it);

            auto const& prev = *prev_circulator(circulator);
            auto const& next = *next_circulator(circulator);

            if (p_prev != p_next
                && !check_angle(q, p, p_prev, p_next))
               continue;

            if (p != q
                && detail::segment_in_visibility_graph({p, q}, begin, end)
                && check_angle(p, q, prev, next)) {
               result.push_back({p, q});
               result.push_back({q, p});
            }
         }
      }

   }

   template<class Iterator>
   std::vector<segment_2> visibility_graph_simple(point_2 const& start, point_2 const& finish, Iterator begin, Iterator end)
   {
      std::vector<segment_2> result;

      if (detail::segment_in_visibility_graph({start, finish}, begin, end))
      {
         result.push_back({start, finish});
         return result;
      }

      for (auto i = begin; i != end; ++i)
      {
         contour_2 const& contour = *i;
         detail::process_contour(result, start, contour, begin, end, start, start);
         detail::process_contour(result, finish, contour, begin, end, start, start);
      }

      for (auto i = begin; i != end; i++)
      {
         contour_2 const& contour = *i;
         for (auto contour_itr1 = contour.begin(); contour_itr1 != contour.end(); ++contour_itr1)
         {
            auto const& p = *contour_itr1;

            auto circulator = contour.circulator(contour_itr1);
            auto const& p_prev = *(detail::prev_circulator(circulator));
            auto const& p_next = *(detail::next_circulator(circulator));

            for (auto contour_itr2 = std::next(contour_itr1); contour_itr2 != contour.end(); ++contour_itr2)
            {
               bool add = true;
               for (auto internal = std::next(contour_itr1); internal != contour_itr2; ++internal)
               {
                  if (orientation(p, *contour_itr2, *internal) == CG_LEFT)
                  {
                     add = false;
                     break;
                  }
               }
               if (add)
               {
                  circulator = contour.circulator(contour_itr2);
                  auto const& q = *contour_itr2;
                  if (detail::check_angle(p, q,
                                  *detail::prev_circulator(circulator),
                                  *detail::next_circulator(circulator))
                      && detail::check_angle(q, p, p_prev, p_next))
                  {
                     result.push_back({p, *contour_itr2});
                     result.push_back({*contour_itr2, p});
                  }
               }
            }

            if (contour_itr1 != contour.begin()) {
               bool add = true;
               auto const& fst = *contour.begin();
               for (auto internal = std::next(contour_itr1);
                    internal != contour.end(); ++internal)
               {
                  if(orientation(*contour_itr1, fst, *internal) == CG_LEFT)
                  {
                     add = false;
                     break;
                  }
               }

               if (add)
               {
                  if (detail::check_angle(p, fst,
                                          *std::prev(contour.end()),
                                          *std::next(contour.begin()))
                      && detail::check_angle(fst, p, p_prev, p_next))
                  {
                     result.push_back({p, fst});
                     result.push_back({fst, p});
                  }
               }
            }

            for(auto j = std::next(i); j != end; ++j)
            {
              detail::process_contour(result, p, *j, begin, end, p_prev, p_next);
            }
         }
      }


      return result;
   }

}
