# Introduction

This was an interpreter for a simple scheme like (in semantics, not in syntax) language I wrote. It is the same as described in "Essentials of Programming Languages" 2nd edition (Friedmann and Wand) except it is in C not in Scheme. I did this back in 2002. It is a mess now but my goal is to clean it up and make it compile again under gcc. (It was originally a console app for Visual studio, so this should not be too bad!)

I might also see if there is anything new to do with the 3rd edition, but I have not heard great things about that edition.

* Parser

The Parser uses Lex/Yacc, but it looks like I used something called "ParserWizard".  I have cleaned it up some but will probably need to redo this .
