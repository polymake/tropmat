#include "comparable.h"


namespace polymake { namespace tom {


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

bool comparable(const Array<Set<int> > & type1, const Array<Set<int> > & type2, int d) {

	Array<Array<Set<int>, Set<int> > > nb;
	neighbours(nb, type1,type2,d);

	for (int i=1; i<=d; ++i) {	// check whether there is a cycle starting with i

		Set<int> undir;	// will contain all vertices that can be reached from i via undir edges
		Set<int> dir;	// will contain all vertices that can be reached from i via at least one dir edge

		undir.insert(i);

		int x = 0;
		
		while (x<dir.size()+undir.size()) {

			x = dir.size()+undir.size();
			
			// go thru all vertices in undir
			for (Set<int>::iterator curr=undir.begin(); curr!=undir.end(); ++curr) {
				// go thru all undir-neighbours of the current vertex
				for (Set<int>::iterator nu= nb[*curr-1][1].begin(); nu!=nb[*curr-1][1].end(); ++nu) {
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


Function4perl(&comparable, "comparable(Array Array $)");
InsertEmbeddedRule(	"# @category Axioms\n"
					"# Two types are __comparable__ if their comparability graph is acyclic.\n"
					"# @param Array<Set<Int>> type1\n"
					"# @param Array<Set<Int>> type2\n"
					"# @return Bool\n"
					"user_function comparable(Array Array) {\n"
					"	comparable($_[0], $_[1],max_entry($_[0],$_[1]));}\n");

void neighbours(Array<Array<Set<int>, Set<int> > > & nb, const Array<Set<int> > & type1, const Array<Set<int> > & type2, int d) {

	nb.resize(d);
	
	for (int j=0; j<d; ++j) {
		nb[j].resize(2);
	}
		
	for (int i=0; i<type1.size(); ++i) {	// go thru all sets in type1 and type2
		
		for (Set<int>::const_iterator s=type1[i].begin(); s!=type1[i].end(); ++s) {
			for (Set<int>::const_iterator s2 = type2[i].begin(); s2!=type2[i].end(); ++s2) {
				//cout<<*s<<" "<<*s2<<endl;
				if (*s!=*s2) {
					if (type1[i].contains(*s2) && type2[i].contains(*s)) {
						nb[*s-1][1] += *s2;
						//cout<<"undir"<<endl;
					} else {
						nb[*s-1][0] += *s2;
						//cout<<"dir"<<endl;
					}
				}
			}
		}
	}

//	for (int k=0; k<d; ++k) {
//		cout<<nb[k][0]<<endl;
//		cout<<nb[k][1]<<endl;
//		cout<<endl;
//	}
}


} }

