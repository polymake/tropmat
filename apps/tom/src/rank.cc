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


#include "polymake/client.h"
#include "rank.h"

namespace polymake { namespace tom {


int rank(const Array<Set<int> > &type, int d) {
	
	// TODO: check that type actually is a type
	
	Set<Set<int> > tmp(type.begin(), type.end());
	Set<Set<int> > tmp2;

	Set<int> S;

	for (int i=1; i<=d; ++i) {
		S += i;
		for (Set<Set<int> >::iterator it = tmp.begin(); it!=tmp.end(); ++it) {
			if (it->contains(i)) {
				S += *it;
			} else {
				tmp2 += *it;
			}
		}
		tmp2 += S;
		S.clear();
		tmp = tmp2;
		tmp2.clear();
	}
	
	return tmp.size();
}



Function4perl(&rank, "rank");

} }
