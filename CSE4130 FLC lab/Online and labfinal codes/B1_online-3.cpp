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
    string name, data_type;
};
vector <SymbolTableStruct> table; // vector of SymbolTable structure

int table_input(){
    ifstream inputFile("input.txt");
    if(!inputFile){
        cerr<<"Error opening file."<<endl;
        return 1;
    }
    SymbolTableStruct tb;
    while(inputFile >> tb.si_no)
    {
        inputFile >> tb.name;
        inputFile >> tb.data_type;
        table.push_back(tb);
    }
    inputFile.close();
}
void displayTable(){
    if(table.size()>0){
        cout <<left<< setw(20) << "SI.No" << setw(20) << "Name" << setw(20) << "Data Type" << endl;
        cout<<"-------------------------------------------------------------------------------"<<endl;
        for(const auto& t: table){
            cout <<left<< setw(20) << t.si_no <<setw(20)<<  t.name <<setw(20)<<  t.data_type <<endl;
        }
        cout<<endl;
    }
    else cout<<"--Symbol table is empty."<<endl<<endl;
}
void userChoice(){
    SymbolTableStruct tb;
    string a,b,c;
        cout<<"Insert data: ";
        cin>>a>>b;
        cout<<"Insert Index: ";
        cin>>b;
        table[no-1].pushback(tb);
        cout<<endl;
        displayTable();
}

int main(){
    table_input();
    displayTable();
    userInput();
}
