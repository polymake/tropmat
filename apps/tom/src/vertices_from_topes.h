// Copyright (c) 2012 Silke Möser
// http://solros.de/polymake/tropmat
// 
// This file is part of the polymake extension tropmat.
// 
// tropmat is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// tropmat is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with tropmat.  If not, see <http://www.gnu.org/licenses/>.


#ifndef TOM_VERTICES_FROM_TOPES_H
#define TOM_VERTICES_FROM_TOPES_H

#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <vector>
#include "polymake/list"
#include "rank.h"


namespace polymake { namespace tom {


Array<Array<Set<int> > > vertices_from_topes(const Array<Array<Set<int> > > topes, const int d);

typedef std::vector<int> tope;
typedef std::vector<Set<int> > tomtype;
typedef Set<Array<Set<int> > > vertexset;

tomtype union_of_types(const tomtype &, const tomtype &);
tomtype union_of_types(const tope &, const tope &);
tomtype union_of_types(const tope &, const tomtype &);
tomtype union_of_types(const tomtype &, const tope &);

}}

#endif
