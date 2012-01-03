// Copyright (c) 2012 Silke Möser
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


#if 0

#include "vertices_from_topes.h"
#include "utils.h"
#include "comparable.h"

namespace polymake { namespace tom {

Array<Array<Set<int> > > vertices_from_topes_nongen(const Array<Array<Set<int> > > topes, const int d);

void vertices_in_nh_nongen(vertexset &, int d, int i, const std::vector<tope> &);

bool get_vertices_rec_nongen(vertexset & vertices, int d, tope &, int j, const tomtype curr, const std::vector<tope> & all);

bool check_comparability(tomtype & type, const std::vector<tope> & t, int d);
bool already_found_vertex(const vertexset & vertices, const tomtype & newtype);



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


void vertices_in_nh_nongen(vertexset & vertices, int d, int i, const std::vector<tope> & all) {
	// vertices - the list found so far
	// d - rank
	// i - index of current tope
	// all - list of all topes
	tope current=all[i];
	get_vertices_rec_nongen(vertices,d,current,i+1,tope2type(all[i]),all);	
}


// recursively compute list of potential vertices
bool get_vertices_rec_nongen(vertexset & vertices, int d, tope & t, int j, const tomtype curr, const std::vector<tope> & all) {
	// vertices - the list found so far
	// d - rank
	// t - current tope
	// j - index of next tope
	// curr - current type
	// all - list of all topes


	std::cout<<std::endl<<"step down"<<std::endl;//<<"j: "<<j<<std::endl;
	std::cout<<"current: "; print(curr);
// 	std::cout<<"vertices:"<<std::endl; print(vertices);

	bool ret=0;

	for (int k=j; k<int(all.size()); ++k) {
// 		std::cout<<"  k: "<<k<<std::endl;
		tomtype newtype=union_of_types(curr,all[k]);
		cout<<"newtope: "; print(all[k]);
		cout<<"newtype: "; print(newtype);
		Array<Set<int> > a(newtype.begin(),newtype.end());
// 		std::cout<<"rank: "<<rank(a,d)<<"  edges: "<<nedges(newtype)<<std::endl;

		Array<Set<int> > newtypepm(newtype.begin(),newtype.end());
		
		if (check_comparability(newtype, all, d)) {
			std::cout<<"comparable"<<std::endl;
			ret=1;
			
			bool next=get_vertices_rec_nongen(vertices,d,t,k+1,newtype,all);
	
			if (rank(newtypepm, d)==1 && !next) {
				if (!already_found_vertex(vertices,newtype))
				vertices += pmtype(newtype);
			}
		} else 
			std::cout<<"not comparable"<<std::endl;
	}
	
	return ret;
}


bool check_comparability(tomtype & type, const std::vector<tope> & t, int d) {
	for (std::vector<tope>::const_iterator ts=t.begin(); ts!=t.end(); ++ts) {
		if (!comparable(pmtype(type), pmtype(tope2type(*ts)), d)) {
			return 0;
		}
	}
	return 1;
}

bool already_found_vertex(const vertexset & vertices, const tomtype & newtype) {
	std::cout<<"found_vertex:"<<std::endl;
	print(newtype);
	for (vertexset::const_iterator it=vertices.begin(); it!=vertices.end(); ++it) {
		tomtype::const_iterator tomit=newtype.begin();
		print(*it);
		for (Array<Set<int> >::const_iterator it2=it->begin(); it2!=it->end(); ++it2) {
			std::cout<<incl(*it2,*tomit)<<std::endl;
			if(incl(*it2,*tomit)!=1) break;
			tomit++;
		}
		std::cout<<"1"<<std::endl; return 1;
	}
	std::cout<<"0"<<std::endl;
	return 0;
}

}}	//namespace end

#endif