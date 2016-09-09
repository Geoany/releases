// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Planar_map_2/Onetuple.h
// package       : Planar_map (5.73)
// revision      : 1.0
// revision_date : 27 Jun 2000 
// author(s)     : Oren Nechushtan
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_PLANAR_MAP_2_ONETUPLE_H
#define CGAL_PLANAR_MAP_2_ONETUPLE_H

CGAL_BEGIN_NAMESPACE

template < class T >
class _Onetuple : public Rep
{
public:
  T  e0;

  _Onetuple() {}
  _Onetuple(const T & a0) : e0(a0) {}
  ~_Onetuple() {}
};

template < class T >
class Onetuple : public Ref_counted
{
public:
  T  e0;

  Onetuple() {}
  Onetuple(const T & a0) : e0(a0) {}
};

CGAL_END_NAMESPACE

#endif // CGAL_PLANAR_MAP_2_ONETUPLE_H