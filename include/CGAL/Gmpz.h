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
// source        : Gmpz.fw
// file          : include/CGAL/Gmpz.h
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_GMPZ_H
#define CGAL_GMPZ_H


#include<CGAL/basic.h>
#include<cctype>
#include<gmp.h>

CGAL_BEGIN_NAMESPACE

class Gmpz_rep : public Rep
{
public:
  mpz_t  mpZ;

  Gmpz_rep()
  // { mpz_init_set_si(mpZ, 0); }
  { mpz_init(mpZ); }

  Gmpz_rep(mpz_t  z)
  { mpz_init_set(mpZ, z); }

  Gmpz_rep(int si)
  { mpz_init_set_si(mpZ, si); }

  Gmpz_rep(long li)
  { mpz_init_set_si(mpZ, li); }

  Gmpz_rep(unsigned long li)
  { mpz_init_set_ui(mpZ, li); }

  Gmpz_rep(double d)
  { mpz_init_set_d(mpZ, d); }

  Gmpz_rep(char* str)
  { mpz_init_set_str(mpZ, str, 10); }

  Gmpz_rep(char* str, int base)
  { mpz_init_set_str(mpZ, str, base); }

  ~Gmpz_rep()
  { mpz_clear(mpZ); }
};

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

class Gmpz;

class Gmpz : public Handle
{
public:
  Gmpz();

  Gmpz(const Gmpz &z);

  Gmpz(mpz_t z);

  Gmpz(int i);

  Gmpz(long l);

  Gmpz(unsigned long l);

  Gmpz(double d);

  Gmpz(char* str);
  Gmpz(char* str, int base);

  Gmpz(Gmpz_rep* R);

  ~Gmpz();

  Gmpz &operator=(const Gmpz &z);

  bool operator==(const Gmpz &z) const;
  bool operator==(int i) const;

  bool operator!=(const Gmpz &z) const;
  bool operator!=(int i) const;

  bool operator<(const Gmpz &z) const;
  bool operator<(int i) const;

  bool operator<=(const Gmpz &z) const;
  bool operator<=(int i) const;

  bool operator>(const Gmpz &z) const;
  bool operator>(int i) const;

  bool operator>=(const Gmpz &z) const;
  bool operator>=(int i) const;

  Gmpz operator-() const;

  Gmpz operator+(const Gmpz &z) const;
  Gmpz operator+(int i) const;

  Gmpz operator-(const Gmpz &z) const;
  Gmpz operator-(int i) const;

  Gmpz operator*(const Gmpz &z) const;
  Gmpz operator*(int i) const;

  Gmpz operator/(const Gmpz &z) const;
  Gmpz operator/(int i) const;

  Gmpz& operator+=(const Gmpz &z);
  Gmpz operator+=(int i);

  Gmpz& operator-=(const Gmpz &z);
  Gmpz operator-=(int i);

  Gmpz& operator*=(const Gmpz &z);
  Gmpz operator*=(int i);

  Gmpz& operator/=(const Gmpz &z);
  Gmpz operator/=(int i);

  size_t approximate_decimal_length() const;

  Gmpz_rep* ptr() const;
  double to_double() const;
  Sign sign() const;
};


inline
Gmpz_rep*
Gmpz::ptr() const
{ return (Gmpz_rep*) PTR; }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz()
{ PTR = new Gmpz_rep(0); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(const Gmpz &z)
  : Handle((Handle&)z)
{}

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(mpz_t z)
{ std::cout << "OLD construction called"; PTR = new Gmpz_rep(z); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(int i)
{ PTR = new Gmpz_rep(i); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(long l)
{ PTR = new Gmpz_rep(l); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(unsigned long l)
{ PTR = new Gmpz_rep(l); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(double d)
{ PTR = new Gmpz_rep(d); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(char* str)
{ PTR = new Gmpz_rep(str); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(char* str, int base)
{ PTR = new Gmpz_rep(str, base); }

inline   // CGAL_KERNEL_CTOR_INLINE
Gmpz::Gmpz(Gmpz_rep* R)
{ PTR = R; }

inline
Gmpz::~Gmpz()
{}

inline
Gmpz &
Gmpz::operator=(const Gmpz &z)
{
  Handle::operator=(z);
  return *this;
}

inline
bool
Gmpz::operator==(const Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) == 0 ); }

inline
bool
Gmpz::operator<(const Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) < 0 ); }

inline
bool
Gmpz::operator<(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) < 0 ); }

inline
bool            /* XXX */
Gmpz::operator<=(const Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) <= 0 ); }


inline
bool
Gmpz::operator<=(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) <= 0 ); }

inline
bool             /* XXX */
Gmpz::operator>(const Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) > 0 ); }

inline
bool
Gmpz::operator>(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) > 0 ); }

inline
bool             /* XXX */
Gmpz::operator>=(const Gmpz &z) const
{ return ( mpz_cmp(ptr()->mpZ, z.ptr()->mpZ) >= 0 ); }

inline
bool
Gmpz::operator>=(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) >= 0 ); }

inline
bool             /* XXX */
Gmpz::operator!=(const Gmpz &z) const
{ return ! (*this == z); }

inline
bool
Gmpz::operator==(int i) const
{ return ( mpz_cmp_si(ptr()->mpZ, i) == 0 ); }

inline
bool
Gmpz::operator!=(int i) const
{ return ! (*this == i); }

inline
Gmpz
Gmpz::operator-() const
{
    Gmpz_rep* Res = new Gmpz_rep();
    mpz_neg(Res->mpZ, ptr()->mpZ);
    return Gmpz(Res);
}

inline
Gmpz
Gmpz::operator+(const Gmpz &z) const
{
    Gmpz_rep* Res = new Gmpz_rep();
    mpz_add(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return Gmpz(Res);
}

inline
Gmpz
Gmpz::operator+(int i) const
{
    if (i>0)
    {
        Gmpz_rep* Res = new Gmpz_rep();
        mpz_add_ui(Res->mpZ, ptr()->mpZ, i);
        return Gmpz(Res);
    }
    return *this + Gmpz(i);
}

inline
Gmpz&
Gmpz::operator+=(const Gmpz &z)
{
    *this = *this + z;
    return *this;
}

inline
Gmpz
Gmpz::operator+=(int i)
{
    *this = *this + Gmpz(i);
    return *this;
}

inline
Gmpz
Gmpz::operator-(const Gmpz &z) const
{
    Gmpz_rep* Res = new Gmpz_rep();
    mpz_sub(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return Gmpz(Res);
}

inline
Gmpz Gmpz::operator-(int i) const
{
    if (i>0)
    {
        Gmpz_rep* Res = new Gmpz_rep();
        mpz_sub_ui(Res->mpZ, ptr()->mpZ, i);
        return Gmpz(Res);
    }
    return *this - Gmpz(i);
}

inline
Gmpz&
Gmpz::operator-=(const Gmpz &z)
{
    *this = *this - z;
    return *this;
}

inline
Gmpz
Gmpz::operator-=(int i)
{
    *this = *this - Gmpz(i);
    return *this;
}

inline
Gmpz
Gmpz::operator*(const Gmpz &z) const
{
    Gmpz_rep* Res = new Gmpz_rep();
    mpz_mul(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return Gmpz(Res);
}

inline
Gmpz
Gmpz::operator*(int i) const
{
    if (i>0)
    {
        Gmpz_rep* Res = new Gmpz_rep();
        mpz_mul_ui(Res->mpZ, ptr()->mpZ, i);
        return Gmpz(Res);
    }
    return *this * Gmpz(i);
}

inline
Gmpz&
Gmpz::operator*=(const Gmpz &z)
{
    *this = *this * z;
    return *this;
}

inline
Gmpz
Gmpz::operator*=(int i)
{
    *this = *this * Gmpz(i);
    return *this;
}

inline
Gmpz
Gmpz::operator/(const Gmpz &z) const
{
    Gmpz_rep* Res = new Gmpz_rep();
    mpz_tdiv_q(Res->mpZ, ptr()->mpZ, z.ptr()->mpZ);
    return Gmpz(Res);
}

inline
Gmpz
Gmpz::operator/(int i) const
{
    if (i>0)
    {
        Gmpz_rep* Res = new Gmpz_rep();
        mpz_tdiv_q_ui(Res->mpZ, ptr()->mpZ, i);
        return Gmpz(Res);
    }
    return *this / Gmpz(i);
}

inline
Gmpz&
Gmpz::operator/=(const Gmpz &z)
{
    *this = *this / z;
    return *this;
}

inline
Gmpz
Gmpz::operator/=(int i)
{
    *this = *this / Gmpz(i);
    return *this;
}

inline
double
Gmpz::to_double() const
{ return mpz_get_d(ptr()->mpZ); }

inline
io_Operator
io_tag(const Gmpz&)
{ return io_Operator(); }

inline
Sign
Gmpz::sign() const
{ return (Sign)mpz_sgn(ptr()->mpZ); }

inline
Gmpz
operator+(int i, const Gmpz &z)
{ return z + i; }

inline
Gmpz
operator-(int i, const Gmpz &z)
{ return Gmpz(i) - z; }

inline
Gmpz
operator*(int i, const Gmpz &z)
{ return z * i; }

inline
double
to_double(const Gmpz &z)
{ return z.to_double(); }

inline
Number_tag
number_type_tag(const Gmpz& )
{ return Number_tag(); }

inline
Sign
sign(const Gmpz &z)
{ return z.sign(); }

inline
bool
is_valid(const Gmpz &)
{ return true; }

inline
bool
is_finite(const Gmpz &)
{ return true; }

inline
Gmpz
sqrt(const Gmpz &z)
{
  Gmpz_rep* Res = new Gmpz_rep();
  mpz_sqrt(Res->mpZ, z.ptr()->mpZ);
  return Gmpz(Res);
}

inline
Gmpz
gcd(const Gmpz &z1, const Gmpz &z2)
{
  Gmpz_rep* Res = new Gmpz_rep();
  mpz_gcd(Res->mpZ, z1.ptr()->mpZ, z2.ptr()->mpZ);
  return Gmpz(Res);
}

inline
Gmpz
gcd(const Gmpz &z, int i)
{
  if (i > 0)
  {
      Gmpz_rep* Res = new Gmpz_rep();
      mpz_gcd_ui(Res->mpZ, z.ptr()->mpZ, i);
      return Gmpz(Res);
  }
  return gcd(z, Gmpz(i));
}

inline
Gmpz
exact_division(const Gmpz &z1,
                    const Gmpz &z2)
{
  Gmpz_rep* Res = new Gmpz_rep();
  mpz_divexact(Res->mpZ, z1.ptr()->mpZ, z2.ptr()->mpZ);
#ifdef CHECK_POSTCONDITIONS
  mpz_t prod;
  mpz_init(prod);
  mpz_mul(prod, Res->mpZ, z2.ptr()->mpZ);
  CGAL_kernel_postcondition_msg(mpz_cmp(prod, z1.ptr()->mpZ) == 0,
                                "exact_division failed\n");
  mpz_clear( prod);
#endif // CHECK_POSTCONDITIONS
  return Gmpz(Res);
}

inline
size_t
Gmpz::approximate_decimal_length() const
{ return mpz_sizeinbase(ptr()->mpZ,10); }

inline
std::ostream&
operator<<(std::ostream& os, const Gmpz &z)
{
  char *str = new char [mpz_sizeinbase(z.ptr()->mpZ,10) + 2];
  str = mpz_get_str(str, 10, z.ptr()->mpZ);
  os << str ;
  delete str;
  return os;
}

inline
std::istream&
operator>>(std::istream& is, Gmpz &z)
{
  int negative = 0;
  const int null = '0';
  char c;

  while (is.get(c) && isspace(c))
  {}

  if (c == '-')
  {
        negative = 1;
        while (is.get(c) && isspace(c))
        {}
  }
  if (isdigit(c))
  {
        z = c - '0';
        while (is.get(c) && isdigit(c))
        {
            z = 10*z + (c-null);
        }
  }
  if (is)
  {
        is.putback(c);
  }
  if (sign(z) != (Sign)0 && negative)
  {
        z = -z;
  }
  return is;
}

CGAL_END_NAMESPACE


#ifdef CGAL_INTERVAL_ARITHMETIC_H
#include <CGAL/Interval_arithmetic/IA_Gmpz.h>
#endif // CGAL_INTERVAL_ARITHMETIC_H

#endif // CGAL_GMPZ_H