#include "stdafx.h"
#include "common.h"
#include <algorithm>

// Gotta define all these functions... woohoo
// also add in if expressions to check that the type is suitable!!!

Value getDatum(Expression exp)
{
 
return	 mkintval(exp.avalue);  
 
}


// for variable exp, assign exp 
string& getId(Expression  varexp)
{
	return (*(varexp.strings))[0]; 
}



// for  let, app, prim ap 
vector<Expression> getRands(Expression exp)
{
    vector<Expression> res;
	switch(exp.type)
	{
	case APPLICATION:
		 // for whatever reason, teh body is first in an application.
		copy(exp.exps->begin()+1,exp.exps->end(),back_inserter(res));
		return res;
	case LET:
		  // the body is last in a let
        copy(exp.exps->begin(),exp.exps->end()-1,back_inserter(res));
		return res;
	case PRIMAPP:
	     return *(exp.exps);
	default:
		 // error! 
		printf("ERROR! get rands on something without rands\n");
		exit(0);
	}

}



// for procexp and let
vector<string>&  getIds(Expression exp)
{
	return *(exp.strings);  // test this
}



// for anything with a body, like proc, let letrec, 
// and variable assignment (RHS is the body)  (NOT application expressions)
Expression getBody(Expression exp)
{
	// body is allways the last element
	return *((exp.exps)->end() - 1);  // needs testing
}




// for letrec 
// 	recall  vector<vector<string> >  n+1 element is ids , vector<Expression> , n+1 element is body
vector<string>& getProcNames(Expression exp)
{
	return *(exp.idss->end() - 1 );
}

// also for letrec
vector<vector<string> > getIdss(Expression exp)
{
	// return all but the last in a new vector
	vector<vector<string> > result = *(exp.idss); // Invoke copy const
	result.pop_back(); // pop the last element
	
	return result;
}


vector<Expression> getBoundBodys(Expression exp)
{
	 // return all but the last..
	vector<Expression> result = *(exp.exps);
	result.pop_back();
 
	return result;
}

// for app exp

Expression getRator(Expression exp)
{
	return (*exp.exps)[0];
}

// for prim app
string& getPrim(Expression exp)
{
	return (*exp.strings)[0];
}



// for if exp
Expression getTest(Expression exp)
{
	return (*exp.exps)[0];
}

Expression getTrue(Expression exp)
{
	return (*exp.exps)[1];
}

Expression getFalse(Expression exp)
{
	return (*exp.exps)[2];
}

Expression mkliteral(int avalue) {
	Expression res;
	res.type = LITERAL;
	res.avalue =avalue;
	return res;
}


Expression mkvariable(const string& astring)
{

    Expression res;
	res.type = VARIABLE;
	res.strings = new vector<string>();
	(res.strings)->push_back(astring);
	return res;
	}

Expression mkapp(Expression Op,vector<Expression>& args)
{
	Expression res;
	res.type = APPLICATION;
	res.exps = new vector<Expression>();
	res.exps->push_back(Op);
	// now copy the args. ok, I admit this is pretty cool.
	copy(args.begin(),args.end(),back_inserter(*(res.exps)));
    res.avalue=0; // just so something is in that part of the union
	
	return res;
}

Expression mkproc(vector<string>& ids,Expression body)
{
	Expression res;
	res.type = PROCEXP;
	res.exps = new vector<Expression>();
	res.strings = new vector<string>(ids);
	res.exps->push_back(body);
	return res;
}

Expression mkifexp(Expression boolexp,Expression true_exp,Expression false_exp)
{
	Expression res;
	res.type = IF;
	res.exps = new vector<Expression>();
	res.exps->push_back(boolexp);
	res.exps->push_back(true_exp);
	res.exps->push_back(false_exp);
	res.avalue= 0;
	return res;
}


Expression mkletrec(vector<string>& procids,vector< vector<string> >& idss, 
				     vector<Expression>& bodies, Expression body)
{
	  Expression res;
	  res.type = LETREC;
	  res.exps = new vector<Expression>();
	  // copy the letrec bodies
	  copy(bodies.begin(),bodies.end(),back_inserter(*(res.exps)));
	  // n+1 exp is the body
	  res.exps->push_back(body);
	  // now copy the strings... I probably could just assign a pointer
	  // to the arguments, but for saftey, and because I am not sure
	  // what the hell is going on, I will make a local copy
	  res.idss = new vector< vector<string> >(); 
	  copy(idss.begin(),idss.end(),back_inserter(*(res.idss)));
	  res.idss->push_back(procids); // n+1 of res.idss is the procids!
	  return res;
}



Expression mklet(vector<string>& ids,vector<Expression>& rands,Expression body)
{
	Expression res;
	res.type = LET;
	res.exps = new vector<Expression>(rands);
	res.exps->push_back(body);
	res.strings = new vector<string>(ids);
	return res;
}



Expression mkvarassign(const string& id,Expression body)
{
  Expression res;
  res.type = VARASSIGN;
  res.strings = new vector<string>();
  res.strings->push_back(id);
  res.exps = new vector<Expression>();
  res.exps->push_back(body);
  return res;
}

Expression mkprimmapp(const string& prim,vector<Expression>& args)
{
   Expression res;
   res.type = PRIMAPP;
   res.strings = new vector<string>();
   res.strings->push_back(prim);
   res.exps = new vector<Expression>(args);
   return res;
}


Expression testexps(void)
{
	printf("TESTING THE EXP DATA TYPE\n");
	printf("ok, creating a random exps: let y = 3 in \n(lambda(x) (+ x x)) y) \n");
	vector<Expression> args;
	args.push_back(mkvariable("y"));
	// Very wordy i know...
	vector<Expression> primargs;
	primargs.push_back(mkvariable("x"));
	primargs.push_back(mkvariable("x"));
	vector<string> ids;
	ids.push_back("x");
	Expression res1 = mkapp(mkproc(ids,mkprimmapp("+",primargs)),args);
 
	vector<Expression> rands;
	rands.push_back(mkliteral(3));
	vector<string> letids;
	letids.push_back("y");
	Expression res  = mklet(letids,rands,res1);
	return res;

}
