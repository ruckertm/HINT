#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.resources"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1217]; const double alignment; void * const ptr;}  resources_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\310\000\000\000\000\000\000\050\006\000\000\000"
  "\000\000\000\000\000\000\000\000\001\000\000\000\003\000\000\000"
  "\003\000\000\000\004\000\000\000\301\232\212\013\002\000\000\000"
  "\310\000\000\000\004\000\114\000\314\000\000\000\320\000\000\000"
  "\312\121\246\226\005\000\000\000\320\000\000\000\003\000\114\000"
  "\324\000\000\000\330\000\000\000\324\265\002\000\377\377\377\377"
  "\330\000\000\000\001\000\114\000\334\000\000\000\340\000\000\000"
  "\130\030\230\114\004\000\000\000\340\000\000\000\004\000\166\000"
  "\350\000\000\000\251\004\000\000\007\116\345\135\001\000\000\000"
  "\251\004\000\000\011\000\114\000\264\004\000\000\270\004\000\000"
  "\305\367\047\054\000\000\000\000\270\004\000\000\003\000\114\000"
  "\274\004\000\000\300\004\000\000\145\144\165\057\005\000\000\000"
  "\143\163\057\000\004\000\000\000\057\000\000\000\000\000\000\000"
  "\154\157\147\157\000\000\000\000\261\003\000\000\000\000\000\000"
  "\211\120\116\107\015\012\032\012\000\000\000\015\111\110\104\122"
  "\000\000\000\100\000\000\000\100\010\003\000\000\000\235\267\201"
  "\354\000\000\000\004\147\101\115\101\000\000\257\310\067\005\212"
  "\351\000\000\000\031\164\105\130\164\123\157\146\164\167\141\162"
  "\145\000\101\144\157\142\145\040\111\155\141\147\145\122\145\141"
  "\144\171\161\311\145\074\000\000\000\314\120\114\124\105\377\377"
  "\377\377\277\000\277\277\277\357\357\357\337\337\337\360\360\360"
  "\317\317\317\060\060\060\340\340\340\257\257\257\300\300\300\220"
  "\220\220\320\320\320\357\263\000\337\247\000\177\177\177\100\100"
  "\100\277\233\057\077\077\077\277\257\177\240\240\240\217\217\217"
  "\000\000\000\262\165\071\040\040\040\120\120\120\160\160\160\057"
  "\057\057\137\137\137\140\140\140\337\333\317\317\313\277\277\263"
  "\220\337\253\020\157\157\157\317\307\257\200\200\200\277\237\100"
  "\277\247\137\317\237\017\205\127\052\317\243\037\117\117\117\277"
  "\263\217\277\237\077\246\155\065\017\017\017\260\260\260\020\020"
  "\020\115\063\030\237\177\037\237\207\077\013\007\003\135\103\050"
  "\172\120\047\277\247\140\277\227\037\214\174\155\041\025\012\144"
  "\101\040\257\253\237\237\217\137\245\236\226\054\035\016\257\227"
  "\120\254\234\215\277\243\117\377\377\377\115\023\135\330\000\000"
  "\000\104\164\122\116\123\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\000\161\322\217\022\000\000"
  "\002\033\111\104\101\124\170\332\354\226\131\167\332\060\020\205"
  "\245\261\144\311\013\340\030\014\066\244\115\113\150\113\322\354"
  "\335\327\244\345\377\377\247\172\221\145\113\226\010\165\116\137"
  "\172\174\137\170\220\346\316\365\007\170\006\355\236\050\064\030"
  "\014\006\203\301\277\065\010\037\270\255\204\317\370\036\003\032"
  "\320\335\316\007\170\207\137\276\060\327\003\020\002\276\137\134"
  "\065\031\054\217\023\000\204\116\106\030\343\127\206\020\034\120"
  "\176\234\013\140\162\305\273\006\341\252\074\105\107\270\120\067"
  "\004\020\344\072\325\025\344\075\063\044\210\052\373\267\130\110"
  "\015\221\267\107\216\053\352\035\106\273\006\263\343\352\354\115"
  "\155\240\204\310\333\043\361\000\271\046\101\027\042\115\253\170"
  "\257\161\113\165\010\136\226\022\042\352\011\063\174\013\313\244"
  "\074\053\011\142\055\004\124\225\062\100\354\167\015\124\202\355"
  "\020\224\212\102\215\240\146\240\023\154\364\111\324\353\004\125"
  "\203\056\101\251\317\242\261\116\120\061\060\022\254\064\072\025"
  "\340\164\202\212\201\231\140\251\013\204\314\004\333\006\126\202"
  "\030\217\211\215\140\333\300\116\020\117\255\004\133\006\173\010"
  "\236\331\011\066\006\075\011\066\006\075\011\112\203\276\004\245"
  "\201\040\370\335\116\220\030\011\326\006\025\101\007\310\164\154"
  "\041\010\004\134\003\301\332\340\306\203\134\305\215\347\107\046"
  "\202\004\112\377\134\236\307\114\157\345\145\134\077\040\102\152"
  "\210\213\252\275\074\115\130\150\174\255\373\314\223\167\332\041"
  "\012\202\104\342\107\316\371\222\132\346\002\315\316\115\041\246"
  "\112\173\057\365\367\014\226\353\264\033\342\314\121\332\147\164"
  "\357\144\242\331\132\013\061\072\155\265\207\364\372\321\321\066"
  "\143\240\204\270\153\062\071\153\143\173\375\245\312\243\126\210"
  "\337\143\267\151\317\202\003\207\153\020\311\052\362\103\326\257"
  "\043\176\360\164\346\154\042\377\265\342\323\215\202\277\032\357"
  "\233\225\253\374\375\046\235\337\316\143\373\101\310\222\306\300"
  "\135\155\172\054\030\233\070\037\302\277\276\374\164\120\022\207"
  "\275\066\224\331\125\174\271\130\054\076\304\254\347\212\023\314"
  "\267\171\375\342\362\153\332\323\300\237\337\177\333\156\077\336"
  "\276\317\372\056\131\233\233\171\241\214\077\141\315\363\375\160"
  "\167\200\206\125\167\060\370\117\014\376\010\060\000\151\226\377"
  "\022\137\031\116\172\000\000\000\000\111\105\116\104\256\102\140"
  "\202\000\000\050\165\165\141\171\051\150\151\156\164\166\151\145"
  "\167\057\000\000\003\000\000\000\150\155\057\000\001\000\000\000"
  "" };

static GStaticResource static_resource = { resources_resource_data.data, sizeof (resources_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *resources_get_resource (void);
GResource *resources_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resourcesresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resourcesresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resourcesresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resourcesresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resourcesresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resourcesresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
