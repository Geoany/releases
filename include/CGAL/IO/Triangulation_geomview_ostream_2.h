// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/IO/Triangulation_geomview_ostream_2.h
// package       : Triangulation_2 (5.18)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/12/14 13:26:55 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_2_H
#define CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_2_H

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/Triangulation_2.h>

CGAL_BEGIN_NAMESPACE

// There are 2 drawing functions for triangulations : depending on the wired
// mode of the Geomview_stream, we draw either the edges or the faces.

// TODO :
// - Check the correctness when dimension < 2.
// - Use the current stream color instead of built-in constant.

template < class GT, class TDS >
void
show_triangulation_edges(Geomview_stream &gv, const Triangulation_2<GT,TDS> &T)
{
    // Header.
    gv.set_ascii_mode();
    gv << "(geometry " << gv.get_new_id("triangulationedge")
       << " {appearance {}{ SKEL \n"
       << T.number_of_vertices()
       << T.number_of_vertices() + T.number_of_faces()-1 << "\n";

    // Finite vertices coordinates.
    std::map<Triangulation_2<GT, TDS>::Vertex_handle, int> V;
    int inum = 0;
    for( Triangulation_2<GT, TDS>::Vertex_iterator
	  vit = T.vertices_begin(); vit != T.vertices_end(); ++vit) {
        V[vit] = inum++;
        gv << vit->point() << "\n";
    }
  
    // Finite edges indices.
    for( Triangulation_2<GT, TDS>::Edge_iterator
	  eit = T.edges_begin(); eit != T.edges_end(); ++eit) {
        gv << 2
           << V[(*eit).first->vertex(T.ccw((*eit).second))]
           << V[(*eit).first->vertex(T. cw((*eit).second))]
           << "\n"; // without color.
        // << 4 << drand48() << drand48() << drand48() << 1.0; // random color
    }
}

template < class GT, class TDS >
void
show_triangulation_faces(Geomview_stream &gv, const Triangulation_2<GT,TDS> &T)
{
    // Header.
    gv.set_binary_mode();
    gv << "(geometry " << gv.get_new_id("triangulation")
       << " {appearance {}{ OFF BINARY\n"
       << T.number_of_vertices() << T.number_of_faces() << 0;

    // Finite vertices coordinates.
    std::map<Triangulation_2<GT, TDS>::Vertex_handle, int> V;
    int inum = 0;
    for( Triangulation_2<GT, TDS>::Vertex_iterator
	  vit = T.vertices_begin(); vit != T.vertices_end(); ++vit) {
        V[vit] = inum++;
        gv << vit->point();
    }
  
    // Finite faces indices.
    for( Triangulation_2<GT, TDS>::Face_iterator
	  fit = T.faces_begin(); fit != T.faces_end(); ++fit) {
        gv << 3;
        for (int i=0; i<3; i++)
            gv << V[fit->vertex(i)];
        gv << 0; // without color.
     // gv << 4 << drand48() << drand48() << drand48() << 1.0; // random color
    }
}

template < class GT, class TDS >
Geomview_stream&
operator<<( Geomview_stream &gv, const Triangulation_2<GT,TDS> &T)
{
    bool ascii_bak = gv.get_ascii_mode();
    bool raw_bak = gv.set_raw(true);

    if (gv.get_wired())
	show_triangulation_edges(gv, T);
    else
	show_triangulation_faces(gv, T);

    // Footer.
    gv << "}})";

    gv.set_raw(raw_bak);
    gv.set_ascii_mode(ascii_bak);
    return gv;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_2_H