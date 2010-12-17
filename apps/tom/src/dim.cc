#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"

namespace polymake { namespace tom {

int dim(const Array<Array<Set<int> > > &types) {
	int d = 0;

	const int r(types.size());
	const int c(types[0].size());

	for (int i=0; i<r; ++i) {
		for (int j=0; j<c; ++j) {
			const Set<int> S = (types[i][j]); 
			for (Set<int>::const_iterator it = S.begin(); it != S.end(); ++it) {
				if (*it > d) {
					d= *it;
				}
			}
		}
	}
	return d;
}

Function4perl(&dim, "dim");

} }
