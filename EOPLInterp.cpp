// EOPLInterp.cpp : Main is defined in here
// This is the toplevel for the EOPL interpreter. It will be based
// on ex 7.23/22  (using trampoline to prevent building control 
// context on calls to 'apply continuation', which will really just
// return a data structure. This is meant to be as primative as possible...
// Avoid the c stack!
//
////////////////////////////////////////////////////////////////
// About the tagged unions: 
// I tried to seperate the implementation from the use, so I defined
// accessors and constructors for all the varients of expressions, values,
// and environments. This makes the interpreter much clearer (to me), but
// made for a lot of extra work. Could have just used 'naked' unions and
// 'finished' this much sooner!
///////////////////////////////////////////////////////////
// Speaking of finishing, this is of course not complete. Things that are missing:
// 1) Run time checking of types and arguments to functions, with better
// error messages (More informative) (maybe an error continuation is a way to do it)
// 2) better parse error messages  
// 3) Garbage collection
// 4) A lot of other things, but I learned all I can learn from this one at 
// the moment.
// As of may 22 2002
// Dr. Ronald J. Legere
// 31337 h4x0r

#include "stdafx.h"
#include <algorithm>
#include "common.h"

 
#include "yacc.h"
void eval_rands(void);

/* note that the evaluator this takes and returnsno  arguments. 
    the current exp , env and continuation are in globals. This is
	again to get away from the control context mechanisms of the machine*/
int going = 1;

Expression exp = mkliteral(0); 

Environment *env = initialenv(); // include a couple of bindings
Continuation cont= haltcont();  // yep, this is the finisher
vector<Value> vals; //  Note this type will have to be a vector 
                      // to allow for multiple values
vector<Expression> rands;  
vector<Value> args;  // evaluated rands. used only for apply-primative
Closure proc; // uninitiallized

char *p; // a string to be parsed
 
Environment *extend_env_recursively(vector<string>& procname,vector<vector<string> >&idss,
									  vector<Expression>& bodies, Environment* env);

/* note that a lot of the work is done when the continuation is
  applied! */

// This doenst define all interesting primatives, nor 
// does it check that the correct arguments have
// been passed in. In fact it ignores any extra arguments

Value apply_primitive(string prim, vector<Value> args)
{
	int arg1;
	int arg2;
	if(prim == "+")  
	{
	arg1 = getintval(args[0]);
	arg2 = getintval(args[1]);
	return mkintval(arg1+arg2);
	} else 
    if(prim == "-")
		 {
	 arg1 = getintval(args[0]);
	arg2 = getintval(args[1]);
	return mkintval(arg1-arg2);
		 } else 
	 if(prim == "add1")
	 {
	  arg1 =getintval(args[0]);
	  return mkintval(arg1+1);
	 } else 
		   if(prim == "zero?")
		   {
		    arg1 = getintval(args[0]);
			if(arg1==0) 
				return mkintval(1);
			else
				return mkintval(0);
		   }
	else 
	       if(prim == "sub1")
		   {
			 arg1 = getintval(args[0]);
			 return mkintval(arg1-1);
		   } else {


		printf("No such primitive\n");
	
		going = 0;
		return mkintval(0);
	}

}


// This is the meat.
void evalexpression()
{

 while(1)
	 switch(exp.type)
     {
      /* Now consider all the types and do something appropriate, which will be 
	   to either build a new continuation and set something else in the global
	   expression (and then loop) or to just return, then 
	    the  main loop will apply the cont to the val. That is 'return' is an
		implicit 'apply-cont'
		  
		  This is basically a verbatim copy of the code from EOPL 2nd ed. 

		If we want multiple contexts, then we would need to return 
		a stucture with a copy of the continuation and the 
		value */

    case LITERAL: 
		 vals.clear();
		 vals.push_back(getDatum(exp));
		 return ; // this trick is how we get the trampoline to work=appy-cont
    case VARIABLE:
		 vals.clear();
		 vals.push_back(apply_env(getId(exp),env));
		 return;
	case PROCEXP:
		// make the closure

		 vals.clear();
		 vals.push_back(mkprocval(getIds(exp),getBody(exp),env));
		return;
    case LETREC:
		// this is a complicated case! 
		env = extend_env_recursively(getProcNames(exp),getIdss(exp),getBoundBodys(exp),env);
		exp = getBody(exp);
		break; // keep going! 

	
	case IF:
		cont = testcont(getTrue(exp),getFalse(exp),env,cont);
		exp = getTest(exp);
		break;
	case VARASSIGN:
		cont = varassigncont(env,getId(exp),cont);
		exp = getBody(exp);
		break;
	case PRIMAPP:
		cont = primargscont(getPrim(exp),cont);
		rands = getRands(exp);
		eval_rands(); // I dont like this subroutine being here
		return;

	case LET:
		cont = letexpcont(getIds(exp),env,getBody(exp),cont);
		rands = getRands(exp);
		eval_rands();
		return;

	case APPLICATION:
		cont = evalratorcont(getRands(exp),env,cont);
		exp = getRator(exp);

		break; // loop back to eval some more
	
	

	
	
	
	default: return;
	  
	 }
}


void eval_rands()
{
// 
	 if(rands.size()==0)
	 {
		 vals.clear();
		 return;
	 } else {
      exp = rands[0];
	  cont = evalfirstcont(rands,env,cont);
	  evalexpression();  // this builds some control context... could be replaced with a goto
	 }

}

void apply_procval(void)
{
	exp = proc.theCode;
    if(proc.ids.size() == args.size())
	{
	env =  extend_env(proc.ids,args,proc.env);
    evalexpression();  // this builds control context. Could replace with goto
	}
	else
	{
	printf("function applied to wrong number of arguments.\n");
	going = 0;
	}

}

void applycont(void) 
{
		// another pain in the ass, i have to define all these variables
		vector<Value> pargs;
		Value aproc;
		Environment *newenv;
		vector<Expression> rest;
		vector<Value> vrest;
		vector<Expression> oldrands;
	switch(cont.conttag)
	{


	case HALT: 
		  if(vals.size() == 0)
		  {
			  printf("all done, no value\n");
		  } else {
			  printf("all done:%d",getintval(vals[0]));// or something like that
		  }
		  going =0;
		  return;
	case TESTCONT:
		  if(getintval(vals[0]))
		  {
			  exp = CgetTrue(cont);
		  } else {
			  exp = CgetFalse(cont);
		  }
			  env = CgetEnv(cont);
			  cont = CgetCont(cont);
			  evalexpression();
		 return;
	case VARASSIGNCONT:
		 *apply_env_ref(CgetId(cont),CgetEnv(cont))=vals[0];
		 cont = CgetCont(cont);
		 vals.clear();
		 vals.push_back(mkintval(1));
		 return;
	case PRIMARGSCONT:
		 pargs = vals; // save the results!
		 vals.clear();
		 vals.push_back(apply_primitive(CgetId(cont),pargs));
         
         cont = CgetCont(cont);
		 return;
	case LETEXPCONT:
		  env= extend_env(CgetIds(cont),vals,CgetEnv(cont));
		  exp = CgetBody(cont);
		  cont = CgetCont(cont);
		  evalexpression();
		  return;

	case EVALRATORCONT:
		  aproc = vals[0];
		  rands = CgetExps(cont);
		  env = CgetEnv(cont);
		  cont = evalrandscont(aproc,CgetCont(cont));
		  eval_rands();
		  return;

	case EVALRANDSCONT:
		   pargs = vals;
		   aproc = CgetValue(cont);
		   if(aproc.tag == PROC)
		   {
			   proc = *getprocval(aproc); // not right
			   args = pargs;
				cont = CgetCont(cont);
				apply_procval();
				// through about 2 other returns, we get back here :)
				return;
		   } else {
			    printf("Error.. attempt to apply non procedures\n");
		        going = 0;
				return;
			}


	case EVALFIRSTCONT:
           rest.clear(); // should be clear
		    oldrands = CgetExps(cont);
		  copy(oldrands.begin()+1,oldrands.end(),back_inserter(rest)); // this is lame
		   // I should have made the back teh front if you see what I mean !
		   rands = rest;
		   env = CgetEnv(cont);
		   cont = evalrestcont(vals[0],CgetCont(cont));
		   eval_rands();
		   return;


		   
	case EVALRESTCONT:
		    vrest = vals;
		   vals.clear();
			vals.push_back(CgetValue(cont));
			// here is a typical stupid problem. if i have rest below instead of 
			// vrest, I get a very strange error instead of a simple one.

			copy(vrest.begin(),vrest.end(),back_inserter(vals));
             cont = CgetCont(cont);
		   return;
	default:
		printf("Hmm, some kind of strange error\nFell through at the APPLYCONT");
		going = 0;
		return;

	}
 
}

		  
void mainloop(void)
{
	/* Need to add some way to get out, so apply cont will set going to zero
	  when it hits the halt! */ 
	// note that control context is still built in the calls to eval expression
	// that occur above..c
	while(going)
	{
	applycont();
	}

	
}

void testenv(void);
Expression testexps(void);
int _tmain(int argc, _TCHAR* argv[])
{
	testenv();
	//exp = testexps();
	 // set up the globals and then..
//	p = "let x = 3 "
//		 "in +(x,x)"; // works
/*p = "let f = proc () 3 "
        " in (f)"; */

	 p = "let x = 0"
		" in letrec"
		"   even() = if zero?(x)"
		"			then 1 "
		"			else let d = set x = sub1(x)"
		"			      in (odd)"
		"   odd() = if zero?(x)"
		"	         then 0  "
		"	        else let d  = set x = sub1(x)"
		"             in (even)"
		" in let d = set x = 12 in (odd)";  
	 /* p = "letrec f(x,y) = +(x,y)"
		     " in \n"
			    "let y = 4\n"
				    "z = 8\n"
					"in (f y z)"; */
     // everything seems to work .. but these are the only
	// tests I ran. Others exist :)
	//p = "add1(3)";  // works
	//p= "3";    // works
	//note that yyparse will set exp to the parsed value...
	if(!yyparse()) 
	{
	 
	evalexpression();
	mainloop();
	} else {
	printf("Parse error.\n");
	}

    printf("Exiting...\n");

	
	return 0;
}


// pain in the arse letrec
// UNTESTED
Environment *extend_env_recursively(vector<string>& procnames,vector<vector<string> >&idss,
									  vector<Expression>& bodies, Environment* env)
{
// First make a new env that has the proc names bound to dummy values
vector<Value> procvalues;
for(unsigned int i = 0; i < procnames.size();++i)
  procvalues.push_back(mkintval(0));

Environment *newenv=extend_env(procnames,procvalues,env);
// now bind each name to its real value
// Since I need to access multiple stuff, iterators dont work so well
for(unsigned int i= 0;i < procnames.size();++i)
{
*apply_env_ref(procnames[i],newenv) = mkprocval(idss[i],bodies[i],newenv);
}

return newenv;
}


