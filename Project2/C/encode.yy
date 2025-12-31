/**
* Encode: take any letter in the alphabet and shift it 13 spaces
* forward, with wraparound
*/

%%

[a-z]   { char c = yytext[0];
    printf("%c", ((c - 'a' + 13) % 26) + 'a');
}

[A-Z]   { char c = yytext[0];
    printf("%c", ((c - 'A' + 13) % 26) + 'A');
}

%%

int main(int argc, char *argv[]){
    yylex();
    return 0;
}