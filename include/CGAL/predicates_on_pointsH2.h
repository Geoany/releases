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
// source        : geometric_predicatesH2.fw
// file          : include/CGAL/predicates_on_pointsH2.h
// package       : H2 (2.1.3)
// revision      : 2.1.3
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#define CGAL_PREDICATES_ON_POINTSH2_H

#ifndef PVDH2_H
#include <CGAL/PVDH2.h>
#endif // PVDH2_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_lexicographically_xy(const PointH2<FT,RT>& p,
                             const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx*qhw;
  RT qV = qhx*phw;
  if ( pV == qV )
  {
      pV = phy*qhw;
      qV = qhy*phw;
  }
  if ( pV < qV )
  {
      return SMALLER;
  }
  else
  {
      return (qV < pV) ? LARGER : EQUAL;
  }
}


template < class FT, class RT>
CGAL_KERNEL_INLINE
bool
lexicographically_xy_smaller_or_equal(const PointH2<FT,RT>& p,
                                           const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx * qhw;
  RT qV = qhx * phw;
  if ( qV < pV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }

  pV = phy * qhw;
  qV = qhy * phw;
  return ( pV <= qV );
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
bool
lexicographically_xy_smaller(const PointH2<FT,RT>& p,
                                  const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx * qhw;
  RT qV = qhx * phw;
  if ( qV < pV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }
  pV = phy * qhw;
  qV = qhy * phw;
  return ( pV < qV );
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
bool
lexicographically_xy_larger(const PointH2<FT,RT>& p,
                                 const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx * qhw;
  RT qV = qhx * phw;
  if ( pV < qV )
  {
      return false;
  }
  else if ( qV < pV )
  {
      return true;
  }
  pV = phy * qhw;
  qV = qhy * phw;
  return ( qV < pV  );
}
template < class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_lexicographically_yx(const PointH2<FT,RT>& p,
                                  const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy*qhw;
  RT qV = qhy*phw;
  if ( pV == qV )
  {
      pV = phx*qhw;
      qV = qhx*phw;
  }
  if ( pV < qV )
  {
      return SMALLER;
  }
  else
  {
      return ( qV < pV ) ? LARGER : EQUAL;
  }
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
bool
lexicographically_yx_smaller_or_equal(const PointH2<FT,RT>& p,
                                           const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy * qhw;
  RT qV = qhy * phw;
  if ( qV < pV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }
  pV = phx * qhw;
  qV = qhx * phw;
  return ( pV <= qV );
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
bool
lexicographically_yx_smaller(const PointH2<FT,RT>& p,
                                  const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy * qhw;
  RT qV = qhy * phw;
  if ( qV < pV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }
  pV = phx * qhw;
  qV = qhx * phw;
  return ( pV < qV );
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
bool
lexicographically_yx_larger(const PointH2<FT,RT>& p,
                                 const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy * qhw;
  RT qV = qhy * phw;
  if ( pV < qV )
  {
      return false;
  }
  else if ( qV < pV )
  {
      return true;
  }
  pV = phx * qhw;
  qV = qhx * phw;
  return ( qV < pV );
}


template < class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const PointH2<FT,RT>& p,
               const PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhw = q.hw();
  const RT  RT0 = RT(0);
  RT com = phx * qhw - qhx * phw;
  if ( com < RT0 )
  {
      return SMALLER;
  }
  else if ( RT0 < com )
  {
      return LARGER;
  }
  return EQUAL;
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const PointH2<FT,RT>& p,
               const PointH2<FT,RT>& q)
{
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT  RT0 = RT(0);
  RT com = phy * qhw - qhy * phw;
  if ( com < RT0 )
  {
      return SMALLER;
  }
  else if ( RT0 < com )
  {
     return LARGER;
  }
  return EQUAL;
}

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Orientation
orientation( const PointH2<FT,RT>& p,
                  const PointH2<FT,RT>& q,
                  const PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL::sign(det) == CGAL::sign(det_old)) )
  {
      std::cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/



  if (det < RT0  )
  {
      return CLOCKWISE;
  }
  else
  {
      return (RT0 < det) ? COUNTERCLOCKWISE : COLLINEAR;
  }
}

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
leftturn( const PointH2<FT,RT>& p,
               const PointH2<FT,RT>& q,
               const PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL::sign(det) == CGAL::sign(det_old)) )
  {
      std::cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/


  return ( RT0 < det );
}

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
rightturn( const PointH2<FT,RT>& p,
                const PointH2<FT,RT>& q,
                const PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL::sign(det) == CGAL::sign(det_old)) )
  {
      std::cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/


  return ( det < RT0 );
}

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear( const PointH2<FT,RT>& p,
                const PointH2<FT,RT>& q,
                const PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL::sign(det) == CGAL::sign(det_old)) )
  {
      std::cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/


  return ( det == RT0 );
}
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
side_of_bounded_circle( const PointH2<FT,RT>& q,
                             const PointH2<FT,RT>& r,
                             const PointH2<FT,RT>& s,
                             const PointH2<FT,RT>& t)
{

  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT& shx = s.hx();
  const RT& shy = s.hy();
  const RT& shw = s.hw();
  const RT& thx = t.hx();
  const RT& thy = t.hy();
  const RT& thw = t.hw();
  const RT  RT0 = RT(0);

  CGAL_kernel_precondition( ! collinear(q,r,s) );

  // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
  //                      |      --  r  --      | = | e f g h |
  //     determinant      |      --  s  --      | = | i j k l |
  //                      |      --  t  --      |   | m n o p |
  //           where

  RT a = qhx*qhw;
  RT b = qhy*qhw;
  RT c = qhx*qhx + qhy*qhy;
  RT d = qhw*qhw;

  RT e = rhx*rhw;
  RT f = rhy*rhw;
  RT g = rhx*rhx + rhy*rhy;
  RT h = rhw*rhw;

  RT i = shx*shw;
  RT j = shy*shw;
  RT k = shx*shx + shy*shy;
  RT l = shw*shw;

  RT m = thx*thw;
  RT n = thy*thw;
  RT o = thx*thx + thy*thy;
  RT p = thw*thw;

  RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
           - e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
           + i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
           - m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );


  if ( det == RT0 )
  {
      return ON_BOUNDARY;
  }
  else
  {
      if (orientation(q,r,s) == CLOCKWISE)
      {
          det = -det;
      }
      return (RT0 < det ) ? ON_BOUNDED_SIDE : ON_UNBOUNDED_SIDE;
  }
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side
side_of_oriented_circle( const PointH2<FT,RT>& q,
                              const PointH2<FT,RT>& r,
                              const PointH2<FT,RT>& s,
                              const PointH2<FT,RT>& t)
{

  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT& shx = s.hx();
  const RT& shy = s.hy();
  const RT& shw = s.hw();
  const RT& thx = t.hx();
  const RT& thy = t.hy();
  const RT& thw = t.hw();
  const RT  RT0 = RT(0);

  CGAL_kernel_precondition( ! collinear(q,r,s) );

  // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
  //                      |      --  r  --      | = | e f g h |
  //     determinant      |      --  s  --      | = | i j k l |
  //                      |      --  t  --      |   | m n o p |
  //           where

  RT a = qhx*qhw;
  RT b = qhy*qhw;
  RT c = qhx*qhx + qhy*qhy;
  RT d = qhw*qhw;

  RT e = rhx*rhw;
  RT f = rhy*rhw;
  RT g = rhx*rhx + rhy*rhy;
  RT h = rhw*rhw;

  RT i = shx*shw;
  RT j = shy*shw;
  RT k = shx*shx + shy*shy;
  RT l = shw*shw;

  RT m = thx*thw;
  RT n = thy*thw;
  RT o = thx*thx + thy*thy;
  RT p = thw*thw;

  RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
           - e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
           + i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
           - m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );


  if ( det < RT0 )
  {
      return ON_NEGATIVE_SIDE;
  }
  else
  {
      return (RT0 < det ) ? ON_POSITIVE_SIDE : ON_ORIENTED_BOUNDARY;
  }
}
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_ordered_along_line( const PointH2<FT,RT>& p,
                                       const PointH2<FT,RT>& q,
                                       const PointH2<FT,RT>& r )
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();

  if ( !(phx * rhw == rhx * phw ) )          // non-vertical ?
  {
     return !( (  ( phx * qhw < qhx * phw)
                &&( rhx * qhw < qhx * rhw))
             ||(  ( qhx * phw < phx * qhw)
                &&( qhx * rhw < rhx * qhw)) );
  }
  else if ( !(phy * rhw == rhy * phw ) )
  {
     return !( (  ( phy * qhw < qhy * phw)
                &&( rhy * qhw < qhy * rhw))
             ||(  ( qhy * phw < phy * qhw)
                &&( qhy * rhw < rhy * qhw)) );
  }
  else
     return (( phx*qhw == qhx*phw) && ( phy*qhw == qhy*phw));
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
bool
are_ordered_along_line( const PointH2<FT,RT>& p,
              const PointH2<FT,RT>& q,
              const PointH2<FT,RT>& r )
{
  if ( collinear(p,q,r) )
  {
     return collinear_are_ordered_along_line(p,q,r);
  }
  else
  {
     return false;
  }
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_strictly_ordered_along_line( const PointH2<FT,RT>& p,
                                                const PointH2<FT,RT>& q,
                                                const PointH2<FT,RT>& r )
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();

  if ( !(phx * rhw == rhx * phw ) )
  {
     return (   ( phx * qhw < qhx * phw)
              &&( qhx * rhw < rhx * qhw))
          ||(   ( qhx * phw < phx * qhw)    // ( phx * qhw > qhx * phw)
              &&( rhx * qhw < qhx * rhw));  // ( qhx * rhw > rhx * qhw)
  }
  else
  {
     return (   ( phy * qhw < qhy * phw)
              &&( qhy * rhw < rhy * qhw))
          ||(   ( qhy * phw < phy * qhw)    // ( phy * qhw > qhy * phw)
              &&( rhy * qhw < qhy * rhw));  // ( qhy * rhw > rhy * qhw)
  }
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
bool
are_strictly_ordered_along_line( const PointH2<FT,RT>& p,
                                      const PointH2<FT,RT>& q,
                                      const PointH2<FT,RT>& r )
{
  if ( collinear(p,q,r) )
  {
     return collinear_are_strictly_ordered_along_line(p,q,r);
  }
  else
  {
     return false;
  }
}
template <class FT, class RT>
inline
bool
x_equal( const PointH2<FT,RT>& p,
              const PointH2<FT,RT>& q )
{ return ( p.hx()*q.hw() == q.hx()*p.hw() ); }

template <class FT, class RT>
inline
bool
y_equal( const PointH2<FT,RT>& p,
              const PointH2<FT,RT>& q )
{ return ( p.hy()*q.hw() == q.hy()*p.hw() ); }
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side
_where_wrt_L_wedge( const PointH2<FT,RT>& p,
                         const PointH2<FT,RT>& q )
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  int xs = (int)CGAL::sign( qhx*phw - phx*qhw );  // sign( qx - px )
  int ys = (int)CGAL::sign( qhy*phw - phy*qhw );  // sign( qy - py )

  if (( xs == -1 ) || ( ys == -1 ))
  {
      return ON_NEGATIVE_SIDE;
  }
  if (( xs ==  1 ) && ( ys ==  1 ))
  {
      return ON_POSITIVE_SIDE;
  }
  return ON_ORIENTED_BOUNDARY;
}

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_deltax_deltay(const PointH2<FT,RT>& p,
                           const PointH2<FT,RT>& q,
                           const PointH2<FT,RT>& r,
                           const PointH2<FT,RT>& s)
{
  const RT& phx = p.hx();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhw = q.hw();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT& shy = s.hy();
  const RT& shw = s.hw();
  const RT  tbc1 = abs(phx*qhw - qhx*phw) * rhw*shw;
  const RT  tbc2 = abs(rhy*shw - shy*rhw) * phw*qhw;

  return (tbc2 < tbc1) ? LARGER
                       : (tbc1 == tbc2) ? EQUAL : SMALLER;

}

CGAL_END_NAMESPACE


#endif // CGAL_PREDICATES_ON_POINTSH2_H