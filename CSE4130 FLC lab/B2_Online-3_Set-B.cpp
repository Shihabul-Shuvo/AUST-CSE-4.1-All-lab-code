#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<vector>
#include <iomanip>

using namespace std;
struct SymbolTableStruct{ // structure of the symbol table
    int si_no;
    string name, id_type, scope;
};
vector <SymbolTableStruct> table; // vector of SymbolTable structure
int getAttribute(){
    ifstream inputFile("input.txt");
    if(!inputFile){
        cerr<<"Error opening file."<<endl;
        return 1;
    }
    SymbolTableStruct s;
    while(inputFile >> s.si_no)
    {
        inputFile >> s.name;
        inputFile >> s.id_type;
        inputFile >> s.scope;
        table.push_back(s);
    }
    inputFile.close();
}
void lookUp(){
    // lookUp() function search for a name in the symbol table
    if(table.size()>0){
        string name, scope;
        cout<<"Enter a name and scope: ";
        cin>>name>>scope;

        SymbolTableStruct s;
        s.si_no = 0;
        s.name = name;
        s.id_type = "var";
        s.scope = scope;

        int flag =0;
        for(const auto& t: table){
            if(t.scope == scope){
                flag = 1;
            }
            if(flag ==1 && t.scope != scope){
                break;
            }
            s.si_no++;
        }

        if(flag==1){
            table.insert(table.begin() + s.si_no, s);
            for(int i=s.si_no; i<table.size(); i++){
                table[i].si_no = table[i].si_no + 1;
            }
        }
        else {
            s.si_no = table.size();
            table.insert(table.end(), s);
        }
    }
    else cout<<"--Symbol table is empty."<<endl<<endl;
}

void displayTable(){
    if(table.size()>0){
        cout <<left<< setw(20) << "SI.No" << setw(20) << "Name" << setw(20) << "ID Type" << setw(20) << "Scope" << endl;
        cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
        for(const auto& t: table){
            cout <<left<< setw(20) << t.si_no <<setw(20)<<  t.name <<setw(20)<<  t.id_type << setw(20)<<  t.scope << endl;
        }
        cout<<endl;
    }
    else cout<<"--Symbol table is empty."<<endl<<endl;
}

int main(){
    getAttribute();
    displayTable();
    lookUp();
    displayTable();
}
