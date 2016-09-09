// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/intersections_d.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/06/13 15:47:49 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_INTERSECTIONS_D_H
#define CGAL_INTERSECTIONS_D_H

#include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

template <class R>
Object intersection(const Line_d<R>& l1, const Line_d<R>& l2)
{ typedef typename R::Line_d_Line_d_pair ll_pair;
  ll_pair LL(l1, l2);
  switch (LL.intersection_type()) {
    case ll_pair::NO:
    default: 
      return Object();
    case ll_pair::POINT: {
      Point_d<R> pt;
      LL.intersection(pt);
      return make_object(pt);
    }
    case ll_pair::LINE:
      return make_object(l1);
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Ray_d<R>& l1, const Ray_d<R>& l2)
{ typedef typename R::Ray_d_Ray_d_pair ll_pair;
  ll_pair LL(l1,l2);
  switch (LL.intersection_type()) {
    case ll_pair::NO:
    default: 
      return Object();
    case ll_pair::POINT: {
      Point_d<R> p;
      LL.intersection(p);
      return make_object(p);
    }
    case ll_pair::RAY: {
      Ray_d<R> r;
      LL.intersection(r);
      return make_object(r);
    }
    case ll_pair::SEGMENT: {
      Segment_d<R> s;
      LL.intersection(s);
      return make_object(s);
    }
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Segment_d<R>& l1, const Segment_d<R>& l2)
{ typedef typename R::Segment_d_Segment_d_pair ll_pair;
  ll_pair LL(l1,l2);
  switch (LL.intersection_type()) {
    case ll_pair::NO:
    default: 
      return Object();
    case ll_pair::POINT: {
      Point_d<R> p;
      LL.intersection(p);
      return make_object(p);
    }
    case ll_pair::SEGMENT: {
      Segment_d<R> s;
      LL.intersection(s);
      return make_object(s);
    }
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Line_d<R>& l, const Ray_d<R>& r)
{ typedef typename R::Line_d_Ray_d_pair lr_pair;
  lr_pair LR(l,r);
  switch (LR.intersection_type()) {
    case lr_pair::NO:
    default:
        return Object();
    case lr_pair::POINT: {
        Point_d<R> pt;
        LR.intersection(pt);
        return make_object(pt);
    }
    case lr_pair::RAY: {
        return make_object(r);
    }
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Ray_d<R>& r, const Line_d<R>& l)
{ return intersection(l,r); }

template <class R>
Object intersection(const Ray_d<R>& r, const Segment_d<R>& s)
{ typedef typename R::Ray_d_Segment_d_pair rs_pair;
  rs_pair RS(r,s);
  switch (RS.intersection_type()) {
    case rs_pair::NO:
    default:
        return Object();
    case rs_pair::POINT: {
        Point_d<R> pt;
        RS.intersection(pt);
        return make_object(pt);
    }
    case rs_pair::SEGMENT: {
        Segment_d<R> st;
        RS.intersection(st);
        return make_object(st);
    }
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Segment_d<R>& s, const Ray_d<R>& r)
{ return intersection(r,s); }

template <class R>
Object intersection(const Line_d<R>& l, const Segment_d<R>& s)
{ typedef typename R::Line_d_Segment_d_pair rs_pair;
  rs_pair RS(l,s);
  switch (RS.intersection_type()) {
    case rs_pair::NO:
    default:
        return Object();
    case rs_pair::POINT: {
        Point_d<R> pt;
        RS.intersection(pt);
        return make_object(pt);
    }
    case rs_pair::SEGMENT: {
        Segment_d<R> st;
        RS.intersection(st);
        return make_object(st);
    }
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Segment_d<R>& s, const Line_d<R>& l)
{ return intersection(l,s); }

template <class R>
Object intersection(const Line_d<R>& l, const Hyperplane_d<R>& h)
{
  typedef typename R::Line_d_Hyperplane_d_pair lh_pair;
  lh_pair LH(l,h);
  switch (LH.intersection_type()) {
    case lh_pair::NO:
    default:
        return Object();
    case lh_pair::POINT: {
        Point_d<R> pt;
        LH.intersection(pt);
        return make_object(pt);
    }
    case lh_pair::LINE:
        return make_object(l);
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Hyperplane_d<R>& h, const Line_d<R>& l)
{ return intersection(l,h); }

template <class R>
Object intersection(const Ray_d<R>& r, const Hyperplane_d<R>& h)
{
  typedef typename R::Ray_d_Hyperplane_d_pair rh_pair;
  rh_pair RH(r,h);
  switch (RH.intersection_type()) {
    case rh_pair::NO:
    default:
        return Object();
    case rh_pair::POINT: {
        Point_d<R> pt;
        RH.intersection(pt);
        return make_object(pt);
    }
    case rh_pair::RAY:
        return make_object(r);
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Hyperplane_d<R>& h, const Ray_d<R>& r)
{ return intersection(r,h); }

template <class R>
Object intersection(const Segment_d<R>& s, const Hyperplane_d<R>& h)
{ typedef typename R::Segment_d_Hyperplane_d_pair sh_pair;
  sh_pair SH(s,h);
  switch (SH.intersection_type()) {
    case sh_pair::NO:
    default:
        return Object();
    case sh_pair::POINT: {
        Point_d<R> pt;
        SH.intersection(pt);
        return make_object(pt);
    }
    case sh_pair::SEGMENT:
        return make_object(s);
  }
#if !defined(__KCC) && !defined(__BORLANDC__)
  return Object(); // never reached
#endif
}

template <class R>
Object intersection(const Hyperplane_d<R>& h, const Segment_d<R>& s)
{ return intersection(s,h); }

template <class R>
inline bool do_intersect(const Line_d<R> &l1, const Line_d<R> &l2)
{ typedef typename R::Line_d_Line_d_pair ll_pair;
  ll_pair LL(l1,l2);
  return LL.intersection_type() != ll_pair::NO;
}

template <class R>
inline bool do_intersect(const Ray_d<R> &l1, const Ray_d<R> &l2)
{ typedef typename R::Ray_d_Ray_d_pair ll_pair;
  ll_pair LL(l1,l2);
  return LL.intersection_type() != ll_pair::NO;
}

template <class R>
inline bool do_intersect(const Segment_d<R> &l1, const Segment_d<R> &l2)
{ typedef typename R::Segment_d_Segment_d_pair ll_pair;
  ll_pair LL(l1,l2);
  return LL.intersection_type() != ll_pair::NO;
}

template <class R>
inline bool do_intersect(const Line_d<R>& l, const Ray_d<R>& r)
{ typedef typename R::Line_d_Ray_d_pair lr_pair;
  lr_pair LR(l,r);
  return LR.intersection_type() != lr_pair::NO;
}

template <class R>
inline bool do_intersect(const Ray_d<R>& r, const Line_d<R>& l)
{ return do_intersect(l,r); }

template <class R>
inline bool do_intersect(const Line_d<R>& l, const Segment_d<R>& s)
{ typedef typename R::Line_d_Segment_d_pair ls_pair;
  ls_pair LS(l,s);
  return LS.intersection_type() != ls_pair::NO;
}

template <class R>
inline bool do_intersect(const Segment_d<R>& s, const Line_d<R>& l)
{ return do_intersect(l,s); }

template <class R>
inline bool do_intersect(const Ray_d<R>& r, const Segment_d<R>& s)
{ typedef typename R::Ray_d_Segment_d_pair rs_pair;
  rs_pair RS(r,s);
  return RS.intersection_type() != rs_pair::NO;
}

template <class R>
inline bool do_intersect(const Segment_d<R>& s, const Ray_d<R>& r)
{ return do_intersect(r,s); }

template <class R>
inline bool do_intersect(const Line_d<R>& l, const Hyperplane_d<R>& h)
{ typedef typename R::Line_d_Hyperplane_d_pair lh_pair;
  lh_pair LH(l,h);
  return LH.intersection_type() != lh_pair::NO;
}

template <class R>
inline bool do_intersect(const Hyperplane_d<R>& h, const Line_d<R>& l)
{ return do_intersect(l,h); }

template <class R>
inline bool do_intersect(const Ray_d<R>& r, const Hyperplane_d<R>& h)
{ typedef typename R::Ray_d_Hyperplane_d_pair rh_pair;
  rh_pair RH(r,h);
  return RH.intersection_type() != rh_pair::NO;
}

template <class R>
inline bool do_intersect(const Hyperplane_d<R>& h, const Ray_d<R>& r)
{ return do_intersect(r,h); }

template <class R>
inline bool do_intersect(const Segment_d<R>& s, const Hyperplane_d<R>& h)
{ typedef typename R::Segment_d_Hyperplane_d_pair sh_pair;
  sh_pair SH(s,h);
  return SH.intersection_type() != sh_pair::NO;
}

template <class R>
inline bool do_intersect(const Hyperplane_d<R>& h, const Segment_d<R>& s)
{ return do_intersect(s,h); }

CGAL_END_NAMESPACE
#endif //CGAL_INTERSECTIONS_D_H
