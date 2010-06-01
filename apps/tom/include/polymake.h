
#ifndef _POLYMAKE_TOM_POLYMAKE_H
#define _POLYMAKE_TOM_POLYMAKE_H

#ifndef POLYMAKE_APPLICATION_PKG
#define POLYMAKE_APPLICATION_PKG "Polymake::tom::"
#endif

#include_next <polymake.h>

namespace polymake { namespace tom {
   defFunctionWrapper;
namespace {
   StaticRegistrator4perl;
} }

namespace perl_bindings {
   using namespace polymake::tom;

///==== Automatically generated contents follow.    Please do not delete this line. ====
///==== Automatically generated contents end here.  Please do not delete this line. ====
} }

#endif // _POLYMAKE_TOM_POLYMAKE_H

// Local Variables:
// mode:C++
// c-basic-offset:3
// End:
