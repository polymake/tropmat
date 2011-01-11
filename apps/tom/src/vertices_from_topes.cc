#include "vertices_from_topes.h"

namespace polymake { namespace tom {



Array<Array<Set<int> > > vertices_from_topes(const Array<Array<Set<int> > > topes, const int d) {

	std::vector<tope> t = types2topes(topes);
	Set<tomtype> vertices;
	
	int ntopes=t.size();
	
	for (int i=0; i<ntopes-1; ++i) {
		vertices_in_nh(vertices,d,i,t);
	
// 		for (int j=i+1; j<ntopes; ++j) {
// 			if (dist(t[i],t[j])==d-1) {
// 				std::vector<Set<int> > u=tope_union(t[i],t[j]);
// 				if (acyclic(u,d)) {
// 					vertices.push_back(u);
// 				}
// 			}
// 		}
	}
	Array<Array<Set<int> > > ret= conv_types(vertices);
	return ret;
}

Function4perl(&vertices_from_topes, "vertices_from_topes");




void vertices_in_nh(Set<tomtype>& vertices, int d, int i, const std::vector<tope> & all) {

	std::vector<tope> nh=neighbourhood(d,i,all);
	
	get_vertices_rec(vertices,d,i,i+1,tope2type(all[i]),nh);
	
}

void get_vertices_rec(Set<tomtype>& vertices, int d, int i, int j, const tomtype curr, const std::vector<tope> & all) {

	for (int k=j; k<all.size(); ++k) {

		tomtype newtype=union_of_types(curr,all[k]);
		if (acyclic(newtype,d)) {
			if (nedges(curr)==d-1) {
				vertices.push_back(curr);
			} else {
				get_vertices_rec(vertices,d,i,k+1,newtype,all);	
			}
		}
	}
}


std::vector<tope> neighbourhood(int d, int i, const std::vector<tope> & all) {
	std::vector<tope> nh;
	for (int j=i+1; j<all.size(); ++j) {
		if (dist(all[i],all[j])<= d-1) {
			nh.push_back(all[j]);
		}
	}
	return nh;
}

tomtype union_of_types(const tomtype & a, const tomtype & b) {
	tomtype u;
	
	for (int i=0; i<a.size(); ++i){
		Set<int> s=a[i]+b[i];
		u.push_back(s);
	}
	return u;
}
tomtype union_of_types(const tope & a, const tope & b) {
	return union_of_types(tope2type(a),tope2type(b));
}
tomtype union_of_types(const tomtype & a, const tope & b) {
	return union_of_types(a,tope2type(b));
}
tomtype union_of_types(const tope & a, const tomtype & b) {
	return union_of_types(tope2type(a),b);
}


bool acyclic(const tomtype & u, int d) {
	Array<Set<int> > a(u.begin(),u.end());
	
	int edges=nedges(u);
	int r=rank(a,d);
	if (r==d-edges) {return 1;} else {return 0;}
}

int nedges(const tomtype & t) {
	int edges=0;
	for (tomtype::const_iterator it=t.begin(); it!=t.end(); ++it) {
		edges+= it->size()-1;
	}
	return edges;
}

int dist(const tope & a, const tope & b) {
	int n=a.size();
	int count=0;
	
	for (int i=0; i<n; ++i) {
		if (a[i]!=b[i]) { count++; }
	}
	return count;
}




std::vector<tope> types2topes(const Array<Array<Set<int> > > & types) {
	std::vector<tope> r;

	for (Array<Array<Set<int> > >::const_iterator it=types.begin(); it!=types.end(); ++it) {
		
		r.push_back(type2tope(*it));
	}
	return r;
}

tope type2tope(const Array<Set<int> >& type) {
	tope t;
	for (Array<Set<int> >::const_iterator it=type.begin(); it!=type.end(); ++it) {
		for (Set<int>::const_iterator sit=it->begin(); sit!=it->end();++sit) {
			t.push_back(*sit);
		}
	}
	return t;
}

UserFunction4perl("# @category Utilities"
				"# @param Array<Array<Set>> types"
				"# @return Array<Array>",
				&types2topes, "types2topes");


UserFunction4perl("# @category Utilities"
				"# @param Array<Set> type"
				"# @return Array",
				&type2tope, "type2tope");


tomtype tope2type(const tope t) {
	tomtype ret;
	
	for(tope::const_iterator it=t.begin(); it!=t.end(); ++it) {
		Set<int> curr;
		curr.push_back(*it);
		ret.push_back(curr);
	}
	return ret;
}

Array<Array<Set<int> > > conv_types(const Set<tomtype> & types)
{//convert types to polymake form
	std::list<Array<Set<int> > > r;

	for (Set<tomtype>::const_iterator it=types.begin(); it!=types.end(); ++it) {
		Array<Set<int> > type(it->begin(),it->end());
		r.push_back(type);
	}

	Array<Array<Set<int> > > ret(r.begin(),r.end());

	return ret;
}


Array<Array<Set<int> > > topes2types(const std::vector<tope> & topes)
{
	std::vector<Array<Set<int> > > ret;

	for (std::vector<tope>::const_iterator it=topes.begin(); it!=topes.end(); ++it) {
		tomtype ctype;
		
		for (tope::const_iterator it2=it->begin(); it2!=it->end(); ++it2) {
			Set<int> l; 
			l.push_back(*it2);
			ctype.push_back(l);
		}
		Array<Set<int> > ptype(ctype.begin(),ctype.end());
		ret.push_back(ptype);
	}

	Array<Array<Set<int> > > r(ret.begin(),ret.end());

	return r;
}


}}	//namespace end