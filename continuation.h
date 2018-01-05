#ifndef EOPL_CONTINUATION_H
#define EOPL_CONTINUATION_H
#include "value.h" 

 

/* the tags here are needlessly exposed, but whatever */


enum ContTag
{
HALT,
TESTCONT,
VARASSIGNCONT,
PRIMARGSCONT,
LETEXPCONT,
EVALRATORCONT,
EVALRANDSCONT,
EVALFIRSTCONT,
EVALRESTCONT
	
};
 
struct Continuation;

struct Continuation
{
	 ContTag conttag;
	 Continuation* cont; // ok ... 
	 vector<Expression> exps; // May be empty if not used. A union would be better maybe?
	 Environment *env; // ditto
     vector<string> ids; // ditto again, 
	 Value value;
};

// Constructors
Continuation testcont(Expression trueexp,Expression falseexp,Environment *env,Continuation cont);
Continuation varassigncont(Environment *env,string id,Continuation cont);
Continuation primargscont(string prim,Continuation cont);
Continuation letexpcont(vector<string> ids,Environment *env,Expression body,Continuation cont);
Continuation evalratorcont(vector<Expression> rands,Environment *env,Continuation cont);
Continuation evalrandscont(Value proc, Continuation cont);
Continuation evalfirstcont(vector<Expression> exps,Environment *env,Continuation cont);
Continuation evalrestcont(Value first, Continuation cont);


Continuation haltcont(); // halt cont constructor

// Destructors :)
// First, everyone has a continuation pointer...
Continuation CgetCont(Continuation cont);
// ALmost all have envs
Environment *CgetEnv(Continuation cont);

// Varassign and primargs has a string id we need to get back
string CgetId(Continuation cont);
// let exp has a  vector of them
vector<string> CgetIds(Continuation cont);

// evalrands and eval rest have values
Value CgetValue(Continuation cont);

// For testcont, there are two expressions
Expression CgetTrue(Continuation cont);
Expression CgetFalse(Continuation cont);
// let exp just has a body

Expression CgetBody(Continuation cont);

// EvalRator and Evalrands have vvectors of expressions

vector<Expression> CgetExps(Continuation cont);




#endif