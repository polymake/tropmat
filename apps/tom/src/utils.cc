#include "utils.h"

using namespace std;
namespace polymake { namespace tom {


void print(const tope & t) {
	cout<<"( ";
	for (tope::const_iterator it=t.begin(); it!=t.end(); ++it) {
		cout<<*it<<" ";	
	}
	cout<<")";
	cout<<endl;
}
void print(const vector<tope> & ts) {
	for (vector<tope>::const_iterator it=ts.begin(); it!=ts.end(); ++it) {
		print(*it);
	}
	cout<<endl;
}


void print(const tomtype & t) {
	cout<<"( ";
	for (tomtype::const_iterator it=t.begin(); it!=t.end(); ++it) {
		cout<<"{ ";
		for (Set<int>::const_iterator sit=it->begin(); sit!=it->end(); ++sit) {
			cout<<*sit<<" ";
		}
		cout<<"} ";
	}
	cout<<")"<<endl;
}

void print(const vector<tomtype> & ts) {
	for (vector<tomtype>::const_iterator it=ts.begin(); it!=ts.end(); ++it) {
		print(*it);
	}
	cout<<endl;
}

void print(const Set<tomtype> & s) {
	vector<tomtype> t(s.begin(),s.end());
	print(t);
}

void print(const Array<Set<int> > & t) {
	print(tomtype(t.begin(),t.end()));
}





std::vector<tope> types2topes(const Array<Array<Set<int> > > & types) {
	std::vector<tope> r;

	for (Array<Array<Set<int> > >::const_iterator it=types.begin(); it!=types.end(); ++it) {
		
		r.push_back(type2tope(*it));
	}
	return r;
}

tope type2tope(const Array<Set<int> >& type) {
	tope t;
	for (Array<Set<int> >::const_iterator it=type.begin(); it!=type.end(); ++it) {
		for (Set<int>::const_iterator sit=it->begin(); sit!=it->end();++sit) {
			t.push_back(*sit);
		}
	}
	return t;
}


tomtype tope2type(const tope & t) {
	tomtype ret;
	
	for(tope::const_iterator it=t.begin(); it!=t.end(); ++it) {
		Set<int> curr;
		curr.push_back(*it);
		ret.push_back(curr);
	}
	return ret;
}

Array<Array<Set<int> > > topes2types(const std::vector<tope> & topes)
{
	std::vector<Array<Set<int> > > ret;

	for (std::vector<tope>::const_iterator it=topes.begin(); it!=topes.end(); ++it) {
		tomtype ctype;
		
		for (tope::const_iterator it2=it->begin(); it2!=it->end(); ++it2) {
			Set<int> l; 
			l.push_back(*it2);
			ctype.push_back(l);
		}
		Array<Set<int> > ptype(ctype.begin(),ctype.end());
		ret.push_back(ptype);
	}

	Array<Array<Set<int> > > r(ret.begin(),ret.end());

	return r;
}

UserFunction4perl("# @category Utilities"
				"# @param Array<Array<Int>> types"
				"# @return Array<Array<Set<Int>>>",
				&topes2types, "topes2types");




Array<Set<int> > pmtype(const tomtype & t) {
	Array<Set<int> > r(t.begin(),t.end());
	return r;
}




}}