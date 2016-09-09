// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Cartesian/plane_constructions_3.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/11/03 13:53:55 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PLANE_CONSTRUCTIONS_3_H
#define CGAL_CARTESIAN_PLANE_CONSTRUCTIONS_3_H

#include <CGAL/Cartesian/redefine_names_3.h>
#include <CGAL/Cartesian/Point_3.h>
#include <CGAL/constructions/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template <class R>
CGAL_KERNEL_LARGE_INLINE
PlaneC3<R CGAL_CTAG>
plane_from_points(const PointC3<R CGAL_CTAG> &p,
                  const PointC3<R CGAL_CTAG> &q,
		  const PointC3<R CGAL_CTAG> &r)
{
  typename R::FT a, b, c, d;
  plane_from_pointsC3(p.x(), p.y(), p.z(),
                      q.x(), q.y(), q.z(),
                      r.x(), r.y(), r.z(),
                      a, b, c, d);
  return PlaneC3<R CGAL_CTAG>(a, b, c, d);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PlaneC3<R CGAL_CTAG>
plane_from_point_direction(const PointC3<R CGAL_CTAG> &p,
                           const DirectionC3<R CGAL_CTAG> &d)
{
  typename R::FT A, B, C, D;
  plane_from_point_directionC3(p.x(), p.y(), p.z(), d.dx(), d.dy(), d.dz(),
                               A, B, C, D);
  return PlaneC3<R CGAL_CTAG>(A, B, C, D);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_PLANE_CONSTRUCTIONS_3_H