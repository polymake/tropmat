#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"


namespace polymake { namespace tom {


int rank(const Array<Set<int> > &type, int d) {
	
	// TODO: check that type actually is a type
	
	Set<Set<int> > tmp(type.begin(), type.end());
	Set<Set<int> > tmp2;

	Set<int> S;

	for (int i=1; i<=d; ++i) {
		S += i;
		for (Set<Set<int> >::iterator it = tmp.begin(); it!=tmp.end(); ++it) {
			if (it->contains(i)) {
				S += *it;
			} else {
				tmp2 += *it;
			}
		}
		tmp2 += S;
		S.clear();
		tmp = tmp2;
		tmp2.clear();
	}
	
	return tmp.size();
}



Function4perl(&rank, "rank");

} }
