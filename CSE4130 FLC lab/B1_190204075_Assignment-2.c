#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

char ops[] = "+-*/%=<>!|&";
char pars[] = "(){}[]", op[5];
char seps[]=",;'\"";
char c,s[20];

FILE *rf,*wf;
int opflag=0;

//this function will take a file name input from user and open it in read mode
int read_file(){
    char filename[100];

    printf("\nEnter the filename: ");
    scanf("%s", filename);
    rf = fopen(filename, "r");
    if (rf == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
}

//this plainC() function removes all newline, extra spaces and comments from a c source code file
//one problem occurs for this function is
//it end with a unknown character in the end on the generated file
void plainC(){
    FILE *p2;
    char c, c2 = ' ';
    p2 = fopen("lexemes.txt", "w");

    while((c = fgetc(rf))!= EOF)
    {
        if(c==' ' || c=='\n'){
            fputc(' ', p2);
            while((c=fgetc(rf)) == ' ' | c == '\n');
        }
        if((c=='/') && ((c2 = fgetc(rf))== '/'))
        {
            while( ((c=fgetc(rf))!='\n'));
        }
        else if((c=='/') && (c2=='*'))
        {
            while((c!='/') && (c2 != '*'))
            {
                c2 = c;
                c = fgetc(rf);
            }
        }
        else {fputc(c, p2);}
        c2 = c;
    }
    fclose(p2);
    fclose(rf);

    p2 = fopen("lexemes.txt", "r");
    while((c = fgetc(p2))!= EOF)
    {
        printf("%c", c);
    }
    fclose(p2);
}
//isoperator() function will check for a operators
int isoperator(){
    int len=strlen(ops);
    for(int i=0; i<len; i++){
        if(ops[i] == c){
            op[opflag] = c;
            opflag++;
            if((c=fgetc(rf))!=EOF){
                isoperator();
            }
            return 1;
        }
    }
    if(opflag>0) {
        op[opflag] = '\0';
        fseek(rf, -1, SEEK_CUR);
        opflag=0;
    }
    return 0;
}
//isparenthesis() function will check for a parenthesis
int isprenthesis(){
    int len=strlen(pars);
    for(int i=0; i<len; i++){
        if(pars[i] == c){
            //printf("[par %c] ",c);
            return 1;
        }
    }
    return 0;
}
//isseparator() function will check for a separator
int isseparator(){
    int len=strlen(seps);
    for(int i=0; i<len; i++){
        if(seps[i] == c){
            //printf("[sep %c] ",c);
            return 1;
        }
    }
    return 0;
}
//isidentifier() function find the valid keywords also label as id and if not valid then label as unkn
int isidentifier(){
    int i=0,idflag=0;
    int len=strlen(s);
    if(s[0]=='_' || isalpha(s[0])){
        for(i=1; i<len; i++){
            if(s[i]=='_' || isalnum(s[i])){
                idflag=1;
            }else return 0;
        }
        idflag=1;
    }
    if(idflag==1){
        printf("[id %s] ",s);
        idflag=0;
        return 1;
    }
    return 0;
}
//check if the word is a number or not
int isnumber(){
    int len=strlen(s);
    int i, nflag=0;
    for(i=0; i<len; i++){
        if( isdigit(s[i]) ){
            nflag=1;
        }
        else if(s[i]=='.'){
            nflag=2;
            i++;
            break;
        }
        else {
            return 0;
        }
    }
    if(nflag==2){
        while(i<len){
            if(isdigit(s[i])){
                nflag=1;
            }
            else { return 0; }
            i++;
        }
    }
    if(nflag==1){printf("[num %s] ",s); return 1;}
    return 0;
}
//this function analyses all the words and find the lexemes
//this function produces expected result but returns with a error
//cause of error: unknown
int lexemes(){
    //read a file to get the lexemes
    read_file();
    while((c=fgetc(rf)) != EOF){
        int i=0;
        //read letters and store the word
        for(i=0; !(isspace(c))&& !(isoperator()) && !(isprenthesis()) && !(isseparator()); i++){
            //store the letters until there is a space, operator, parenthesis or separator
            // if isoperator function called this will store the operators
            // other function will only return a positive value or 1
            s[i] = c;
            c=fgetc(rf);
        }
        s[i]='\0';
        int len = strlen(s);
        if(len>0){
            //printf("\ncur word is: %s    ",s);
            if(strncmp(s, "int", 3) == 0 || strncmp(s, "double", 6) == 0 ||
                strncmp(s, "float", 5) == 0 || strncmp(s, "char", 4) == 0 ||
                strncmp(s, "string", 6) == 0 ){
                printf("[kw %s] ",s);
            }
            else if(strncmp(s, "for", 3) == 0 || strncmp(s, "while", 5) == 0 ||
                strncmp(s, "do", 2) == 0 || strncmp(s, "case", 4) == 0 ||
                strncmp(s, "if", 2) == 0 || strncmp(s, "else", 4) == 0 ||
                strncmp(s, "switch", 5) == 0){
                printf("[kw %s] ",s);
            }
            else if(isidentifier());
            else if(isnumber()){}
            else if(strncmp(s, "return", 5)==0){
                printf("[ret %s] ",s);
            }
            else{
                printf("[unkn %s] ",s);
            }
            s[0] = '\0';
        }
        if(strlen(op)>0){
            //if there is a operator stored from the call of isoperator() function in line 168
            printf("[op %s] ",op);
            op[0]='\0';
        }
        else if(isprenthesis()){
            //call the isparanthesis function and print the paranthesis
            printf("[par %c] ",c);
        }
        else if(isseparator()){
            //call the isoperator function and print the operator
            printf("[sep %c] ",c);
        }
    }
    fclose(rf);

}
int main()
{
    read_file();
    //to remove all the new line, extra white spaces and comments
    plainC();
    //get the lexemes and identify them
    lexemes();
    return 0;

}
