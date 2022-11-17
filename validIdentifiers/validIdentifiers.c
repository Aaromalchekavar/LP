#include <stdio.h>

int firstchar(char ch){
    if(ch > '0' && ch <= '9') return 1;
    else return 0;
}

int isvalid(char ch){
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= '0' && ch <= '9'))
        return 1;
    else return 0;
}

int main(){
    char id[16];
    int i, flag = 1;
    printf("Enter an identifier : \t");
    scanf("%s",&id);
    
    //Condition 1
    if(firstchar(id[0])==1) flag = 0;
    //Condition 2
    for(i = 0; id[i] != '\0'; i++){
        if(isvalid(id[i])==0) flag = 0;
    }
    //Condition 3
    if(i>16) flag = 0;

    if(flag == 0) printf("Invalid Identifier");
    else printf("Valid Identifier");

    return 0;
}