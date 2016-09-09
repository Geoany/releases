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
// source        : LineH2.fw
// file          : include/CGAL/LineH2.h
// package       : H2 (2.1.3)
// revision      : 2.1.3
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_LINEH2_H
#define CGAL_LINEH2_H

#ifndef CGAL_POINTH2_H
#include <CGAL/PointH2.h>
#endif // CGAL_POINTH2_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
class LineH2 : public Handle
{
public:
                        LineH2();
                        LineH2(const LineH2<FT,RT>& l);
                        LineH2(const PointH2<FT,RT>& p,
                                    const PointH2<FT,RT>& q);
                        LineH2(const RT& a, const RT& b, const RT& c);
                        LineH2(const SegmentH2<FT,RT>& s);
                        LineH2(const RayH2<FT,RT>& r);
                        LineH2(const PointH2<FT,RT>& p,
                                    const DirectionH2<FT,RT>& d);

    LineH2<FT,RT>& operator=(const LineH2<FT,RT>& l);

    bool                operator==(const LineH2<FT,RT>& l) const ;
    bool                operator!=(const LineH2<FT,RT>& l) const ;
    bool                identical(const LineH2<FT,RT>& l)  const ;
    int                 id()  const ;

    RT                  a() const;
    RT                  b() const;
    RT                  c() const;

    FT                  x_at_y(FT y) const;
    FT                  y_at_x(FT x) const;

    LineH2<FT,RT>  perpendicular(const PointH2<FT,RT>& p ) const;
    LineH2<FT,RT>  opposite() const;
    PointH2<FT,RT> point() const;
    PointH2<FT,RT> point(int i) const;
    PointH2<FT,RT> projection(const PointH2<FT,RT>& p) const;
    DirectionH2<FT,RT>
                        direction() const;
    Oriented_side  oriented_side( const PointH2<FT,RT>& p ) const;
    bool                has_on( const PointH2<FT,RT>& p ) const;
    bool                has_on_boundary( const PointH2<FT,RT>& p ) const;
    bool                has_on_positive_side( const PointH2<FT,RT>& p )
                                                                         const;
    bool                has_on_negative_side( const PointH2<FT,RT>& p )
                                                                         const;
    bool                is_horizontal() const;
    bool                is_vertical()   const;
    bool                is_degenerate() const;

    LineH2<FT,RT>  transform(const Aff_transformationH2<FT,RT>&)
                                                         const;

protected:
    _Threetuple<RT>*  ptr() const;
};

template < class FT, class RT >
inline
_Threetuple<RT>*
LineH2<FT,RT>::ptr() const
{ return (_Threetuple<RT>*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
LineH2<FT,RT>::LineH2()
{ PTR = new _Threetuple<RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
LineH2<FT,RT>::LineH2(const LineH2<FT,RT>& l)
  : Handle(l)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
LineH2<FT,RT>::LineH2(const PointH2<FT,RT>& p,
                                const PointH2<FT,RT>& q)
{
  //  a() * X + b() * Y + c() * W() == 0
  //      |    X        Y       W     |
  //      |  p.hx()   p.hy()  p.hw()  |
  //      |  q.hx()   q.hy()  q.hw()  |

  PTR = new _Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );

}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
LineH2<FT,RT>::LineH2(const RT& a, const RT& b, const RT& c)
{ PTR = new _Threetuple<RT>(a,b,c); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
LineH2<FT,RT>::LineH2(const SegmentH2<FT,RT>& s)
{
  PointH2<FT,RT> p = s.start();
  PointH2<FT,RT> q = s.end();
  PTR = new _Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
LineH2<FT,RT>::LineH2(const RayH2<FT,RT>& r)
{
  PointH2<FT,RT> p = r.start();
  PointH2<FT,RT> q = r.second_point();
  PTR = new _Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
LineH2<FT,RT>::LineH2(const PointH2<FT,RT>& p,
                                const DirectionH2<FT,RT>& d)
{
  PointH2<FT,RT> q = p + VectorH2<FT,RT>(d);
  PTR = new _Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH2<FT,RT>&
LineH2<FT,RT>::operator=(const LineH2<FT,RT>& l)
{
  Handle::operator=(l);
  return *this;
}
template < class FT, class RT >
inline
RT
LineH2<FT,RT>::a() const
{ return ptr()->e0; }

template < class FT, class RT >
inline
RT
LineH2<FT,RT>::b() const
{ return ptr()->e1; }

template < class FT, class RT >
inline
RT
LineH2<FT,RT>::c() const
{ return ptr()->e2; }


template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
LineH2<FT,RT>::x_at_y(FT y) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return (FT(-b())*y - FT(c()) )/FT(a());
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
LineH2<FT,RT>::y_at_x(FT x) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return (FT(-a())*x - FT(c()) )/FT(b());
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH2<FT,RT>
LineH2<FT,RT>::perpendicular(const PointH2<FT,RT>& p ) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH2<FT,RT>( -b()*p.hw(), a()*p.hw(), b()*p.hx() - a()*p.hy() );
}

template < class FT, class RT >
inline
LineH2<FT,RT>
LineH2<FT,RT>::opposite() const
{ return LineH2<FT,RT>( -a(), -b(), -c() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
LineH2<FT,RT>::point() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  if (is_vertical() )
  {
      return PointH2<FT,RT>(-c(), RT(0)  , a() );
  }
  else
  {
      return PointH2<FT,RT>(RT(0)  , -c(), b() );
  }
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
LineH2<FT,RT>::point(int i) const
{ return point() + RT(i) * (direction().vector()); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
LineH2<FT,RT>::projection(const PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  LineH2<FT,RT>  l( p, DirectionH2<FT,RT>( a(), b() ));
  return PointH2<FT,RT>( b()*l.c() - l.b()*c(),
                              l.a()*c() - a()*l.c(),
                              a()*l.b() - l.a()*b() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
DirectionH2<FT,RT>
LineH2<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH2<FT,RT>( b(), -a() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH2<FT,RT>
LineH2<FT,RT>::transform(const Aff_transformationH2<FT,RT>& t) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  PointH2<FT,RT> p = point() + direction().vector();
  return LineH2<FT,RT>( t.transform(point() ), t.transform(p) );
}

#ifndef NO_OSTREAM_INSERT_LINEH2
template < class FT, class RT >
std::ostream &
operator<<(std::ostream &os, const LineH2<FT,RT> &l)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << l.a() << ' ' << l.b() << ' ' << l.c();
    case IO::BINARY :
        write(os, l.a());
        write(os, l.b());
        write(os, l.c());
        return os;
    default:
        return os << "LineH2(" << l.a() << ", " << l.b() << ", " << l.c() <<')';
  }
}
#endif // NO_OSTREAM_INSERT_LINEH2

#ifndef NO_ISTREAM_EXTRACT_LINEH2
template < class FT, class RT >
std::istream &
operator>>(std::istream &is, LineH2<FT,RT> &p)
{
  RT a, b, c;
  switch(is.iword(IO::mode))
  {
    case IO::ASCII :
        is >> a >> b >> c;
        break;
    case IO::BINARY :
        read(is, a);
        read(is, b);
        read(is, c);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
  }
  p = LineH2<FT,RT>(a, b, c);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_LINEH2
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
LineH2<FT,RT>::has_on( const PointH2<FT,RT>& p ) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) == RT(0)   );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
LineH2<FT,RT>::has_on_boundary( const PointH2<FT,RT>& p ) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) == RT(0)   );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
LineH2<FT,RT>::has_on_positive_side( const PointH2<FT,RT>& p ) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) > RT(0)   );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
LineH2<FT,RT>::has_on_negative_side( const PointH2<FT,RT>& p ) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) < RT(0)   );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
Oriented_side
LineH2<FT,RT>::oriented_side( const PointH2<FT,RT>& p ) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  RT v = a()*p.hx() + b()*p.hy() + c()*p.hw();
  if (v > RT(0)   )
  {
      return ON_POSITIVE_SIDE;
  }
  else
  {
      return (v < RT(0)   ) ? ON_NEGATIVE_SIDE : ON_ORIENTED_BOUNDARY;
  }
}

template < class FT, class RT >
inline
bool
LineH2<FT,RT>::is_horizontal() const
{ return ( a() == RT(0)   ); }

template < class FT, class RT >
inline
bool
LineH2<FT,RT>::is_vertical() const
{ return ( b() == RT(0)   ); }

template < class FT, class RT >
inline
bool
LineH2<FT,RT>::is_degenerate() const
{ return (a() == RT(0)  )&&(b() == RT(0)  ) ; }
template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
bool
LineH2<FT,RT>::operator==(const LineH2<FT,RT>& l) const
{
  if (  (a() * l.c() != l.a() * c() )
      ||(b() * l.c() != l.b() * c() ) )
  {
      return false;
  }
  int sc  = (int)CGAL::sign(c() );
  int slc = (int)CGAL::sign(l.c() );
  if ( sc == slc )
  {
      if (sc == 0)
      {
          return (  (a()*l.b() == b()*l.a() )
                  &&(CGAL::sign(a() )== CGAL::sign( l.a() ))
                  &&(CGAL::sign(b() )== CGAL::sign( l.b() )) );
      }
      else
      {
          return true;
      }
  }
  else
  {
      return false;
  }
}

template < class FT, class RT >
inline
bool
LineH2<FT,RT>::operator!=(const LineH2<FT,RT>& l) const
{ return !(*this == l); }   /* XXX */

template < class FT, class RT >
inline
bool
LineH2<FT,RT>::identical(const LineH2<FT,RT>& l) const
{ return PTR == l.PTR; }

template < class FT, class RT >
inline
int
LineH2<FT,RT>::id() const
{ return (int)PTR; }

CGAL_END_NAMESPACE


#endif // CGAL_LINEH2_H