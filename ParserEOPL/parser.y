%{
/****************************************************************************
parser.y
ParserWizard generated YACC file.

Date: Sunday, May 19, 2002
****************************************************************************/
// THE odds that I EVER get this to work are slim to none! 
#include "stdafx.h"
#include "lexer.h"
#include "../common.h" // gets all the types for the program

#include "parserspecials.h" 
extern Expression exp;
vector<Expression>* temp;
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

%union {
   string* ident;
   vector<string>* idents;
   Expression* exp;
   vector<Expression>* exps;
   lbs* letbs; // Is this the cannonical way to do this??
   lb* letb;
   lrs* letrecbs;
   lr* letrecb;  // Ok, this is painful
   int intval;
   }
  
%token IF LET IN SET PROC THEN ELSE LETREC
%token <ident> NAME PRIM
%token <intval> NUMBER

%type <exp> expression
%type <exps> arglist expressions 
%type <letb> letbind
%type <letbs>  letbinds
%type <letrecb> letrecbind
%type <letrecbs> letrecbinds
%type <idents> namelist
// place any declarations here
 
%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your YACC rules here (there must be at least one)

expression: 
 	NUMBER  {$$ = new Expression;exp = mkliteral($1); *$$=exp;}
 |  NAME    {$$ = new Expression;exp= mkvariable(*$1);*$$=exp; }
 |  PRIM '(' arglist ')'   {$$ = new Expression;exp= mkprimmapp(*$1,*$3);*$$=exp;}
 |  IF expression THEN expression ELSE expression   {$$ = new Expression();exp= mkifexp(*$2,*$4,*$6);*$$=exp;}
 |  LET letbinds IN expression  {$$ = new Expression; exp = mklet($2->idents,$2->exps,*$4);*$$=exp;}
 |  PROC '(' namelist ')' expression  {$$ = new Expression; exp= mkproc(*$3,*$5);*$$=exp; }
 |  '(' expressions ')'  {$$ = new Expression;
 							   temp = new vector<Expression>; // Here the args go
 							   for(int i=1;i<(*$2).size();i++)
 							      {
 							       temp->push_back((*$2)[i]);
 							       }
 							   exp= mkapp((*$2)[0],*temp);
 							   *$$=exp;}
 |  LETREC letrecbinds IN expression  {$$ = new Expression; exp = mkletrec($2->idents,$2->idss,$2->exps,*$4);*$$=exp;}
 |  SET NAME '=' expression { $$ = new Expression; exp=mkvarassign(*$2,*$4);*$$=exp;}
 ;
 
 // I hope the following ACTUALLY works...
namelist:
   /* empty */ {$$ = new vector<string>;}
  |  NAME      {$$ = new vector<string>; $$->push_back(*$1);}
  |  namelist ',' NAME  {$1->push_back(*$3);$$=$1; }
  ;

 
expressions:
     expression  {$$ = new vector<Expression>; $$->push_back(*$1);}
 |   expressions expression  {$1->push_back(*$2);$$=$1;}
 ;
arglist:
   /* empty */  {$$ = new vector<Expression>;}
 |  expression  {$$ = new vector<Expression>; $$->push_back(*$1);}
 |  arglist ',' expression {$1->push_back(*$3);$$=$1;}
 ;
 

letbind:
    NAME '=' expression {$$ = new lb;$$->ident=*$1;$$->exp=*$3;}
    ;
    
letbinds:
    letbind  {$$ = new lbs; ($$->idents).push_back($1->ident);($$->exps).push_back($1->exp);}
 |  letbinds letbind {($1->idents).push_back($2->ident);($1->exps).push_back($2->exp);$$=$1;}
 ;

letrecbind:
    NAME '(' namelist ')' '=' expression {$$ = new lr;$$->ident=*$1;$$->ids=*$3;$$->exp=*$6;}
    ;
letrecbinds:
    letrecbind  {$$ = new lrs;
    			 ($$->idents).push_back($1->ident);
    			 ($$->idss).push_back($1->ids);
    			 ($$->exps).push_back($1->exp);
    			 }
  | letrecbinds letrecbind {
    			 ($1->idents).push_back($2->ident);
    			 ($1->idss).push_back($2->ids);
    			 ($1->exps).push_back($2->exp);
    			 $$=$1;
    			 }

;
%%

/////////////////////////////////////////////////////////////////////////////
// programs section

