#ifndef EOPL_EXPRESSION_H
#define EOPL_EXPRESSION_H
/* This file contains the interface to the expression type. 
  I may use C++ vectors/strings to implement it, but otherwise
no oop stuff will be used. Just to be a pain
 */
// Include file compiled ok on may 8th... 
 
/* expose the enumerated type ExprType */
#include <vector>
using namespace std;
//#include "value.h"
struct Value; // forward declaration

enum ExprType
{
	LITERAL,   // int
	VARIABLE,  // string
	APPLICATION, //vector<Expression> (0th element is proc body)
	PRIMAPP,   //string vector<Expression> 
	PROCEXP,   // vector<string> Expression 
	IF,     // vector<Expression> (bool trueexp falseexp)
	LETREC, // vector<vector<string> >  n+1 element is ids , vector<Expression> , n+1 element is body
	LET,    // vector<string> vector<Expression> , n+1 element is body
	VARASSIGN // string Expression
};

struct Expression;
 
// Note that I use pointers in the expression type to make them
// lightweight. 

    
struct Expression {
	 ExprType type;
	 vector<Expression> *exps; // used by almost all exps
	 union {
		   // special data for each
     vector<string> *strings; // also used by variables...
	 vector<vector<string> > *idss;  // used only  by letrec
     int avalue;
	 };
};
// note that expressions are not pointers to something. These are tagged
// unions 

// unfortunatly, having all these functions return vector<exp> or exp
// may get abit expensive, because of the extra copying going on.


/* Now define all the accessor functions we will need 
 Probably about 15 of them... any other way? 
 ALso what to do about the various lists that will appear. 
  I think I will want to use vectors here, but wont bison
  get screwed? Well, can just make a 
  vaneer interface for the bison thing if it doesnt
  like vectors. 
  NOTE ADDED 5/21/2002: No problem with yacc/lex
  See also www.uman.com/faq.shtml or whatever it
  was. */
Value getDatum(Expression litexpr);

// for variable exp, assign exp 
string& getId(Expression varexp);


// for  let, app, prim ap
vector<Expression> getRands(Expression exp);

// for procexp and let
vector<string>& getIds(Expression exp); 


// for anything with a body, like proc, let letrec, 
// and variable assignment (RHS is the body)
Expression getBody(Expression exp); 



// for letrec 
vector<string>& getProcNames(Expression exp);
vector<vector<string> > getIdss(Expression exp);
vector<Expression> getBoundBodys(Expression exp);

// for app exp

Expression getRator(Expression exp);
// for prim app
string& getPrim(Expression exp);

// for if exp
Expression getTest(Expression exp);
Expression getTrue(Expression exp);
Expression getFalse(Expression exp);

/* Now define all the builders */
 

Expression mkliteral(int avalue);
Expression mkvariable(const string& astring);
Expression mkapp(Expression Op,vector<Expression>& args);
Expression mkproc(vector<string>& ids,Expression body);
Expression mkifexp(Expression boolexp,Expression true_exp,Expression false_exp);
Expression mkletrec(vector<string>& procids,vector< vector<string> >& idss, 
				     vector<Expression>& bodies, Expression body);
Expression mklet(vector<string>& ids,vector<Expression>& rands,Expression body);
Expression mkvarassign(const string& id,Expression body);
Expression mkprimmapp(const string& prim,vector<Expression>& args);
#endif 