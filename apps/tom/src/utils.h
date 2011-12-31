#ifndef TOM_UTILS_H
#define TOM_UTILS_H


#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <vector>
#include <iostream>
#include "vertices_from_topes.h"

namespace polymake { namespace tom {

void print(const tope &);
void print(const tomtype &);
void print(const std::vector<tope> &);
void print(const std::vector<tomtype> &);
void print(const Set<tomtype> &);
void print(const Array<Set<int> > &); 
void print(const vertexset &);


tope type2tope(const Array<Set<int> >&);
std::vector<tope> types2topes(const Array<Array<Set<int> > > &);

tomtype tope2type(const tope &);
Array<Array<Set<int> > > topes2types(const std::vector<tope> & topes);

Array<Set<int> > pmtype(const tomtype &);

}}


#endif
