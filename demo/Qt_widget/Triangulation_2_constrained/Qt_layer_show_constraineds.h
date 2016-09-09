// ============================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_layer_show_points.h
// package       : Qt_widget
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_LAYER_SHOW_CONSTRAINEDS_H
#define CGAL_QT_LAYER_SHOW_CONSTRAINEDS_H

#include <CGAL/IO/Qt_widget_layer.h>

namespace CGAL {

template <class T>
class Qt_layer_show_constraineds : public Qt_widget_layer {
public:
  typedef typename T::Edge            Edge;
  typedef typename T::Finite_edges_iterator
                                      Finite_edges_iterator;

  Qt_layer_show_constraineds(T &t) : tr(t){};

  void draw()
  {  
    Finite_edges_iterator it = tr.finite_edges_begin();
    *widget << CGAL::RED << CGAL::LineWidth(2);
    while(it != tr.finite_edges_end()) {
      if(tr.is_constrained(*it))
        *widget << tr.segment(it);
      ++it;
    }
  };
private:
  T	&tr;
  
};//end class 

} // namespace CGAL

#endif // CGAL_QT_LAYER_SHOW_CONSTRAINEDS_H