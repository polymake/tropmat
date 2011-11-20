#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/Array.h"
#include <vector>
#include "polymake/list"
#include "rank.h"


namespace polymake { namespace tom {


Array<Array<Set<int> > > vertices_from_topes(const Array<Array<Set<int> > > topes, const int d);
Array<Array<Set<int> > > vertices_from_topes_nongen(const Array<Array<Set<int> > > topes, const int d);

typedef std::vector<int> tope;
typedef std::vector<Set<int> > tomtype;
typedef Set<Array<Set<int> > > vertexset;

void vertices_in_nh(vertexset &, int d, int i, const std::vector<tope> &);
void vertices_in_nh_nongen(vertexset &, int d, int i, const std::vector<tope> &);

void get_vertices_rec(vertexset & vertices, int d, tope &, int j, const tomtype curr, const std::vector<tope> & all);
void get_vertices_rec_nongen(vertexset & vertices, int d, tope &, int j, const tomtype curr, const std::vector<tope> & all);

void select_good_ones(vertexset & vertices, const std::vector<tope> & t, int d);

int nedges(const tomtype &);
bool acyclic(const tomtype &, int d);

std::vector<tope> neighbourhood(int d, int i, const std::vector<tope> & all);


int dist(const tope &, const tope &);

tomtype union_of_types(const tomtype &, const tomtype &);
tomtype union_of_types(const tope &, const tope &);
tomtype union_of_types(const tope &, const tomtype &);
tomtype union_of_types(const tomtype &, const tope &);



}}