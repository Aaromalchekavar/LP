%{
int COMMENT=0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*


%%
#.* {printf("\n%s is a preprocessor directive",yytext);}
int |float |char |double |while |for |struct |typedef |do |if |break |continue |void |switch |return |else |goto {printf("\n\t%s is a keyword",yytext);}
"/*" {COMMENT=1;}{printf("\n\t %s is a COMMENT",yytext);}

// check func if not comment
{identifier}\( {if(!COMMENT)printf("\nFUNCTION \n\t%s",yytext);}

//check block begining if not comment
\{  {if(!COMMENT)printf("\n BLOCK BEGINS");}

//check block end  if not comment
\}  {if(!COMMENT)printf("BLOCK ENDS ");}

//check for identifier if not comment
{identifier}(\[[0-9]*\])? {if(!COMMENT) printf("\n %s IDENTIFIER",yytext);}

//check for string if not comment
\".*\" {if(!COMMENT)printf("\n\t %s is a STRING",yytext);}

//check for number if not comment
[0-9]+ {if(!COMMENT) printf("\n %s is a NUMBER ",yytext);}

\)(\:)? {if(!COMMENT)printf("\n\t");ECHO;printf("\n");}
\( ECHO;

//check for assignment operator
= {if(!COMMENT)printf("\n\t %s is an ASSIGNMENT OPERATOR",yytext);}

//check for relational operator
\<= |\>= |\< |== |\> {if(!COMMENT) printf("\n\t%s is a RELATIONAL OPERATOR",yytext);}
%%


int main(int argc, char **argv)
{
FILE *file;
file=fopen("var.c","r");
if(!file)
{
printf("could not open the file");
exit(0);
}
yyin=file;
yylex();
printf("\n");
return(0);
}
int yywrap()
{
return(1);
}