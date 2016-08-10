// Copyright (c) 2013-2014 Silke Horn
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
#include "polymake/list"
#include <iostream>
#include "types_from_vertices.h"
#include "refinement.h"
#include "utils.h"


using namespace std;
namespace polymake { namespace tom {

list<partition> rec_ordps(const Set<int> & s);

Array<partition> enumerate_ordered_partitions(const Set<int> & s) {
	list<partition> r = rec_ordps(s);
	
	Array<partition> ret(r.begin(), r.end());
	return ret;
}

UserFunction4perl("# @category Utilities\n"
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
void all_subtypes_nongen(std::list<pmtomtype> & ret, const pmtomtype curr, int d) {
	
	Set<pmtomtype> r; 	// will contain types
	
	Set<int> all;		// the set [d]
	for (int i=1; i<=d; ++i) {
		all += i;
	}

	Array<partition> ops = enumerate_ordered_partitions(all);	// all ordered partitions of [d]
	
	for (Array<partition>::const_iterator it = ops.begin(); it != ops.end(); ++it) {
		r += refinement(curr, *it);	// refine curr with everyone
	}
	
	ret = std::list<pmtomtype>(r.begin(), r.end());
}

int max_entry(const Array<Set<int> > & a);

Array<Array<Set<int> > > star_of_type_nongen(const Array<Set<int> > curr) {
	std::list<Array<Set<int> > > r;
	all_subtypes_nongen(r, curr, max_entry(curr));
	Array<Array<Set<int> > > ret(r.begin(), r.end());
	return ret;
}

Function4perl(&star_of_type_nongen, "star_of_type_nongen");


Array<Array<int> > tom_convex_hull_nongen(const Array<Set<int> > curr) {
	Array<Array<Set<int> > > star = star_of_type_nongen(curr);
	
	std::list<Array<int> > r;
	
	for (Array<Array<Set<int> > >::const_iterator it = star.begin(); it != star.end(); ++it) {
		if (isTope(*it)) {
			r.push_back(pmtope(*it));
		}
	}
	
	Array<Array<int> > ret(r.begin(), r.end());
	return ret;
}

Function4perl(&tom_convex_hull_nongen, "tom_convex_hull_nongen");




Array<pmtomtype> types_from_vertices_nongen(const Array<pmtomtype> & vertices, int d) {
	Set<pmtomtype> types;		// will contain types
	
	for (Array<pmtomtype>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		list<pmtomtype> star;
		all_subtypes_nongen(star, *it, d);
		
		for (list<pmtomtype>::const_iterator sit = star.begin(); sit != star.end(); ++sit) {
			types += *sit;
		}
	}
	return Array<pmtomtype>(types.begin(),types.end());
}


Function4perl(&types_from_vertices_nongen, "types_from_vertices_nongen");



}}
