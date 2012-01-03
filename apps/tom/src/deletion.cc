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

namespace polymake { namespace tom {


perl::Object deletion(const Array<Array<Set<int> > > &vertices, const int n, const int d, int pos) {
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


Function4perl(&deletion, "deletion");

} }
