%{
    #include<stdio.h>
%}
%token NAME NUMBER
%%
statement : E { printf("Answer=%d\n",$1);}
 ;
E:E'+' NUMBER{$$ = $1+$3;}
 |E '-' NUMBER {$$ = $1-$3;}
 |E '*' NUMBER {$$ = $1*$3;}
 |E '/' NUMBER { if ($3!=0){ $$ = $1/$3; }else { printf("Error: divide by Zero"); } }
 |NUMBER {$$=$1;}
 ;

%%
int main()
{
yyparse();
return 0;
}
int yyerror(char *s)
{
 printf("%s",s);
}