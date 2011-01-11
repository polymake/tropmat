#include "vertices_from_topes.h"
#include "utils.h"
#include "comparable.h"

namespace polymake { namespace tom {



Array<Array<Set<int> > > vertices_from_topes(const Array<Array<Set<int> > > topes, const int d) {

	std::vector<tope> t = types2topes(topes);
	vertexset vertices;
	
	for (int i=0; i<int(t.size())-1; ++i) {
		vertexset newvertices;
		vertices_in_nh(newvertices,d,i,t);
		vertices+=newvertices;
	}
	Array<Array<Set<int> > > ret(vertices.begin(), vertices.end());
	return ret;
}

Function4perl(&vertices_from_topes, "vertices_from_topes");

Array<Array<Set<int> > > vertices_from_topes_nongen(const Array<Array<Set<int> > > topes, const int d) {

	std::vector<tope> t = types2topes(topes);
	vertexset vertices;
	
	
	for (int i=0; i<int(t.size())-1; ++i) {
		vertices_in_nh_nongen(vertices,d,i,t);
	}
	Array<Array<Set<int> > > ret(vertices.begin(), vertices.end());
	return ret;
}

Function4perl(&vertices_from_topes_nongen, "vertices_from_topes_nongen");



void vertices_in_nh(vertexset & vertices, int d, int i, const std::vector<tope> & all) {
	tope current=all[i];
	std::vector<tope> nh=neighbourhood(d,i,all);
	get_vertices_rec(vertices,d,current,0,tope2type(all[i]),nh);
	select_good_ones(vertices,nh,d);
}

void vertices_in_nh_nongen(vertexset & vertices, int d, int i, const std::vector<tope> & all) {
	tope current=all[i];
	get_vertices_rec(vertices,d,current,i+1,tope2type(all[i]),all);	
}


void get_vertices_rec(vertexset & vertices, int d, tope & t, int j, const tomtype curr, const std::vector<tope> & all) {
// 	std::cout<<std::endl<<"step down"<<std::endl<<"j: "<<j<<std::endl;
// 	std::cout<<"current: "; print(curr);
// 	std::cout<<"vertices: "; print(vertices);

	for (int k=j; k<int(all.size()); ++k) {
// 		std::cout<<"  k: "<<k<<std::endl;
		tomtype newtype=union_of_types(curr,all[k]);
// 		cout<<"newtype: "; print(newtype);
		Array<Set<int> > a(newtype.begin(),newtype.end());
// 		std::cout<<"rank: "<<rank(a,d)<<"  edges: "<<nedges(newtype)<<std::endl;
		if (acyclic(newtype,d)) {
			if (nedges(newtype)==int(curr.size())+d-1) {
				vertices += pmtype(newtype);
			} else {
				get_vertices_rec(vertices,d,t,k+1,newtype,all);	
			}
		}
	}
}

void select_good_ones(vertexset & vertices, const std::vector<tope> & t, int d) {
	for (vertexset::iterator it=vertices.begin(); it!=vertices.end(); ++it) {
		for (std::vector<tope>::const_iterator ts=t.begin(); ts!=t.end(); ++ts) {
			if (!comparable(*it, pmtype(tope2type(*ts)), d)) {
				vertices -= *it; --it;
				break;
			}
		}
	}
}

std::vector<tope> neighbourhood(int d, int i, const std::vector<tope> & all) {
	std::vector<tope> nh;
	for (int j=i+1; j<int(all.size()); ++j) {
		if (dist(all[i],all[j])<= d-1) {
			nh.push_back(all[j]);
		}
	}
	return nh;
}


tomtype union_of_types(const tomtype & a, const tomtype & b) {
	tomtype u;
	
	for (int i=0; i<int(a.size()); ++i){
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

// UserFunction4perl("# @category Type manipulation"
// 				"# @param Array<Set<Int>> type1"
// 				"# @param Array<Set<Int>> type2"
// 				"# @return Array<Set<Int>>",
// 				&union_of_types, "union_of_types");

bool acyclic(const tomtype & u, int d) {
	Array<Set<int> > a(u.begin(),u.end());
	
	int edges=nedges(u);
	int r=rank(a,d);
	if (r==int(u.size())+d-edges) {return 1;} else {return 0;}
}

int nedges(const tomtype & t) {
	int edges=0;
	for (tomtype::const_iterator it=t.begin(); it!=t.end(); ++it) {
		edges+= it->size();
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




}}	//namespace end