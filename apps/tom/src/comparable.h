#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include "utils.h"
#include <iostream>

namespace polymake { namespace tom {

bool comparable(const Array<Set<int> > & type1, const Array<Set<int> > & type2, int d);

void neighbours(Array<Array<Set<int>, Set<int> > > &, const Array<Set<int> > &, const Array<Set<int> > &, int);

}}