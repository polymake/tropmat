#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <vector>
#include "polymake/list"
#include "rank.h"


namespace polymake { namespace tom {


Array<Array<Set<int> > > vertices_from_topes(const Array<Array<Set<int> > > topes, const int d);

typedef std::vector<int> tope;
typedef std::vector<Set<int> > tomtype;
typedef Set<Array<Set<int> > > vertexset;

tomtype union_of_types(const tomtype &, const tomtype &);
tomtype union_of_types(const tope &, const tope &);
tomtype union_of_types(const tope &, const tomtype &);
tomtype union_of_types(const tomtype &, const tope &);



}}