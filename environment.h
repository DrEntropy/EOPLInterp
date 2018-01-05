#ifndef EOPL_ENVIRONMENT_H
#define EOPL_ENVIRONMENT_H


#include "common.h"
// use a standard ribbed environment
// a nother way is to use the STL map<> type, but 
// i didnt think of doing it that way :)
// Do i get the behavior i want here? 
// that is, if I do a 'set' operation on a variable,
// and that variable was used in a function definition,
// does it change? 
// In scheme and in EOPL langauge, it does, as it does here.


struct Environment
{ 
	 
	 vector<string> ids;
	 vector<Value> values;
	 Environment* rest;

};


Environment *emptyenv(void); // empty environment
Environment *extend_env(vector<string>,vector<Value>,Environment*);
// This uses destructive update,
 // but gets right semantics, because of the rib structure, when 
// you save a copy of the env before extending, it doesnt change
// by extending. BUT as required , a var assignment does change both.
// A bit confusing, yes.


Value apply_env(string,Environment *);
// doesnt create a copy
vector<Value>::iterator apply_env_ref(string, Environment*); 
// return  pointer to the value so we can change it


Environment *initialenv(void); // generate initial environment;
/* environments */





#endif