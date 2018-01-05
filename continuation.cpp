#include "stdafx.h"
#include "common.h"

Continuation haltcont(void)
{
	Continuation res;
	res.conttag=HALT;
	return res;
}



// Constructors
Continuation testcont(Expression trueexp,Expression falseexp,Environment *env,Continuation cont)
{
  Continuation res;
  res.conttag = TESTCONT;
  res.exps.push_back(trueexp);
  res.exps.push_back(falseexp);
  res.env = env;



  // make a copy of the continuation ... safety!

  res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}

Continuation varassigncont(Environment *env,string id,Continuation cont)
{
  Continuation res;
  res.conttag = VARASSIGNCONT;
  res.env = env;
  res.ids.push_back(id);
  res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}
Continuation primargscont(string prim,Continuation cont)
{
	Continuation res;
	res.conttag = PRIMARGSCONT;
  res.ids.push_back(prim);
  res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}

Continuation letexpcont(vector<string> ids,Environment *env,Expression body,Continuation cont)
{
	Continuation res;
	res.conttag = LETEXPCONT;
     res.ids=ids;
	 res.env=env;
	 res.exps.push_back(body);
	  res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}

Continuation evalratorcont(vector<Expression> rands,Environment *env,Continuation cont)
{
	Continuation res;
	res.conttag = EVALRATORCONT;
	res.exps=rands;
	res.env=env;
	res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}
Continuation evalrandscont(Value proc, Continuation cont)
{   
	Continuation res;
	res.conttag=EVALRANDSCONT;
	res.value = proc;
	res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}

Continuation evalfirstcont(vector<Expression> exps,Environment *env,Continuation cont)
{  Continuation res;
res.conttag = EVALFIRSTCONT;
   res.exps=exps;
   res.env = env;
   res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}

Continuation evalrestcont(Value first, Continuation cont)
{  
	Continuation res;
	res.conttag = EVALRESTCONT;
	res.value=first;
	res.cont = new Continuation;
  *(res.cont) = cont;

  return res;
}


// Destructors :)
// First, everyone has a continuation pointer...
Continuation CgetCont(Continuation cont)
{
	return *(cont.cont);
}

// ALmost all have envs
Environment *CgetEnv(Continuation cont)
{
	return cont.env;
}


// Varassign and primargs has a string id we need to get back
string CgetId(Continuation cont)
{
	return cont.ids[0];
}

// let exp has a  vector of them
vector<string> CgetIds(Continuation cont)
{
	return cont.ids;
}


// evalrands and eval rest have values
Value CgetValue(Continuation cont)
{
	return cont.value;
}


// For testcont, there are two expressions
Expression CgetTrue(Continuation cont)
{
	return cont.exps[0];
}

Expression CgetFalse(Continuation cont)
{
	return cont.exps[1];
}

// let exp just has a body

Expression CgetBody(Continuation cont)
{
	return cont.exps[0];
}

// EvalRator and Evalrands have vvectors of expressions

vector<Expression> CgetExps(Continuation cont)
{
	return cont.exps;
}
