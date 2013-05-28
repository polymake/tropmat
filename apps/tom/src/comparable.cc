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
#include "utils.h"
#include <iostream>
#include "comparable.h"


namespace polymake { namespace tom {

void neighbours(Array<Array<Set<int>, Set<int> > > &, const Array<Set<int> > &, const Array<Set<int> > &, int);

// check whether each pair of vertices is comparable
// d is the rank
bool comparability_axiom(const Array<Array<Set<int> > > types, int d) {
	for (Array<Array<Set<int> > >::const_iterator it=types.begin(); it!=types.end();) {
		Array<Array<Set<int> > >::const_iterator it2=++it;
		for ( ; it2!=types.end(); ++it2) {
			if (!comparable(*it,*it2,d)) {
				// print(*it); print(*it2);
				return 0;
			}
		}
	}
	return 1;
}

Function4perl(&comparability_axiom, "comparability_axiom(Array<Array<Set<Int>>>,$)");

// check whether two types type1 and type2 are comparable
// d is the rank
bool comparable(const Array<Set<int> > & type1, const Array<Set<int> > & type2, int d) {

	Array<Array<Set<int>, Set<int> > > nb;
	neighbours(nb, type1, type2, d);	// for every vertex i in [d] compute two lists of neighbours: the first one for directed edges i -> j, the second for undirected edges i -- j

	for (int i=1; i<=d; ++i) {	// check whether there is a cycle starting with i

		Set<int> undir;	// will contain all vertices that can be reached from i via undir edges
		Set<int> dir;	// will contain all vertices that can be reached from i via at least one dir edge

		undir.insert(i);

		int x = 0; // number of vertices reachable from i (so far)
		
		while (x < dir.size()+undir.size()) {	// we can stop if dir and undir did not change

			x = dir.size()+undir.size();
			
			// go thru all vertices in undir
			for (Set<int>::iterator curr = undir.begin(); curr != undir.end(); ++curr) {
				// go thru all undir-neighbours of the current vertex
				for (Set<int>::iterator nu = nb[*curr-1][1].begin(); nu != nb[*curr-1][1].end(); ++nu) {
						undir.insert(*nu);	// and add to undir
				}
				
				// go thru all dir-neighbours of the current vertex
				for (Set<int>::iterator nd= nb[*curr-1][0].begin(); nd!=nb[*curr-1][0].end(); ++nd) {
					if (*nd == i) {		// if one neighbour is the start vertex i ...
						return 0;		// ... we found a cycle
					}
					dir.insert(*nd);	// otherwise add to dir
				}
			}
						
			// go thru all vertices in dir
			for (Set<int>::iterator curr=dir.begin(); curr!=dir.end(); ++curr) {
				// go thru all undir-neighbours of the current vertex
				for (Set<int>::iterator nu= nb[*curr-1][1].begin(); nu!=nb[*curr-1][1].end(); ++nu) {
					if (*nu ==i) {return 0;}	// cycle
					dir.insert(*nu);	// otherwise add to dir
				}
				// go thru all dir-neighbours of the current vertex
				for (Set<int>::iterator nd= nb[*curr-1][0].begin(); nd!=nb[*curr-1][0].end(); ++nd) {
					if (*nd == i) {		// if one neighbour is the start vertex i ...
						return 0;		// ... we found a cycle
					}
					dir.insert(*nd);	// otherwise add to dir
				}
				
			}
		}
	}	
	
	return 1;
}



// determine the maximal entry of a given type a
int max_entry(const Array<Set<int> > & a) {
	int max=1;
	for(Array<Set<int> >::const_iterator it=a.begin(); it!=a.end(); ++it) {
		for(Set<int>::const_iterator it2=it->begin(); it2!=it->end(); ++it2) {
			if (*it2>max) {max=*it2;}
		}
	}

	return max;
}

int max_entry(const Array<Set<int> > & a, const Array<Set<int> > & b) {
	int ma=max_entry(a);
	int mb=max_entry(b);
	if (ma>mb) {return ma;} else {return mb;}
}




// determine the neighbours of each vertex in the comparability graph of two
// types type1 and type2
// the result is stored in nb
void neighbours(Array<Array<Set<int>, Set<int> > > & nb, const Array<Set<int> > & type1, const Array<Set<int> > & type2, int d) {

	nb.resize(d);	// one for each vertex in [d]
	
	for (int j=0; j<d; ++j) {
		nb[j].resize(2);	// every vertex needs two lists of neighbours: for directed and undirected edges
	}
		
	for (int i=0; i<type1.size(); ++i) {	// go thru all positions in type1 and type2
		
		// in each position check for each pair of entries whether there is an edge between them
		for (Set<int>::const_iterator s = type1[i].begin(); s != type1[i].end(); ++s) {
			for (Set<int>::const_iterator s2 = type2[i].begin(); s2 != type2[i].end(); ++s2) {
				//cout<<*s<<" "<<*s2<<endl;
				if (*s!=*s2) {
					if (type1[i].contains(*s2) && type2[i].contains(*s)) {
						nb[*s-1][1] += *s2;	// undirected edge
						//cout<<"undir"<<endl;
					} else {
						nb[*s-1][0] += *s2;	// directed edge
						//cout<<"dir"<<endl;
					}
				}
			}
		}
	}
}


bool comp4perl(const Array<Set<int> >& A, const Array<Set<int> >& B) {
	return comparable(A, B, max_entry(A, B));
}

UserFunction4perl(	"CREDIT tropmat\n\n"
					"# @category Axioms\n"
					"# Two types are __comparable__ if their comparability graph is acyclic.\n"
					"# @param Array<Set<Int>> A\n"
					"# @param Array<Set<Int>> B\n"
					"# @return Bool\n",
					&comp4perl, "comparable");


} }

