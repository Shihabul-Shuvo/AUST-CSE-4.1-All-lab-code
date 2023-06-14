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
    string name, id_type, data_type, scope, value;
};
vector <SymbolTableStruct> table; // vector of SymbolTable structure
vector <pair<string, string>> tokens;

int tokenize(){
    ifstream inputFile("input.txt");
    if(!inputFile){
        cerr<<"Error opening file."<<endl;
        return 1;
    }
    string tokenType;
    string word;
    while(inputFile >> tokenType)
    {
        inputFile >> word;
        tokenType.erase(tokenType.begin());
        word.erase(word.end() - 1);
        tokens.push_back(make_pair(tokenType, word));
    }
    inputFile.close();
}
void addNewRow(int no,string name,string id,string data,string scope,string value){
    SymbolTableStruct addRow;
    addRow.si_no = no;
    addRow.name = name;
    addRow.id_type = id;
    addRow.data_type = data;
    addRow.scope = scope;
    addRow.value = value;
    table.push_back(addRow);
}
bool isdatatype(string str) {
    vector<string> dt = { "int", "float", "double", "char", "bool", "vector", "string" };
    for (const string& datatype : dt) {
        if (str == datatype) {
            return true;
        }
    }
    return false;
}
int setAttribute(int i, string scopee){
    //find id the variable already exist in the symbol table and if it has assigned a value
    //then update the value in symbol table
    string idName = tokens[i].second;

    for(auto& updatetable: table){
        if(idName==updatetable.name && updatetable.id_type=="var" && scopee==updatetable.scope){
            if(tokens[++i].second == "="){
                string varValue = "\0";
                if(tokens[++i].first == "num")
                    varValue = tokens[i].second;
                else i--;
                updatetable.value = varValue;
                break;
            }else i--;
        }
    }
    return i;
}
void generateSymbolTable(){
    int no= 1;
    //string dataTypes = "intfloatdoublecharboolvectorstring";
    string scope = "Global";
    for(int i=0; i<tokens.size(); i++){
        string tokenType= tokens[i].first;
        string tokenName = tokens[i].second;

        //size_t startpos = 0;
        //size_t validType = tokenName.find_first_of(dataTypes, startpos);

        if(tokenType == "kw" && isdatatype(tokenName)/*&& validType!=string::npos*/ ){ // tokenName is datatype
            //cout<<"found ";
            if(tokens[++i].first == "id"){
                string idName = tokens[i].second;


                if(tokens[++i].first=="sep" || tokens[i].first=="par" || tokens[i].first=="op"){
                    if(tokens[i].second == "("){
                        //cout<<"found ";
                        addNewRow(no, idName, "func", tokenName, "Global", "\0");
                        no=no+1;
                        scope = idName;
                    }
                    else if(tokens[i].second == "=" || tokens[i].second == ";" || tokens[i].second == "," || tokens[i].second == ")"){
                        string varValue = "\0";
                        if(tokens[i].second == "="){
                            if(tokens[++i].first == "num")
                                varValue = tokens[i].second;
                            else i--;
                        }
                        addNewRow(no++, idName, "var", tokenName, scope, varValue);
                    }

                } else i--;
            } else i--;
        }
        else if(tokens[i].first == "id"){
            i = setAttribute(i, scope);
        }

    }
    cout<<endl;
}
void free(){
    // Delete all the entry from symbol table
    if(table.size()>0){
        table.erase(table.begin(),table.end());
        cout<<"--All entry cleared successfully."<<endl<<endl;
    }
    else cout<<"--Symbol table is already empty."<<endl<<endl;
}
bool searchByString(const SymbolTableStruct& obj, const string& value) {
    return obj.name == value;
}
void lookUp(){
    // lookUp() function search for a name in the symbol table
    if(table.size()>0){
        string searchName;
        cout<<"Enter a name to search: ";
        cin>>searchName;
        auto stringResult = find_if(table.begin(), table.end(),
            [searchName](const SymbolTableStruct& obj) { return searchByString(obj, searchName); });
        if (stringResult != table.end()) {
            cout << "--Result: The searched name's SI.No is: " << stringResult->si_no << endl<<endl;
        }
        else {
            cout << "--Error: Name \""<<searchName  <<"\" doesn't exist on the symbol table!" << endl<<endl;
        }
    }
    else cout<<"--Symbol table is empty."<<endl<<endl;
}
void displayTable(){
    if(table.size()>0){
        cout <<left<< setw(20) << "SI.No" << setw(20) << "Name" << setw(20) << "ID Type" << setw(20) << "Data Type" << setw(20) << "Scope" << setw(20) << "Value" << endl;
        cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
        for(const auto& t: table){
            cout <<left<< setw(20) << t.si_no <<setw(20)<<  t.name <<setw(20)<<  t.id_type <<setw(20)<<  t.data_type <<setw(20)<<  t.scope <<setw(20)<< t.value << endl;
        }
        cout<<endl;
    }
    else cout<<"--Symbol table is empty."<<endl<<endl;
}
void userChoice(){
    int choice;
    while(1){
        cout<<"Choose an option: " << endl
            << " 1. Lookup: Search for a name on the symbol table. " << endl
            << " 2. Free: remove all entries." << endl
            << " 3. Display Symbol table" << endl
            << " 4. Exit" << endl
            << "\nEnter your choice: ";
            cin>>choice;
            if(choice == 1) lookUp();
            else if(choice == 2) free();
            else if(choice == 3) displayTable();
            else exit(0);
    }
}

int main(){
    tokenize();

    //for(const auto& token : tokens){
      //  cout<<token.first<<" "<<token.second<<"  ";
    //}
    generateSymbolTable();
    userChoice();
}
