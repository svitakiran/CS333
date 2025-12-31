/**
* Prose: replacing words with more emphatic ones
*/

%option case-insensitive

%%

[a-zA-Z0-9]+    {
    if (strcasecmp(yytext, "cat") == 0)
        printf("lion");
    else if (strcasecmp(yytext, "cats") == 0)
        printf("lions");
    else if (strcmp(yytext, "0") == 0) printf("zero");
    else if (strcmp(yytext, "1") == 0) printf("one");
    else if (strcmp(yytext, "2") == 0) printf("two");
    else if (strcmp(yytext, "3") == 0) printf("three");
    else if (strcmp(yytext, "4") == 0) printf("four");
    else if (strcmp(yytext, "5") == 0) printf("five");
    else if (strcmp(yytext, "6") == 0) printf("six");
    else if (strcmp(yytext, "7") == 0) printf("seven");
    else if (strcmp(yytext, "8") == 0) printf("eight");
    else if (strcmp(yytext, "9") == 0) printf("nine");
    else if (strcmp(yytext, "10") == 0) printf("ten");
    else ECHO;
}

.|\n    ECHO;

%%

int main(int argc, char *argv[]) {
    yylex();
}