// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// 
// release       : 
// release_date  : 
// 
// file          : Aff_transformationH3.h
// package       : H3
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra@mpi-sb.mpg.de>)
// ======================================================================
 

#ifndef CGAL_AFF_TRANSFORMATIONH3_H
#define CGAL_AFF_TRANSFORMATIONH3_H

#if defined(CGAL_CFG_INCOMPLETE_TYPE_BUG_1) && \
   !defined(CGAL_NO_PLANE_TRANSFORM_IN_AT)
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

#include <CGAL/determinant.h>

CGAL_BEGIN_NAMESPACE

// forward declaration
template < class R >
class Aff_transformationH3;

template < class R >
class Aff_transformation_repH3;

template < class R >
Aff_transformationH3<R>
_general_transformation_composition (
                           Aff_transformation_repH3<R> l,
                           Aff_transformation_repH3<R> r
                                         );

template <class R_ >
class Aff_transformation_rep_baseH3 : public Rep
// abstract base class of aff transformation representations
{
public:
  typedef R_                       R;
  typedef typename R::FT           FT;
  typedef typename R::RT           RT;

  virtual  ~Aff_transformation_rep_baseH3(){}

  virtual  PointH3<R>
           transform(const PointH3<R>&) const = 0;

  virtual  VectorH3<R>
           transform(const VectorH3<R>&) const = 0;

  virtual  DirectionH3<R>
           transform(const DirectionH3<R>&) const = 0;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  PlaneH3<R>
           transform(const PlaneH3<R>&) const = 0;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  virtual  Aff_transformationH3<R>
           inverse() const = 0;

  virtual  Aff_transformationH3<R>
           transpose() const = 0;

  virtual  Aff_transformation_repH3<R>
           general_form() const = 0;

  virtual  bool
           is_even() const = 0;

  virtual  RT
           homogeneous(int i, int j) const = 0;

  virtual  FT
           cartesian(int i, int j) const = 0;
};

template < class R_ >
class Aff_transformation_repH3 : public Aff_transformation_rep_baseH3<R_>
{
public:
  typedef R_                       R;
  typedef typename R::FT           FT;
  typedef typename R::RT           RT;

  Aff_transformation_repH3();
  Aff_transformation_repH3(
                 const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                 const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                 const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                              const RT& m33);
  virtual  ~Aff_transformation_repH3() {}

  virtual  PointH3<R>
           transform(const PointH3<R>& p) const;

  virtual  VectorH3<R>
           transform(const VectorH3<R>& v) const;

  virtual  DirectionH3<R>
           transform(const DirectionH3<R>& dir) const;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  PlaneH3<R>
           transform(const PlaneH3<R>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  virtual  Aff_transformationH3<R>
           inverse() const;

  virtual  Aff_transformation_repH3<R>
           general_form() const;

  virtual  Aff_transformationH3<R>
           transpose() const;

  virtual  bool
           is_even() const;

  virtual  RT
           homogeneous(int i, int j) const ;

  virtual  FT
           cartesian(int i, int j) const ;

friend class Aff_transformationH3<R>;

friend
Aff_transformationH3<R>
_general_transformation_composition CGAL_NULL_TMPL_ARGS (
                           Aff_transformation_repH3<R> l,
                           Aff_transformation_repH3<R> r);

friend
std::ostream &
operator<< CGAL_NULL_TMPL_ARGS (std::ostream & out,
                                const Aff_transformationH3<R>& t);

private:
    RT   t00, t01, t02, t03;
    RT   t10, t11, t12, t13;
    RT   t20, t21, t22, t23;
    RT                  t33;
};

template < class R_ >
class Identity_repH3 : public Aff_transformation_rep_baseH3<R_>
{
public:
  typedef R_                R;
  typedef typename R::RT    RT;
  typedef typename R::FT    FT;

           Identity_repH3()
           {}

  virtual  ~Identity_repH3()
           {}

  virtual  PointH3<R>
           transform(const PointH3<R>& p) const
           { return p; }

  virtual  VectorH3<R>
           transform(const VectorH3<R>& v) const
           { return v; }

  virtual  DirectionH3<R>
           transform(const DirectionH3<R>& dir) const
           { return dir; }

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  PlaneH3<R>
           transform(const PlaneH3<R>& pl) const
           { return pl; }
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  virtual  Aff_transformationH3<R>
           inverse() const
           { return Aff_transformationH3<R>( IDENTITY); }

  virtual  Aff_transformation_repH3<R>
           general_form() const;

  virtual  Aff_transformationH3<R>
           transpose() const
           { return Aff_transformationH3<R>( IDENTITY); }

  virtual  bool
           is_even() const
           { return true; }

  virtual  RT
           homogeneous(int i, int j) const
           { return (i==j) ? RT(1) : RT(0); }

  virtual  FT
           cartesian(int i, int j) const
           { return (i==j) ? FT(1) : FT(0); }
};


template < class R_ >
class Translation_repH3 : public Aff_transformation_rep_baseH3<R_>
{
public:
  typedef R_                   R;
  typedef typename R::FT       FT;
  typedef typename R::RT       RT;

           Translation_repH3();

           Translation_repH3( const VectorH3<R>& v);

  virtual  ~Translation_repH3() {}


  virtual  PointH3<R>
           transform(const PointH3<R>& p) const;

  virtual  VectorH3<R>
           transform(const VectorH3<R>& v) const;

  virtual  DirectionH3<R>
           transform(const DirectionH3<R>& dir) const;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  PlaneH3<R>
           transform(const PlaneH3<R>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  virtual  Aff_transformationH3<R>
           inverse() const;

  virtual  Aff_transformation_repH3<R>
           general_form() const;

  virtual  Aff_transformationH3<R>
           transpose() const;

  virtual  bool
           is_even() const;

  virtual  RT
           homogeneous(int i, int j) const ;

  virtual  FT
           cartesian(int i, int j) const ;

friend class Aff_transformationH3<R>;

private:
  VectorH3<R>  tv;
};


template < class R_ >
class Aff_transformationH3 : public Handle
{
public:
  typedef R_                R;
  typedef typename R::RT    RT;
  typedef typename R::FT    FT;

  Aff_transformationH3();

  Aff_transformationH3(const Aff_transformationH3<R>& tbc);

  // Identity
  Aff_transformationH3(const Identity_transformation&);

  // Translation
  Aff_transformationH3(const Translation& , const VectorH3<R>& v);

  //  Scaling
  Aff_transformationH3(const Scaling&, const RT& num, const RT& den);

  //  General form
  Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                  const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                  const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                               const RT& m33);
  Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02,
                  const RT& m10, const RT& m11, const RT& m12,
                  const RT& m20, const RT& m21, const RT& m22,
                                                               const RT& m33);

#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_1
  Aff_transformationH3(Aff_transformation_repH3<R>* ptr);
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

  ~Aff_transformationH3();


  PointH3<R>
  transform(const PointH3<R>& p) const;

  VectorH3<R>
  transform(const VectorH3<R>& v) const;

  DirectionH3<R>
  transform(const DirectionH3<R>& d) const;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  PlaneH3<R>
  transform(const PlaneH3<R>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  Aff_transformationH3<R>
  inverse()   const;

  Aff_transformationH3<R>
  transpose() const;

  bool
  is_even()   const;

  bool
  is_odd()    const;

  FT
  cartesian(int i, int j) const
  { return ptr()->cartesian(i,j); }

  RT
  homogeneous(int i, int j) const
  { return ptr()->homogeneous(i,j); }

  FT
  m(int i, int j) const
  { return ptr()->cartesian(i,j); }

  RT
  hm(int i, int j) const
  { return ptr()->homogeneous(i,j); }

// protected:
  Aff_transformation_rep_baseH3<R>*   ptr() const;
};

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformation_repH3<R>::Aff_transformation_repH3()
#ifdef INITIALIZE_AFF_TRANSFORMATIONS
  :  t00(RT(1)), t01(RT(0)), t02(RT(0)), t03(RT(0)),
     t10(RT(0)), t11(RT(1)), t12(RT(0)), t13(RT(0)),
     t20(RT(0)), t21(RT(0)), t22(RT(1)), t23(RT(0)),
                                         t33(RT(1))
#endif // INITIALIZE_AFF_TRANSFORMATIONS
{}

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformation_repH3<R>::Aff_transformation_repH3(
                   const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                   const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                   const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                                const RT& m33)
  :  t00(m00), t01(m01), t02(m02), t03(m03),
     t10(m10), t11(m11), t12(m12), t13(m13),
     t20(m20), t21(m21), t22(m22), t23(m23),
                                   t33(m33)
{}

template < class R >
CGAL_KERNEL_INLINE
PointH3<R>
Aff_transformation_repH3<R>::transform(const PointH3<R>& p) const
{
  return
  PointH3<R>(t00 * p.hx() + t01 * p.hy() + t02 * p.hz() + t03 * p.hw(),
                 t10 * p.hx() + t11 * p.hy() + t12 * p.hz() + t13 * p.hw(),
                 t20 * p.hx() + t21 * p.hy() + t22 * p.hz() + t23 * p.hw(),
                 t33 * p.hw());
}

template < class R >
CGAL_KERNEL_INLINE
VectorH3<R>
Aff_transformation_repH3<R>::transform(const VectorH3<R>& v) const
{
  return
  VectorH3<R>(t00 * v.hx() + t01 * v.hy() + t02 * v.hz(),
                  t10 * v.hx() + t11 * v.hy() + t12 * v.hz(),
                  t20 * v.hx() + t21 * v.hy() + t22 * v.hz(),
                  t33 * v.hw() );
}

template < class R >
CGAL_KERNEL_INLINE
DirectionH3<R>
Aff_transformation_repH3<R>::transform(const DirectionH3<R>& d) const
{
  VectorH3<R> v( d.to_vector() );
  return DirectionH3<R>(t00 * v.hx() + t01 * v.hy() + t02 * v.hz(),
                            t10 * v.hx() + t11 * v.hy() + t12 * v.hz(),
                            t20 * v.hx() + t21 * v.hy() + t22 * v.hz(),
                            t33 * v.hw() );

/*
  return DirectionH3<R>( t00 * d.hx() + t01 * d.hy() + t02 * d.hz(),
                             t10 * d.hx() + t11 * d.hy() + t12 * d.hz(),
                             t20 * d.hx() + t21 * d.hy() + t22 * d.hz() );
*/
}

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class R >
CGAL_KERNEL_INLINE
PlaneH3<R>
Aff_transformation_repH3<R>::transform(const PlaneH3<R>& pl) const
{
  if ( is_even() )
  {
      return
        PlaneH3<R>(
               transform(pl.point() ),
               transpose().inverse().transform(pl.orthogonal_direction() ));
  }
  else
  {
     return
       PlaneH3<R>(
               transform(pl.point() ),
               -(transpose().inverse().transform(pl.orthogonal_direction() )));
  }
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class R >
CGAL_KERNEL_INLINE
Aff_transformationH3<R>
Aff_transformation_repH3<R>::inverse() const
{
  typedef typename R::RT RT;
  const RT  RT0(0);
  return Aff_transformationH3<R>(
                           det3x3_by_formula( t11, t12, t13,
                                                   t21, t22, t23,     // i 00
                                                   RT0, RT0, t33 ),

                        -  det3x3_by_formula( t01, t02, t03,
                                                   t21, t22, t23,     // i 01
                                                   RT0, RT0, t33 ),

                           det3x3_by_formula( t01, t02, t03,
                                                   t11, t12, t13,     // i 02
                                                   RT0, RT0, t33 ),

                        -  det3x3_by_formula( t01, t02, t03,
                                                   t11, t12, t13,     // i 03
                                                   t21, t22, t23 ),


                        -  det3x3_by_formula( t10, t12, t13,
                                                   t20, t22, t23,     // i 10
                                                   RT0, RT0, t33 ),

                           det3x3_by_formula( t00, t02, t03,
                                                   t20, t22, t23,     // i 11
                                                   RT0, RT0, t33 ),

                        -  det3x3_by_formula( t00, t02, t03,
                                                   t10, t12, t13,     // i 12
                                                   RT0, RT0, t33 ),

                           det3x3_by_formula( t00, t02, t03,
                                                   t10, t12, t13,     // i 13
                                                   t20, t22, t23 ),


                           det3x3_by_formula( t10, t11, t13,
                                                   t20, t21, t23,     // i 20
                                                   RT0, RT0, t33 ),

                        -  det3x3_by_formula( t00, t01, t03,
                                                   t20, t21, t23,     // i 21
                                                   RT0, RT0, t33 ),

                           det3x3_by_formula( t00, t01, t03,
                                                   t10, t11, t13,     // i 22
                                                   RT0, RT0, t33 ),

                        -  det3x3_by_formula( t00, t01, t03,
                                                   t10, t11, t13,     // i 23
                                                   t20, t21, t23 ),


                           det3x3_by_formula( t00, t01, t02,
                                                   t10, t11, t12,     // i 33
                                                   t20, t21, t22 )
                                                       ) ;
}

template < class R >
inline
Aff_transformation_repH3<R>
Aff_transformation_repH3<R>::general_form() const
{ return *this; }

template < class R >
CGAL_KERNEL_INLINE
Aff_transformationH3<R>
Aff_transformation_repH3<R>::transpose() const
{
  typedef typename R::RT RT;
  const RT  RT0(0);
  return Aff_transformationH3<R>( t00,    t10,    t20,    RT0,
                                      t01,    t11,    t21,    RT0,
                                      t02,    t12,    t22,    RT0,
                                                              t33);
}

template < class R >
CGAL_KERNEL_INLINE
bool
Aff_transformation_repH3<R>::is_even() const
{
  return (CGAL_NTS sign( t33 * det3x3_by_formula(t00, t01, t02,
                                              t10, t11, t12,
                                              t20, t21, t22 ) ) == 1 );
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename R::RT
Aff_transformation_repH3<R>::
homogeneous(int i, int j) const
{
  typedef typename R::RT RT;
  CGAL_kernel_precondition( (i >= 0) && (i <= 3) && (j >= 0) && (j <= 3) );
  const RT  RT0(0);
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return t00;
              case 1: return t01;
              case 2: return t02;
              case 3: return t03;
            }
    case 1: switch (j)
            {
              case 0: return t10;
              case 1: return t11;
              case 2: return t12;
              case 3: return t13;
            }
    case 2: switch (j)
            {
              case 0: return t20;
              case 1: return t21;
              case 2: return t22;
              case 3: return t23;
            }
    case 3: switch (j)
            {
              case 0: return RT0;
              case 1: return RT0;
              case 2: return RT0;
              case 3: return t33;
            }
  }
  return RT0;
}

template < class R >
inline
typename R::FT
Aff_transformation_repH3<R>::
cartesian(int i, int j) const
{
  typedef typename R::FT FT;
  return  FT(homogeneous(i,j)) / FT(t33);
}

template <class R>
Aff_transformation_repH3<R>
Identity_repH3<R>::general_form() const
{
  typedef typename R::RT RT;
  const RT  RT0(0);
  const RT  RT1(1);
  return Aff_transformation_repH3<R>(RT1, RT0, RT0, RT0,
                                         RT0, RT1, RT0, RT0,
                                         RT0, RT0, RT1, RT0,
                                                        RT1 );
}

// not used (default ctor in Aff_transformationH3
// calls default ctor of Aff_transformation_repH3 )
template < class R >
inline
Translation_repH3<R>::Translation_repH3()
#ifdef INITIALIZE_AFF_TRANSFORMATIONS
  : tv( VectorH3<R>( RT(0), RT(0) ))
#endif // INITIALIZE_AFF_TRANSFORMATIONS
{}

template < class R >
inline
Translation_repH3<R>::Translation_repH3( const VectorH3<R>& v)
 : tv(v)
{}

template < class R >
CGAL_KERNEL_INLINE
PointH3<R>
Translation_repH3<R>::transform(const PointH3<R>& p) const
{
  return PointH3<R>( tv.hw() * p.hx() + tv.hx() * p.hw(),
                         tv.hw() * p.hy() + tv.hy() * p.hw(),
                         tv.hw() * p.hz() + tv.hz() * p.hw(),
                         tv.hw() * p.hw() );
}

template < class R >
inline
VectorH3<R>
Translation_repH3<R>::transform(const VectorH3<R>& v) const
{ return v; }

template < class R >
inline
DirectionH3<R>
Translation_repH3<R>::transform(const DirectionH3<R>& dir) const
{ return dir; }

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class R >
inline
PlaneH3<R>
Translation_repH3<R>::transform(const PlaneH3<R>& pl) const
{
  return PlaneH3<R>( transform( pl.point() ), pl.orthogonal_vector() );
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class R >
inline
Aff_transformationH3<R>
Translation_repH3<R>::inverse() const
{ return Aff_transformationH3<R>(TRANSLATION,  - tv ); }

template < class R >
CGAL_KERNEL_INLINE
Aff_transformation_repH3<R>
Translation_repH3<R>::general_form() const
{
  const RT  RT0(0);
  return Aff_transformation_repH3<R>(tv.hw(), RT0,  RT0,  tv.hx(),
                                         RT0,  tv.hw(), RT0,  tv.hy(),
                                         RT0,  RT0,  tv.hw(), tv.hz(),
                                                              tv.hw() );
}

template < class R >
CGAL_KERNEL_INLINE
Aff_transformationH3<R>
Translation_repH3<R>::transpose() const
{
  typedef typename R::RT RT;
  const RT  RT0(0);
  const RT  RT1(1);
  return Aff_transformationH3<R>( RT1,  RT0,  RT0,  RT0,
                                  RT0,  RT1,  RT0,  RT0,
                                  RT0,  RT0,  RT1,  RT0,
                                  RT1 );
}

template < class R >
inline
bool
Translation_repH3<R>::is_even() const
{ return true; }

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename R::RT
Translation_repH3<R>::homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 3) && (j >= 0) && (j <= 3) );
  const RT  RT0(0);
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return tv.hw();
              case 1: return RT0;
              case 2: return RT0;
              case 3: return tv.hx();
            }
    case 1: switch (j)
            {
              case 0: return RT0;
              case 1: return tv.hw();
              case 2: return RT0;
              case 3: return tv.hy();
            }
    case 2: switch (j)
            {
              case 0: return RT0;
              case 1: return RT0;
              case 2: return tv.hw();
              case 3: return tv.hz();
            }
    case 3: switch (j)
            {
              case 0: return RT0;
              case 1: return RT0;
              case 2: return RT0;
              case 3: return tv.hw();
            }
  }
  return RT0;
}

template < class R >
inline
typename R::FT
Translation_repH3<R>::
cartesian(int i, int j) const
{
  return FT(homogeneous(i,j)) / FT(tv.hw());
}


template < class R >
CGAL_KERNEL_INLINE
Aff_transformationH3<R>
_general_transformation_composition(
    Aff_transformation_repH3<R> l,
    Aff_transformation_repH3<R> r )
{
  return Aff_transformationH3<R>(
            l.t00*r.t00 + l.t01*r.t10 + l.t02*r.t20,
            l.t00*r.t01 + l.t01*r.t11 + l.t02*r.t21,
            l.t00*r.t02 + l.t01*r.t12 + l.t02*r.t22,
            l.t00*r.t03 + l.t01*r.t13 + l.t02*r.t23 + l.t03*r.t33,

            l.t10*r.t00 + l.t11*r.t10 + l.t12*r.t20,
            l.t10*r.t01 + l.t11*r.t11 + l.t12*r.t21,
            l.t10*r.t02 + l.t11*r.t12 + l.t12*r.t22,
            l.t10*r.t03 + l.t11*r.t13 + l.t12*r.t23 + l.t13*r.t33,

            l.t20*r.t00 + l.t21*r.t10 + l.t22*r.t20,
            l.t20*r.t01 + l.t21*r.t11 + l.t22*r.t21,
            l.t20*r.t02 + l.t21*r.t12 + l.t22*r.t22,
            l.t20*r.t03 + l.t21*r.t13 + l.t22*r.t23 + l.t23*r.t33,

            l.t33*r.t33 );
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::Aff_transformationH3()
{ PTR = new Aff_transformation_repH3<R>(); }

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::
Aff_transformationH3( const Aff_transformationH3<R>& tbc)
 : Handle(tbc)
{}

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::
Aff_transformationH3(const Identity_transformation&)
{ PTR = new Identity_repH3<R>(); }

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::
Aff_transformationH3(const Translation&, const VectorH3<R>& v)
{ PTR = new Translation_repH3<R>( v ); }

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::
Aff_transformationH3(const Scaling&, const RT& num, const RT& den)
{
  const RT RT0(0);
  PTR = new Aff_transformation_repH3<R>(num, RT0, RT0, RT0,
                                            RT0, num, RT0, RT0,
                                            RT0, RT0, num, RT0,
                                                           den );
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::
Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                  const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                  const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                               const RT& m33)
{
  PTR = new Aff_transformation_repH3<R>(m00, m01, m02, m03,
                                            m10, m11, m12, m13,
                                            m20, m21, m22, m23,
                                                           m33 );
}

template < class R >
CGAL_KERNEL_CTOR_INLINE
Aff_transformationH3<R>::
Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02,
                  const RT& m10, const RT& m11, const RT& m12,
                  const RT& m20, const RT& m21, const RT& m22,
                                                               const RT& m33)
{
  const RT RT0 = RT(0);
  PTR = new Aff_transformation_repH3<R>(m00, m01, m02, RT0,
                                            m10, m11, m12, RT0,
                                            m20, m21, m22, RT0,
                                                           m33 );
}

template < class R >
inline
Aff_transformation_rep_baseH3<R>*
Aff_transformationH3<R>::ptr() const
// static_cast
{ return (Aff_transformation_rep_baseH3<R>*) PTR; }

template < class R >
inline
Aff_transformationH3<R>::~Aff_transformationH3()
{}

template < class R >
inline
PointH3<R>
Aff_transformationH3<R>::transform(const PointH3<R>& p) const
{ return ptr()->transform(p); }

template < class R >
inline
VectorH3<R>
Aff_transformationH3<R>::transform(const VectorH3<R>& v) const
{ return ptr()->transform(v); }

template < class R >
inline
DirectionH3<R>
Aff_transformationH3<R>::
transform(const DirectionH3<R>& d) const
{ return ptr()->transform(d); }

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class R >
inline
PlaneH3<R>
Aff_transformationH3<R>::
transform(const PlaneH3<R>& pl) const
{ return ptr()->transform(pl); }
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class R >
inline
Aff_transformationH3<R>
Aff_transformationH3<R>::inverse() const
{ return ptr()->inverse(); }

template < class R >
inline
Aff_transformationH3<R>
Aff_transformationH3<R>::transpose() const
{ return ptr()->transpose(); }

template < class R >
inline
bool
Aff_transformationH3<R>::is_even() const
{ return ptr()->is_even(); }

template < class R >
inline
bool
Aff_transformationH3<R>::is_odd() const
{ return ( ! (ptr()->is_even() )); }

template < class R >
CGAL_KERNEL_INLINE
Aff_transformationH3<R>
operator*(const Aff_transformationH3<R>& left_argument,
          const Aff_transformationH3<R>& right_argument )
{
 return _general_transformation_composition(
              left_argument.ptr() ->general_form(),
              right_argument.ptr()->general_form() );
}

template < class R >
std::ostream &
operator<< ( std::ostream & out,
             const Aff_transformationH3<R>& t)
{
 typename R::RT RT0(0);
 Aff_transformation_repH3<R> r = t.ptr()->general_form();
 return  out
 << "| "<< r.t00 <<' '<< r.t01 <<' '<< r.t02 <<' '<< r.t03 << " |\n"
 << "| "<< r.t10 <<' '<< r.t11 <<' '<< r.t12 <<' '<< r.t13 << " |\n"
 << "| "<< r.t20 <<' '<< r.t21 <<' '<< r.t22 <<' '<< r.t23 << " |\n"
 << "| "<< RT0   <<' '<< RT0   <<' '<< RT0   <<' '<< r.t33 << " |\n";
}

CGAL_END_NAMESPACE

#endif // CGAL_AFF_TRANSFORMATIONH3_H
