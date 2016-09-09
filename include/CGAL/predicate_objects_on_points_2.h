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
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/predicate_objects_on_points_2.h
// package       : Convex_hull (2.0.8)
// source        : convex_hull_2.lw
// revision      : 2.0.8
// revision_date : 06 May 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H
#define CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H

#include <CGAL/user_classes.h>

CGAL_BEGIN_NAMESPACE
template <class Point>
class p_Left_of_line_2p
{
public:
        p_Left_of_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        { return leftturn( p_a, p_b, c ); }

private:
    Point p_a;
    Point p_b;
};

template <class Point>
class p_Right_of_line_2p
{
public:
        p_Right_of_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        { return rightturn( p_a, p_b, c ); }

private:
    Point p_a;
    Point p_b;
};

template <class Point>
class p_Right_of_line_2p_safer
{
public:
        p_Right_of_line_2p_safer(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        {
          if ( (c == p_a) || ( c == p_b ) ) return false;
          return rightturn( p_a, p_b, c );
        }

private:
    Point p_a;
    Point p_b;
};


template <class Point>
struct p_Less_xy
{
  bool operator()( const Point& p1, const Point& p2) const
       { return lexicographically_xy_smaller( p1, p2); }
};

template <class Point>
struct p_Greater_xy
{
  bool operator()( const Point& p1, const Point& p2) const
       { return lexicographically_xy_larger( p1, p2); }
};

template <class Point>
struct p_Less_yx
{
  bool operator()( const Point& p1, const Point& p2) const
       { return lexicographically_yx_smaller( p1, p2); }
};

template <class Point>
struct p_Greater_yx
{
  bool operator()( const Point& p1, const Point& p2) const
       { return lexicographically_yx_larger( p1, p2); }
};

template <class Point>
class p_Less_dist_to_line_2p
{
public:
        p_Less_dist_to_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c, const Point& d) const
        {
          Comparison_result 
            res = cmp_signed_dist_to_line( p_a, p_b, c, d);
          if ( res == LARGER )
          {
              return false;
          }
          else if ( res == SMALLER )
          {
              return true;
          }
          else
          {
              return lexicographically_xy_smaller( c, d );
          }
        }

private:
  Point           p_a;
  Point           p_b;
};

template <class Point>
class p_Less_negative_dist_to_line_2p
{
public:
        p_Less_negative_dist_to_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c, const Point& d) const
        {
          Comparison_result 
            res = cmp_signed_dist_to_line( p_a, p_b, c, d);
          if ( res == LARGER )
          {
              return true;
          }
          else if ( res == SMALLER )
          {
              return false;
          }
          else
          {
              return lexicographically_xy_smaller( c, d );
          }
        }

private:
  Point           p_a;
  Point           p_b;
};

template <class Point>
class p_Less_rotate_ccw
{
public:
        p_Less_rotate_ccw(const Point& p)
        : rot_point(p)
        {}

  bool  operator()(const Point& p, const Point& q) const
        {
          Orientation ori = orientation(rot_point, p, q);
          if ( ori == LEFTTURN )
          {
              return true;
          }
          else if ( ori == RIGHTTURN )
          {
              return false;
          }
          else
          {
              if (p == rot_point) return false;
              if (q == rot_point) return true;
              if (p == q)         return false;
              return  collinear_are_ordered_along_line( rot_point, q, p);
          }
        }

  void  set_rotation_center( const Point& p)
        { rot_point = p; }


private:
    Point  rot_point;
};

template <class Point>
class p_Less_rotate_ccw_safer
{
public:
        p_Less_rotate_ccw_safer(const Point& p)
        : rot_point(p)
        {}

  bool  operator()(const Point& p, const Point& q) const
        {
          if (p == rot_point) return false;
          if (q == rot_point) return true;
          if (p == q)         return false;
          Orientation ori = orientation(rot_point, p, q);
          if ( ori == LEFTTURN )
          {
              return true;
          }
          else if ( ori == RIGHTTURN )
          {
              return false;
          }
          else
          {
              return  collinear_are_ordered_along_line( rot_point, q, p);
          }
        }
  
  void  set_rotation_center( const Point& p)
        { rot_point = p; }


private:
  Point  rot_point;
};

template <class Point>
class p_Less_rotate_ccw_E
{
public:
        p_Less_rotate_ccw_E(const Point& p)
        : rot_point(p)
        {}

  bool  operator()(const Point& p, const Point& q) const
        {
          Orientation ori = orientation(rot_point, p, q);
          if ( ori == LEFTTURN )
          {
              return true;
          }
          else if ( ori == RIGHTTURN )
          {
              return false;
          }
          else
          {
              return  has_larger_dist_to_point( rot_point, p, q) ;
          }
        }

  void  set_rotation_center( const Point& p)
        { rot_point = p; }


private:
  Point  rot_point;
};

template <class R>
class r_Right_of_line
{
public:
        r_Right_of_line(const Point_2<R>& a, 
                             const Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const Point_2<R>& c) const
        {
          if ( l_ab.is_degenerate() ) return false;
          return (l_ab.oriented_side(c) == ON_NEGATIVE_SIDE);
        }

private:
  Line_2<R>    l_ab;
};

template <class R>
class r_Left_of_line
{
public:
        r_Left_of_line(const Point_2<R>& a, 
                            const Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const Point_2<R>& c) const
        { return (l_ab.oriented_side(c) == ON_POSITIVE_SIDE); }

private:
  Line_2<R>    l_ab;
};

template <class R>
class r_Less_dist_to_line
{
public:
        r_Less_dist_to_line(const Point_2<R>& a, 
                               const Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const Point_2<R>& c, const Point_2<R>& d) const
        {
          Comparison_result res = cmp_signed_dist_to_line(l_ab, c, d);
          if ( res == LARGER )
          {
              return false;
          }
          else if ( res == EQUAL )
          {
              return lexicographically_xy_smaller( c, d );
          }
          else
          {
              return true;
          }
        }

private:
  Line_2<R>    l_ab;
};

template <class R>
class r_Less_negative_dist_to_line
{
public:
        r_Less_negative_dist_to_line(const Point_2<R>& a, 
                               const Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const Point_2<R>& c, const Point_2<R>& d) const
        {
          Comparison_result res = cmp_signed_dist_to_line(l_ab, c, d);
          if ( res == LARGER )
          {
              return true;
          }
          else if ( res == EQUAL )
          {
              return lexicographically_xy_smaller( c, d );
          }
          else
          {
              return false;
          }
        }

private:
  Line_2<R>    l_ab;
};

template <class R>
class r_Less_in_direction
{
public:
        typedef typename  R::RT   RT;

        r_Less_in_direction( const Direction_2<R>& dir )
        : l( Point_2<R>( RT(0) , RT(0) ),
             Direction_2<R>(-(dir.dy()), dir.dx() ))
        {}

  bool  operator()(const Point_2<R>& c, const Point_2<R>& d) const
        {
          Comparison_result res = cmp_signed_dist_to_line(l, c, d);
          if ( res == LARGER )
          {
              return true;
          }
          else if ( res == EQUAL )
          {
              return  lexicographically_xy_smaller( c, d) ;
          }
          else
          {
              return false;
          }
        }

private:
  Line_2<R>  l;
};

template <class Point>
struct p_Leftturn
{
  bool  operator()(const Point& p, const Point& q, const Point& r) const
        { return leftturn(p,q,r); }
};

template <class Point>
struct p_Rightturn
{
  bool  operator()(const Point& p, const Point& q, const Point& r) const
        { return rightturn(p,q,r); }
};

template <class Point>
struct p_Orientation
{
  Orientation  
        operator()(const Point& p, const Point& q, const Point& r) const
        { return orientation(p,q,r); }
};

CGAL_END_NAMESPACE

#endif // CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H