/*Write a C program that will scan an input file (c source code) and find out how many input and
output functions are used in that input program.*/


#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *p1,*p2;
    char c, s[20];
    int input=0, output = 0;

    p1 = fopen("FileCompile.c","r");

    //If file is not created then show this message
    if(!p1)printf("\nFile not found");

    /*if File is created then
     remove the spaces, empty line & comments*/

    else
    {
        while((c = fgetc(p1))!= EOF)
        {
            if(c=='p' || c=='s')
            {
                int i = 0;
                s[i] = c;
                //for loop to get a word
                for(i=1; ((c = fgetc(p1))!=' ') && (c !='('); i++)
                {
                    s[i] = c;
                }
                s[i] = '\0';
            }

            //check if the word is main
            if(strncmp(s,"scanf", 5) == 0)
            {
                s[0] = '\0';
                input++;
            }
            else if(strncmp(s,"printf", 5) == 0){
                output++;
                s[0] = '\0';
            }
        }
    }
    fclose(p1);
    printf("No. of input function: %d\n", input);
    printf("No. of output function: %d", output);
    return 0;
}
