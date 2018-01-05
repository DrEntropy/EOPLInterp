#ifndef EOPL_VALUE_H
#define EOPL_VALUE_H
// Define stuff for values (inlcuding closures ,which are a kind of value)
#include "common.h"
 
struct Closure { 
  Expression theCode;
  vector<string> ids;
  Environment *env;
  } ; // concrete type, so we dont need any accessors etc 

 

enum valTag {
	NUM,
	PROC
};

struct Value {
     valTag tag;
	 union {
		 int intval;
		 Closure *closval;
	        };
}; // NOT a pointer

Value mkintval(int anint);
Value mkprocval(vector<string>& ids,Expression body, Environment *env);



// make some predicates and selectors too..


Closure* getprocval(Value);
int getintval(Value);






#endif