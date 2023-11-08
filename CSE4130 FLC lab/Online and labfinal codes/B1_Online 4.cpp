/*
Name: MD Shihabul Islam Shovo
ID: 190204075
Group: B1
}
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<iomanip>
#include<algorithm>

using namespace std;
void plainC() {
    // This plainC() function removes all newlines, extra spaces, and comments from a C source code file
    FILE *readFile,*writeFile;
    char c1='\0', c2 = ' ';
    int line_no = 1;
    readFile = fopen("input4.c","r");
    writeFile = fopen("plainC.txt", "w");

    //If file is not created then show this message
    if(!readFile)cout<<"\nFile not found"<<endl;

    /*if File is created then
     remove the spaces, empty line & comments*/

    else
    {
        fprintf(writeFile, "%d ", line_no++);
        while((c1 = fgetc(readFile))!= EOF)
        {
            if(c1==' '){
                fputc(' ', writeFile);
                while((c1=fgetc(readFile)) == ' ');
            }
            if((c1=='\n')){
                fputc('\n', writeFile);
                fprintf(writeFile, "%d ", line_no++);
                continue;
            }
            if((c1=='/') && ((c2 = fgetc(readFile))== '/')){
                while((c1=fgetc(readFile))!='\n');
                fputc('\n', writeFile);
                fprintf(writeFile, "%d ", line_no++);
            }
            else if((c1=='/') && (c2=='*')){
                c2 = c1; c1 = fgetc(readFile);
                if(c1=='\n'){
                    fputc('\n', writeFile);
                    fprintf(writeFile, "%d ", line_no++);
                }
                while((c1!='/') && (c2 != '*')) {
                    c2 = c1;
                    c1 = fgetc(readFile);
                    if(c1=='\n'){
                        fputc('\n', writeFile);
                        fprintf(writeFile, "%d ", line_no++);
                    }
                }
            }
            else{
                fputc(c1, writeFile);
            }
            c2 = c1;
        }
    }
    fclose(readFile);
    fclose(writeFile);
}
void curly(){
    FILE* rf;
    rf = fopen("plainC.txt","r");
    int cb=0;
    char c1='\0',c='1';
    if(!rf)cout<<"\nFile not found"<<endl;
    else{
        while((c1 = fgetc(rf))!= EOF){
        if(c1=='\n'){
            c1 = fgetc(rf);
            c=c1;
        }
            if(c1=='{')
                cb++;
            if(c1=='}')
                cb--;
            if(cb<0) {cout<<"Misplaced Curly Brace at Line Number "<<c<<endl;
                cb=0;
            }
        }
    }
    fclose(rf);
}
int main()
{
    plainC();
    curly();
}
