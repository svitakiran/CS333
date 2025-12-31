/**
* Reader: read a text file and return the number of rows, characters,
* and how many of each vowel are in the file
*/

%{
int rows = 0;
int chars = 0;
int a = 0;
int e = 0;
int i = 0;
int o = 0;
int u = 0;
%}

%%

[\n]    {rows += 1;}

[aA]    {chars++; a++;}
[eE]    {chars++; e++;}
[iI]    {chars++; i++;}
[oO]    {chars++; o++;}
[uU]    {chars++; u++;}

.   {chars += 1;}

%%

int main(int argc, char *argv[]) {
    yylex();
    printf("rows: %d\n", rows);
    printf("As: %d\n", a);
    printf("Es: %d\n", e);
    printf("Is: %d\n", i);
    printf("Os: %d\n", o);
    printf("Us: %d\n", u);
    printf("characters: %d\n", chars);
    return 0;
}