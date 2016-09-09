// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/HalfedgeDS_decorator.h
// package       : HalfedgeDS (3.21)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds_decorator.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/05 21:07:09 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Decorator.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HALFEDGEDS_DECORATOR_H
#define CGAL_HALFEDGEDS_DECORATOR_H 1

#ifndef CGAL_HALFEDGEDS_ITEMS_DECORATOR_H
#include <CGAL/HalfedgeDS_items_decorator.h>
#endif
#ifndef CGAL_HALFEDGEDS_CONST_DECORATOR_H
#include <CGAL/HalfedgeDS_const_decorator.h>
#endif
#ifndef CGAL_PROTECT_VECTOR
#include <vector>
#define CGAL_PROTECT_VECTOR
#endif

#ifndef CGAL_IO_VERBOSE_OSTREAM_H
#include <CGAL/IO/Verbose_ostream.h>
#endif // CGAL_IO_VERBOSE_OSTREAM_H

CGAL_BEGIN_NAMESPACE

template < class p_HDS >
class HalfedgeDS_decorator : public HalfedgeDS_items_decorator<p_HDS> {

// TYPES (inherited from Items_decorator, but have to be repeated)
// ---------------------------------------------------------------
public:
    typedef p_HDS                                 HDS;
    typedef p_HDS                                 HalfedgeDS;
    typedef typename HDS::Traits                  Traits;
    typedef typename HDS::Vertex                  Vertex;
    typedef typename HDS::Halfedge                Halfedge;
    typedef typename HDS::Face                    Face;

    typedef typename HDS::Vertex_handle           Vertex_handle;
    typedef typename HDS::Vertex_const_handle     Vertex_const_handle;
    typedef typename HDS::Vertex_iterator         Vertex_iterator;
    typedef typename HDS::Vertex_const_iterator   Vertex_const_iterator;

    typedef typename HDS::Halfedge_handle         Halfedge_handle;
    typedef typename HDS::Halfedge_const_handle   Halfedge_const_handle;
    typedef typename HDS::Halfedge_iterator       Halfedge_iterator;
    typedef typename HDS::Halfedge_const_iterator Halfedge_const_iterator;

    typedef typename HDS::Face_handle             Face_handle;
    typedef typename HDS::Face_const_handle       Face_const_handle;
    typedef typename HDS::Face_iterator           Face_iterator;
    typedef typename HDS::Face_const_iterator     Face_const_iterator;

    typedef typename HDS::size_type               size_type;
    typedef typename HDS::difference_type         difference_type;
    typedef typename HDS::iterator_category       iterator_category;

// The following types are equal to either `Tag_true' or `Tag_false',
// dependent whether the named feature is supported or not.

    typedef typename HDS::Supports_vertex_halfedge
                                                  Supports_vertex_halfedge;
    typedef typename HDS::Supports_halfedge_prev  Supports_halfedge_prev;
    typedef typename HDS::Supports_halfedge_vertex
                                                  Supports_halfedge_vertex;
    typedef typename HDS::Supports_halfedge_face  Supports_halfedge_face;
    typedef typename HDS::Supports_face_halfedge  Supports_face_halfedge;

    typedef typename HDS::Supports_removal        Supports_removal;

protected:
    typedef typename Vertex::Base                 VBase;
    typedef typename Halfedge::Base               HBase;
    typedef typename Halfedge::Base_base          HBase_base;
    typedef typename Face::Base                   FBase;

// PRIVATE MEMBER VARIABLES
// ----------------------------------
private:
    p_HDS*  hds;

// CREATION
    // ----------------------------------
public:
    // No default constructor, keeps always a reference to a HDS!

    HalfedgeDS_decorator( p_HDS& h) : hds(&h) {}
        // keeps internally a reference to `hds'.

// Creation of New Elements
// ----------------------------------

    Vertex_handle vertices_push_back( const Vertex& v) {
        // appends a copy of v to `hds' if vertices are supported. Returns
        // handle of the new vertex, or `Vertex_handle()' otherwise.
        return vertices_push_back( v, Supports_halfedge_vertex());
    }

    Face_handle faces_push_back( const Face& f) {
        // appends a copy of f to `hds' if faces are supported. Returns
        // handle of the new face, or `Face_handle()' otherwise.
        return faces_push_back( f, Supports_halfedge_face());
    }

private:
    Vertex_handle vertices_push_back( Vertex_const_handle v) {
        // appends a copy of *v to `hds' if vertices are supported. Returns
        // handle of the new vertex, or `Vertex_handle()' otherwise.
        return vertices_push_back( v, Supports_halfedge_vertex());
    }

    Face_handle faces_push_back( Face_const_handle f) {
        // appends a copy of *f to `hds' if faces are supported. Returns
        // handle of the new face, or `Face_handle()' otherwise.
        return faces_push_back( f, Supports_halfedge_face());
    }
public:

// Creation of New Composed Items
// ----------------------------------

    Halfedge_handle create_loop() {
        // returns handle of a halfedge from a newly created loop in `hds'
        // consisting of a single closed edge, one vertex and two faces
        // (if supported respectively).
        Halfedge_handle h = hds->edges_push_back( Halfedge(), Halfedge());
        h->HBase::set_next( h);
        h->opposite()->HBase::set_next( h->opposite());
        set_prev( h, h);
        set_prev( h->opposite(), h->opposite());
        set_vertex( h, vertices_push_back( Vertex()));
        set_vertex( h->opposite(), get_vertex(h));
        set_face( h, faces_push_back( Face()));
        set_face( h->opposite(), faces_push_back( Face()));
        set_face_halfedge( h);
        set_face_halfedge( h->opposite());
        set_vertex_halfedge( h);
        return h;
    }

    Halfedge_handle create_segment() {
        // returns a halfedge from a newly created segment in `hds'
        // consisting of a single open edge, two vertices and one face (if
        // supported respectively).
        Halfedge_handle h = hds->edges_push_back( Halfedge(), Halfedge());
        h->HBase::set_next( h->opposite());
        h->opposite()->HBase::set_next( h);
        set_prev( h, h->opposite());
        set_prev( h->opposite(), h);
        set_vertex( h, vertices_push_back( Vertex()));
        set_vertex( h->opposite(), vertices_push_back( Vertex()));
        set_face( h, faces_push_back( Face()));
        set_face( h->opposite(), get_face(h));
        set_face_halfedge( h);
        set_vertex_halfedge( h);
        set_vertex_halfedge( h->opposite());
        return h;
    }

// Removal of Elements
// ----------------------------------

    void vertices_pop_front() {
        // removes the first vertex if vertices are supported.
        // Precondition: `Supports_removal' == `Tag_true'.
        vertices_pop_front( Supports_halfedge_vertex());
    }
    void vertices_pop_back() {
        // removes the last vertex if vertices are supported.
        vertices_pop_back( Supports_halfedge_vertex());
    }
    void vertices_erase( Vertex_handle v) {
        // removes the vertex v if vertices are supported. Precondition:
        // `Supports_removal' == `Tag_true'.
        vertices_erase( v, Supports_halfedge_vertex());
    }
    void vertices_erase( Vertex_handle first, Vertex_handle last) {
        // removes the range of vertices `[first,last)' if vertices
        // are supported. Precondition: `Supports_removal' ==
        // `Tag_true'.
        vertices_erase( first, last, Supports_halfedge_vertex());
    }

    void faces_pop_front() {
        // removes the first face if faces are supported. Precondition:
        // `Supports_removal' == `Tag_true'.
        faces_pop_front( Supports_halfedge_face());
    }
    void faces_pop_back() {
        // removes the last face if faces are supported.
        faces_pop_back( Supports_halfedge_face());
    }
    void faces_erase( Face_handle f) {
        // removes the face f if faces are supported. Precondition:
        // `Supports_removal' == `Tag_true'.
        faces_erase( f, Supports_halfedge_face());
    }
    void faces_erase( Face_handle first, Face_handle last) {
        // removes the range of faces `[first,last)' if faces
        // are supported. Precondition: `Supports_removal' ==
        // `Tag_true'.
        faces_erase( first, last, Supports_halfedge_face());
    }


// Modifying Functions (Euler Operators)
// -------------------------------------

// The following Euler operations modify consistently the combinatorial
// structure of the halfedge data structure. The geometry remains
// unchanged. Note that well known graph operations are also captured with
// these Euler operators, for example an edge contraction is equal to a
// `join_vertex()' operation, or an edge removal to `join_face()'.
//
// Given a halfedge data structure `hds' and a halfedge handle h four
// special applications of the Euler operators are worth mentioning:
// `split_vertex(h,h)' results in an antenna emanating from the tip of `h';
// `split_vertex(h,h->next()->opposite())' results in an edge split of
// the halfedge `h->next' with a new vertex in-between; `split_face(h,h)'
// results in a loop directly following `h'; and `split_face(h,h->next())'
// results in a bridge parallel to the halfedge `h->next' with a new face
// in-between.

    Halfedge_handle split_face( Halfedge_handle h, Halfedge_handle g) {
        // splits the face incident to `h' and `g' into two faces with a
        // new diagonal between the two vertices denoted by `h' and `g'
        // respectively. The second (new) face obtained from `hds' is a
        // copy of the first face. The new diagonal is returned. The time
        // is proportional to the distance from `h' to `g' around the
        // face.
        Halfedge_handle hnew = hds->edges_push_back( Halfedge(),
                                                     Halfedge());
        Face_handle fnew = faces_push_back( get_face(h));
        insert_tip( hnew, g);
        insert_tip( hnew->opposite(), h);
        set_face( hnew, get_face(h));
        set_face_in_face_loop( hnew->opposite(), fnew);
        set_face_halfedge( hnew);
        set_face_halfedge( hnew->opposite());
        return hnew;
    }

    Halfedge_handle join_face( Halfedge_handle h) {
        // joins the two faces incident to h. The face incident to
        // `h->opposite()' gets removed from `hds'. Both faces might be
        // holes. Returns the predecessor of h around the face. The
        // invariant `join_face( split_face( h, g))' returns h and keeps
        // the data structure unchanged. The time is proportional to the
        // size of the face removed and the time to compute `h->prev()'.
        // Precondition: `Supports_removal' == `Tag_true'.
        Assert_compile_time_tag( Tag_true(), Supports_removal());
        Halfedge_handle hprev = find_prev( h);
        Halfedge_handle gprev = find_prev( h->opposite());
        remove_tip( hprev);
        remove_tip( gprev);
        hds->edges_erase( h);
        if ( get_face( gprev) != Face_handle())
            faces_erase( get_face( gprev));
        h = hprev;
        // 'half' of the halfedges have their correct faces.
        // Here we do the remaining halfedges.
        CGAL_assertion_code( std::size_t termination_count = 0;)
        while ( h != gprev) {
            CGAL_assertion( ++termination_count != 0);
            h = h->next();
            set_face( h, get_face( hprev));
        }
        if ( get_face( hprev) != Face_handle())
            set_face_halfedge(  hprev);
        set_vertex_halfedge( hprev);
        set_vertex_halfedge( gprev);
        return hprev;
    }

    Halfedge_handle split_vertex( Halfedge_handle h, Halfedge_handle g) {
        // splits the vertex incident to `h' and `g' into two vertices and
        // connects them with a new edge. The second (new) vertex obtained
        // from `hds' is a copy of the first vertex. The new edge is
        // returned. The time is proportional to the distance from `h' to
        // `g' around the vertex.
        Halfedge_handle hnew = hds->edges_push_back( Halfedge(),
                                                     Halfedge());
        Vertex_handle vnew = vertices_push_back( get_vertex(h));
        insert_halfedge( hnew, g);
        insert_halfedge( hnew->opposite(), h);
        set_vertex( hnew, get_vertex(h));
        set_vertex_in_vertex_loop( hnew->opposite(), vnew);
        set_vertex_halfedge( hnew);
        set_vertex_halfedge( hnew->opposite());
        return hnew;
    }

    Halfedge_handle join_vertex( Halfedge_handle h) {
        // joins the two vertices incident to h. The vertex denoted by
        // `h->opposite()' gets removed by `hds'. Returns the predecessor
        // of h around the vertex. The invariant `join_vertex(
        // split_vertex( h, g))' returns h and keeps the polyhedron
        // unchanged. The time is proportional to the degree of the vertex
        // removed and the time to compute `h->prev()'. Precondition:
        // `Supports_removal' == `Tag_true'.
        Assert_compile_time_tag( Tag_true(), Supports_removal());
        Halfedge_handle hprev = find_prev( h->opposite());
        Halfedge_handle gprev = find_prev( h);
        remove_halfedge( hprev);
        remove_halfedge( gprev);
        hds->edges_erase( h);
        vertices_erase( get_vertex( gprev));
        // 'half' of the halfedges have their correct vertex.
        // Here we do the remaining halfedges.
        h = hprev;
        CGAL_assertion_code( std::size_t termination_count = 0;)
        while ( h != gprev) {
            CGAL_assertion( ++termination_count != 0);
            h = h->next()->opposite();
            set_vertex( h, get_vertex( hprev));
        }
        set_vertex_halfedge( hprev);
        if ( ! hprev->is_border())
            set_face_halfedge(  hprev);
        if ( ! gprev->is_border())
            set_face_halfedge(  gprev);
        return hprev;
    }

    Halfedge_handle create_center_vertex( Halfedge_handle h) {
        Halfedge_handle hnew = hds->edges_push_back( Halfedge(),
                                                     Halfedge());
        Vertex_handle vnew = vertices_push_back( get_vertex( h));
        close_tip( hnew, vnew);
        insert_tip( hnew->opposite(), h);
        set_face( hnew, get_face( h));
        set_face_halfedge( h);
        Halfedge_handle g = hnew->opposite()->next();
        while ( g->next() != hnew) {
            Halfedge_handle gnew = hds->edges_push_back( Halfedge(),
                                                         Halfedge());
            insert_tip( gnew, hnew);
            insert_tip( gnew->opposite(), g);
            Face_handle fnew = faces_push_back( get_face(hnew));
            set_face( g, fnew);
            set_face( gnew, fnew);
            set_face( gnew->next(), fnew);
            set_face_halfedge( g);
            g = gnew->opposite()->next();
        }
        set_face( hnew->next(), get_face( hnew));
        set_vertex_halfedge( hnew);
        return hnew;
    }

    Halfedge_handle erase_center_vertex( Halfedge_handle h) {
        // h points to the vertex that gets removed
        Halfedge_handle g    = h->next()->opposite();
        Halfedge_handle hret = find_prev( h);
        while ( g != h) {
            Halfedge_handle gprev = find_prev( g);
            set_vertex_halfedge( gprev);
            remove_tip( gprev);
            if ( get_face( g) != Face_handle())
                faces_erase( get_face( g));
            Halfedge_handle gnext = g->next()->opposite();
            hds->edges_erase( g);
            g = gnext;
        }
        set_vertex_halfedge( hret);
        remove_tip( hret);
        vertices_erase( get_vertex( h));
        hds->edges_erase( h);
        set_face_in_face_loop( hret, get_face( hret));
        set_face_halfedge(hret);
        return hret;
    }

    Halfedge_handle split_loop( Halfedge_handle h,
                                Halfedge_handle i,
                                Halfedge_handle j) {
        // cuts the halfedge data structure into two parts along the cycle
        // (h,i,j). Three new vertices (one copy for each vertex in the
        // cycle) and three new halfedges (one copy for each halfedge in
        // the cycle), and two new triangles are created. h,i,j will be
        // incident to the first new triangle. The return value will be
        // the halfedge incident to the second new triangle which is the
        // copy of `h-opposite()'. Precondition: h,i,j denote distinct,
        // consecutive vertices of the halfedge data structure and form a
        // cycle: i.e. `h->vertex() == i->opposite()->vertex()', ...,
        // `j->vertex() == h->opposite()->vertex()'.
        CGAL_precondition( h != i);
        CGAL_precondition( h != j);
        CGAL_precondition( i != j);
        CGAL_precondition( get_vertex(h) == get_vertex(i->opposite()));
        CGAL_precondition( get_vertex(i) == get_vertex(j->opposite()));
        CGAL_precondition( get_vertex(j) == get_vertex(h->opposite()));
        // Create a copy of the triangle.
        Halfedge_handle hnew = hds->edges_push_back( *h);
        Halfedge_handle inew = hds->edges_push_back( *i);
        Halfedge_handle jnew = hds->edges_push_back( *j);
        close_tip( hnew, vertices_push_back( get_vertex( h)));
        close_tip( inew, vertices_push_back( get_vertex( i)));
        close_tip( jnew, vertices_push_back( get_vertex( j)));
        insert_tip( inew->opposite(), hnew);
        insert_tip( jnew->opposite(), inew);
        insert_tip( hnew->opposite(), jnew);
        // Make the new incidences with the old stucture.
        CGAL_assertion_code( std::size_t termination_count = 0;)
        if ( h->next() != i) {
            Halfedge_handle g = h->next();
            h->HBase::set_next( i);
            set_prev( i, h);
            hnew->HBase::set_next( g);
            set_prev( g, hnew);
            g = g->opposite();
            while ( g->next() != i) {
                CGAL_assertion( ++termination_count != 0);
                set_vertex( g, get_vertex( hnew));
                g = g->next()->opposite();
            }
            set_vertex( g, get_vertex( hnew));
            g->HBase::set_next( inew);
            set_prev( inew, g);
        }
        if ( i->next() != j) {
            Halfedge_handle g = i->next();
            i->HBase::set_next( j);
            set_prev( j, i);
            inew->HBase::set_next( g);
            set_prev( g, inew);
            g = g->opposite();
            while ( g->next() != j) {
                CGAL_assertion( ++termination_count != 0);
                set_vertex( g, get_vertex( inew));
                g = g->next()->opposite();
            }
            set_vertex( g, get_vertex( inew));
            g->HBase::set_next( jnew);
            set_prev( jnew, g);
        }
        if ( j->next() != h) {
            Halfedge_handle g = j->next();
            j->HBase::set_next( h);
            set_prev( h, j);
            jnew->HBase::set_next( g);
            set_prev( g, jnew);
            g = g->opposite();
            while ( g->next() != h) {
                CGAL_assertion( ++termination_count != 0);
                set_vertex( g, get_vertex( jnew));
                g = g->next()->opposite();
            }
            set_vertex( g, get_vertex( jnew));
            g->HBase::set_next( hnew);
            set_prev( hnew, g);
        }
        // Fill the holes with two new faces.
        Face_handle f = faces_push_back( Face());
        set_face( h, f);
        set_face( i, f);
        set_face( j, f);
        set_face_halfedge( h);
        f = faces_push_back( Face());
        set_face( hnew->opposite(), f);
        set_face( inew->opposite(), f);
        set_face( jnew->opposite(), f);
        set_face_halfedge( hnew->opposite());
        // Take care of maybe changed halfedge pointers.
        set_face_halfedge( hnew);
        set_face_halfedge( inew);
        set_face_halfedge( jnew);
        set_vertex_halfedge( hnew);
        set_vertex_halfedge( inew);
        set_vertex_halfedge( jnew);
        return hnew->opposite();
    }

    Halfedge_handle join_loop( Halfedge_handle h, Halfedge_handle g) {
        // glues the boundary of the two faces denoted by h and g together
        // and returns h. Both faces and the vertices along the face
        // denoted by g gets removed. Both faces may be holes. The
        // invariant `join_loop( h, split_loop( h, i, j))' returns h and
        // keeps the data structure unchanged. Precondition:
        // `Supports_removal' == `Tag_true'. The faces denoted by h
        // and g are different and have equal degree (i.e. number of
        // edges).
        Assert_compile_time_tag( Tag_true(), Supports_removal());
        CGAL_precondition(    get_face(h) == Face_handle()
                    || get_face(h) != get_face(g));
        if ( get_face( h) != Face_handle())
            faces_erase( get_face(h));
        if ( get_face( g) != Face_handle())
            faces_erase( get_face(g));
        Halfedge_handle hi = h;
        Halfedge_handle gi = g;
        CGAL_assertion_code( std::size_t termination_count = 0;)
        do {
            CGAL_assertion( ++termination_count != 0);
            Halfedge_handle hii = hi;
            Halfedge_handle gii = gi;
            hi = hi->next();
            // gi = find_prev(gi); // Replaced by search around vertex.
            set_face( hii, get_face( gii->opposite()));
            set_face_halfedge( hii);
            vertices_erase( get_vertex( gii->opposite()));
            if ( gii->opposite()->next()->opposite()->next() == gii) {
                gi = gii->opposite()->next()->opposite();
            } else {
                hii->HBase::set_next( gii->opposite()->next());
                set_prev( hii->next(), hii);
                gii = gii->opposite()->next()->opposite();
                set_vertex( gii, get_vertex(hii));
                while ( gii->next()->opposite()->next() != gi) {
                    CGAL_assertion( ++termination_count != 0);
                    gii = gii->next()->opposite();
                    set_vertex( gii, get_vertex(hii));
                }
                gi = gii->next()->opposite();
                gii->HBase::set_next( hi);
                set_prev( gii->next(), gii);
            }
        } while ( hi != h);
        CGAL_assertion( gi == g);
        do {
            Halfedge_handle gii = gi;
            gi = gi->next();
            hds->edges_erase( gii);
        } while ( gi != g);
        return h;
    }

  protected:
    // supports face or not.
    void make_hole( Halfedge_handle, Tag_false) {}
    void fill_hole( Halfedge_handle, Tag_false) {}
    void fill_hole( Halfedge_handle, const Face&, Tag_false) {}

    void make_hole( Halfedge_handle h, Tag_true) {
        Assert_compile_time_tag( Tag_true(), Supports_removal());
        CGAL_precondition( h != Halfedge_handle());
        CGAL_precondition( ! h->is_border());
        hds->faces_erase( h->face());
        set_face_in_face_loop( h, Face_handle());
    }

    void fill_hole( Halfedge_handle h, Tag_true) {
        CGAL_precondition( h != Halfedge_handle());
        CGAL_precondition( h->is_border());
        Face_handle f = faces_push_back( Face());
        set_face_in_face_loop( h, f);
        set_face_halfedge( h);
    }

    void fill_hole( Halfedge_handle h, const Face& f, Tag_true) {
        CGAL_precondition( h != Halfedge_handle());
        CGAL_precondition( h->is_border());
        Face_handle fh = faces_push_back( f);
        set_face_in_face_loop( h, fh);
        set_face_halfedge( h);
    }

  public:

    Halfedge_handle make_hole( Halfedge_handle h) {
        // removes the face incident to `h' from `hds' and creates a hole.
        // Precondition: `h != Halfedge_handle()' and `!(h->is_border())'.
        // If faces are supported, `Supports_removal' == `Tag_true'.
        make_hole( h, Supports_halfedge_face());
        return h;
    }

    Halfedge_handle fill_hole( Halfedge_handle h) {
        // fills the hole incident to `h' with a new face from `hds'.
        // Precondition: `h != Halfedge_handle()' and `h->is_border()'.
        fill_hole( h, Supports_halfedge_face());
        return h;
    }

    Halfedge_handle fill_hole( Halfedge_handle h, const Face& f) {
        // fills the hole incident to `h' with a copy of face f.
        // Precondition: `h != Halfedge_handle()' and `h->is_border()'.
        fill_hole( h, f, Supports_halfedge_face());
        return h;
    }

    Halfedge_handle add_face_to_border( Halfedge_handle h,
                                        Halfedge_handle g,
                                        const Face& f) {
        // extends the surface with a copy of face f into the hole
        // incident to h and g. It creates a new edge connecting the tip
        // of g with the tip of h and fills this separated part of the
        // hole with a copy of face f, such that the new face is incident
        // to g. Returns the new halfedge that is incident to the new
        // face. Precondition: `h != Halfedge_handle()', `g !=
        // Halfedge_handle()', `h->is_border()', `g->is_border()' and g
        // can be reached along the hole starting with h.
        CGAL_precondition( h != Halfedge_handle());
        CGAL_precondition( g != Halfedge_handle());
        CGAL_precondition( h->is_border());
        CGAL_precondition( g->is_border());
        Halfedge_handle hh = hds->edges_push_back( Halfedge(), Halfedge());
        insert_tip( hh, h);
        insert_tip( hh->opposite(), g);
        fill_hole( g, f);
        return hh;
    }

    Halfedge_handle add_face_to_border( Halfedge_handle h,
                                        Halfedge_handle g) {
        // extends the surface with a new face from `hds' into the hole
        // incident to h and g. It creates a new edge connecting the tip
        // of g with the tip of h and fills this separated part of the
        // hole with a new face, such that the new face is incident to g.
        // Returns the new halfedge that is incident to the new face.
        // Precondition: `h != Halfedge_handle()', `g != Halfedge_handle(
        // )', `h->is_border()', `g->is_border()' and g can be reached
        // along the hole starting with h.
        return add_face_to_border( h, g, Face());
    }

// Erasing
// ----------------------------------
  protected:
    // supports face or not.
    void erase_face( Halfedge_handle,   Tag_false) {}
    void erase_face( Halfedge_handle h, Tag_true)  {
        Assert_compile_time_tag( Tag_true(), Supports_removal());
        CGAL_precondition( h != Halfedge_handle());
        CGAL_precondition( ! h->is_border());
        hds->faces_erase( h->face());
        CGAL_assertion_code( std::size_t termination_count = 0;)
        Halfedge_handle end = h;
        do {
            CGAL_assertion( ++termination_count != 0);
            set_face( h, Face_handle());
            Halfedge_handle g = h->next();
            bool h_tag = h->opposite()->is_border();
            bool g_tag = g->opposite()->is_border();
            if ( h_tag && g_tag && g->opposite()->next() == h->opposite()){
                vertices_erase( get_vertex(h));
                if ( h != end)
                    hds->edges_erase( h);
            } else {
                if ( g_tag) {
                    set_vertex_halfedge(g->opposite()->next()->opposite());
                    remove_tip(h);
                }
                if ( h_tag) {
                    set_vertex_halfedge(h->next()->opposite());
                    remove_tip( find_prev_around_vertex( h->opposite()));
                    if ( h != end)
                        hds->edges_erase(h);
                }
            }
            h = g;
        } while ( h != end);
        if ( h->opposite()->is_border())
            hds->edges_erase( h);
    }

  public:
    void erase_face( Halfedge_handle h) {
        // removes the face incident to `h' from `hds' and changes all
        // halfedges incident to the face into border edges or removes
        // them from the halfedge data structure if they were already
        // border edges. See `make_hole(h)' for a more specialized
        // variant. Precondition: `h != Halfedge_handle()'. If faces are
        // supported, `Supports_removal' == `Tag_true'.
        erase_face( h, Supports_halfedge_face());
    }

  protected:                               // Supports_halfedge_vertices
      void erase_connected_component_vertex( Halfedge_handle  ,Tag_false){}
      void erase_connected_component_vertex( Halfedge_handle h, Tag_true) {
          // Erases the the vertex incident to h and sets all references
          // from halfedges around this vertex to Halfedge_handle(),
          // if the incident vertex handle is not already equal to
          // Halfedge_handle(). It is used to erase vertices as soon
          // as an vertex is encountered in the graph traversal. At this
          // point of the graph traversal the halfedge cycle around the
          // vertex is still closed. Lateron it will be broken.
          if ( h->vertex() != Vertex_handle()) {
              hds->vertices_erase( h->vertex());
              set_vertex_in_vertex_loop( h, Vertex_handle());
          }
      }
      void erase_connected_component_vertex( Halfedge_handle h) {
          erase_connected_component_vertex( h, Supports_halfedge_vertex());
      }

      void erase_connected_component_face_cycle( Halfedge_handle h,
                  std::vector<Halfedge_handle>& stack) {
          // Delete incident face and set all incidences to Face_handle().
          if ( get_face(h) != Face_handle()) {
              faces_erase( get_face(h));
              set_face_in_face_loop( h, Face_handle());
          }
          // Cycle around face, delete incident vertices, push new
          // edges on the stack and mark edges as visited.
          erase_connected_component_vertex( h);
          Halfedge_handle g = h->next();
          h->HBase::set_next( Halfedge_handle());
          while (g != h) {
              erase_connected_component_vertex( g);
              if ( g->opposite()->next() != Halfedge_handle())
                  stack.push_back( g->opposite());
              Halfedge_handle gg = g->next();
              g->HBase::set_next( Halfedge_handle());
              g = gg;
          }
      }

  public:
    void erase_connected_component( Halfedge_handle h) {
        // removes the vertices, halfedges, and facets that belong to the
        // connected component of h. Precondition: `Supports_removal'
        // == `Tag_true'. For all halfedges g in the connected
        // component `g.next() != Halfedge_handle()'.
        Assert_compile_time_tag( Tag_true(), Supports_removal());
        typedef std::vector<Halfedge_handle> HVector;
        HVector stack;
        // Algorithm: The next() pointer is used as visited tag
        //     for a graph search. If the next pointer of an halfedge
        //     or its opposite halfedge is set to Halfedge_handle(),
        //     this edge has already been visited and must not be put
        //     on the stack again.
        // Initializing: Cycle through the face-cycle of h and put
        //     all opposite halfedges on the stack. Put h->opposite()
        //     on the stack. Note that even if the face cycle of h looks
        //     ugly ( e.g. h->opposite() is also in the cycle), neither
        //     h nor h->opposite() will be put on the stack. If
        //     h->opposite() is in the cycle, when h will be popped from
        //     the stack it will be immediately deleted.
        // Loop invariant: For each edge h on the stack h->opposite()->
        //     next() == Halfedge_handle().
        // Looping: For each edge h on the stack, if h->next() is
        //     not already equal to Halfedge_handle(), cycle through
        //     the face-cycle of h and put all opposite halfedges on
        //     the stack. Delete h.
        // Where: Cycle through a face means: If h->face() !=
        //     Halfedge_handle() delete h->face() and set all face
        //     handles to Halfedge_handle(). Loop through the
        //     halfedges g around the face, call
        //     erase_connected_component_vertex for each g, push
        //     g->opposite() on the stack if g->opposite()->next()
        //     is not already Halfedge_handle(). This implies that
        //     h->opposite() is not put on the stack again.
        erase_connected_component_face_cycle( h, stack);
        stack.push_back( h->opposite());
        while ( ! stack.empty()) {
            h = stack.back();
            stack.pop_back();
            CGAL_assertion( h->opposite()->next() == Halfedge_handle());
            if ( h->next() != Halfedge_handle())
                erase_connected_component_face_cycle( h, stack);
            hds->edges_erase( h);
        }
    }

// Implementing These Functions.
// ====================================================
// Creation of New Elements
// ----------------------------------
private:

    Vertex_handle vertices_push_back( const Vertex&  , Tag_false) {
        return Vertex_handle();
    }
    Vertex_handle vertices_push_back( const Vertex& v, Tag_true) {
        return hds->vertices_push_back(v);
    }

    Vertex_handle vertices_push_back( Vertex_const_handle  , Tag_false) {
        return Vertex_handle();
    }
    Vertex_handle vertices_push_back( Vertex_const_handle v, Tag_true) {
        return hds->vertices_push_back(*v);
    }

    Face_handle faces_push_back( const Face&  , Tag_false) {
        return Face_handle();
    }
    Face_handle faces_push_back( const Face& f, Tag_true) {
        return hds->faces_push_back(f);
    }

    Face_handle faces_push_back( Face_const_handle  , Tag_false) {
        return Face_handle();
    }
    Face_handle faces_push_back( Face_const_handle f, Tag_true) {
        return hds->faces_push_back(*f);
    }


// Removal of Elements
// ----------------------------------

    void vertices_erase( Vertex_handle  , Tag_false) {}
    void vertices_erase( Vertex_handle v, Tag_true) {
        hds->vertices_erase( v);
    }

    void vertices_pop_front( Tag_false) {}
    void vertices_pop_front( Tag_true) {
        hds->vertices_pop_front();
    }

    void vertices_pop_back( Tag_false) {}
    void vertices_pop_back( Tag_true) {
        hds->vertices_pop_back();
    }

    void faces_erase( Face_handle  , Tag_false) {}
    void faces_erase( Face_handle f, Tag_true) {
        hds->faces_erase( f);
    }

    void faces_pop_front( Tag_false) {}
    void faces_pop_front( Tag_true) {
        hds->faces_(pop_front);
    }

    void faces_pop_back( Tag_false) {}
    void faces_pop_back( Tag_true) {
        hds->faces_pop_back();
    }

// Others
// ----------------------------------
public:

    bool normalized_border_is_valid( bool verb = false) const {
        // returns `true' if the border halfedges are in normalized
        // representation, which is when enumerating all halfedges with
        // the halfedge iterator the following holds: The non-border edges
        // precede the border edges. For border edges, the second halfedge
        // is a border halfedge. (The first halfedge may or may not be a
        // border halfedge.) The halfedge iterator `border_halfedges_begin
        // ()' denotes the first border edge. If `verbose' is `true',
        // statistics are written to `cerr'.
        HalfedgeDS_const_decorator<p_HDS> decorator(*hds);
        return decorator.normalized_border_is_valid( verb);
    }
    bool is_valid( bool verb = false, int level = 0) const {
        // returns `true' if the halfedge data structure `hds' is valid
        // with respect to the `level' value as defined in the reference
        // manual. If `verbose' is `true', statistics are written to
        // `cerr'.
        HalfedgeDS_const_decorator<p_HDS> decorator(*hds);
        return decorator.is_valid( verb, level);
    }
    void reorient_face( Halfedge_handle first);
                  // Supports: halfedge pointer in faces.
    void inside_out( Tag_false);
    void inside_out( Tag_true);

    void inside_out() {
        inside_out( Supports_face_halfedge());
    }
};

template < class p_HDS >  CGAL_MEDIUM_INLINE
void
HalfedgeDS_decorator<p_HDS>::
reorient_face( Halfedge_handle first) {
    if ( first == Halfedge_handle())
        return;
    Halfedge_handle last  = first;
    Halfedge_handle prev  = first;
    Halfedge_handle start = first;
    first = first->next();
    Vertex_handle  new_v = get_vertex( start);
    while (first != last) {
        Vertex_handle  tmp_v = get_vertex( first);
        set_vertex( first, new_v);
        set_vertex_halfedge( first);
        new_v = tmp_v;
        Halfedge_handle next = first->next();
        first->HBase::set_next( prev);
        set_prev( first, next);
        prev  = first;
        first = next;
    }
    set_vertex( start, new_v);
    set_vertex_halfedge( start);
    Halfedge_handle next = start->next();
    start->HBase::set_next( prev);
    set_prev( start, next);
}

template < class p_HDS >
void                            // Supports: halfedge pointer in faces.
HalfedgeDS_decorator<p_HDS>::
inside_out( Tag_false) {
    Halfedge_iterator begin = hds->halfedges_begin();
    Halfedge_iterator end   = hds->halfedges_end();
    for( ; begin != end; ++begin) {
        // Define the halfedge with the `smallest' pointer
        // value as the one that is used to reorient the face.
        Halfedge_handle h = begin;
        bool is_min = true;
        Halfedge_handle c = h;
        Halfedge_handle d = c;
        do {
            CGAL_assertion( c != Halfedge_handle());
            if ( h > c)
                is_min = false;
            c = c->next();
        } while ( c != d && is_min);
        if ( is_min)
            reorient_face( h);
    }
}

template < class p_HDS >
void                            // Supports: halfedge pointer in faces.
HalfedgeDS_decorator<p_HDS>::
inside_out( Tag_true) {
    Face_iterator begin = hds->faces_begin();
    Face_iterator end   = hds->faces_end();
    for( ; begin != end; ++begin)
        reorient_face( begin->halfedge());
    // Note: A border edge is now parallel to its opposite edge.
    // We scan all border edges for this property. If it holds, we
    // reorient the associated hole and search again until no border
    // edge with that property exists any longer. Then, all holes are
    // reoriented.
    Halfedge_iterator first = hds->halfedges_begin();
    Halfedge_iterator last  = hds->halfedges_end();
    for( ; first != last; ++first) {
        if ( first->is_border() &&
             first->vertex() == first->opposite()->vertex())
            reorient_face( first);
    }
}

CGAL_END_NAMESPACE

#endif // CGAL_HALFEDGEDS_DECORATOR_H //
// EOF //