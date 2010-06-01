#include <polymake.h>
#include <Set.h>
#include <Array.h>
#include <list>
#include <iostream>


using namespace std;
namespace polymake { namespace tom {

list<Set<int> > rec_subsets(const Set<int> &);

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
				"# Return all non-empty subsets of a given set //set//."
				"# @param Set set"
				"# @return Array<Set>",
				&enumerate_subsets, "enumerate_subsets");



Array<Array<Set<int> > > types_from_vertices(const Array<Array<Set<int> > > vertices) {

	const int r(vertices.size());

	Set<Array<Set<int> > > types;	// will contain the types
	std::list<Array<Set<int> > > mylist;
	
	Array<Set<int> > curr;	// current vertex
	for (int i=0; i<r; ++i) {	// go thru all vertices
		curr = vertices[i];
		std::list<Array<Set<int> > > mylist;	// will contain types
		mylist.push_back(curr);
		//cout<<"curr "<<curr<<endl;
		std::list<Array<Set<int> > >::iterator curr_v = mylist.begin();

		while (curr_v!=mylist.end()) {	// perform BFS on mylist
								
			for (int j = 0; j < curr_v->size(); ++j) {	// go thru entries of current vertex
				Set<int> & set = (*curr_v)[j];	// current entry of curr_v
				
				if (set.size() > 1) {
					
					Array<Set<int> > subsets = enumerate_subsets(set);
					int setsize=set.size();
					
					for (Array<Set<int> >::iterator sit = subsets.begin(); sit != subsets.end(); ++sit) {
					// for each subset of s ...
						if (setsize > sit->size()){
							Array<Set<int> > next = *curr_v;
							next[j] = *sit;	// create a type with current 	position j replaced by that subset
							mylist.push_back(next);
							//cout<<"next "<<next<<endl;
						}
					}
					
					++curr_v;	// proceed
					break;
				}
				else if (j==curr_v->size()-1) {
					++curr_v;
					break;
				}
			}
		}
		
		// now add everything to types
		for (std::list<Array<Set<int> > >::iterator l = mylist.begin(); l!=mylist.end(); ++l) {
			types += *l;
		}
	}
		
	Array<Array<Set<int> > > ret(types.begin(),types.end());
	return ret;
}



Function4perl(&types_from_vertices, "types_from_vertices");

} }

