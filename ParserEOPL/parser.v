    0  $accept : expression $end

    1  expression : NUMBER
    2             | NAME
    3             | PRIM '(' arglist ')'
    4             | IF expression THEN expression ELSE expression
    5             | LET letbinds IN expression
    6             | PROC '(' namelist ')' expression
    7             | '(' expressions ')'
    8             | LETREC letrecbinds IN expression
    9             | SET NAME '=' expression

   10  namelist :
   11           | NAME
   12           | namelist ',' NAME

   13  expressions : expression
   14              | expressions expression

   15  arglist :
   16          | expression
   17          | arglist ',' expression

   18  letbind : NAME '=' expression

   19  letbinds : letbind
   20           | letbinds letbind

   21  letrecbind : NAME '(' namelist ')' '=' expression

   22  letrecbinds : letrecbind
   23              | letrecbinds letrecbind


state 0
	$accept : . expression $end

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 10


state 1
	expression : '(' . expressions ')'

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 11
	expressions goto 12


state 2
	expression : IF . expression THEN expression ELSE expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 13


state 3
	expression : LET . letbinds IN expression

	NAME  shift 14

	letbind goto 15
	letbinds goto 16


state 4
	expression : SET . NAME '=' expression

	NAME  shift 17


state 5
	expression : PROC . '(' namelist ')' expression

	'('  shift 18


state 6
	expression : LETREC . letrecbinds IN expression

	NAME  shift 19

	letrecbind goto 20
	letrecbinds goto 21


state 7
	expression : NAME .  (2)

	.  reduce 2


state 8
	expression : PRIM . '(' arglist ')'

	'('  shift 22


state 9
	expression : NUMBER .  (1)

	.  reduce 1


state 10
	$accept : expression . $end  (0)

	$end  accept


state 11
	expressions : expression .  (13)

	.  reduce 13


state 12
	expression : '(' expressions . ')'
	expressions : expressions . expression

	'('  shift 1
	')'  shift 23
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 24


state 13
	expression : IF expression . THEN expression ELSE expression

	THEN  shift 25


state 14
	letbind : NAME . '=' expression

	'='  shift 26


state 15
	letbinds : letbind .  (19)

	.  reduce 19


state 16
	expression : LET letbinds . IN expression
	letbinds : letbinds . letbind

	IN  shift 27
	NAME  shift 14

	letbind goto 28


state 17
	expression : SET NAME . '=' expression

	'='  shift 29


state 18
	expression : PROC '(' . namelist ')' expression
	namelist : .  (10)

	NAME  shift 30
	.  reduce 10

	namelist goto 31


state 19
	letrecbind : NAME . '(' namelist ')' '=' expression

	'('  shift 32


state 20
	letrecbinds : letrecbind .  (22)

	.  reduce 22


state 21
	expression : LETREC letrecbinds . IN expression
	letrecbinds : letrecbinds . letrecbind

	IN  shift 33
	NAME  shift 19

	letrecbind goto 34


state 22
	expression : PRIM '(' . arglist ')'
	arglist : .  (15)

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9
	.  reduce 15

	expression goto 35
	arglist goto 36


state 23
	expression : '(' expressions ')' .  (7)

	.  reduce 7


state 24
	expressions : expressions expression .  (14)

	.  reduce 14


state 25
	expression : IF expression THEN . expression ELSE expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 37


state 26
	letbind : NAME '=' . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 38


state 27
	expression : LET letbinds IN . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 39


state 28
	letbinds : letbinds letbind .  (20)

	.  reduce 20


state 29
	expression : SET NAME '=' . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 40


state 30
	namelist : NAME .  (11)

	.  reduce 11


state 31
	expression : PROC '(' namelist . ')' expression
	namelist : namelist . ',' NAME

	')'  shift 41
	','  shift 42


state 32
	letrecbind : NAME '(' . namelist ')' '=' expression
	namelist : .  (10)

	NAME  shift 30
	.  reduce 10

	namelist goto 43


state 33
	expression : LETREC letrecbinds IN . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 44


state 34
	letrecbinds : letrecbinds letrecbind .  (23)

	.  reduce 23


state 35
	arglist : expression .  (16)

	.  reduce 16


state 36
	expression : PRIM '(' arglist . ')'
	arglist : arglist . ',' expression

	')'  shift 45
	','  shift 46


state 37
	expression : IF expression THEN expression . ELSE expression

	ELSE  shift 47


state 38
	letbind : NAME '=' expression .  (18)

	.  reduce 18


state 39
	expression : LET letbinds IN expression .  (5)

	.  reduce 5


state 40
	expression : SET NAME '=' expression .  (9)

	.  reduce 9


state 41
	expression : PROC '(' namelist ')' . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 48


state 42
	namelist : namelist ',' . NAME

	NAME  shift 49


state 43
	namelist : namelist . ',' NAME
	letrecbind : NAME '(' namelist . ')' '=' expression

	')'  shift 50
	','  shift 42


state 44
	expression : LETREC letrecbinds IN expression .  (8)

	.  reduce 8


state 45
	expression : PRIM '(' arglist ')' .  (3)

	.  reduce 3


state 46
	arglist : arglist ',' . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 51


state 47
	expression : IF expression THEN expression ELSE . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 52


state 48
	expression : PROC '(' namelist ')' expression .  (6)

	.  reduce 6


state 49
	namelist : namelist ',' NAME .  (12)

	.  reduce 12


state 50
	letrecbind : NAME '(' namelist ')' . '=' expression

	'='  shift 53


state 51
	arglist : arglist ',' expression .  (17)

	.  reduce 17


state 52
	expression : IF expression THEN expression ELSE expression .  (4)

	.  reduce 4


state 53
	letrecbind : NAME '(' namelist ')' '=' . expression

	'('  shift 1
	IF  shift 2
	LET  shift 3
	SET  shift 4
	PROC  shift 5
	LETREC  shift 6
	NAME  shift 7
	PRIM  shift 8
	NUMBER  shift 9

	expression goto 54


state 54
	letrecbind : NAME '(' namelist ')' '=' expression .  (21)

	.  reduce 21


17 tokens, 9 nonterminals
24 grammar rules, 55 states
