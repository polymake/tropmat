#include "polymake/client.h"
#include <iostream>

namespace polymake { namespace tom {

void N_PERL() {
	std::cout<<"test"<<std::endl;
}

Function4perl(&N_PERL, "N_PERL");

// InsertEmbeddedRule("user_function mytest() {std::cout<<\"mytest\"<<std::endl;}");

}}
// # @category Hidden
// user_method N_JAVASCRIPT {
// 	print "Oh, you're very funny. Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_PERL {
// 	print "I thought you'd try that.";
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_FORTRAN {
// 	print "Rolf? Is this you? Math without FORTRAN? I'm in! Honestly: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_JAVA {
// 	print "Hey, you found another programming language. Congratulations!";
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_SHAKESPEARE {
// 	print "Fun fact to know: Although Shakespeare is known to have used at least six or seven different spellings of his name, the one you just typed, which is most commonly used nowadays, was not among them.";
// }
// 
// # @category Hidden
// user_method N_WHITESPACE {
// 	print "Well, this is getting a bit too absurd now, don't you think.";
// }
// 
// # @category Hidden
// user_method N_PASCAL {
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_HASKELL {
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// 
// # @category Hidden
// user_method N_CPLUSPLUS {
// 	print "Well, that was so obvious.";
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_PYTHON {
// 	print "In your dreams...";
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_HTML {
// 	print "Oh, come on, html isn't even a programming language.";
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
// 
// # @category Hidden
// user_method N_CSS {
// 	print "Now, come on, css isn't even a programming language.";
// 	print "Btw: php in N_PHP stands for PseudoHyperPlane.";
// }
