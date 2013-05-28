// Copyright (c) 2013 Silke Horn
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
#include "polymake/list"
#include <iostream>

using namespace std;
namespace polymake { namespace tom {


Array<Array<Set<int> > > topes_from_vertices(const Array<Array<Set<int> > > vertices) {
	
	const int r(vertices.size());

	Set<Array<Set<int> > > topes;
	std::list<Array<Set<int> > > mylist;
	
	Array<Set<int> > curr;
	for (int i=0; i<r; ++i) {
		curr = vertices[i];
		std::list<Array<Set<int> > > mylist;
		mylist.push_back(curr);
		std::list<Array<Set<int> > >::iterator it = mylist.begin();

		while (it!=mylist.end()) {
								
			for (int j = 0; j<it->size(); ++j) {
				Set<int> & set = (*it)[j];
				
				if (set.size() > 1) {
					
					for (Set<int>::iterator elt = set.begin(); elt != set.end(); ++elt) {
						Array<Set<int> > next = *it;
						
						Set<int> S; S.push_back(*elt);
						next[j] = S;
						
						mylist.push_back(next);
						
					}
					
					it = mylist.erase(it);
					break;
				}
				else if (j==it->size()-1) {
					++it;
					break;
				}
			}
		}
		
		for (std::list<Array<Set<int> > >::iterator l = mylist.begin(); l!=mylist.end(); ++l) {
			topes += *l;
		}
	}
	
	Array<Array<Set<int> > > ret(topes.begin(),topes.end());
	return ret;
}


Function4perl(&topes_from_vertices, "topes_from_vertices");

} }
