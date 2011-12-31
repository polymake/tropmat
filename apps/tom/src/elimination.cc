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

