/**
* Parser: implementing a parser for Clite
*/

DIGIT     [0-9]
LETTER    [a-zA-Z]
ID        {LETTER}({LETTER}|{DIGIT})*
KEYWORDS  if|else|while|for|int|float

%%

"//".*                            ;

[ \t\r\n]+                        ;

"=="|"<="|">="|"<"|">"            { printf("Comparison-%s\n", yytext); }

"="                               { printf("Assignment\n"); }

"+"|"-"|"*"|"/"                   { printf("Operator-%s\n", yytext); }

"{"                               { printf("Open-bracket\n"); }
"}"                               { printf("Close-bracket\n"); }
"("                               { printf("Open-paren\n"); }
")"                               { printf("Close-paren\n"); }

{DIGIT}+"."{DIGIT}+               { printf("Float-%s\n", yytext); }

{DIGIT}+                          { printf("Integer-%s\n", yytext); }

{KEYWORDS}                        { printf("Keyword-%s\n", yytext); }

{ID}                              { printf("Identifier-%s\n", yytext); }

.                                 ;

%%

int main(int argc, char *argv[]) {
    yylex();
    return 0;
}