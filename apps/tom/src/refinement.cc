#include "polymake/client.h"
#include "refinement.h"

namespace polymake { namespace tom {


Set<int> ref_one_comp(const Set<int> & s, const partition & op);

tomtype refinement(const tomtype & A, const partition & op) {
	tomtype r(A.size());
	
	int i=0;
	for (tomtype::const_iterator it = A.begin(); it != A.end(); ++it) {
		r[i] = ref_one_comp(*it, op); 
		++i;
	}
	
	return r;
}

// this version also works with incomplete partitions
tomtype refinement_gen(const tomtype & A, const partition & op, int d) {
	Set<int> u;
	for (int i=0; i<op.size(); ++i) {
		u = u + op[i];
	}
	
	if (u.size() == d) 
		return refinement(A, op);
	
	Set<int> all;
	for (int i=1; i<=d; ++i) {
		all += i;
	}
	
	partition nop = op;
	nop.resize(op.size()+1);
	nop[nop.size()-1] = all-u;
	
	return refinement(A, nop);
}

Function4perl(&refinement_gen, "refinement");


Set<int> ref_one_comp(const Set<int> & s, const partition & op) {
	for (partition::const_iterator it = op.begin(); it != op.end(); ++it) {
		Set<int> c = s*(*it);
		if (!c.empty()) {
			return c;
		}
	}
}

}}