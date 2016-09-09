// Copyright (c) 2001  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Arrangement/include/CGAL/IO/Qt_widget_Conic_arc_2.h,v $
// $Revision: 1.2 $ $Date: 2003/09/18 10:19:48 $
// $Name: current_submission $
//
// Author(s)     : Efi Fogel <efif@post.tau.ac.il>

#ifndef CGAL_QT_WIDGET_NEF_2_H
#define CGAL_QT_WIDGET_NEF_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Arrangement_2/Conic_arc_2.h>

CGAL_BEGIN_NAMESPACE

template <class Kernel>
Qt_widget & operator<<(Qt_widget & ws, const Conic_arc_2<Kernel> & cv)
{
  // Get the co-ordinates of the curve's source and target.
  double sx = CGAL::to_double(cv.source().x()),
         sy = CGAL::to_double(cv.source().y()),
         tx = CGAL::to_double(cv.target().x()),
         ty = CGAL::to_double(cv.target().y());

  if (cv.is_segment()) {
    // The curve is a segment - simply draw it.
    ws.get_painter().drawLine(ws.x_pixel(sx), ws.y_pixel(sy),
                              ws.x_pixel(tx), ws.y_pixel(ty));
    return (ws); 
  }

  // The arc is circular
  // If the curve is monotone, than its source and its target has the
  // extreme x co-ordinates on this curve.
  if (cv.is_x_monotone()) {
    bool is_source_left = (sx < tx);
    int  x_min = is_source_left ? ws.x_pixel(sx) : ws.x_pixel(tx);
    int  x_max = is_source_left ? ws.x_pixel(tx) : ws.x_pixel(sx);
    double prev_y = is_source_left ? sy : ty;
    double end_x = is_source_left ? tx : sx;
    double end_y = is_source_left ? ty : sy;
    double curr_x, curr_y;
    int x;

    typename Conic_arc_2<Kernel>::Point_2 ps[2];
    int nps;

    ws.get_painter().moveTo(x_min, ws.y_pixel(prev_y));
      
    for (x = x_min + 1; x < x_max; x++) {
      curr_x = ws.x_real(x);
      nps =
        cv.get_points_at_x(Conic_arc_2<Kernel>::
                           Point_2(typename Kernel::FT(curr_x), 0), ps);
      if (nps == 1) {
        curr_y = CGAL::to_double(ps[0].y());
        ws.get_painter().lineTo(x, ws.y_pixel(curr_y));
      }
    }

    ws.get_painter().lineTo(ws.x_pixel(end_x), ws.y_pixel(end_y));
    return (ws); 
  }

  // We should never reach here.
  CGAL_assertion(false);
  return (ws); 
}

CGAL_END_NAMESPACE

#endif