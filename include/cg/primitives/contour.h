#pragma once

#include <vector>

#include "point.h"
#include "cg/common/range.h"

namespace cg
{
   template <class Scalar>
   struct contour_2t;

   typedef contour_2t<float> contour_2f;
   typedef contour_2t<double> contour_2;
   typedef contour_2t<int>   contour_2i;

   template <class Scalar>
   struct contour_2t
   {
      contour_2t(std::vector<point_2t<Scalar> > && pts) : pts_(pts)
      {}

      contour_2t(contour_2t const&)              = delete;
      contour_2t& operator = (contour_2t const&) = delete;

      contour_2t(contour_2t && cnt);
      contour_2t& operator = (contour_2t && cnt);

      typedef typename std::vector<point_2t<Scalar> >::const_iterator const_iterator;

      const_iterator begin()    const
      {
         return pts_.begin();
      }
      const_iterator end()      const
      {
         return pts_.end();
      }

      common::range_circulator<contour_2t<Scalar>> circulator() const
      {
         return common::range_circulator<contour_2t<Scalar>>(*this);
      }

      common::range_circulator<contour_2t<Scalar>> circulator(const_iterator itr) const
      {
         return common::range_circulator<contour_2t<Scalar>>(*this, itr);
      }

      size_t vertices_num() const
      {
         return pts_.size();
      }

      point_2t<Scalar> const& operator [] (size_t idx) const
      {
         return pts_[idx];
      }

   private:
      friend struct contour_builder_type;

      std::vector<point_2t<Scalar> > pts_;
   };

   typedef common::range_circulator<contour_2f> contour_circulator;
}
