#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include "polymake/list"
#include <iostream>


using namespace std;
namespace polymake { namespace tom {

list<Set<int> > rec_subsets(const Set<int> &);

// list all subsets of a given set
Array<Set<int> > enumerate_subsets(const Set<int> & s) {
	list<Set<int> > r;
	
	r = rec_subsets(s);
	
	Array<Set<int> > ret(r.begin(),r.end());
	return ret;
}

list<Set<int> > rec_subsets(const Set<int> & s) {
	list<Set<int> > r;

	if (s.size()==1) {
		r.push_back(s);
		return r;
	}
	Set<int>::const_iterator it = s.end(); --it;
	int curr=*it;
	Set<int> t; t.push_back(curr);
	r = rec_subsets(s-t);
	
	list<Set<int> > ret;
	Set<int> l; l.push_back(curr); ret.push_back(l);
	for (list<Set<int> >::iterator it=r.begin(); it!=r.end(); ++it) {
		ret.push_back(*it);
		Set<int> l = *it; l.push_back(curr);
		ret.push_back(l);
	}
	
	return ret;

}	
	
UserFunction4perl("# @category Utilities"
				"# Return all non-empty subsets of a given set //s//."
				"# @param Set s"
				"# @return Array<Set>",
				&enumerate_subsets, "enumerate_subsets");



// Array<Array<Set<int> > > enumerate_ordered_partitions(const Set<int> & s) {
// 	list<list<Set<int> > > r;
// 	
// 	r=rec_ordps(s);
// 	
// 	Array<Array<Set<int > > > ret(r.begin(), r.end());
// }
// 
// list<list<Set<int> > > rec_ordps(const Set<int> & s) {
// 	list<list<Set<int> > > r;
// 	
// 	Array<Set<int> > all_ss=enumerate_subsets(s);
// 
// 	for (Array<Set<int> >::const_iterator it=all_ss.begin(); it!=all_ss.end(); ++it) {
// 	
// 		Set<int> new_s=s-*it;
// 		if (new_s.size()==0) {
// 			;
// 		} else {
// 		
// 		}
// 	}
// 
// }


void all_subtypes(std::list<Array<Set<int> > >&, const Array<Set<int> >);


// compute all types_from_vertices
// works only for toms in general position
// computes subtypes of each vertex and then unites these sets -> could be done better but does not seem to be a bottle neck
Array<Array<Set<int> > > types_from_vertices(const Array<Array<Set<int> > > vertices) {

	Set<Array<Set<int> > > types;	// will contain the types
	
	Array<Set<int> > curr;	// current vertex
	for (Array<Array<Set<int> > >::const_iterator it = vertices.begin(); it != vertices.end(); ++it) { 	// go thru all vertices
		std::list<Array<Set<int> > > mylist; // all types containing current vertex
		all_subtypes(mylist, *it);	
		
		// now add everything to types
		for (std::list<Array<Set<int> > >::iterator l = mylist.begin(); l != mylist.end(); ++l) {
			types += *l;
		}
	}
		
	Array<Array<Set<int> > > ret(types.begin(),types.end());
	return ret;
}


std::list<Array<Set<int> > > fold_sets(const std::list<Array<Set<int> > > & prev, const Array<Array<Set<int> > > & sets, int current) {

	int n = sets.size();
	
	Array<Set<int> > c = sets[current];	// next entry
	
	std::list<Array<Set<int> > > r;
	
	for (std::list<Array<Set<int> > >::const_iterator it = prev.begin(); it != prev.end(); ++it) {
		for (Array<Set<int> >::const_iterator s = c.begin(); s != c.end(); ++s) {
			Array<Set<int> > next = *it;
			next[current] = *s;
			r.push_back(next);
		}
	}
	
	if (current == n-1) return r;
	
	return fold_sets(r, sets, current + 1);
}

// computes all subtypes of a given type curr
void all_subtypes(std::list<Array<Set<int> > > & ret, const Array<Set<int> > curr) {

	int n = curr.size();
	Array<Set<int> > init(n);

	ret.push_back(init);
	
	Array<Array<Set<int> > > subsetlist(n);
	int i=0;
	for (Array<Set<int> >::const_iterator it = curr.begin(); it != curr.end(); ++it) {
		subsetlist[i] = enumerate_subsets(*it);
		++i;
	}

	ret = fold_sets(ret, subsetlist, 0);
}

Array<Array<Set<int> > > star_of_type(const Array<Set<int> > curr) {
	std::list<Array<Set<int> > > r;
	all_subtypes(r, curr);
	Array<Array<Set<int> > > ret(r.begin(), r.end());
	return ret;
}


Function4perl(&types_from_vertices, "types_from_vertices");

Function4perl(&star_of_type, "star_of_type");


} } // end of namespaces

