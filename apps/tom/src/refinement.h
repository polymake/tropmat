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


#ifndef TOM_REFINEMENT_H
#define TOM_REFINEMENT_H

#include "polymake/Set.h"
#include "polymake/Array.h"
#include "utils.h"

namespace polymake { namespace tom {


pmtomtype refinement(const pmtomtype & A, const partition & op);

}}

#endif