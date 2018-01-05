#include "stdafx.h"
#include "common.h"
Value mkintval(int anint)
{
	Value a;
	a.intval = anint;
	a.tag = NUM;
	return a;

}

Value mkprocval(vector<string>& ids,Expression body, Environment* env)
{
	Value a;
	Closure *clos = new Closure();
	clos->env = env;
	clos->ids = ids;
	clos->theCode = body;
	a.tag = PROC;
	a.closval = clos;
	return a;

}



Closure* getprocval(Value a)
{
// check tag...
return a.closval;
}

int getintval(Value a)
{
	// should check tag
return a.intval;

}


