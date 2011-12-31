#include "polymake/client.h"
#include "polymake/list"
#include <iostream>
#include "types_from_vertices.h"
#include "refinement.h"


using namespace std;
namespace polymake { namespace tom {

list<partition> rec_ordps(const Set<int> & s);

Array<partition> enumerate_ordered_partitions(const Set<int> & s) {
	list<partition> r = rec_ordps(s);
	
	Array<partition> ret(r.begin(), r.end());
	return ret;
}

UserFunction4perl(	"# @category Utilities\n"
					"# Enumerate all ordered partitions of the set //S//."
					"# @param Set<Int> S\n"
					"# @return Array<Array<Set<Int>>>\n",
					&enumerate_ordered_partitions, "enumerate_ordered_partitions");

list<partition> rec_ordps(const Set<int> & s) {

	list<partition> ret;

	if (s.empty()) {
		partition empty_p;
		ret.push_back(empty_p);
		return ret;
	}
	
	Array<Set<int> > all_ss = enumerate_subsets(s);

	for (Array<Set<int> >::const_iterator it = all_ss.begin(); it != all_ss.end(); ++it) {
		
		Set<int> rest = s - *it; // remaining elts
		
		list<partition> l = rec_ordps(rest);
		
		for (list<partition>::const_iterator pit = l.begin(); pit != l.end(); ++pit) {
			partition p = *pit;
			p.resize(pit->size()+1);
			p[p.size()-1] = *it;
			ret.push_back(p);
		}
	}
	
	return ret;
}


// all subtypes of a given type curr
void all_subtypes_nongen(std::list<tomtype> & ret, const tomtype curr, int d) {
	
	Set<tomtype> r; 	// will contain types
	
	Set<int> all;
	for (int i=1; i<=d; ++i) {
		all += i;
	}

	Array<partition> ops = enumerate_ordered_partitions(all);	// all ordered partitions of [d]
	
	for (Array<partition>::const_iterator it = ops.begin(); it != ops.end(); ++it) {
		r += refinement(curr, *it);	// refine curr with everyone
	}
	
	ret = std::list<tomtype>(r.begin(), r.end());
}

Array<Array<Set<int> > > star_of_type_nongen(const Array<Set<int> > curr, int d) {
	std::list<Array<Set<int> > > r;
	all_subtypes_nongen(r, curr, d);
	Array<Array<Set<int> > > ret(r.begin(), r.end());
	return ret;
}

Function4perl(&star_of_type_nongen, "star_of_type_nongen");


Array<tomtype> types_from_vertices_nongen(const Array<tomtype> & vertices, int d) {
	Set<tomtype> types;		// will contain types
	
	for (Array<tomtype>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		list<tomtype> star;
		all_subtypes_nongen(star, *it, d);
		
		for (list<tomtype>::const_iterator sit = star.begin(); sit != star.end(); ++sit) {
			types += *sit;
		}
	}
	return types;
}


Function4perl(&types_from_vertices_nongen, "types_from_vertices_nongen");



}}