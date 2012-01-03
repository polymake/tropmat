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
