#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *p1,*p2;
    char c, s[20];
    int cnt = 0;

    p1 = fopen("test.c","r");

    //If file is not created then show this message
    if(!p1)printf("\nFile not found");

    /*if File is created then
     remove the spaces, empty line & comments*/

    else
    {
        while((c = fgetc(p1))!= EOF)
        {
            if(c!=' ' || c!='\n' )
            {
                int i = 0;
                s[i] = c;
                //for loop to get a word
                for(i=1; (c = fgetc(p1))!=' ' && c!='(' && c!='\n'; i++)
                {
                    s[i] = c;
                }
                s[i] = '\0';
                /*if(strncmp(s,"main", 4) == 0 ||strncmp(s,"if", 2) == 0 ||strncmp(s,"for", 3) == 0 || strncmp(s,"while", 5) == 0){
                    while((c=fgetc(p1)) != ')' );
                }*/
                if(c=='(' && !(strncmp(s,"main", 4) == 0 ||strncmp(s,"if", 2) == 0 ||strncmp(s,"for", 3) == 0 || strncmp(s,"while", 5) == 0)){
                    printf("s= %s\n",s);
                    s[0] = '\0';
                    cnt++;
                }
            }
        }
    }
    fclose(p1);
    printf("%d ",cnt);
    return 0;
}
