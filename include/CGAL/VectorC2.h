 
// Source: VectorC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_VECTORC2_H
#define CGAL_VECTORC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointC2.h>

 
template < class FT >
class CGAL_VectorC2 : public CGAL_Handle_base
{
friend CGAL_VectorC2<FT> operator-(const CGAL_PointC2<FT> &p,
                                   const CGAL_Origin &o);

#ifdef CGAL_WORKAROUND_001
  // SGI has problems with the 'inline'
friend CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const;

#else


#ifdef CGAL_WORKAROUND_003
  friend class CGAL_DirectionC2<FT>;
#else
  // that's what we want but the GNU g++ compiler has trouble with
  // the not yet defined class CGAL_DirectionC2<FT>
  friend inline CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const;
#endif // CGAL_WORKAROUND_003

#endif  // CGAL_WORKAROUND_001

public:
                       CGAL_VectorC2();
                       CGAL_VectorC2(const CGAL_VectorC2 &v);
                       CGAL_VectorC2(const FT &hx, const FT &hy, const FT &hw);
                       CGAL_VectorC2(const FT &x, const FT &y);

                       ~CGAL_VectorC2();


  CGAL_VectorC2<FT>    &operator=(const CGAL_VectorC2<FT> &v);

  bool                 operator==(const CGAL_VectorC2 &p) const;
  bool                 operator!=(const CGAL_VectorC2 &p) const;
  bool                 identical(const CGAL_VectorC2 &p) const;

  FT                   hx() const;
  FT                   hy() const;
  FT                   hw() const;

  FT                   x() const;
  FT                   y() const;
  FT                   cartesian(int i) const;
  FT                   operator[](int i) const;

  FT                   homogeneous(int i) const;

  int                  dimension() const;

  CGAL_VectorC2        operator+(const CGAL_VectorC2 &w) const;
  CGAL_VectorC2        operator-(const CGAL_VectorC2 &w) const;
  CGAL_VectorC2        operator-() const;
  FT                   operator*(const CGAL_VectorC2 &w) const;
  CGAL_VectorC2        operator*(const FT &c) const;
  CGAL_VectorC2        operator/(const FT &c) const;
  CGAL_DirectionC2<FT> direction() const;

  CGAL_VectorC2<FT>    perpendicular(const CGAL_Ordertype &o) const;
  CGAL_VectorC2<FT>    transform(const CGAL_Aff_transformationC2<FT> &) const;

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const;
#endif

protected:
                       CGAL_VectorC2(const CGAL_PointC2<FT> &p);
                       CGAL_VectorC2(const CGAL_DirectionC2<FT> &d);
private:
  CGAL__Twotuple<FT>*   ptr() const;
};
 

 
#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
inline bool CGAL_VectorC2<FT>::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif

template < class FT >
inline CGAL__Twotuple<FT>*   CGAL_VectorC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}
 


#include <CGAL/DirectionC2.h>


 
template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple<FT>();
#endif
}

template < class FT >
inline CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_VectorC2<FT>  &v) :
  CGAL_Handle_base((CGAL_Handle_base&)v)
{
  // CGAL_kernel_precondition(v.is_defined());
}

template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2(const FT &hx, const FT &hy, const FT &hw)
{
  if( hw == FT(1)){
    PTR = new CGAL__Twotuple<FT>(hx, hy);
  } else {
    PTR = new CGAL__Twotuple<FT>(hx/hw, hy/hw);
  }
}

template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2(const FT &x, const FT &y)
{
  PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
inline CGAL_VectorC2<FT>::~CGAL_VectorC2()
{}

template < class FT >
CGAL_VectorC2<FT> &CGAL_VectorC2<FT>::operator=(const CGAL_VectorC2<FT> &v)
{
  CGAL_kernel_precondition(v.is_defined());
  CGAL_Handle_base::operator=(v);
  return *this;
}
 
template < class FT >
inline CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_PointC2<FT> &p) :
  CGAL_Handle_base((CGAL_Handle_base&)p)
{
  CGAL_kernel_precondition(p.is_defined());
}

template < class FT >
inline CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_DirectionC2<FT> &d) :
  CGAL_Handle_base((CGAL_Handle_base&)d)
{
  CGAL_kernel_precondition(d.is_defined());
}
 
template < class FT >
bool CGAL_VectorC2<FT>::operator==(const CGAL_VectorC2<FT> &v) const
{
  CGAL_kernel_precondition(is_defined() && v.is_defined());
  return  ((x() == v.x()) && (y() == v.y())) ;
}

template < class FT >
inline bool CGAL_VectorC2<FT>::operator!=(const CGAL_VectorC2<FT> &v) const
{
  return !(*this == v);
}

template < class FT >
bool CGAL_VectorC2<FT>::identical(const CGAL_VectorC2<FT> &v) const
{
  CGAL_kernel_precondition(is_defined() && v.is_defined());
  return ( PTR == v.PTR );
}
 
template < class FT >
FT CGAL_VectorC2<FT>::x()  const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
FT CGAL_VectorC2<FT>::y()  const
{
  CGAL_kernel_precondition(is_defined());
  return  ptr()->e1 ;
}

template < class FT >
inline FT  CGAL_VectorC2<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition((i == 0 || i == 1) && is_defined());
  if(i == 0) {
    return x();
  }
  return y();
}

template < class FT >
inline FT  CGAL_VectorC2<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
inline int CGAL_VectorC2<FT>::dimension() const
{
  CGAL_kernel_precondition(is_defined());
  return 2;
}

template < class FT >
FT CGAL_VectorC2<FT>::hx()  const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
FT CGAL_VectorC2<FT>::hy()  const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e1;
}

template < class FT >
FT CGAL_VectorC2<FT>::hw()  const
{
  CGAL_kernel_precondition(is_defined());
  return FT(1);
}

template < class FT >
FT  CGAL_VectorC2<FT>::homogeneous(int i) const
{
  return cartesian(i);
}
 
template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator+(
                                             const CGAL_VectorC2<FT> &w) const
{
  CGAL_kernel_precondition(is_defined() && w.is_defined());
  return CGAL_VectorC2<FT>(x() + w.x(), y() + w.y()) ;
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator-(
                                             const CGAL_VectorC2<FT> &w) const
{
  CGAL_kernel_precondition(is_defined() && w.is_defined());
  return CGAL_VectorC2<FT>(x() - w.x(), y() - w.y()) ;
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator-() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_VectorC2<FT>(-x(), -y()) ;
}

template < class FT >
inline FT CGAL_VectorC2<FT>::operator*(const CGAL_VectorC2<FT> &w) const
{
  CGAL_kernel_precondition(is_defined() && w.is_defined());
  return x() * w.x() + y() * w.y() ;
}

template < class FT >
CGAL_VectorC2<FT> operator*(const FT &c, const CGAL_VectorC2<FT> &w)
{
  CGAL_kernel_precondition(w.is_defined());
   return CGAL_VectorC2<FT>( c* w.x(), c * w.y()) ;
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator*(const FT &c) const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_VectorC2<FT>( c* x(), c * y()) ;
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator/(const FT &c) const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_VectorC2<FT>( x()/c, y()/c) ;
}
 

template < class FT >
inline CGAL_DirectionC2<FT>   CGAL_VectorC2<FT>::direction() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_DirectionC2<FT>(*this) ;
}

template < class FT >
CGAL_VectorC2<FT> CGAL_VectorC2<FT>::perpendicular(
                                                const CGAL_Ordertype &o) const
{
  CGAL_kernel_precondition(is_defined() && (o != CGAL_COLLINEAR));
  if(o == CGAL_COUNTERCLOCKWISE){
    return CGAL_VectorC2<FT>(-y(), x());
  }else{
    return CGAL_VectorC2<FT>(y(), -x());
  }
}

template < class FT >
CGAL_VectorC2<FT> CGAL_VectorC2<FT>::transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition(is_defined());
  return t.transform(*this);
}

 


#endif
