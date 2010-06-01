#include <polymake.h>
#include <Set.h>
#include <Array.h>

namespace polymake { namespace tom {


perl::Object contraction(const Array<Array<Set<int> > > &vertices, const int n, const int d, int pos) {
	const int r(vertices.size()), c(vertices[0].size());
	
	perl::Object p("TropicalOrientedMatroid");
	Array<Array<Set<int> > > new_v;
	
	new_v.resize(r);
	for (int i=0; i<r; ++i) {
		new_v[i].resize(c-1);
	}

	// copy vertices to new_v leaving out column pos
	for (int i=0; i<r; ++i) {
		for (int j=0; j<c; ++j) {
			if (j < pos) {
				new_v[i][j]=vertices[i][j];
			} else if (j > pos) {
				new_v[i][j-1]=vertices[i][j];
			}
		}
	}
	
	
	
	p.take("VERTICES") << new_v;
	
	return p;
}


Function4perl(&contraction, "contraction");

} }
