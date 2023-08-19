// Detect pattern
// s-> pXr | Yst, X-> q|pY, Y-> r
#include<iostream>
#include<string>
using namespace std;
int main(){
    string s="pprr";
    int f=0;
    if(s[0] =='p'){
        if(s[1]=='q' && s[2]=='r')
            f=1;
        else if(s[1]=='p' && s[2]=='r' && s[3]=='r')
            f=1;
    }
    else if(s[0] == 'r' && s[1]=='s' && s[2]=='t'){
        f=1;
    }
    if(f==1) cout<<"String is valid"<<endl;
    else cout<<"String is invalid"<<endl;

    return 0;
}
