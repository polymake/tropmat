#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"

namespace polymake { namespace tom {


bool boundary_axiom(const Array<Array<Set<int> > > &vertices, const int n, const int d) {

	const int r(vertices.size()), c(vertices[0].size());

	bool check;
	
	for (int i=1; i<= d; ++i){			// go thru [d]
		for (int j=0; j<r; ++j){		// go thru all types (= rows of matrix)
			check=1;

			for (int k=0; k<c; ++k){	// go thru all sets in current type
				if (! vertices[j][k].contains(i)){	// if current set does not contain i...
					check = 0;
					break;				// ... then we need not examine this type any further
				}
			}
			if (check==1){			// if this loop is never stopped via break, then we found the i-th boundary and check is still true
				break;				// so we can proceed to the next i 
			}
		}
		if (check == 0) {	// if there is no i-th boundary for some type
			return 0;		// then the axiom is not satisfied

		}
	}
	return 1;
}


Function4perl(&boundary_axiom, "boundary_axiom");

} }
