#include "stdafx.h"

#include "common.h"

#include <algorithm>



//Ok, i think this part is done... needs to be tested ! 
Environment *emptyenv(void) 
{
return NULL; // empty env is just NULL
}

Environment *extend_env(vector<string> idents,vector<Value> vals,Environment *old_env)
{
Environment *res = new Environment;
res->rest = old_env;
res->values = vals; // copy constructor called automagically
res->ids = idents;
return res;
}


Value apply_env(string id,Environment *env)
{
	// Lookup and return actual value by dereferencing 
	return *apply_env_ref(id,env);
 
}

vector<Value>::iterator apply_env_ref(string id, Environment *env) 
// return  pointer to the value so we can change it
{
// check in the top rib for the value
	vector<string>::const_iterator it = find(env->ids.begin(),env->ids.end(),id);
    
	if(it != env->ids.end())
	{
		// ok, get the corresponding value
		vector<string>::difference_type cnt = it - env->ids.begin();

		// Two things I dont recall-- how to get the index
		// and how to get a pointer  to a value rather then an iterator
		vector<Value>::iterator resit= env->values.begin() + cnt;
		return resit;

	} else {

	  //
	  // not in this rib, try the next if there is one, or return an error
	  if(env->rest!=NULL)
	  {
	   return apply_env_ref(id,env->rest);
	  } else {
	     	cout <<  "Error, value" << id << " not bound";
	      throw UnboundVar();

          }
	}

}


Environment *initialenv(void) // generate initial environment;
/* environments */
{
	vector<string> initialids;
	vector<Value> initialvals;
	initialids.push_back("x");
	initialvals.push_back(mkintval(3));

return extend_env(initialids,initialvals,emptyenv());

}


void testenv(void) // test er
{
	Environment *myinv = initialenv();
	printf("Env. made!\n");
	printf("Look up x: %d",apply_env("x",myinv).intval);
	printf("Now I am going to set a new variable y and z \n");
	vector<string> ids;
	vector<Value> vals;
	ids.push_back("y");
	ids.push_back("z");
	vals.push_back(mkintval(3242));
	vals.push_back(mkintval(33));
	myinv = extend_env(ids,vals,myinv);
	printf("Ok... look up x:%d and z:%d. I sould get 3 and 33\n",apply_env("x",myinv).intval,
		apply_env("z",myinv).intval);

}
