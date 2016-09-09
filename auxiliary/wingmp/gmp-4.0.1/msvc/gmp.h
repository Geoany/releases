/* Definitions for GNU multiple precision functions.   -*- mode: c -*-

Copyright 1991, 1993, 1994, 1995, 1996, 1997, 1999, 2000, 2001
Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#ifndef __GMP_H__


/* Instantiated by configure, for internal use only. */
#if ! __GMP_WITHIN_CONFIGURE
#define __GMP_BITS_PER_MP_LIMB             32
#define __GMP_HAVE_HOST_CPU_FAMILY_power   0
#define __GMP_HAVE_HOST_CPU_FAMILY_powerpc 0
#endif


/* The following (everything under ifndef __GNU_MP__) must be identical in
   gmp.h and mp.h to allow both to be included in an application or during
   the library build.  */
#ifndef __GNU_MP__
#define __GNU_MP__ 4

#define __need_size_t
#include <stddef.h>
#undef __need_size_t

/* Instantiated by configure, for internal use only */
#if ! __GMP_WITHIN_CONFIGURE
/* #undef _LONG_LONG_LIMB */

/* Whether static, shared or both has been built. */
#define __GMP_LIBGMP_STATIC  0
#define __GMP_LIBGMP_SHARED  1
#endif


/* __STDC__ - some ANSI compilers define this only to 0, hence the use of
       "defined" and not "__STDC__-0".  In particular Sun workshop C 5.0
       sets __STDC__ to 0, but requires "##" for token pasting.

   _AIX - gnu ansidecl.h asserts that all known AIX compilers are ANSI but
       don't always define __STDC__.

   _mips - gnu ansidecl.h says the RISC/OS MIPS compiler is ANSI in SVR4
       mode, but doesn't define __STDC__.

   _MSC_VER - Microsoft C is ANSI, but __STDC__ is undefined unless the /Za
       option is given (in which case it's 1).

   _WIN32 - tested for by gnu ansidecl.h, no doubt on the assumption that
      all w32 compilers are ansi.  */

#if  defined (__STDC__)                                 \
  || defined (__cplusplus)                              \
  || defined (_AIX)                                     \
  || defined (__DECC)                                   \
  || (defined (__mips) && defined (_SYSTYPE_SVR4))      \
  || defined (_MSC_VER)                                 \
  || defined (_WIN32)
#define __GMP_HAVE_CONST        1
#define __GMP_HAVE_PROTOTYPES   1
#define __GMP_HAVE_TOKEN_PASTE  1
#else
#define __GMP_HAVE_CONST        0
#define __GMP_HAVE_PROTOTYPES   0
#define __GMP_HAVE_TOKEN_PASTE  0
#endif


#if __GMP_HAVE_CONST
#define __gmp_const   const
#define __gmp_signed  signed
#else
#define __gmp_const
#define __gmp_signed
#endif


/* __GMP_DECLSPEC marks a function or variable for import or export for a
   windows DLL, or is empty on other systems.

   When building GMP, libtool gives us DLL_EXPORT when making objects that
   will go into a DLL and hence should have export directives.  Notice
   DLL_EXPORT is only tested under __GMP_WITHIN_GMP, since if some other
   libtool based package is using gmp.h then DLL_EXPORT will be telling it
   what to do, not us.

   When compiling an application, __GMP_LIBGMP_SHARED indicates whether the
   installed GMP is a DLL or not.  For a DLL we use import directives.

   There's no attempt here to support GMP installed both static and DLL,
   doing so would mean applications would have to tell us which of the two
   is going to be used, and that seems very tedious and error prone when
   using GMP by hand, and equally tedious from a package since autoconf and
   automake don't give much help.

   Note that __GMP_DECLSPEC is only wanted on documented global functions
   and variables.  Internals in gmp-impl.h etc should be left unadorned and
   won't be visible to applications using a DLL.

   For testing on a non-windows system, __GMP_DECLSPEC can be set to
   __attribute__ ((section ("foo"))) or similar, and the resulting objects
   checked with readelf or whatever to see if all the expected globals have
   ended up with that attribute.

   PORTME: What does Borland use? */

#if defined (__GNUC__) || defined (_MSC_VER) || defined(__BORLANDC__)
#define __GMP_DECLSPEC_EXPORT  __declspec(dllexport)
#define __GMP_DECLSPEC_IMPORT  __declspec(dllimport)
#endif
#ifdef __WATCOMC__
#define __GMP_DECLSPEC_EXPORT  __export
#define __GMP_DECLSPEC_IMPORT  __import
#endif
#ifdef __IBMC__
#define __GMP_DECLSPEC_EXPORT  _Export
#define __GMP_DECLSPEC_IMPORT  _Import
#endif

#if __GMP_WITHIN_GMP
#ifdef DLL_EXPORT
#define __GMP_DECLSPEC  __GMP_DECLSPEC_EXPORT
#endif
#else
#if defined (_WIN32) && __GMP_LIBGMP_SHARED
#define __GMP_DECLSPEC  __GMP_DECLSPEC_IMPORT
#endif
#endif

#ifndef __GMP_DECLSPEC
#define __GMP_DECLSPEC
#endif


#ifdef _SHORT_LIMB
typedef unsigned int		mp_limb_t;
typedef int			mp_limb_signed_t;
#else
#ifdef _LONG_LONG_LIMB
typedef unsigned long long int	mp_limb_t;
typedef long long int		mp_limb_signed_t;
#else
typedef unsigned long int	mp_limb_t;
typedef long int		mp_limb_signed_t;
#endif
#endif

typedef mp_limb_t *		mp_ptr;
typedef __gmp_const mp_limb_t *	mp_srcptr;
#if defined (_CRAY) && ! defined (_CRAYMPP)
/* plain `int' is much faster (48 bits) */
#define __GMP_MP_SIZE_T_INT     1
typedef int			mp_size_t;
typedef int			mp_exp_t;
#else
#define __GMP_MP_SIZE_T_INT     0
typedef long int		mp_size_t;
typedef long int		mp_exp_t;
#endif

typedef struct
{
  int _mp_alloc;		/* Number of *limbs* allocated and pointed
				   to by the _mp_d field.  */
  int _mp_size;			/* abs(_mp_size) is the number of limbs the
				   last field points to.  If _mp_size is
				   negative this is a negative number.  */
  mp_limb_t *_mp_d;		/* Pointer to the limbs.  */
} __mpz_struct;
#endif /* __GNU_MP__ */

typedef __mpz_struct MP_INT;
typedef __mpz_struct mpz_t[1];

typedef struct
{
  __mpz_struct _mp_num;
  __mpz_struct _mp_den;
} __mpq_struct;

typedef __mpq_struct MP_RAT;
typedef __mpq_struct mpq_t[1];

typedef struct
{
  int _mp_prec;			/* Max precision, in number of `mp_limb_t's.
				   Set by mpf_init and modified by
				   mpf_set_prec.  The area pointed to by the
				   _mp_d field contains `prec' + 1 limbs.  */
  int _mp_size;			/* abs(_mp_size) is the number of limbs the
				   last field points to.  If _mp_size is
				   negative this is a negative number.  */
  mp_exp_t _mp_exp;		/* Exponent, in the base of `mp_limb_t'.  */
  mp_limb_t *_mp_d;		/* Pointer to the limbs.  */
} __mpf_struct;

/* typedef __mpf_struct MP_FLOAT; */
typedef __mpf_struct mpf_t[1];

/* Available random number generation algorithms.  */
typedef enum
{
  GMP_RAND_ALG_DEFAULT = 0,
  GMP_RAND_ALG_LC = GMP_RAND_ALG_DEFAULT /* Linear congruential.  */
} gmp_randalg_t;

/* Linear congruential data struct.  */
typedef struct {
  mpz_t _mp_a;			/* Multiplier. */
  unsigned long int _mp_c;	/* Adder. */
  mpz_t _mp_m;			/* Modulus (valid only if m2exp == 0).  */
  unsigned long int _mp_m2exp;	/* If != 0, modulus is 2 ^ m2exp.  */
} __gmp_randata_lc;

/* Random state struct.  */
typedef struct
{
  mpz_t _mp_seed;		/* Current seed.  */
  gmp_randalg_t _mp_alg;	/* Algorithm used.  */
  union {			/* Algorithm specific data.  */
    __gmp_randata_lc *_mp_lc;	/* Linear congruential.  */
  } _mp_algdata;
} __gmp_randstate_struct;
typedef __gmp_randstate_struct gmp_randstate_t[1];

/* Types for function declarations in gmp files.  */
/* ??? Should not pollute user name space with these ??? */
typedef __gmp_const __mpz_struct *mpz_srcptr;
typedef __mpz_struct *mpz_ptr;
typedef __gmp_const __mpf_struct *mpf_srcptr;
typedef __mpf_struct *mpf_ptr;
typedef __gmp_const __mpq_struct *mpq_srcptr;
typedef __mpq_struct *mpq_ptr;

#ifndef _PROTO
#if __GMP_HAVE_PROTOTYPES
#define _PROTO(x) x
#else
#define _PROTO(x) ()
#endif
#endif

#ifndef __MPN
#if __GMP_HAVE_TOKEN_PASTE
#define __MPN(x) __gmpn_##x
#else
#define __MPN(x) __gmpn_/**/x
#endif
#endif

#if defined (FILE)                                              \
  || defined (H_STDIO)                                          \
  || defined (_H_STDIO)               /* AIX */                 \
  || defined (_STDIO_H)               /* glibc, Sun, SCO */     \
  || defined (_STDIO_H_)              /* BSD, OSF */            \
  || defined (__STDIO_H__)            /* IRIX */                \
  || defined (_STDIO_INCLUDED)        /* HPUX */                \
  || defined (__dj_include_stdio_h_)  /* DJGPP */               \
  || defined (_FILE_DEFINED)          /* Microsoft */          \
  || defined (__STDIO__)              /* Apple MPW MrC */
#define _GMP_H_HAVE_FILE 1
#endif

/* In ISO C, if a prototype involving "struct obstack *" is given without
   that structure defined, then the struct is scoped down to just the
   prototype, causing a conflict if it's subsequently defined for real.  So
   only give prototypes if we've got obstack.h.  */
#if defined (_OBSTACK_H)   /* glibc <obstack.h> */
#define _GMP_H_HAVE_OBSTACK 1
#endif

/* The prototypes for gmp_vprintf etc are provided only if va_list is
   available, via an application having included <stdarg.h> or <varargs.h>.
   Usually va_list is a typedef so can't be tested directly, but va_start is
   almost certainly a macro, so look for that.

   <stdio.h> will define some sort of va_list for vprintf and vfprintf, but
   let's not bother trying to use that since it's not standard and since
   application uses for gmp_vprintf etc will almost certainly require the
   whole <stdarg.h> or <varargs.h> anyway.  */

#ifdef va_start
#define _GMP_H_HAVE_VA_LIST 1
#endif

/* Test for gcc >= maj.min, as per __GNUC_PREREQ in glibc */
#if defined (__GNUC__) && defined (__GNUC_MINOR__)
#define __GMP_GNUC_PREREQ(maj, min) \
  ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define __GMP_GNUC_PREREQ(maj, min)  0
#endif

/* "pure" is in gcc 2.96 and up, see "(gcc)Function Attributes".  Basically
   it means a function does nothing but examine its arguments and memory
   (global or via arguments) to generate a return value, but changes nothing
   and has no side-effects. */
#if __GMP_GNUC_PREREQ (2,96)
#define __GMP_ATTRIBUTE_PURE   __attribute__ ((__pure__))
#else
#define __GMP_ATTRIBUTE_PURE
#endif


/* PORTME: What other compilers have a useful "extern inline"?  "static
   inline" would be an acceptable substitute if the compiler (or linker)
   discards unused statics.  */

/* gcc has __inline__ in all modes, including strict ansi.  Give a prototype
   for an inline too, so as to correctly specify "dllimport" on windows, in
   case the function is called rather than inlined.  */
#ifdef __GNUC__
#define __GMP_EXTERN_INLINE      extern __inline__
#define __GMP_INLINE_PROTOTYPES  1
#endif

/* SCO OpenUNIX 8 cc supports "static inline foo()" but not in -Xc strict
   ANSI mode (__STDC__ is 1 in that mode).  Inlining only actually takes
   place under -O.  Without -O "foo" seems to be emitted whether it's used
   or not, which is wasteful.  "extern inline foo()" isn't useful, the
   "extern" is apparently ignored, so foo is inlined if possible but also
   emitted as a global, which causes multiple definition errors when
   building a shared libgmp.  */
#if __SCO_VERSION__ > 400000000 && __STDC__ != 1 \
  && ! defined (__GMP_EXTERN_INLINE)
#define __GMP_EXTERN_INLINE  static inline
#endif

/* C++ always has "inline" and since it's a normal feature the linker should
   discard duplicate non-inlined copies, or if it doesn't then that's a
   problem for everyone, not just GMP.  */
#if defined (__cplusplus) && ! defined (__GMP_EXTERN_INLINE)
#ifdef _MSC_VER
#define __GMP_EXTERN_INLINE  static inline
#else
#define __GMP_EXTERN_INLINE  inline
#endif
#endif

/* By default, don't give a prototype when there's going to be an inline
   version.  Note in particular that Cray C++ objects to the combination of
   prototype and inline.  */
#ifdef __GMP_EXTERN_INLINE
#ifndef __GMP_INLINE_PROTOTYPES
#define __GMP_INLINE_PROTOTYPES  0
#endif
#else
#define __GMP_INLINE_PROTOTYPES  1
#endif


#define __GMP_ABS(x)   ((x) >= 0 ? (x) : -(x))
#define __GMP_MAX(h,i) ((h) > (i) ? (h) : (i))

#define __GMP_UINT_MAX   (~ (unsigned) 0)
#define __GMP_ULONG_MAX  (~ (unsigned long) 0)
#define __GMP_USHRT_MAX  ((unsigned short) ~0)


/* Allow direct user access to numerator and denominator of a mpq_t object.  */
#define mpq_numref(Q) (&((Q)->_mp_num))
#define mpq_denref(Q) (&((Q)->_mp_den))


#if defined (__cplusplus)
extern "C" {
#endif

#define mp_set_memory_functions __gmp_set_memory_functions
void __GMP_DECLSPEC mp_set_memory_functions _PROTO ((void *(*) (size_t),
				      void *(*) (void *, size_t, size_t),
				      void (*) (void *, size_t)));

#define mp_bits_per_limb __gmp_bits_per_limb
extern __gmp_const int __GMP_DECLSPEC mp_bits_per_limb;

/* the following for internal use only */
__GMP_DECLSPEC extern void * (* __gmp_allocate_func) _PROTO ((size_t));
__GMP_DECLSPEC extern void * (* __gmp_reallocate_func) _PROTO ((void *, size_t, size_t));
__GMP_DECLSPEC extern void   (* __gmp_free_func) _PROTO ((void *, size_t));


/**************** Random number routines.  ****************/

/* obsolete */
#define gmp_randinit __gmp_randinit
void __GMP_DECLSPEC gmp_randinit _PROTO ((gmp_randstate_t, gmp_randalg_t, ...));

#define gmp_randinit_default __gmp_randinit_default
void __GMP_DECLSPEC gmp_randinit_default _PROTO ((gmp_randstate_t));

#define gmp_randinit_lc __gmp_randinit_lc
void __GMP_DECLSPEC gmp_randinit_lc _PROTO ((gmp_randstate_t,
                              mpz_srcptr, unsigned long int, mpz_srcptr));

#define gmp_randinit_lc_2exp __gmp_randinit_lc_2exp
void __GMP_DECLSPEC gmp_randinit_lc_2exp _PROTO ((gmp_randstate_t,
                                   mpz_srcptr, unsigned long int,
				   unsigned long int));

#define gmp_randinit_lc_2exp_size __gmp_randinit_lc_2exp_size
int __GMP_DECLSPEC gmp_randinit_lc_2exp_size _PROTO ((gmp_randstate_t, unsigned long));

#define gmp_randseed __gmp_randseed
void __GMP_DECLSPEC gmp_randseed _PROTO ((gmp_randstate_t, mpz_srcptr));

#define gmp_randseed_ui __gmp_randseed_ui
void __GMP_DECLSPEC gmp_randseed_ui _PROTO ((gmp_randstate_t, unsigned long int));

#define gmp_randclear __gmp_randclear
void __GMP_DECLSPEC gmp_randclear _PROTO ((gmp_randstate_t));


/**************** Formatted output routines.  ****************/

#define gmp_asprintf __gmp_asprintf
int __GMP_DECLSPEC gmp_asprintf _PROTO ((char **, const char *, ...));

#define gmp_fprintf __gmp_fprintf
#if _GMP_H_HAVE_FILE
int __GMP_DECLSPEC gmp_fprintf _PROTO ((FILE *, const char *, ...));
#endif

#define gmp_obstack_printf __gmp_obstack_printf
#if _GMP_H_HAVE_OBSTACK
int __GMP_DECLSPEC gmp_obstack_printf _PROTO ((struct obstack *, const char *, ...));
#endif

#define gmp_obstack_vprintf __gmp_obstack_vprintf
#if _GMP_H_HAVE_OBSTACK && _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_obstack_vprintf _PROTO ((struct obstack *, const char *, va_list));
#endif

#define gmp_printf __gmp_printf
int __GMP_DECLSPEC gmp_printf _PROTO ((const char *, ...));

#define gmp_snprintf __gmp_snprintf
int __GMP_DECLSPEC gmp_snprintf _PROTO ((char *, size_t, const char *, ...));

#define gmp_sprintf __gmp_sprintf
int __GMP_DECLSPEC gmp_sprintf _PROTO ((char *, const char *, ...));

#define gmp_vasprintf __gmp_vasprintf
#if _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vasprintf _PROTO ((char **, const char *, va_list));
#endif

#define gmp_vfprintf __gmp_vfprintf
#if _GMP_H_HAVE_FILE && _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vfprintf _PROTO ((FILE *, const char *, va_list));
#endif

#define gmp_vprintf __gmp_vprintf
#if _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vprintf _PROTO ((const char *, va_list));
#endif

#define gmp_vsnprintf __gmp_vsnprintf
#if _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vsnprintf _PROTO ((char *, size_t, const char *, va_list));
#endif

#define gmp_vsprintf __gmp_vsprintf
#if _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vsprintf _PROTO ((char *, const char *, va_list));
#endif


/**************** Formatted input routines.  ****************/

#define gmp_fscanf __gmp_fscanf
#if _GMP_H_HAVE_FILE
int __GMP_DECLSPEC gmp_fscanf _PROTO ((FILE *, const char *, ...));
#endif

#define gmp_scanf __gmp_scanf
int __GMP_DECLSPEC gmp_scanf _PROTO ((const char *, ...));

#define gmp_sscanf __gmp_sscanf
int __GMP_DECLSPEC gmp_sscanf _PROTO ((const char *, const char *, ...));

#define gmp_vfscanf __gmp_vfscanf
#if _GMP_H_HAVE_FILE && _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vfscanf _PROTO ((FILE *, const char *, va_list));
#endif

#define gmp_vscanf __gmp_vscanf
#if _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vscanf _PROTO ((const char *, va_list));
#endif

#define gmp_vsscanf __gmp_vsscanf
#if _GMP_H_HAVE_VA_LIST
int __GMP_DECLSPEC gmp_vsscanf _PROTO ((const char *, const char *, va_list));
#endif


/**************** Integer (i.e. Z) routines.  ****************/

#define _mpz_realloc __gmpz_realloc
#define mpz_realloc __gmpz_realloc
__GMP_DECLSPEC void * _mpz_realloc _PROTO ((mpz_ptr, mp_size_t));

#define mpz_abs __gmpz_abs
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_abs
void __GMP_DECLSPEC mpz_abs _PROTO ((mpz_ptr, mpz_srcptr));
#endif

#define mpz_add __gmpz_add
void __GMP_DECLSPEC mpz_add _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_add_ui __gmpz_add_ui
void __GMP_DECLSPEC mpz_add_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_addmul __gmpz_addmul
void __GMP_DECLSPEC mpz_addmul _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_addmul_ui __gmpz_addmul_ui
void __GMP_DECLSPEC mpz_addmul_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_and __gmpz_and
void __GMP_DECLSPEC mpz_and _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_array_init __gmpz_array_init
void __GMP_DECLSPEC mpz_array_init _PROTO ((mpz_ptr, mp_size_t, mp_size_t));

#define mpz_bin_ui __gmpz_bin_ui
void __GMP_DECLSPEC mpz_bin_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_bin_uiui __gmpz_bin_uiui
void __GMP_DECLSPEC mpz_bin_uiui _PROTO ((mpz_ptr, unsigned long int, unsigned long int));

#define mpz_cdiv_q __gmpz_cdiv_q
void __GMP_DECLSPEC mpz_cdiv_q _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_cdiv_q_2exp __gmpz_cdiv_q_2exp
void __GMP_DECLSPEC mpz_cdiv_q_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long));

#define mpz_cdiv_q_ui __gmpz_cdiv_q_ui
unsigned long int __GMP_DECLSPEC mpz_cdiv_q_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_cdiv_qr __gmpz_cdiv_qr
void __GMP_DECLSPEC mpz_cdiv_qr _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_cdiv_qr_ui __gmpz_cdiv_qr_ui
unsigned long int __GMP_DECLSPEC mpz_cdiv_qr_ui _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_cdiv_r __gmpz_cdiv_r
void __GMP_DECLSPEC mpz_cdiv_r _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_cdiv_r_2exp __gmpz_cdiv_r_2exp
void __GMP_DECLSPEC mpz_cdiv_r_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long));

#define mpz_cdiv_r_ui __gmpz_cdiv_r_ui
unsigned long int __GMP_DECLSPEC mpz_cdiv_r_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_cdiv_ui __gmpz_cdiv_ui
unsigned long int __GMP_DECLSPEC mpz_cdiv_ui _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_clear __gmpz_clear
void __GMP_DECLSPEC mpz_clear _PROTO ((mpz_ptr));

#define mpz_clrbit __gmpz_clrbit
void __GMP_DECLSPEC mpz_clrbit _PROTO ((mpz_ptr, unsigned long int));

#define mpz_cmp __gmpz_cmp
int __GMP_DECLSPEC mpz_cmp _PROTO ((mpz_srcptr, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_cmp_d __gmpz_cmp_d
int __GMP_DECLSPEC mpz_cmp_d _PROTO ((mpz_srcptr, double)) __GMP_ATTRIBUTE_PURE;

#define _mpz_cmp_si __gmpz_cmp_si
int __GMP_DECLSPEC _mpz_cmp_si _PROTO ((mpz_srcptr, signed long int)) __GMP_ATTRIBUTE_PURE;

#define _mpz_cmp_ui __gmpz_cmp_ui
int __GMP_DECLSPEC _mpz_cmp_ui _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_cmpabs __gmpz_cmpabs
int __GMP_DECLSPEC mpz_cmpabs _PROTO ((mpz_srcptr, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_cmpabs_d __gmpz_cmpabs_d
int __GMP_DECLSPEC mpz_cmpabs_d _PROTO ((mpz_srcptr, double)) __GMP_ATTRIBUTE_PURE;

#define mpz_cmpabs_ui __gmpz_cmpabs_ui
int __GMP_DECLSPEC mpz_cmpabs_ui _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_com __gmpz_com
void __GMP_DECLSPEC mpz_com _PROTO ((mpz_ptr, mpz_srcptr));

#define mpz_congruent_p __gmpz_congruent_p
int __GMP_DECLSPEC mpz_congruent_p _PROTO ((mpz_srcptr, mpz_srcptr, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_congruent_2exp_p __gmpz_congruent_2exp_p
int __GMP_DECLSPEC mpz_congruent_2exp_p _PROTO ((mpz_srcptr, mpz_srcptr, unsigned long)) __GMP_ATTRIBUTE_PURE;

#define mpz_congruent_ui_p __gmpz_congruent_ui_p
int __GMP_DECLSPEC mpz_congruent_ui_p _PROTO ((mpz_srcptr, unsigned long, unsigned long)) __GMP_ATTRIBUTE_PURE;

#define mpz_divexact __gmpz_divexact
void __GMP_DECLSPEC mpz_divexact _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_divexact_ui __gmpz_divexact_ui
void __GMP_DECLSPEC mpz_divexact_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long));

#define mpz_divisible_p __gmpz_divisible_p
int __GMP_DECLSPEC mpz_divisible_p _PROTO ((mpz_srcptr, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_divisible_ui_p __gmpz_divisible_ui_p
int __GMP_DECLSPEC mpz_divisible_ui_p _PROTO ((mpz_srcptr, unsigned long)) __GMP_ATTRIBUTE_PURE;

#define mpz_divisible_2exp_p __gmpz_divisible_2exp_p
int __GMP_DECLSPEC mpz_divisible_2exp_p _PROTO ((mpz_srcptr, unsigned long)) __GMP_ATTRIBUTE_PURE;

#define mpz_dump __gmpz_dump
void __GMP_DECLSPEC mpz_dump _PROTO ((mpz_srcptr));

#define mpz_fac_ui __gmpz_fac_ui
void __GMP_DECLSPEC mpz_fac_ui _PROTO ((mpz_ptr, unsigned long int));

#define mpz_fdiv_q __gmpz_fdiv_q
void __GMP_DECLSPEC mpz_fdiv_q _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_fdiv_q_2exp __gmpz_fdiv_q_2exp
void __GMP_DECLSPEC mpz_fdiv_q_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_fdiv_q_ui __gmpz_fdiv_q_ui
unsigned long int __GMP_DECLSPEC mpz_fdiv_q_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_fdiv_qr __gmpz_fdiv_qr
void __GMP_DECLSPEC mpz_fdiv_qr _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_fdiv_qr_ui __gmpz_fdiv_qr_ui
unsigned long int __GMP_DECLSPEC mpz_fdiv_qr_ui _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_fdiv_r __gmpz_fdiv_r
void __GMP_DECLSPEC mpz_fdiv_r _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_fdiv_r_2exp __gmpz_fdiv_r_2exp
void __GMP_DECLSPEC mpz_fdiv_r_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_fdiv_r_ui __gmpz_fdiv_r_ui
unsigned long int __GMP_DECLSPEC mpz_fdiv_r_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_fdiv_ui __gmpz_fdiv_ui
unsigned long int __GMP_DECLSPEC mpz_fdiv_ui _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_fib_ui __gmpz_fib_ui
void __GMP_DECLSPEC mpz_fib_ui _PROTO ((mpz_ptr, unsigned long int));

#define mpz_fib2_ui __gmpz_fib2_ui
void __GMP_DECLSPEC mpz_fib2_ui _PROTO ((mpz_ptr, mpz_ptr, unsigned long int));

#define mpz_fits_sint_p __gmpz_fits_sint_p
int __GMP_DECLSPEC mpz_fits_sint_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_fits_slong_p __gmpz_fits_slong_p
int __GMP_DECLSPEC mpz_fits_slong_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_fits_sshort_p __gmpz_fits_sshort_p
int __GMP_DECLSPEC mpz_fits_sshort_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_fits_uint_p __gmpz_fits_uint_p
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_fits_uint_p
int __GMP_DECLSPEC mpz_fits_uint_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_fits_ulong_p __gmpz_fits_ulong_p
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_fits_ulong_p
int __GMP_DECLSPEC mpz_fits_ulong_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_fits_ushort_p __gmpz_fits_ushort_p
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_fits_ushort_p
int __GMP_DECLSPEC mpz_fits_ushort_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_gcd __gmpz_gcd
void __GMP_DECLSPEC mpz_gcd _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_gcd_ui __gmpz_gcd_ui
unsigned long int __GMP_DECLSPEC mpz_gcd_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_gcdext __gmpz_gcdext
void __GMP_DECLSPEC mpz_gcdext _PROTO ((mpz_ptr, mpz_ptr, mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_get_d __gmpz_get_d
double __GMP_DECLSPEC mpz_get_d _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_get_d_2exp __gmpz_get_d_2exp
double __GMP_DECLSPEC mpz_get_d_2exp _PROTO ((signed long int *, mpz_srcptr));

#define mpz_get_si __gmpz_get_si
/* signed */ long int __GMP_DECLSPEC mpz_get_si _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_get_str __gmpz_get_str
__GMP_DECLSPEC char * mpz_get_str _PROTO ((char *, int, mpz_srcptr));

#define mpz_get_ui __gmpz_get_ui
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_get_ui
unsigned long int __GMP_DECLSPEC mpz_get_ui _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_getlimbn __gmpz_getlimbn
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_getlimbn
mp_limb_t __GMP_DECLSPEC mpz_getlimbn _PROTO ((mpz_srcptr, mp_size_t)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_hamdist __gmpz_hamdist
unsigned long int __GMP_DECLSPEC mpz_hamdist _PROTO ((mpz_srcptr, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_init __gmpz_init
void __GMP_DECLSPEC mpz_init _PROTO ((mpz_ptr));

#define mpz_init2 __gmpz_init2
void __GMP_DECLSPEC mpz_init2 _PROTO ((mpz_ptr, unsigned long));

#define mpz_init_set __gmpz_init_set
void __GMP_DECLSPEC mpz_init_set _PROTO ((mpz_ptr, mpz_srcptr));

#define mpz_init_set_d __gmpz_init_set_d
void __GMP_DECLSPEC mpz_init_set_d _PROTO ((mpz_ptr, double));

#define mpz_init_set_si __gmpz_init_set_si
void __GMP_DECLSPEC mpz_init_set_si _PROTO ((mpz_ptr, signed long int));

#define mpz_init_set_str __gmpz_init_set_str
int  __GMP_DECLSPEC mpz_init_set_str _PROTO ((mpz_ptr, __gmp_const char *, int));

#define mpz_init_set_ui __gmpz_init_set_ui
void __GMP_DECLSPEC mpz_init_set_ui _PROTO ((mpz_ptr, unsigned long int));

#define mpz_inp_raw __gmpz_inp_raw
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpz_inp_raw _PROTO ((mpz_ptr, FILE *));
#endif

#define mpz_inp_str __gmpz_inp_str
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpz_inp_str _PROTO ((mpz_ptr, FILE *, int));
#endif

#define mpz_invert __gmpz_invert
int  __GMP_DECLSPEC mpz_invert _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_ior __gmpz_ior
void __GMP_DECLSPEC mpz_ior _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_jacobi __gmpz_jacobi
int  __GMP_DECLSPEC mpz_jacobi _PROTO ((mpz_srcptr, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_kronecker mpz_jacobi  /* alias */

#define mpz_kronecker_si __gmpz_kronecker_si
int __GMP_DECLSPEC mpz_kronecker_si _PROTO ((mpz_srcptr, long)) __GMP_ATTRIBUTE_PURE;

#define mpz_kronecker_ui __gmpz_kronecker_ui
int __GMP_DECLSPEC mpz_kronecker_ui _PROTO ((mpz_srcptr, unsigned long)) __GMP_ATTRIBUTE_PURE;

#define mpz_si_kronecker __gmpz_si_kronecker
int __GMP_DECLSPEC mpz_si_kronecker _PROTO ((long, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_ui_kronecker __gmpz_ui_kronecker
int __GMP_DECLSPEC mpz_ui_kronecker _PROTO ((unsigned long, mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_lcm __gmpz_lcm
void __GMP_DECLSPEC mpz_lcm _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_lcm_ui __gmpz_lcm_ui
void __GMP_DECLSPEC mpz_lcm_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long));

#define mpz_legendre mpz_jacobi  /* alias */

#define mpz_lucnum_ui __gmpz_lucnum_ui
void __GMP_DECLSPEC mpz_lucnum_ui _PROTO ((mpz_ptr, unsigned long int));

#define mpz_lucnum2_ui __gmpz_lucnum2_ui
void __GMP_DECLSPEC mpz_lucnum2_ui _PROTO ((mpz_ptr, mpz_ptr, unsigned long int));

#define mpz_millerrabin __gmpz_millerrabin
int  __GMP_DECLSPEC mpz_millerrabin _PROTO ((mpz_srcptr, int)) __GMP_ATTRIBUTE_PURE;

#define mpz_mod __gmpz_mod
void __GMP_DECLSPEC mpz_mod _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_mul __gmpz_mul
void __GMP_DECLSPEC mpz_mul _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_mul_2exp __gmpz_mul_2exp
void __GMP_DECLSPEC mpz_mul_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_mul_si __gmpz_mul_si
void __GMP_DECLSPEC mpz_mul_si _PROTO ((mpz_ptr, mpz_srcptr, long int));

#define mpz_mul_ui __gmpz_mul_ui
void __GMP_DECLSPEC mpz_mul_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_neg __gmpz_neg
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_neg
void __GMP_DECLSPEC mpz_neg _PROTO ((mpz_ptr, mpz_srcptr));
#endif

#define mpz_nextprime __gmpz_nextprime
void __GMP_DECLSPEC mpz_nextprime _PROTO ((mpz_ptr, mpz_srcptr));

#define mpz_out_raw __gmpz_out_raw
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpz_out_raw _PROTO ((FILE *, mpz_srcptr));
#endif

#define mpz_out_str __gmpz_out_str
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpz_out_str _PROTO ((FILE *, int, mpz_srcptr));
#endif

#define mpz_perfect_power_p __gmpz_perfect_power_p
int __GMP_DECLSPEC mpz_perfect_power_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpz_perfect_square_p __gmpz_perfect_square_p
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_perfect_square_p
int __GMP_DECLSPEC mpz_perfect_square_p _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_popcount __gmpz_popcount
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_popcount
unsigned long int __GMP_DECLSPEC mpz_popcount _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_pow_ui __gmpz_pow_ui
void __GMP_DECLSPEC mpz_pow_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_powm __gmpz_powm
void __GMP_DECLSPEC mpz_powm _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr, mpz_srcptr));

#define mpz_powm_ui __gmpz_powm_ui
void __GMP_DECLSPEC mpz_powm_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int, mpz_srcptr));

#define mpz_probab_prime_p __gmpz_probab_prime_p
int  __GMP_DECLSPEC mpz_probab_prime_p _PROTO ((mpz_srcptr, int)) __GMP_ATTRIBUTE_PURE;

#define mpz_random __gmpz_random
void __GMP_DECLSPEC mpz_random _PROTO ((mpz_ptr, mp_size_t));

#define mpz_random2 __gmpz_random2
void __GMP_DECLSPEC mpz_random2 _PROTO ((mpz_ptr, mp_size_t));

#define mpz_realloc2 __gmpz_realloc2
void __GMP_DECLSPEC mpz_realloc2 _PROTO ((mpz_ptr, unsigned long));

#define mpz_remove __gmpz_remove
unsigned long int __GMP_DECLSPEC mpz_remove _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_root __gmpz_root
int __GMP_DECLSPEC mpz_root _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_rrandomb __gmpz_rrandomb
void __GMP_DECLSPEC mpz_rrandomb _PROTO ((mpz_ptr, gmp_randstate_t, unsigned long int));

#define mpz_scan0 __gmpz_scan0
unsigned long int __GMP_DECLSPEC mpz_scan0 _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_scan1 __gmpz_scan1
unsigned long int __GMP_DECLSPEC mpz_scan1 _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_set __gmpz_set
void __GMP_DECLSPEC mpz_set _PROTO ((mpz_ptr, mpz_srcptr));

#define mpz_set_d __gmpz_set_d
void __GMP_DECLSPEC mpz_set_d _PROTO ((mpz_ptr, double));

#define mpz_set_f __gmpz_set_f
void __GMP_DECLSPEC mpz_set_f _PROTO ((mpz_ptr, mpf_srcptr));

#define mpz_set_q __gmpz_set_q
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_set_q
void __GMP_DECLSPEC mpz_set_q _PROTO ((mpz_ptr, mpq_srcptr));
#endif

#define mpz_set_si __gmpz_set_si
void __GMP_DECLSPEC mpz_set_si _PROTO ((mpz_ptr, signed long int));

#define mpz_set_str __gmpz_set_str
int  __GMP_DECLSPEC mpz_set_str _PROTO ((mpz_ptr, __gmp_const char *, int));

#define mpz_set_ui __gmpz_set_ui
void __GMP_DECLSPEC mpz_set_ui _PROTO ((mpz_ptr, unsigned long int));

#define mpz_setbit __gmpz_setbit
void __GMP_DECLSPEC mpz_setbit _PROTO ((mpz_ptr, unsigned long int));

#define mpz_size __gmpz_size
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpz_size
size_t __GMP_DECLSPEC mpz_size _PROTO ((mpz_srcptr)) __GMP_ATTRIBUTE_PURE;
#endif

#define mpz_sizeinbase __gmpz_sizeinbase
size_t __GMP_DECLSPEC mpz_sizeinbase _PROTO ((mpz_srcptr, int)) __GMP_ATTRIBUTE_PURE;

#define mpz_sqrt __gmpz_sqrt
void __GMP_DECLSPEC mpz_sqrt _PROTO ((mpz_ptr, mpz_srcptr));

#define mpz_sqrtrem __gmpz_sqrtrem
void __GMP_DECLSPEC mpz_sqrtrem _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr));

#define mpz_sub __gmpz_sub
void __GMP_DECLSPEC mpz_sub _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_sub_ui __gmpz_sub_ui
void __GMP_DECLSPEC mpz_sub_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_submul __gmpz_submul
void __GMP_DECLSPEC mpz_submul _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_submul_ui __gmpz_submul_ui
void __GMP_DECLSPEC mpz_submul_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_swap __gmpz_swap
void __GMP_DECLSPEC mpz_swap _PROTO ((mpz_ptr, mpz_ptr));

#define mpz_tdiv_ui __gmpz_tdiv_ui
unsigned long int __GMP_DECLSPEC mpz_tdiv_ui _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_tdiv_q __gmpz_tdiv_q
void __GMP_DECLSPEC mpz_tdiv_q _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_tdiv_q_2exp __gmpz_tdiv_q_2exp
void __GMP_DECLSPEC mpz_tdiv_q_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_tdiv_q_ui __gmpz_tdiv_q_ui
unsigned long int __GMP_DECLSPEC mpz_tdiv_q_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_tdiv_qr __gmpz_tdiv_qr
void __GMP_DECLSPEC mpz_tdiv_qr _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_tdiv_qr_ui __gmpz_tdiv_qr_ui
unsigned long int __GMP_DECLSPEC mpz_tdiv_qr_ui _PROTO ((mpz_ptr, mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_tdiv_r __gmpz_tdiv_r
void __GMP_DECLSPEC mpz_tdiv_r _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));

#define mpz_tdiv_r_2exp __gmpz_tdiv_r_2exp
void __GMP_DECLSPEC mpz_tdiv_r_2exp _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_tdiv_r_ui __gmpz_tdiv_r_ui
unsigned long int __GMP_DECLSPEC mpz_tdiv_r_ui _PROTO ((mpz_ptr, mpz_srcptr, unsigned long int));

#define mpz_tstbit __gmpz_tstbit
int __GMP_DECLSPEC mpz_tstbit _PROTO ((mpz_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpz_ui_pow_ui __gmpz_ui_pow_ui
void __GMP_DECLSPEC mpz_ui_pow_ui _PROTO ((mpz_ptr, unsigned long int, unsigned long int));

#define mpz_urandomb __gmpz_urandomb
void __GMP_DECLSPEC mpz_urandomb _PROTO ((mpz_ptr, gmp_randstate_t, unsigned long int));

#define mpz_urandomm __gmpz_urandomm
void __GMP_DECLSPEC mpz_urandomm _PROTO ((mpz_ptr, gmp_randstate_t, mpz_srcptr));

#define mpz_xor __gmpz_xor
#define mpz_eor __gmpz_xor
void __GMP_DECLSPEC mpz_xor _PROTO ((mpz_ptr, mpz_srcptr, mpz_srcptr));


/**************** Rational (i.e. Q) routines.  ****************/

#define mpq_abs __gmpq_abs
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpq_abs
void __GMP_DECLSPEC mpq_abs _PROTO ((mpq_ptr, mpq_srcptr));
#endif

#define mpq_add __gmpq_add
void __GMP_DECLSPEC mpq_add _PROTO ((mpq_ptr, mpq_srcptr, mpq_srcptr));

#define mpq_canonicalize __gmpq_canonicalize
void __GMP_DECLSPEC mpq_canonicalize _PROTO ((mpq_ptr));

#define mpq_clear __gmpq_clear
void __GMP_DECLSPEC mpq_clear _PROTO ((mpq_ptr));

#define mpq_cmp __gmpq_cmp
int __GMP_DECLSPEC mpq_cmp _PROTO ((mpq_srcptr, mpq_srcptr)) __GMP_ATTRIBUTE_PURE;

#define _mpq_cmp_si __gmpq_cmp_si
int __GMP_DECLSPEC _mpq_cmp_si _PROTO ((mpq_srcptr, long, unsigned long)) __GMP_ATTRIBUTE_PURE;

#define _mpq_cmp_ui __gmpq_cmp_ui
int __GMP_DECLSPEC _mpq_cmp_ui _PROTO ((mpq_srcptr, unsigned long int, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpq_div __gmpq_div
void __GMP_DECLSPEC mpq_div _PROTO ((mpq_ptr, mpq_srcptr, mpq_srcptr));

#define mpq_div_2exp __gmpq_div_2exp
void __GMP_DECLSPEC mpq_div_2exp _PROTO ((mpq_ptr, mpq_srcptr, unsigned long));

#define mpq_equal __gmpq_equal
int __GMP_DECLSPEC mpq_equal _PROTO ((mpq_srcptr, mpq_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpq_get_num __gmpq_get_num
void __GMP_DECLSPEC mpq_get_num _PROTO ((mpz_ptr, mpq_srcptr));

#define mpq_get_den __gmpq_get_den
void __GMP_DECLSPEC mpq_get_den _PROTO ((mpz_ptr, mpq_srcptr));

#define mpq_get_d __gmpq_get_d
double __GMP_DECLSPEC mpq_get_d _PROTO ((mpq_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpq_get_str __gmpq_get_str
__GMP_DECLSPEC char * mpq_get_str _PROTO ((char *, int, mpq_srcptr));

#define mpq_init __gmpq_init
void __GMP_DECLSPEC mpq_init _PROTO ((mpq_ptr));

#define mpq_inp_str __gmpq_inp_str
#ifdef _GMP_H_HAVE_FILE
size_t mpq_inp_str _PROTO ((mpq_ptr, FILE *, int));
#endif

#define mpq_inv __gmpq_inv
void __GMP_DECLSPEC mpq_inv _PROTO ((mpq_ptr, mpq_srcptr));

#define mpq_mul __gmpq_mul
void __GMP_DECLSPEC mpq_mul _PROTO ((mpq_ptr, mpq_srcptr, mpq_srcptr));

#define mpq_mul_2exp __gmpq_mul_2exp
void __GMP_DECLSPEC mpq_mul_2exp _PROTO ((mpq_ptr, mpq_srcptr, unsigned long));

#define mpq_neg __gmpq_neg
#if __GMP_INLINE_PROTOTYPES || __GMP_FORCE_mpq_neg
void __GMP_DECLSPEC mpq_neg _PROTO ((mpq_ptr, mpq_srcptr));
#endif

#define mpq_out_str __gmpq_out_str
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpq_out_str _PROTO ((FILE *, int, mpq_srcptr));
#endif

#define mpq_set __gmpq_set
void __GMP_DECLSPEC mpq_set _PROTO ((mpq_ptr, mpq_srcptr));

#define mpq_set_d __gmpq_set_d
void __GMP_DECLSPEC mpq_set_d _PROTO ((mpq_ptr, double));

#define mpq_set_den __gmpq_set_den
void __GMP_DECLSPEC mpq_set_den _PROTO ((mpq_ptr, mpz_srcptr));

#define mpq_set_f __gmpq_set_f
void __GMP_DECLSPEC mpq_set_f _PROTO ((mpq_ptr, mpf_srcptr));

#define mpq_set_num __gmpq_set_num
void __GMP_DECLSPEC mpq_set_num _PROTO ((mpq_ptr, mpz_srcptr));

#define mpq_set_si __gmpq_set_si
void __GMP_DECLSPEC mpq_set_si _PROTO ((mpq_ptr, signed long int, unsigned long int));

#define mpq_set_str __gmpq_set_str
int __GMP_DECLSPEC mpq_set_str _PROTO ((mpq_ptr, const char *, int));

#define mpq_set_ui __gmpq_set_ui
void __GMP_DECLSPEC mpq_set_ui _PROTO ((mpq_ptr, unsigned long int, unsigned long int));

#define mpq_set_z __gmpq_set_z
void __GMP_DECLSPEC mpq_set_z _PROTO ((mpq_ptr, mpz_srcptr));

#define mpq_sub __gmpq_sub
void __GMP_DECLSPEC mpq_sub _PROTO ((mpq_ptr, mpq_srcptr, mpq_srcptr));

#define mpq_swap __gmpq_swap
void __GMP_DECLSPEC mpq_swap _PROTO ((mpq_ptr, mpq_ptr));


/**************** Float (i.e. F) routines.  ****************/

#define mpf_abs __gmpf_abs
void __GMP_DECLSPEC mpf_abs _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_add __gmpf_add
void __GMP_DECLSPEC mpf_add _PROTO ((mpf_ptr, mpf_srcptr, mpf_srcptr));

#define mpf_add_ui __gmpf_add_ui
void __GMP_DECLSPEC mpf_add_ui _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));
#define mpf_ceil __gmpf_ceil
void __GMP_DECLSPEC mpf_ceil _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_clear __gmpf_clear
void __GMP_DECLSPEC mpf_clear _PROTO ((mpf_ptr));

#define mpf_cmp __gmpf_cmp
int __GMP_DECLSPEC mpf_cmp _PROTO ((mpf_srcptr, mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_cmp_d __gmpf_cmp_d
int __GMP_DECLSPEC mpf_cmp_d _PROTO ((mpf_srcptr, double)) __GMP_ATTRIBUTE_PURE;

#define mpf_cmp_si __gmpf_cmp_si
int __GMP_DECLSPEC mpf_cmp_si _PROTO ((mpf_srcptr, signed long int)) __GMP_ATTRIBUTE_PURE;

#define mpf_cmp_ui __gmpf_cmp_ui
int __GMP_DECLSPEC mpf_cmp_ui _PROTO ((mpf_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpf_div __gmpf_div
void __GMP_DECLSPEC mpf_div _PROTO ((mpf_ptr, mpf_srcptr, mpf_srcptr));

#define mpf_div_2exp __gmpf_div_2exp
void __GMP_DECLSPEC mpf_div_2exp _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));

#define mpf_div_ui __gmpf_div_ui
void __GMP_DECLSPEC mpf_div_ui _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));

#define mpf_dump __gmpf_dump
void __GMP_DECLSPEC mpf_dump _PROTO ((mpf_srcptr));

#define mpf_eq __gmpf_eq
int __GMP_DECLSPEC mpf_eq _PROTO ((mpf_srcptr, mpf_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpf_fits_sint_p __gmpf_fits_sint_p
int __GMP_DECLSPEC mpf_fits_sint_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_fits_slong_p __gmpf_fits_slong_p
int __GMP_DECLSPEC mpf_fits_slong_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_fits_sshort_p __gmpf_fits_sshort_p
int __GMP_DECLSPEC mpf_fits_sshort_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_fits_uint_p __gmpf_fits_uint_p
int __GMP_DECLSPEC mpf_fits_uint_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_fits_ulong_p __gmpf_fits_ulong_p
int __GMP_DECLSPEC mpf_fits_ulong_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_fits_ushort_p __gmpf_fits_ushort_p
int __GMP_DECLSPEC mpf_fits_ushort_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_floor __gmpf_floor
void __GMP_DECLSPEC mpf_floor _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_get_d __gmpf_get_d
double __GMP_DECLSPEC mpf_get_d _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_get_d_2exp __gmpf_get_d_2exp
double __GMP_DECLSPEC mpf_get_d_2exp _PROTO ((signed long int *, mpf_srcptr));

#define mpf_get_default_prec __gmpf_get_default_prec
unsigned long int __GMP_DECLSPEC mpf_get_default_prec _PROTO ((void)) __GMP_ATTRIBUTE_PURE;

#define mpf_get_prec __gmpf_get_prec
unsigned long int __GMP_DECLSPEC mpf_get_prec _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_get_si __gmpf_get_si
long __GMP_DECLSPEC mpf_get_si _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_get_str __gmpf_get_str
__GMP_DECLSPEC char * mpf_get_str _PROTO ((char *, mp_exp_t *, int, size_t, mpf_srcptr));

#define mpf_get_ui __gmpf_get_ui
unsigned long __GMP_DECLSPEC mpf_get_ui _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_init __gmpf_init
void __GMP_DECLSPEC mpf_init _PROTO ((mpf_ptr));

#define mpf_init2 __gmpf_init2
void __GMP_DECLSPEC mpf_init2 _PROTO ((mpf_ptr, unsigned long int));

#define mpf_init_set __gmpf_init_set
void __GMP_DECLSPEC mpf_init_set _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_init_set_d __gmpf_init_set_d
void __GMP_DECLSPEC mpf_init_set_d _PROTO ((mpf_ptr, double));

#define mpf_init_set_si __gmpf_init_set_si
void __GMP_DECLSPEC mpf_init_set_si _PROTO ((mpf_ptr, signed long int));

#define mpf_init_set_str __gmpf_init_set_str
int  __GMP_DECLSPEC mpf_init_set_str _PROTO ((mpf_ptr, __gmp_const char *, int));

#define mpf_init_set_ui __gmpf_init_set_ui
void __GMP_DECLSPEC mpf_init_set_ui _PROTO ((mpf_ptr, unsigned long int));

#define mpf_inp_str __gmpf_inp_str
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpf_inp_str _PROTO ((mpf_ptr, FILE *, int));
#endif

#define mpf_integer_p __gmpf_integer_p
int __GMP_DECLSPEC mpf_integer_p _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_mul __gmpf_mul
void __GMP_DECLSPEC mpf_mul _PROTO ((mpf_ptr, mpf_srcptr, mpf_srcptr));

#define mpf_mul_2exp __gmpf_mul_2exp
void __GMP_DECLSPEC mpf_mul_2exp _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));

#define mpf_mul_ui __gmpf_mul_ui
void __GMP_DECLSPEC mpf_mul_ui _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));

#define mpf_neg __gmpf_neg
void __GMP_DECLSPEC mpf_neg _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_out_str __gmpf_out_str
#ifdef _GMP_H_HAVE_FILE
size_t __GMP_DECLSPEC mpf_out_str _PROTO ((FILE *, int, size_t, mpf_srcptr));
#endif

#define mpf_pow_ui __gmpf_pow_ui
void __GMP_DECLSPEC mpf_pow_ui _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));

#define mpf_random2 __gmpf_random2
void __GMP_DECLSPEC mpf_random2 _PROTO ((mpf_ptr, mp_size_t, mp_exp_t));

#define mpf_reldiff __gmpf_reldiff
void __GMP_DECLSPEC mpf_reldiff _PROTO ((mpf_ptr, mpf_srcptr, mpf_srcptr));

#define mpf_set __gmpf_set
void __GMP_DECLSPEC mpf_set _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_set_d __gmpf_set_d
void __GMP_DECLSPEC mpf_set_d _PROTO ((mpf_ptr, double));

#define mpf_set_default_prec __gmpf_set_default_prec
void __GMP_DECLSPEC mpf_set_default_prec _PROTO ((unsigned long int));

#define mpf_set_prec __gmpf_set_prec
void __GMP_DECLSPEC mpf_set_prec _PROTO ((mpf_ptr, unsigned long int));

#define mpf_set_prec_raw __gmpf_set_prec_raw
void __GMP_DECLSPEC mpf_set_prec_raw _PROTO ((mpf_ptr, unsigned long int));

#define mpf_set_q __gmpf_set_q
void __GMP_DECLSPEC mpf_set_q _PROTO ((mpf_ptr, mpq_srcptr));

#define mpf_set_si __gmpf_set_si
void __GMP_DECLSPEC mpf_set_si _PROTO ((mpf_ptr, signed long int));

#define mpf_set_str __gmpf_set_str
int  __GMP_DECLSPEC mpf_set_str _PROTO ((mpf_ptr, __gmp_const char *, int));

#define mpf_set_ui __gmpf_set_ui
void __GMP_DECLSPEC mpf_set_ui _PROTO ((mpf_ptr, unsigned long int));

#define mpf_set_z __gmpf_set_z
void __GMP_DECLSPEC mpf_set_z _PROTO ((mpf_ptr, mpz_srcptr));

#define mpf_size __gmpf_size
size_t __GMP_DECLSPEC mpf_size _PROTO ((mpf_srcptr)) __GMP_ATTRIBUTE_PURE;

#define mpf_sqrt __gmpf_sqrt
void __GMP_DECLSPEC mpf_sqrt _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_sqrt_ui __gmpf_sqrt_ui
void __GMP_DECLSPEC mpf_sqrt_ui _PROTO ((mpf_ptr, unsigned long int));

#define mpf_sub __gmpf_sub
void __GMP_DECLSPEC mpf_sub _PROTO ((mpf_ptr, mpf_srcptr, mpf_srcptr));

#define mpf_sub_ui __gmpf_sub_ui
void __GMP_DECLSPEC mpf_sub_ui _PROTO ((mpf_ptr, mpf_srcptr, unsigned long int));

#define mpf_swap __gmpf_swap
void __GMP_DECLSPEC mpf_swap _PROTO ((mpf_ptr, mpf_ptr));

#define mpf_trunc __gmpf_trunc
void __GMP_DECLSPEC mpf_trunc _PROTO ((mpf_ptr, mpf_srcptr));

#define mpf_ui_div __gmpf_ui_div
void __GMP_DECLSPEC mpf_ui_div _PROTO ((mpf_ptr, unsigned long int, mpf_srcptr));

#define mpf_ui_sub __gmpf_ui_sub
void __GMP_DECLSPEC mpf_ui_sub _PROTO ((mpf_ptr, unsigned long int, mpf_srcptr));

#define mpf_urandomb __gmpf_urandomb
void __GMP_DECLSPEC mpf_urandomb _PROTO ((mpf_t, gmp_randstate_t, unsigned long int));


/************ Low level positive-integer (i.e. N) routines.  ************/

/* This is ugly, but we need to make user calls reach the prefixed function. */

#define mpn_add __MPN(add)
mp_limb_t __GMP_DECLSPEC mpn_add _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_srcptr,mp_size_t));

#define mpn_add_1 __MPN(add_1)
mp_limb_t __GMP_DECLSPEC mpn_add_1 _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_add_n __MPN(add_n)
mp_limb_t __GMP_DECLSPEC mpn_add_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));

#define mpn_add_nc __MPN(add_nc)
mp_limb_t __GMP_DECLSPEC mpn_add_nc _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_addmul_1 __MPN(addmul_1)
mp_limb_t __GMP_DECLSPEC mpn_addmul_1 _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_addmul_1c __MPN(addmul_1c)
mp_limb_t __GMP_DECLSPEC mpn_addmul_1c _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t, mp_limb_t));

#define mpn_addsub_n __MPN(addsub_n)
mp_limb_t __GMP_DECLSPEC mpn_addsub_n _PROTO ((mp_ptr, mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));

#define mpn_addsub_nc __MPN(addsub_nc)
mp_limb_t __GMP_DECLSPEC mpn_addsub_nc _PROTO ((mp_ptr, mp_ptr, mp_srcptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_bdivmod __MPN(bdivmod)
mp_limb_t __GMP_DECLSPEC mpn_bdivmod _PROTO ((mp_ptr, mp_ptr, mp_size_t, mp_srcptr, mp_size_t, unsigned long int));

#define mpn_cmp __MPN(cmp)
int __GMP_DECLSPEC mpn_cmp _PROTO ((mp_srcptr, mp_srcptr, mp_size_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_divexact_by3(dst,src,size) \
  mpn_divexact_by3c (dst, src, size, (mp_limb_t) 0)

#define mpn_divexact_by3c __MPN(divexact_by3c)
mp_limb_t __GMP_DECLSPEC mpn_divexact_by3c _PROTO ((mp_ptr dst, mp_srcptr src,
                                     mp_size_t size, mp_limb_t carry));

#define mpn_divmod_1(qp,np,nsize,dlimb) \
  mpn_divrem_1 (qp, (mp_size_t) 0, np, nsize, dlimb)

#define mpn_divrem __MPN(divrem)
mp_limb_t __GMP_DECLSPEC mpn_divrem _PROTO((mp_ptr, mp_size_t, mp_ptr, mp_size_t, mp_srcptr, mp_size_t));

#define mpn_divrem_1 __MPN(divrem_1)
mp_limb_t __GMP_DECLSPEC mpn_divrem_1 _PROTO ((mp_ptr, mp_size_t, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_divrem_1c __MPN(divrem_1c)
mp_limb_t __GMP_DECLSPEC mpn_divrem_1c _PROTO ((mp_ptr, mp_size_t, mp_srcptr, mp_size_t,
                                 mp_limb_t, mp_limb_t));

#define mpn_divrem_2 __MPN(divrem_2)
mp_limb_t __GMP_DECLSPEC mpn_divrem_2 _PROTO ((mp_ptr, mp_size_t, mp_ptr, mp_size_t, mp_srcptr));

#define mpn_dump __MPN(dump)
void __GMP_DECLSPEC mpn_dump _PROTO ((mp_srcptr, mp_size_t));

#define mpn_gcd __MPN(gcd)
mp_size_t __GMP_DECLSPEC mpn_gcd _PROTO ((mp_ptr, mp_ptr, mp_size_t, mp_ptr, mp_size_t));

#define mpn_gcd_1 __MPN(gcd_1)
mp_limb_t __GMP_DECLSPEC mpn_gcd_1 _PROTO ((mp_srcptr, mp_size_t, mp_limb_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_gcdext __MPN(gcdext)
mp_size_t __GMP_DECLSPEC mpn_gcdext _PROTO ((mp_ptr, mp_ptr, mp_size_t *, mp_ptr, mp_size_t, mp_ptr, mp_size_t));

#define mpn_get_str __MPN(get_str)
size_t __GMP_DECLSPEC mpn_get_str _PROTO ((unsigned char *, int, mp_ptr, mp_size_t));

#define mpn_hamdist __MPN(hamdist)
unsigned long int mpn_hamdist _PROTO ((mp_srcptr, mp_srcptr, mp_size_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_lshift __MPN(lshift)
mp_limb_t __GMP_DECLSPEC mpn_lshift _PROTO ((mp_ptr, mp_srcptr, mp_size_t, unsigned int));

#define mpn_mod_1 __MPN(mod_1)
mp_limb_t __GMP_DECLSPEC mpn_mod_1 _PROTO ((mp_srcptr, mp_size_t, mp_limb_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_mod_1c __MPN(mod_1c)
mp_limb_t __GMP_DECLSPEC mpn_mod_1c _PROTO ((mp_srcptr, mp_size_t, mp_limb_t, mp_limb_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_mul __MPN(mul)
mp_limb_t __GMP_DECLSPEC mpn_mul _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_srcptr, mp_size_t));

#define mpn_mul_1 __MPN(mul_1)
mp_limb_t __GMP_DECLSPEC mpn_mul_1 _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_mul_1c __MPN(mul_1c)
mp_limb_t __GMP_DECLSPEC mpn_mul_1c _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t, mp_limb_t));

#define mpn_mul_basecase __MPN(mul_basecase)
void __GMP_DECLSPEC mpn_mul_basecase _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_srcptr, mp_size_t));

#define mpn_mul_n __MPN(mul_n)
void __GMP_DECLSPEC mpn_mul_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));

#define mpn_perfect_square_p __MPN(perfect_square_p)
int  __GMP_DECLSPEC mpn_perfect_square_p _PROTO ((mp_srcptr, mp_size_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_popcount __MPN(popcount)
unsigned long int __GMP_DECLSPEC mpn_popcount _PROTO ((mp_srcptr, mp_size_t)) __GMP_ATTRIBUTE_PURE;

/* undocumented, but retained here for upward compatibility */
#define mpn_preinv_mod_1 __MPN(preinv_mod_1)
mp_limb_t __GMP_DECLSPEC mpn_preinv_mod_1 _PROTO ((mp_srcptr, mp_size_t, mp_limb_t, mp_limb_t)) __GMP_ATTRIBUTE_PURE;

#define mpn_random __MPN(random)
void __GMP_DECLSPEC mpn_random _PROTO ((mp_ptr, mp_size_t));

#define mpn_random2 __MPN(random2)
void __GMP_DECLSPEC mpn_random2 _PROTO ((mp_ptr, mp_size_t));

#define mpn_rshift __MPN(rshift)
mp_limb_t __GMP_DECLSPEC mpn_rshift _PROTO ((mp_ptr, mp_srcptr, mp_size_t, unsigned int));

#define mpn_scan0 __MPN(scan0)
unsigned long int __GMP_DECLSPEC mpn_scan0 _PROTO ((mp_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpn_scan1 __MPN(scan1)
unsigned long int __GMP_DECLSPEC mpn_scan1 _PROTO ((mp_srcptr, unsigned long int)) __GMP_ATTRIBUTE_PURE;

#define mpn_set_str __MPN(set_str)
mp_size_t __GMP_DECLSPEC mpn_set_str _PROTO ((mp_ptr, __gmp_const unsigned char *, size_t, int));

#define mpn_sqr_n __MPN(sqr_n)
void __GMP_DECLSPEC mpn_sqr_n _PROTO ((mp_ptr, mp_srcptr, mp_size_t));

#define mpn_sqr_basecase __MPN(sqr_basecase)
void __GMP_DECLSPEC mpn_sqr_basecase _PROTO ((mp_ptr, mp_srcptr, mp_size_t));

#define mpn_sqrtrem __MPN(sqrtrem)
mp_size_t __GMP_DECLSPEC mpn_sqrtrem _PROTO ((mp_ptr, mp_ptr, mp_srcptr, mp_size_t));

#define mpn_sub __MPN(sub)
mp_limb_t __GMP_DECLSPEC mpn_sub _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_srcptr,mp_size_t));

#define mpn_sub_1 __MPN(sub_1)
mp_limb_t __GMP_DECLSPEC mpn_sub_1 _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_sub_n __MPN(sub_n)
mp_limb_t __GMP_DECLSPEC mpn_sub_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));

#define mpn_sub_nc __MPN(sub_nc)
mp_limb_t __GMP_DECLSPEC mpn_sub_nc _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_submul_1 __MPN(submul_1)
mp_limb_t __GMP_DECLSPEC mpn_submul_1 _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t));

#define mpn_submul_1c __MPN(submul_1c)
mp_limb_t __GMP_DECLSPEC mpn_submul_1c _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_limb_t, mp_limb_t));

#define mpn_tdiv_qr __MPN(tdiv_qr)
void __GMP_DECLSPEC mpn_tdiv_qr _PROTO ((mp_ptr, mp_ptr, mp_size_t, mp_srcptr, mp_size_t, mp_srcptr, mp_size_t));


/**************** mpz inlines ****************/

/* The following are provided as inlines where possible, but always exist as
   library functions too, for binary compatibility.

   Within gmp itself this inlining generally isn't relied on, since it
   doesn't get done for all compilers, whereas if something is worth
   inlining then it's worth arranging always.

   There are two styles of inlining here.  When the same bit of code is
   wanted for the inline as for the library version, then __GMP_FORCE_foo
   arranges for that code to be emitted and the __GMP_EXTERN_INLINE
   directive suppressed, eg. mpz_fits_uint_p.  When a different bit of code
   is wanted for the inline than for the library version, then
   __GMP_FORCE_foo arranges the inline to be suppressed, eg. mpz_abs.  */

#if defined (__GMP_EXTERN_INLINE) && ! __GMP_FORCE_mpz_abs
__GMP_EXTERN_INLINE void
mpz_abs (mpz_ptr w, mpz_srcptr u)
{
  if (w != u)
    mpz_set (w, u);
  w->_mp_size = __GMP_ABS (w->_mp_size);
}
#endif

#define __GMPZ_FITS_UTYPE_P(z,maxval)                   \
  mp_size_t  size = z->_mp_size;                        \
  mp_limb_t  data = z->_mp_d[0];                        \
  return (size == 0 || (size == 1 && data <= maxval));

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_fits_uint_p
#if ! __GMP_FORCE_mpz_fits_uint_p
__GMP_EXTERN_INLINE
#endif
int
mpz_fits_uint_p (mpz_srcptr z)
{
  __GMPZ_FITS_UTYPE_P (z, __GMP_UINT_MAX);
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_fits_ulong_p
#if ! __GMP_FORCE_mpz_fits_ulong_p
__GMP_EXTERN_INLINE
#endif
int
mpz_fits_ulong_p (mpz_srcptr z)
{
  __GMPZ_FITS_UTYPE_P (z, __GMP_ULONG_MAX);
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_fits_ushort_p
#if ! __GMP_FORCE_mpz_fits_ushort_p
__GMP_EXTERN_INLINE
#endif
int
mpz_fits_ushort_p (mpz_srcptr z)
{
  __GMPZ_FITS_UTYPE_P (z, __GMP_USHRT_MAX);
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_get_ui
#if ! __GMP_FORCE_mpz_get_ui
__GMP_EXTERN_INLINE
#endif
unsigned long
mpz_get_ui (mpz_srcptr z)
{
  mp_limb_t l = z->_mp_d[0];
  return z->_mp_size ? l : 0;
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_getlimbn
#if ! __GMP_FORCE_mpz_getlimbn
__GMP_EXTERN_INLINE
#endif
mp_limb_t
mpz_getlimbn (mpz_srcptr z, mp_size_t n)
{
  if (__GMP_ABS (z->_mp_size) <= n || n < 0)
    return 0;
  else
    return z->_mp_d[n];
}
#endif

#if defined (__GMP_EXTERN_INLINE) && ! __GMP_FORCE_mpz_neg
__GMP_EXTERN_INLINE void
mpz_neg (mpz_ptr w, mpz_srcptr u)
{
  if (w != u)
    mpz_set (w, u);
  w->_mp_size = - w->_mp_size;
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_perfect_square_p
#if ! __GMP_FORCE_mpz_perfect_square_p
__GMP_EXTERN_INLINE
#endif
int
mpz_perfect_square_p (mpz_srcptr a)
{
  mp_size_t asize = a->_mp_size;
  if (asize <= 0)
    return (asize == 0);  /* zero is a square, negatives are not */
  else
    return mpn_perfect_square_p (a->_mp_d, asize);
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_popcount
#if ! __GMP_FORCE_mpz_popcount
__GMP_EXTERN_INLINE
#endif
unsigned long
mpz_popcount (mpz_srcptr u)
{
  mp_size_t usize = u->_mp_size;

  if (usize <= 0)
    return (usize < 0 ? __GMP_ULONG_MAX : 0);
  else
    return mpn_popcount (u->_mp_d, usize);
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_set_q
#if ! __GMP_FORCE_mpz_set_q
__GMP_EXTERN_INLINE
#endif
void
mpz_set_q (mpz_ptr w, mpq_srcptr u)
{
  mpz_tdiv_q (w, mpq_numref (u), mpq_denref (u));
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpz_size
#if ! __GMP_FORCE_mpz_size
__GMP_EXTERN_INLINE
#endif
size_t
mpz_size (mpz_srcptr z)
{
  return __GMP_ABS (z->_mp_size);
}
#endif


/**************** mpq inlines ****************/

#if defined (__GMP_EXTERN_INLINE) && ! __GMP_FORCE_mpq_abs
__GMP_EXTERN_INLINE void
mpq_abs (mpq_ptr w, mpq_srcptr u)
{
  if (w != u)
    mpq_set (w, u);
  w->_mp_num._mp_size = __GMP_ABS (w->_mp_num._mp_size);
}
#endif

#if defined (__GMP_EXTERN_INLINE) && ! __GMP_FORCE_mpq_neg
__GMP_EXTERN_INLINE void
mpq_neg (mpq_ptr w, mpq_srcptr u)
{
  if (w != u)
    mpq_set (w, u);
  w->_mp_num._mp_size = - w->_mp_num._mp_size;
}
#endif


/**************** mpn inlines ****************/

/* The comments with __GMPN_ADD_1 below apply here too.

   The test for FUNCTION returning 0 should predict well.  If it's assumed
   {yp,ysize} will usually have a random number of bits then the high limb
   won't be full and a carry out will occur a good deal less than 50% of the
   time.

   ysize==0 isn't a documented feature, but is used internally in a few
   places.

   Producing cout last stops it using up a register during the main part of
   the calculation, though gcc (as of 3.0) on an "if (mpn_add (...))"
   doesn't seem able to move the true and false legs of the conditional up
   to the two places cout is generated.  */

#define __GMPN_AORS(cout, wp, xp, xsize, yp, ysize, FUNCTION, TEST)     \
  do {                                                                  \
    mp_size_t  __i;                                                     \
    mp_limb_t  __x;                                                     \
                                                                        \
    /* ASSERT ((ysize) >= 0); */                                        \
    /* ASSERT ((xsize) >= (ysize)); */                                  \
    /* ASSERT (MPN_SAME_OR_SEPARATE2_P (wp, xsize, xp, xsize)); */      \
    /* ASSERT (MPN_SAME_OR_SEPARATE2_P (wp, xsize, yp, ysize)); */      \
                                                                        \
    __i = (ysize);                                                      \
    if (__i != 0)                                                       \
      {                                                                 \
        if (FUNCTION (wp, xp, yp, __i))                                 \
          {                                                             \
            do                                                          \
              {                                                         \
                if (__i >= (xsize))                                     \
                  {                                                     \
                    (cout) = 1;                                         \
                    goto __done;                                        \
                  }                                                     \
                __x = (xp)[__i];                                        \
              }                                                         \
            while (TEST);                                               \
          }                                                             \
      }                                                                 \
    if ((wp) != (xp))                                                   \
      __GMPN_COPY_REST (wp, xp, xsize, __i);                            \
    (cout) = 0;                                                         \
  __done:                                                               \
    ;                                                                   \
  } while (0)

#define __GMPN_ADD(cout, wp, xp, xsize, yp, ysize)              \
  __GMPN_AORS (cout, wp, xp, xsize, yp, ysize, mpn_add_n,       \
               (((wp)[__i++] = __x + 1) == 0))
#define __GMPN_SUB(cout, wp, xp, xsize, yp, ysize)              \
  __GMPN_AORS (cout, wp, xp, xsize, yp, ysize, mpn_sub_n,       \
               (((wp)[__i++] = __x - 1), __x == 0))


/* The use of __i indexing is designed to ensure a compile time src==dst
   remains nice and clear to the compiler, so that __GMPN_COPY_REST can
   disappear, and the load/add/store gets a chance to become a
   read-modify-write on CISC CPUs.

   Alternatives:

   Using a pair of pointers instead of indexing would be possible, but gcc
   isn't able to recognise compile-time src==dst in that case, even when the
   pointers are incremented more or less together.  Other compilers would
   very likely have similar difficulty.

   gcc could use "if (__builtin_constant_p(src==dst) && src==dst)" or
   similar to detect a compile-time src==dst.  This works nicely on gcc
   2.95.x, it's not good on gcc 3.0 where __builtin_constant_p(p==p) seems
   to be always false, for a pointer p.  But the current code form seems
   good enough for src==dst anyway.

   gcc on x86 as usual doesn't give particularly good flags handling for the
   carry/borrow detection.  It's tempting to want some multi instruction asm
   blocks to help it, and this was tried, but in truth there's only a few
   instructions to save and any gain is all too easily lost by register
   juggling setting up for the asm.  */

#define __GMPN_AORS_1(cout, dst, src, n, v, OP, CB)		\
  do {								\
    mp_size_t  __i;						\
    mp_limb_t  __x, __r;					\
								\
    /* ASSERT ((n) >= 1); */					\
    /* ASSERT (MPN_SAME_OR_SEPARATE_P (dst, src, n)); */	\
								\
    __x = (src)[0];						\
    __r = __x OP (v);						\
    (dst)[0] = __r;						\
    if (CB (__r, __x, (v)))					\
      {								\
	(cout) = 1;						\
	for (__i = 1; __i < (n);)				\
	  {							\
	    __x = (src)[__i];					\
	    __r = __x OP 1;					\
	    (dst)[__i] = __r;					\
	    ++__i;						\
	    if (!CB (__r, __x, 1))				\
	      {							\
		if ((src) != (dst))				\
		  __GMPN_COPY_REST (dst, src, n, __i);		\
		(cout) = 0;					\
		break;						\
	      }							\
	  }							\
      }								\
    else							\
      {								\
	if ((src) != (dst))					\
	  __GMPN_COPY_REST (dst, src, n, 1);			\
	(cout) = 0;						\
      }								\
  } while (0)

#define __GMPN_ADDCB(r,x,y) ((r) < (y))
#define __GMPN_SUBCB(r,x,y) ((x) < (y))

#define __GMPN_ADD_1(cout, dst, src, n, v)	     \
  __GMPN_AORS_1(cout, dst, src, n, v, +, __GMPN_ADDCB)
#define __GMPN_SUB_1(cout, dst, src, n, v)	     \
  __GMPN_AORS_1(cout, dst, src, n, v, -, __GMPN_SUBCB)


/* Compare {xp,size} and {yp,size}, setting "result" to positive, zero or
   negative.  size==0 is allowed.  On random data usually only one limb will
   need to be examined to get a result, so it's worth having it inline.  */
#define __GMPN_CMP(result, xp, yp, size)                        \
  do {                                                          \
    mp_size_t  __i;                                             \
    mp_limb_t  __x, __y;                                        \
                                                                \
    /* ASSERT ((size) >= 0); */                                 \
                                                                \
    (result) = 0;                                               \
    __i = (size);                                               \
    while (--__i >= 0)                                          \
      {                                                         \
        __x = (xp)[__i];                                        \
        __y = (yp)[__i];                                        \
        if (__x != __y)                                         \
          {                                                     \
            /* Cannot use __x - __y, may overflow an "int" */   \
            (result) = (__x > __y ? 1 : -1);                    \
            break;                                              \
          }                                                     \
      }                                                         \
  } while (0)


/* For power and powerpc we want an inline ldu/stu/bdnz loop for copying.
   On ppc630 for instance this is optimal since it can sustain only 1 store
   per cycle.

   gcc 2.95.x (powerpc64 -maix64, or powerpc32) doesn't recognise the "for"
   loop in the generic code below can become ldu/stu/bdnz.  The do/while
   here helps it get to that.

   In gcc -mpowerpc64 mode, without -maix64, __size seems to want to be an
   mp_limb_t to get into the ctr register, and even then the loop is a
   curious ldu/stu/bdz/b.  But let's not worry about that unless there's a
   system using this.  An asm block could force what we want if necessary.

   xlc 3.1 already generates ldu/stu/bdnz from the generic C, and does so
   from this loop too.  */

#if __GMP_HAVE_HOST_CPU_FAMILY_power || __GMP_HAVE_HOST_CPU_FAMILY_powerpc
#define __GMPN_COPY_INCR(dst, src, size)                \
  do {                                                  \
    /* ASSERT ((size) >= 0); */                         \
    /* ASSERT (MPN_SAME_OR_INCR_P (dst, src, size)); */ \
    if ((size) != 0)                                    \
      {                                                 \
        mp_ptr     __dst = (dst) - 1;                   \
        mp_srcptr  __src = (src) - 1;                   \
        mp_size_t  __size = (size);                     \
        do                                              \
          *++__dst = *++__src;                          \
        while (--__size != 0);                          \
      }                                                 \
  } while (0)
#define __GMPN_COPY(dst, src, size)                             \
  do {                                                          \
    /* ASSERT (MPN_SAME_OR_SEPARATE_P (dst, src, size)); */     \
    __GMPN_COPY_INCR (dst, src, size);                          \
  } while (0)
#endif

#if defined (__GMPN_COPY) && ! defined (__GMPN_COPY_REST)
#define __GMPN_COPY_REST(dst, src, size, start)                 \
  do {                                                          \
    /* ASSERT ((start) >= 0); */                                \
    /* ASSERT ((start) <= (size)); */                           \
    __GMPN_COPY ((dst)+(start), (src)+(start), (size)-(start)); \
  } while (0)
#endif

/* Copy {src,size} to {dst,size}, starting at "start".  This is designed to
   keep the indexing dst[j] and src[j] nice and simple for __GMPN_ADD_1,
   __GMPN_ADD, etc.  */
#if ! defined (__GMPN_COPY_REST)
#define __GMPN_COPY_REST(dst, src, size, start)                 \
  do {                                                          \
    mp_size_t __j;                                              \
    /* ASSERT ((size) >= 0); */                                 \
    /* ASSERT ((start) >= 0); */                                \
    /* ASSERT ((start) <= (size)); */                           \
    /* ASSERT (MPN_SAME_OR_SEPARATE_P (dst, src, size)); */     \
    for (__j = (start); __j < (size); __j++)                    \
      (dst)[__j] = (src)[__j];                                  \
  } while (0)
#endif

/* Enhancement: Use some of the smarter code from gmp-impl.h.  Maybe use
   mpn_copyi if there's a native version, and if we don't mind demanding
   binary compatibility for it (on targets which use it).  */

#if ! defined (__GMPN_COPY)
#define __GMPN_COPY(dst, src, size)   __GMPN_COPY_REST (dst, src, size, 0)
#endif


#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpn_add
#if ! __GMP_FORCE_mpn_add
__GMP_EXTERN_INLINE
#endif
mp_limb_t
mpn_add (mp_ptr wp,
         mp_srcptr xp, mp_size_t xsize, mp_srcptr yp, mp_size_t ysize)
{
  mp_limb_t  c;
  __GMPN_ADD (c, wp, xp, xsize, yp, ysize);
  return c;
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpn_add_1
#if ! __GMP_FORCE_mpn_add_1
__GMP_EXTERN_INLINE
#endif
mp_limb_t
mpn_add_1 (mp_ptr dst, mp_srcptr src, mp_size_t size, mp_limb_t n)
{
  mp_limb_t  c;
  __GMPN_ADD_1 (c, dst, src, size, n);
  return c;
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpn_cmp
#if ! __GMP_FORCE_mpn_cmp
__GMP_EXTERN_INLINE
#endif
int
mpn_cmp (mp_srcptr xp, mp_srcptr yp, mp_size_t size)
{
  int result;
  __GMPN_CMP (result, xp, yp, size);
  return result;
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpn_sub
#if ! __GMP_FORCE_mpn_sub
__GMP_EXTERN_INLINE
#endif
mp_limb_t
mpn_sub (mp_ptr wp,
         mp_srcptr xp, mp_size_t xsize, mp_srcptr yp, mp_size_t ysize)
{
  mp_limb_t  c;
  __GMPN_SUB (c, wp, xp, xsize, yp, ysize);
  return c;
}
#endif

#if defined (__GMP_EXTERN_INLINE) || __GMP_FORCE_mpn_sub_1
#if ! __GMP_FORCE_mpn_sub_1
__GMP_EXTERN_INLINE
#endif
mp_limb_t
mpn_sub_1 (mp_ptr dst, mp_srcptr src, mp_size_t size, mp_limb_t n)
{
  mp_limb_t  c;
  __GMPN_SUB_1 (c, dst, src, size, n);
  return c;
}
#endif

#if defined (__cplusplus)
}
#endif


/* Allow faster testing for negative, zero, and positive.  */
#define mpz_sgn(Z) ((Z)->_mp_size < 0 ? -1 : (Z)->_mp_size > 0)
#define mpf_sgn(F) ((F)->_mp_size < 0 ? -1 : (F)->_mp_size > 0)
#define mpq_sgn(Q) ((Q)->_mp_num._mp_size < 0 ? -1 : (Q)->_mp_num._mp_size > 0)

/* When using GCC, optimize certain common comparisons.  */
#if defined (__GNUC__)
#define mpz_cmp_ui(Z,UI) \
  (__builtin_constant_p (UI) && (UI) == 0				\
   ? mpz_sgn (Z) : _mpz_cmp_ui (Z,UI))
#define mpz_cmp_si(Z,SI) \
  (__builtin_constant_p (SI) && (SI) == 0 ? mpz_sgn (Z)			\
   : __builtin_constant_p (SI) && (SI) > 0				\
    ? _mpz_cmp_ui (Z, (unsigned long int) SI)				\
   : _mpz_cmp_si (Z,SI))
#define mpq_cmp_ui(Q,NUI,DUI) \
  (__builtin_constant_p (NUI) && (NUI) == 0				\
   ? mpq_sgn (Q) : _mpq_cmp_ui (Q,NUI,DUI))
#define mpq_cmp_si(q,n,d)                       \
  (__builtin_constant_p ((n) >= 0) && (n) >= 0  \
   ? mpq_cmp_ui (q, (unsigned long) (n), d)     \
   : _mpq_cmp_si (q, n, d))
#else
#define mpz_cmp_ui(Z,UI) _mpz_cmp_ui (Z,UI)
#define mpz_cmp_si(Z,UI) _mpz_cmp_si (Z,UI)
#define mpq_cmp_ui(Q,NUI,DUI) _mpq_cmp_ui (Q,NUI,DUI)
#define mpq_cmp_si(q,n,d)  _mpq_cmp_si(q,n,d)
#endif


/* Using "&" rather than "&&" means these can come out branch-free.  Every
   mpz_t has at least one limb allocated, so fetching the low limb is always
   allowed.  */
#define mpz_odd_p(z)   ((int) ((z)->_mp_size != 0) & (int) (z)->_mp_d[0])
#define mpz_even_p(z)  (! mpz_odd_p (z))


/**************** C++ routines ****************/

#ifdef __cplusplus
#include <iosfwd>
__GMP_DECLSPEC std::ostream& operator<< (std::ostream &o, mpz_srcptr z);
__GMP_DECLSPEC std::ostream& operator<< (std::ostream &o, mpq_srcptr q);
__GMP_DECLSPEC std::ostream& operator<< (std::ostream &o, mpf_srcptr f);
__GMP_DECLSPEC std::istream& operator>> (std::istream &i, mpz_ptr z);
__GMP_DECLSPEC std::istream& operator>> (std::istream &i, mpq_ptr q);
__GMP_DECLSPEC std::istream& operator>> (std::istream &i, mpf_ptr f);
#endif


/* Compatibility with GMP 2 and earlier. */
#define mpn_divmod(qp,np,nsize,dp,dsize) \
  mpn_divrem (qp, (mp_size_t) 0, np, nsize, dp, dsize)

/* Compatibility with GMP 1.  */
#define mpz_mdiv	mpz_fdiv_q
#define mpz_mdivmod	mpz_fdiv_qr
#define mpz_mmod	mpz_fdiv_r
#define mpz_mdiv_ui	mpz_fdiv_q_ui
#define mpz_mdivmod_ui(q,r,n,d) \
  ((r == 0) ? mpz_fdiv_q_ui (q,n,d) : mpz_fdiv_qr_ui (q,r,n,d))
#define mpz_mmod_ui(r,n,d) \
  ((r == 0) ? mpz_fdiv_ui (n,d) : mpz_fdiv_r_ui (r,n,d))

/* Useful synonyms, but not quite compatible with GMP 1.  */
#define mpz_div		mpz_fdiv_q
#define mpz_divmod	mpz_fdiv_qr
#define mpz_div_ui	mpz_fdiv_q_ui
#define mpz_divmod_ui	mpz_fdiv_qr_ui
#define mpz_mod_ui	mpz_fdiv_r_ui
#define mpz_div_2exp	mpz_fdiv_q_2exp
#define mpz_mod_2exp	mpz_fdiv_r_2exp

#define gmp_errno __gmp_errno
extern int __GMP_DECLSPEC gmp_errno;

enum
{
  GMP_ERROR_NONE = 0,
  GMP_ERROR_UNSUPPORTED_ARGUMENT = 1,
  GMP_ERROR_DIVISION_BY_ZERO = 2,
  GMP_ERROR_SQRT_OF_NEGATIVE = 4,
  GMP_ERROR_INVALID_ARGUMENT = 8,
  GMP_ERROR_ALLOCATE = 16,
  GMP_ERROR_BAD_STRING = 32,
  GMP_ERROR_UNUSED_ERROR
};

/* Major version number is the value of __GNU_MP__ too, above and in mp.h. */
#define __GNU_MP_VERSION 4
#define __GNU_MP_VERSION_MINOR 0
#define __GNU_MP_VERSION_PATCHLEVEL 0

#define gmp_version __gmp_version
__GMP_DECLSPEC extern __gmp_const char * __gmp_const gmp_version;

#define __GMP_H__
#endif /* __GMP_H__ */