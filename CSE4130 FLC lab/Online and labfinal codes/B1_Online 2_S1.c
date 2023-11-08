/*
 Course No.: CSE4130
 Session : Fall 2022
 ID: 190204075
 Group: B1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

char ops[] = "+-*/%=<>!|&";
char pars[] = "(){}[]", op[5];
char seps[]=",;'\"";
char ids[100][20];
char c,s[20];
int err=0;

FILE *rf,*wf;
int totid=1, totkw = 11, opflag=0;
int valid=0;

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
//isoperator() function will check for a operator
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
//check if the word is a number or not
int isnumber(){
    int len=strlen(s);
    int i, nflag=0;
    // this condition will check if the number structure is d.dd
    if( isdigit(s[0]) && s[1]=='.' && isdigit(s[2])){
            nflag=1;
    }
    if(nflag==1){
        //this for loop will check if rest of the characters are digits or not
        for(i=3; i<len; i++){
            if(isdigit(s[i])){
                nflag=2;
            }
            else{
                nflag=0;
                break;
            }
        }
    }
    if(nflag==2){
        return 1;
    }
    else
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
            if(isnumber()){
                //printf("%s ",s);
                valid++;
            }
            s[0] = '\0';
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
    printf("Numbers of floating point numbers: %d", valid);
    return 0;

}
