#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *p1,*p2;
    char c, s[20];
    int flag1=0, flag2=0;

    p1 = fopen("FileCompile.c","r");

    //If file is not created then show this message
    if(!p1)printf("\nFile not found");

    /*if File is created then
     remove the spaces, empty line & comments*/

    else
    {
        while((c = fgetc(p1))!= EOF)
        {
            if(c!=' ' && flag1 == 0)
            {
                int i = 0;
                s[i] = c;
                //for loop to get a word
                for(i=1; ((c = fgetc(p1))!=' ') && (c !='('); i++)
                {
                    s[i] = c;
                }

                //check if the word is main
                if(strncmp(s,"main", 4) == 0)
                {
                    flag1 = 1;
                    if(c!='(')
                    {
                        while((c = fgetc(p1))!='(');
                    }
                    i=0;
                    while((c = fgetc(p1))!=')')
                    {
                        s[i] = c;
                        i++;
                    }
                    s[i]= '\0';
                    printf("Parameter(s): %s",s);
                    i=0;
                }

            }
            // find return value
            if(c!=' '&& flag2 == 0)
            {
                int i=0;
                s[i] = c;
                //for loop to get a word
                for(i=1; (c = fgetc(p1))!=' '; i++)
                {
                    s[i] = c;
                }
                if(strncmp(s, "return" , 6) == 0)
                {
                    while((c = fgetc(p1))==' ');
                    printf("\nReturn value: %c",c);
                    flag2 = 1;
                }
            }
            if(flag1 == 1 && flag2 == 1) break;

        }
    }
    fclose(p1);
    return 0;
}
