/* Copyright (c) 1997-2010
   Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Darmstadt, Germany)
   http://www.polymake.org

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version: http://www.gnu.org/licenses/gpl.txt.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
--------------------------------------------------------------------------------
   $Project: polymake $$Id: bindings.cc 9716 2010-06-28 22:22:03Z gawrilow $
*/

///==== this line controls the automatic file splitting: max.instances=40

#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
namespace polymake { namespace common { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0>
   FunctionInterface4perl( new, T0 ) {
      WrapperReturnNew(T0, () );
   };

   template <typename T0, typename T1>
   FunctionInterface4perl( new_X, T0,T1 ) {
      perl::Value arg0(stack[1]);
      WrapperReturnNew(T0, (arg0.get<T1>()) );
   };

   OperatorInstance4perl(Binary_add, perl::Canned< const Set< int > >, perl::Canned< const Set< int > >);
   Class4perl("Polymake::common::Set__Array__Set__Int", Set< Array< Set< int > > >);
   FunctionInstance4perl(new, Set< Array< Set< int > > >);
   OperatorInstance4perl(BinaryAssign_add, perl::Canned< Set< Array< Set< int > > > >, perl::Canned< const Array< Set< int > > >);
   FunctionInstance4perl(new_X, Set< int >, perl::Canned< const pm::Series<int, true> >);
   OperatorInstance4perl(BinaryAssign_add, perl::Canned< Set< Array< Set< int > > > >, perl::Canned< const Set< Array< Set< int > > > >);
   OperatorInstance4perl(Binary__ne, perl::Canned< const Set< int > >, perl::Canned< const Set< int > >);
   OperatorInstance4perl(assign, Set< int >, perl::Canned< const Array< Set< int > > >);
   Class4perl("Polymake::common::Set__Array__Int", Set< Array< int > >);
   FunctionInstance4perl(new, Set< Array< int > >);
   FunctionInstance4perl(new_X, Set< Array< Set< int > > >, perl::Canned< const Array< Array< Set< int > > > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
