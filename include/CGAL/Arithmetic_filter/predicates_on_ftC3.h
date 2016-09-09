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
// file          : include/CGAL/Arithmetic_filter/predicates_on_ftC3.h
// package       : Interval_arithmetic (4.15)
// source        : include/CGAL/predicates_on_ftC3.h
// revision      : $Revision: 1.20 $
// revision_date :
// author(s)     : Sylvain.Pion
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC3_H
#define CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC3_H

// This file is automatically generated by the script for filtering
// predicates, using Interval arithmetic.

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H
#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC3_H
#include <CGAL/basic_constructions_ftC3.h>
#endif // CGAL_BASIC_CONSTRUCTIONS_FTC3_H

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_lexicographically_xyzC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &x1, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &y1, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &z1,
                                
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &x2, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &y2, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &z2)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Comparison_result result = compare_lexicographically_xyzC3(
		x1.interval(),
		y1.interval(),
		z1.interval(),
		x2.interval(),
		y2.interval(),
		z2.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return compare_lexicographically_xyzC3(
		x1.exact(),
		y1.exact(),
		z1.exact(),
		x2.exact(),
		y2.exact(),
		z2.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
collinearC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
            
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
            
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = collinearC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return collinearC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
Orientation
orientationC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
              
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
              
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz,
              
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Orientation result = orientationC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval(),
		sx.interval(),
		sy.interval(),
		sz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return orientationC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact(),
		sx.exact(),
		sy.exact(),
		sz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_ordered_along_lineC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = collinear_are_ordered_along_lineC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return collinear_are_ordered_along_lineC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
collinear_are_strictly_ordered_along_lineC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = collinear_are_strictly_ordered_along_lineC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return collinear_are_strictly_ordered_along_lineC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact());
  }
}


#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_LARGE_INLINE
Oriented_side
side_of_oriented_sphereC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
                          
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
                          
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz,
                          
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sz,
                          
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ty, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Oriented_side result = side_of_oriented_sphereC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval(),
		sx.interval(),
		sy.interval(),
		sz.interval(),
		tx.interval(),
		ty.interval(),
		tz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return side_of_oriented_sphereC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact(),
		sx.exact(),
		sy.exact(),
		sz.exact(),
		tx.exact(),
		ty.exact(),
		tz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
side_of_bounded_sphereC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
                         
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
                         
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz,
                         
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &sz,
                         
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ty, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Bounded_side result = side_of_bounded_sphereC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval(),
		sx.interval(),
		sy.interval(),
		sz.interval(),
		tx.interval(),
		ty.interval(),
		tz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return side_of_bounded_sphereC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact(),
		sx.exact(),
		sy.exact(),
		sz.exact(),
		tx.exact(),
		ty.exact(),
		tz.exact());
  }
}


#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_INLINE
Comparison_result
cmp_dist_to_pointC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
                    
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
                    
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Comparison_result result = cmp_dist_to_pointC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return cmp_dist_to_pointC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_dist_to_pointC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
                           
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
                           
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = has_larger_dist_to_pointC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return has_larger_dist_to_pointC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_dist_to_pointC3(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
                            
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz,
                            
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = has_smaller_dist_to_pointC3(
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval(),
		rx.interval(),
		ry.interval(),
		rz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return has_smaller_dist_to_pointC3(
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact(),
		rx.exact(),
		ry.exact(),
		rz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
cmp_signed_dist_to_planeC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pa, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pb, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pc, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pd,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Comparison_result result = cmp_signed_dist_to_planeC3(
		pa.interval(),
		pb.interval(),
		pc.interval(),
		pd.interval(),
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return cmp_signed_dist_to_planeC3(
		pa.exact(),
		pb.exact(),
		pc.exact(),
		pd.exact(),
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_signed_dist_to_planeC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pa, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pb, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pc, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pd,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = has_larger_signed_dist_to_planeC3(
		pa.interval(),
		pb.interval(),
		pc.interval(),
		pd.interval(),
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return has_larger_signed_dist_to_planeC3(
		pa.exact(),
		pb.exact(),
		pc.exact(),
		pd.exact(),
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_signed_dist_to_planeC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pa, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pb, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pc, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pd,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = has_smaller_signed_dist_to_planeC3(
		pa.interval(),
		pb.interval(),
		pc.interval(),
		pd.interval(),
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return has_smaller_signed_dist_to_planeC3(
		pa.exact(),
		pb.exact(),
		pc.exact(),
		pd.exact(),
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact());
  }
}
#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
cmp_signed_dist_to_planeC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &prx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &prz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    Comparison_result result = cmp_signed_dist_to_planeC3(
		ppx.interval(),
		ppy.interval(),
		ppz.interval(),
		pqx.interval(),
		pqy.interval(),
		pqz.interval(),
		prx.interval(),
		pry.interval(),
		prz.interval(),
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return cmp_signed_dist_to_planeC3(
		ppx.exact(),
		ppy.exact(),
		ppz.exact(),
		pqx.exact(),
		pqy.exact(),
		pqz.exact(),
		prx.exact(),
		pry.exact(),
		prz.exact(),
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_signed_dist_to_planeC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &prx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &prz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = has_larger_signed_dist_to_planeC3(
		ppx.interval(),
		ppy.interval(),
		ppz.interval(),
		pqx.interval(),
		pqy.interval(),
		pqz.interval(),
		prx.interval(),
		pry.interval(),
		prz.interval(),
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return has_larger_signed_dist_to_planeC3(
		ppx.exact(),
		ppy.exact(),
		ppz.exact(),
		pqx.exact(),
		pqy.exact(),
		pqz.exact(),
		prx.exact(),
		pry.exact(),
		prz.exact(),
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact());
  }
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
// CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_signed_dist_to_planeC3(
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ppz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pqz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &prx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pry, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &prz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pz,
     
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qz)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  try
  {
    bool result = has_smaller_signed_dist_to_planeC3(
		ppx.interval(),
		ppy.interval(),
		ppz.interval(),
		pqx.interval(),
		pqy.interval(),
		pqz.interval(),
		prx.interval(),
		pry.interval(),
		prz.interval(),
		px.interval(),
		py.interval(),
		pz.interval(),
		qx.interval(),
		qy.interval(),
		qz.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return has_smaller_signed_dist_to_planeC3(
		ppx.exact(),
		ppy.exact(),
		ppz.exact(),
		pqx.exact(),
		pqy.exact(),
		pqz.exact(),
		prx.exact(),
		pry.exact(),
		prz.exact(),
		px.exact(),
		py.exact(),
		pz.exact(),
		qx.exact(),
		qy.exact(),
		qz.exact());
  }
}


CGAL_END_NAMESPACE

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_ARITHMETIC_FILTER_PREDICATES_ON_FTC3_H
#include <CGAL/Arithmetic_filter/predicates_on_ftC3.h>
#endif // CGAL_ARITHMETIC_FILTER_ARITHMETIC_FILTER_PREDICATES_ON_FTC3_H
#endif

#endif // CGAL_ARITHMETIC_FILTER_PREDICATES_ON_FTC3_H