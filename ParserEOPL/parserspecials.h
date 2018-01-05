#ifndef _PARSERSPECIALS_H
#define _PARSERSPECIALS_H
 
// these structs are ONLY used by the parser to build Expression's
struct lb {
   string ident;
   Expression exp;
   }
   ;
struct lbs {
     vector<string> idents;
     vector<Expression> exps;
     }
;
struct lr {
      string ident;
      vector<string> ids;
      Expression exp;
      };
struct lrs {
      vector<string> idents;
      vector<vector<string> >idss;
      vector<Expression> exps;
      };

#endif
