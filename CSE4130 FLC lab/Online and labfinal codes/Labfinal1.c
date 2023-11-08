// Find total floating point user inputs
// create file input.txt in the same directory
#include<stdio.h>

int main()
{
    FILE *a;
    a = fopen("input.txt","r");
    int cnt  = 0;
    char line[1000];
    while(fgets(line,sizeof(line),a)){
        if(strstr(line,"scanf")){

           for(int i = 0; i<strlen(line)-1;i++){
            if(line[i] == '%' && line[i+1] == 'f')
                cnt++;
           }
        }
    }
  printf("Number of floating points as input : %d",cnt);

    return 0;
}
