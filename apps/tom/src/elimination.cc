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


#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <iostream>
#include "utils.h"

using namespace pm;

namespace polymake { namespace tom {

bool is_elim(const Array<Set<int> >& cand, const Array<Set<int> > & type1, const Array<Set<int> > & type2, int pos);

Array<Set<int> > elimination (const Array<Set<int> > & type1, const Array<Set<int> > & type2, int pos, const Array<Array<Set<int> > > & all_types) {

	for (Array<Array<Set<int> > >::const_iterator it = all_types.begin(); it != all_types.end(); ++it) {
		if (is_elim(*it, type1, type2, pos-1)) 
			return *it;
	}
	return Array<Set<int> >();
}

Function4perl(&elimination, "elimination");

bool is_elim(const Array<Set<int> >& cand, const Array<Set<int> > & type1, const Array<Set<int> > & type2, int pos){
	
	Set<int> Aj = type1[pos];
	Set<int> Bj = type2[pos];
	Set<int> Cj = Aj + Bj;

	if (cand[pos] != Cj) return 0;
	
	for (int i = 0; i < cand.size(); ++i) {
		if (cand[i] != type1[i] && cand[i] != type2[i] && cand[i] != type1[i]+type2[i]) 
			return 0;	
	}
	return 1;
}


bool elim_axiom(const Array<Array<Set<int> > > & all_types, int n) {
	Array<Array<Set<int> > >::const_iterator it, it2;
	for (it = all_types.begin(); it != all_types.end(); ++it) {
		it2 = it; ++it2;
		for (; it2 != all_types.end(); ++it2) {
		
			for (int i=1; i<=n; ++i) {
				Array<Set<int> > e = elimination(*it, *it2, i, all_types); 
				if (e.size()==0) return 0;
			}
		}
	}
	return 1;
}

Function4perl(&elim_axiom, "elim_axiom");
} }

