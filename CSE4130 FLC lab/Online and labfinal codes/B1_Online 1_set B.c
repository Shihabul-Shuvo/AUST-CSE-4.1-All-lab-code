//CSE4130
//Fall-2022, Year: 4, Semester: 1,
//Name: Md. Shihabul Islam Shovo
//ID: 190204075
//Section: B1
//online-1, Set-02
#include <stdio.h>
int main(void)
{
    FILE *p1,*p2;
    char c, c2 = ' ';
    char s[20];
    int i=0;

    p1 = fopen("190204075_B.c","r");
    p2 = fopen("remove.txt", "w");

    //If file is not created then show this message
    if(!p1 && !p2)printf("\nFile not found");
    else{
        while((c = fgetc(p1))!= EOF)
        {
            if(c=='\n' || c==' ') i=0;
            if(c != ' ' || c!='\n')
            {
                s[i++] = c;
            }
            else if( s=="main"){
                while((c = fgetc(p1))!= '\n')
                {
                    if(c!='(' || c!=')')
                        fputc(c, p2);
                }
            }

        }
    }

    return 0;
}
