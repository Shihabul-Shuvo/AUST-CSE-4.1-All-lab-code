/*Write a C program that will scan an input file (c source code) and find out the line numbers of
double floating numbers are declared in that input program.*/

#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *p1,*p2;
    char c, s[20];
    int line_no=1, db_in[10], cnt = 0;

    p1 = fopen("FileCompile.c","r");
    p2 = fopen("output.txt","w");

    //If file is not created then show this message
    if(!p1)printf("\nFile not found");

    /*if File is created then
     remove the spaces, empty line & comments*/

    else
    {
        while((c = fgetc(p1))!= EOF)
        {
            if(c=='\n'){
                line_no++;
            }
            if(c=='d')
            {
                int i = 0;
                s[i] = c;
                //for loop to get a word
                for(i=1; (c = fgetc(p1))!=' ' && c !='\n' ; i++)
                {
                    s[i] = c;
                }
                s[i] = '\0';
                if(c=='\n'){
                    line_no++;
                }
            }

            //check if the word is main
            if(strncmp(s,"double", 6) == 0)
            {
                s[0] = '\0';
                db_in[cnt]= line_no;
                cnt++;
            }
            fputc(c,p2);
        }
    }
    fclose(p1);
    fclose(p2);
    //printf("\nTotal line of code: %d", line_no);
    printf("\nLine no. of double numbers declared in: ");
    for(int j=0; j<cnt; j++){
        printf("%d, ",db_in[j]);
    }
    return 0;
}
