#include "polymake/Set.h"
#include "polymake/Array.h"

namespace polymake { namespace tom {

typedef Array<Set<int> > tomtype;
typedef Array<Set<int> > partition;

tomtype refinement(const tomtype & A, const partition & op);

}}