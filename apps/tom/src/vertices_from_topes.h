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

void vertices_in_nh(Set<tomtype> &, int d, int i, const std::vector<tope> &);

void get_vertices_rec(Set<tomtype>& vertices, int d, int i, int j, const tomtype curr, const std::vector<tope> & all);

int nedges(const tomtype &);
bool acyclic(const tomtype &, int d);

std::vector<tope> neighbourhood(int d, int i, const std::vector<tope> & all);


int dist(const tope &, const tope &);

tomtype union_of_types(const tomtype &, const tomtype &);
tomtype union_of_types(const tope &, const tope &);
tomtype union_of_types(const tope &, const tomtype &);
tomtype union_of_types(const tomtype &, const tope &);




std::vector<int> type2tope(const Array<Set<int> >&);
std::vector<std::vector<int> > types2topes(const Array<Array<Set<int> > > &);

std::vector<Set<int> > tope2type(const std::vector<int>);


Array<Array<Set<int> > > conv_types(const Set<std::vector<Set<int> > > &);



}}