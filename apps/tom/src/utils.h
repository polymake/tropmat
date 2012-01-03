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


#ifndef TOM_UTILS_H
#define TOM_UTILS_H


#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <vector>
#include <iostream>
#include "vertices_from_topes.h"

namespace polymake { namespace tom {

void print(const tope &);
void print(const tomtype &);
void print(const std::vector<tope> &);
void print(const std::vector<tomtype> &);
void print(const Set<tomtype> &);
void print(const Array<Set<int> > &); 
void print(const vertexset &);


tope type2tope(const Array<Set<int> >&);
std::vector<tope> types2topes(const Array<Array<Set<int> > > &);

tomtype tope2type(const tope &);
Array<Array<Set<int> > > topes2types(const std::vector<tope> & topes);

Array<Set<int> > pmtype(const tomtype &);

}}


#endif
