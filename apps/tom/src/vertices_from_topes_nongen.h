#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <vector>
#include "polymake/list"
#include "rank.h"
#include "vertices_from_topes.h"

namespace polymake { namespace tom {


Array<Array<Set<int> > > vertices_from_topes_nongen(const Array<Array<Set<int> > > topes, const int d);

void vertices_in_nh_nongen(vertexset &, int d, int i, const std::vector<tope> &);

bool get_vertices_rec_nongen(vertexset & vertices, int d, tope &, int j, const tomtype curr, const std::vector<tope> & all);

bool check_comparability(tomtype & type, const std::vector<tope> & t, int d);
bool already_found_vertex(const vertexset & vertices, const tomtype & newtype);

}}