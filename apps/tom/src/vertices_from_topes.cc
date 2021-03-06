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


#include "vertices_from_topes.h"
#include "utils.h"
#include "comparable.h"

namespace polymake { namespace tom {

void vertices_in_nh(vertexset &, int d, int i, const std::vector<tope> &);

void get_vertices_rec(vertexset & vertices, int d, tope &, int j, const tomtype curr, const std::vector<tope> & all);

void select_good_ones(vertexset & vertices, const std::vector<tope> & t, int d);

int nedges(const tomtype &);
bool acyclic(const tomtype &, int d);

std::vector<tope> neighbourhood(int d, int i, const std::vector<tope> & all);

int dist(const tope &, const tope &);



Array<Array<Set<int> > > vertices_from_topes(const Array<Array<Set<int> > > topes, const int d) {

	std::vector<tope> t = types2topes(topes);
	vertexset vertices;
	
	for (int i=0; i<int(t.size())-1; ++i) {
		vertices_in_nh(vertices,d,i,t);
	}
	select_good_ones(vertices, t, d);

	Array<Array<Set<int> > > ret(vertices.begin(), vertices.end());
	return ret;
}

Function4perl(&vertices_from_topes, "vertices_from_topes");


// find vertices in neighbourhood of (i.e., containing) i-th tope
void vertices_in_nh(vertexset & vertices, int d, int i, const std::vector<tope> & all) {
	// vertices - the list found so far
	// d - rank
	// i - index of current tope
	// all - list of all topes
	tope current=all[i];
	std::vector<tope> nh=neighbourhood(d,i,all);
	get_vertices_rec(vertices,d,current,0,tope2type(all[i]),nh);
}


void get_vertices_rec(vertexset & vertices, int d, tope & t, int j, const tomtype curr, const std::vector<tope> & all) {
	// go thru all topes in the neighbourhood of current type
	for (int k=j; k<int(all.size()); ++k) {
		// form the union with the next tope
		tomtype newtype=union_of_types(curr,all[k]);
		Array<Set<int> > a(newtype.begin(),newtype.end());
		if (acyclic(newtype,d)) {	// if the type graph contains a cycle this can't be a type
			if (nedges(newtype)==int(curr.size())+d-1) {	// if type if full-dim, add to list
				vertices += pmtype(newtype);
			} else {
				get_vertices_rec(vertices,d,t,k+1,newtype,all);	// else try to increase dim by rec
			}
		}
	}
}


// now select the vertices that are comparable with each tope
void select_good_ones(vertexset & vertices, const std::vector<tope> & t, int d) {
	// go thru potential vertices
	for (vertexset::iterator it=vertices.begin(); it!=vertices.end(); ++it) {
		// go thru topes
		for (std::vector<tope>::const_iterator ts=t.begin(); ts!=t.end(); ++ts) {
			if (!comparable(*it, pmtype(tope2type(*ts)), d)) {
				vertices -= *it--;
				break;
			}
		}
	}
}



// find all topes at distance <= d-1 from i-th tope
std::vector<tope> neighbourhood(int d, int i, const std::vector<tope> & all) {
	std::vector<tope> nh;
	for (int j=i+1; j<int(all.size()); ++j) {
		if (dist(all[i],all[j])<= d-1) {
			nh.push_back(all[j]);
		}
	}
	return nh;
}


bool acyclic(const tomtype & u, int d) {
	Array<Set<int> > a(u.begin(),u.end());
	
	int edges=nedges(u);
	int r=rank(a,d);
	if (r==int(u.size())+d-edges) {return 1;} else {return 0;}
}


// number of edges in the type graph --> dimension of type
int nedges(const tomtype & t) {
	int edges=0;
	for (tomtype::const_iterator it=t.begin(); it!=t.end(); ++it) {
		edges+= it->size();
	}
	return edges;
}

// the distance is the number of positions where the topes differ
int dist(const tope & a, const tope & b) {
	int n=a.size();
	int count=0;
	
	for (int i=0; i<n; ++i) {
		if (a[i]!=b[i]) { count++; }
	}
	return count;
}

}}	//namespace end