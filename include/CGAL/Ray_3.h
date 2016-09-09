// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : Ray_3.fw
// file          : include/CGAL/Ray_3.h
// package       : _3 (2.1.2)
// revision      : 2.1.2
// revision_date : 21 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_RAY_3_H
#define CGAL_RAY_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_RAYH3_H
#include <CGAL/RayH3.h>
#endif // CGAL_RAYH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_RAYC3_H
#include <CGAL/RayC3.h>
#endif // CGAL_RAYC3_H
#endif // CGAL_CARTESIAN_H

CGAL_BEGIN_NAMESPACE

template <class _R>
class Ray_3 : public _R::Ray_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Ray_3                 RRay_3;

  Ray_3() : RRay_3()
  {}
  Ray_3(const Ray_3<R>& r) : RRay_3(r)
  {}
  Ray_3(const RRay_3&  r) : RRay_3(r)
  {}
  Ray_3(const Point_3<R>& sp,
            const Point_3<R>& secondp)
    : RRay_3(sp, secondp)
  {}
  Ray_3(const Point_3<R>& sp,
            const Direction_3<R>& d)
    : RRay_3(sp, d)
  {}

  Ray_3<R>&      operator=(const Ray_3<R>& r)
  {
      RRay_3::operator=(r);
      return *this;
  }
  bool                operator==(const Ray_3<R>& r) const
  { return RRay_3::operator==(r); }
  bool                operator!=(const Ray_3<R>& r) const
  { return !(*this == r); }

  int                 id() const  /* XXX */
  { return (int)  PTR ; }

  Point_3<R>     start() const
  { return RRay_3::start(); }
  Point_3<R>     source() const
  { return RRay_3::source(); }
  Point_3<R>     second_point() const
  { return RRay_3::second_point(); }
  Point_3<R>     point(int i) const
  { return RRay_3::point(i); }
  Direction_3<R> direction() const
  { return RRay_3::direction(); }
  Line_3<R>      supporting_line() const
  { return RRay_3::supporting_line(); }
  Ray_3<R>       opposite() const
  { return RRay_3::opposite(); }
  Ray_3<R>       transform(const Aff_transformation_3<R>& t) const
  { return RRay_3::transform(t); }
  bool                is_degenerate() const
  { return RRay_3::is_degenerate(); }
  bool                has_on(const Point_3<R>& p) const
  { return RRay_3::has_on(p); }
};

#ifndef NO_OSTREAM_INSERT_RAY_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Ray_3<R>& r)
{
  typedef typename  R::Ray_3        RRay_3;
  return os << (const RRay_3& )r;
}
#endif // NO_OSTREAM_INSERT_RAY_3

#ifndef NO_ISTREAM_EXTRACT_RAY_3
template < class R >
std::istream&
operator>>(std::istream& is, Ray_3<R>& r)
{
  typedef typename  R::Ray_3        RRay_3;
  return is >> (RRay_3& )r;
}
#endif // NO_ISTREAM_EXTRACT_RAY_3


CGAL_END_NAMESPACE


#ifndef CGAL_LINE_3_H
#include <CGAL/Line_3.h>
#endif // CGAL_LINE_3_H

#endif // CGAL_RAY_3_H