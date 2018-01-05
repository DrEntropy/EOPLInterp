%{
/****************************************************************************
lexer.l
ParserWizard generated Lex file.

Date: Sunday, May 19, 2002
****************************************************************************/
#include "stdafx.h"
#include "../common.h"
#include "parserspecials.h"
#include "parser.h"
extern char *p; // the input
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// place any declarations here

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your Lex rules here
[\n\t ]	;
-?[0-9]+  {yylval.intval = atoi(yytext);return NUMBER;}
if	 {return IF;}
then {return THEN;}
let {return LET;}
in  {return IN;}
set {return SET;}
proc {return PROC;}
else {return ELSE;}
letrec {return LETREC;}

// primatives. Note the memory waste :)
\+   {yylval.ident = new string("+");return PRIM;}
\-   {yylval.ident = new string("-");return PRIM;}
\*   {yylval.ident = new string("*");return PRIM;}
add1 {yylval.ident = new string("add1");return PRIM;}
sub1 {yylval.ident = new string("sub1");return PRIM;}
zero\? {yylval.ident = new string("zero?");return PRIM;}

[a-zA-z][a-zA-Z0-9]* {yylval.ident = new string(yytext);return NAME;}
.  {return yytext[0];}
%%

/////////////////////////////////////////////////////////////////////////////
// programs section
int yygetchar(void)
{

    if (*p == '\0') {

        return -1;
    }

    return (unsigned char) *p++;
}



 
