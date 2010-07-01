/* Copyright (c) 1997-2010
   Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Darmstadt, Germany)
   http://www.polymake.de

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version: http://www.gnu.org/licenses/gpl.txt.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
--------------------------------------------------------------------------------
   $Project: polymake $$Id: bindings.cc 9691 2010-05-28 23:47:18Z gawrilow $
*/

#define INDEX_CHECKS 1
#define DIMENSION_CHECKS 1

///==== this line controls the automatic file splitting: max.instances=40

#include <Set.h>
#include <Array.h>

namespace polymake { namespace common {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0, typename T1>
   FunctionInterface4perl( new_X, T0,T1 ) {
      perl::Value arg0(stack[1]);
      WrapperReturnNew(T0, (arg0.get<T1>()) );
   };

   OperatorInstance4perl(Binary_add, perl::Canned< const Set< int > >, perl::Canned< const Set< int > >);
   FunctionInstance4perl(new_X, Set< int >, perl::Canned< const pm::Series<int, true> >);
   DisabledFunction4perl(:mul, perl::TryCanned< const Array< int > >, perl::Canned< const Set< int > >);
   DisabledFunction4perl(:mul, perl::Canned< const Set< int > >, perl::TryCanned< const Array< int > >);
   DisabledFunction4perl(:_eq, perl::TryCanned< const Array< int > >, perl::Canned< const Set< int > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} }
