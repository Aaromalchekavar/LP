%{
    #include<stdio.h>
    #include<stdlib.h>
%}

%token A B NL
%%
stmt: S NL {printf("valid"); exit(0);}
S   : A S B
    |
    ;
%%

int yyerror(char *msg){
    printf("Invalid");
    exit(0);
}

int main(){
    printf("Enter Number :");
    yyparse();   
}