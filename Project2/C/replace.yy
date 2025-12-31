/**
* Hello World: replace "sadness" with "happiness""
*/

%%

sadness    printf("happiness");

%%

int main ( int argc, char *argv[] ) {

	yylex();

	return 0;

}