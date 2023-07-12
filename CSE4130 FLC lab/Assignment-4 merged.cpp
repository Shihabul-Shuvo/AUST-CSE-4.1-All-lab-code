#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<iomanip>
#include<algorithm>

using namespace std;

// variable declaration
ifstream rf;
ofstream wf;
vector<string> kws = { "auto", "break", "case", "char", "const", "continue", "default",
                    "do", "double", "else", "enum", "extern", "float", "for", "goto",
                    "if", "inline", "int", "long", "register", "restrict", "return",
                    "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
                    "union", "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary" };
vector<string> ids; //stores all the indentifier
string ops = "+-*/%=<>!|&";
string pars = "(){}[]";
string seps = ",;'\"";
string op;
char c;
string s;
struct TokenStruct { // structure of a token
    int no;
    string type;
    string value;
};
vector <TokenStruct> token; // vector of TokenStruct structure
struct SymbolTableStruct{ // structure of the symbol table
    int si_no;
    string name, id_type, data_type, scope, value;
};
vector <SymbolTableStruct> table; // vector of SymbolTable structure
vector <pair<string, string>> tokens;

// User Defined function as needed
int read_file(string filename) {
    // This function will take a file name input from the user and open it in read mode
    rf.open(filename);
    if (!rf) {
        cout << "Error opening file.\n";
        return 1;
    }
    return 0;
}
void plainC() {
    // This plainC() function removes all newlines, extra spaces, and comments from a C source code file
    FILE *readFile,*writeFile;
    char c1, c2 = ' ';
    int line_no = 1;
    readFile = fopen("input.txt","r");
    writeFile = fopen("plainC.txt", "w");

    //If file is not created then show this message
    if(!readFile)cout<<"\nFile not found";

    /*if File is created then
     remove the spaces, empty line & comments*/

    else
    {
        c1 = fgetc(readFile); c1 = fgetc(readFile);
        c1 = fgetc(readFile); //to avoid garbage value at the start of the file
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

    /*readFile = fopen("plainC.txt", "r");
    while((c1 = fgetc(readFile))!= EOF)
    {
        cout<<c1;
    }
    cout<<endl;
    fclose(readFile);*/
}
int isoperator() {
    // isoperator() function will check for an operator
    if (ops.find(c) != string::npos) {
        op += c;
        if ((c = rf.get()) != EOF) {
            isoperator();
        }
        return 1;
    }

    if (!op.empty()) {
        rf.unget();
        return 0;
    }
    return 0;
}
int isprnorsep(string str) {
    // isprnorsep() function will check for a parenthesis or separator
    if (str.find(c) != string::npos) {
        return 1;
    }
    return 0;
}
int iskeyword() {
    for (const string& keyword : kws) {
        if (s == keyword) {
            return 1;
        }
    }
    return 0;
}
int isidentifier() {
    // isidentifier() function finds the valid keywords also labeled as id and if not valid then labeled as unkn
    for (int i = 1; i < ids.size(); i++) {
        if (s == ids[i]) {
            return 1;
        }
    }

    int len = s.length();
    if (s[0] == '_' || isalpha(s[0])) {
        for (int i = 1; i < len; i++) {
            if (s[i] == '_' || isalnum(s[i])) {
                continue;
            }
            else {
                return 0;
            }
        }
        ids.push_back(s);
        return 1;
    }
    return 0;
}
int isnumber() {
    // Check if the word is a number or not
    int len = s.length();
    int i, nflag = 0;
    for (i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            nflag = 1;
        }
        else if (s[i] == '.') {
            nflag = 2;
            i++;
            break;
        }
        else {
            return 0;
        }
    }
    if (nflag == 2) {
        while (i < len) {
            if (isdigit(s[i])) {
                nflag = 1;
            }
            else {
                return 0;
            }
            i++;
        }
    }
    if (nflag == 1) {
        return 1;
    }
    return 0;
}
void insertToken(string type, string str){
    // insert tokens to a vector of structure
    TokenStruct newtoken;
    newtoken.no = token.size() + 1;
    newtoken.type = type;
    newtoken.value = str;

    token.push_back(newtoken);
}
int lexemes() {
    cout<<"Step 1: Intermediate Output: Recognized tokens in the lines of code."<<endl;
    // This function analyzes all the words and finds the lexemes
    // Read a c file to get the source code
    if (read_file("plainC.txt") != 0) {
        return 1;
    }
    wf.open("input1.txt");
    int err=0;
    c = rf.get(); // to read the first line no value
    s=c; insertToken("lno", s); wf<<"[lno "<<s<<"] ";  s.clear(); cout<<c; c = rf.get(); cout<<c;
    while ((c = rf.get()) != EOF) {
        if(c=='\n'){
            cout<<c;
            c = rf.get(); cout<<c;
            while(isdigit(c)) {s+=c; c = rf.get(); cout<<c;}
            insertToken("lno", s);
            wf<<"[lno "<<s<<"] ";
            s.clear();
        }
        if(isspace(c)){
            cout<<c;
            continue;
        }
        // Read letters and store the word
        for (int i = 0; !isspace(c) && !isoperator() && !isprnorsep(pars) && !isprnorsep(seps); i++) {
            // Store the letters until there is a space, operator, parenthesis, or separator
            // If isoperator() function is called, this will store the operator or consecutive operators
            // Other functi ons will only return a positive value or 1
            s += c;
            c = rf.get();
        }
        if (!s.empty()) {
            if (iskeyword()) {cout<<"kw "<<s<<" "; insertToken("kw", s); wf<<"[kw "<<s<<"] ";} // insertToken(string , string) receives two string value and insert as token
            else if (isidentifier()) {cout<<"id "<<s<<" "; insertToken("id", s); wf<<"[id "<<s<<"] ";}
            else if (isnumber()) {cout<<"num "<<s<<" "; insertToken("num", s); wf<<"[num "<<s<<"] ";}
        }
        if (!op.empty()) {
            // If there is an operator stored from the previous call of isoperator() function tokenize the operator
            insertToken("op", op); wf<<"[op "<<op<<"] ";
            cout<<"op "<<op<<" "; op.clear(); // clear the operator so that next time it don't contain any value if isoperator() function don't assign any value to op
        }
        else if (isprnorsep(pars)) {
            // Call the isprnorsep() function and tokenize the parenthesis
            s=c; // converts char to string
            insertToken("par", s); wf<<"[par "<<s<<"] ";
            cout<<"par "<<s<<" ";
        }
        else if (isprnorsep(seps)) {
            // Call the isprnorsep() function and tokenize the separator
            s=c;
            insertToken("sep", s); wf<<"[sep "<<s<<"] ";
            cout<<"sep "<<s<<" ";
        }
        s.clear();
    }
    rf.close();
    wf.close();
    cout<<endl;
    return 0;
}
int tokenize(){
    ifstream inputFile("input1.txt");
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
}
bool searchByString(const SymbolTableStruct& obj, const string& value) {
    return obj.name == value;
}
void free(){
    // Delete all the entry from symbol table
    if(table.size()>0){
        table.erase(table.begin(),table.end());
        cout<<"--All entry cleared successfully."<<endl<<endl;
    }
    else cout<<"--Symbol table is already empty."<<endl<<endl;
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
void displayLexemes(){
    cout << left << setw(7) <<"No" << setw(12)<< "Type" <<setw(12)<< "Value" << "|| "
            << setw(7) <<"No" << setw(12)<< "Type" <<setw(12)<< "Value" << "|| "
            << setw(7) <<"No" << setw(12)<< "Type" <<setw(12)<< "Value" << endl;
            cout<<"----------------------------------------------------------------------------------------------"<<endl;
    for(int i=0; i<token.size(); i++){
        TokenStruct& t = token[i];
        cout <<left<<setw(7)<< t.no <<setw(12)<<  t.type <<setw(12)<< t.value << "|| ";
        t = token[++i];
        cout << setw(7)<< t.no <<setw(12)<<  t.type <<setw(12)<< t.value << "|| ";
        t = token[++i];
        cout << setw(7)<< t.no <<setw(12)<<  t.type <<setw(12)<< t.value <<endl;
    }
    cout<<endl;
}
void userChoice(){
    int choice;
    while(1){
        cout<<"Choose an option: " << endl
            << " 1. Lookup: Search for a name on the symbol table. " << endl
            << " 2. Free: remove all entries." << endl
            << " 3. Display Symbol table" << endl
            << " 4. Display the lexemes" << endl
            << " 5. Exit" << endl
            << "\nEnter your choice: \n";
            cin>>choice;
            if(choice == 1) lookUp();
            else if(choice == 2) free();
            else if(choice == 3) displayTable();
            else if(choice == 4) displayLexemes();
            else exit(0);
    }
}
void detectErrors(){
    cout<<"\nStep 2: Detected errors:"<<endl;
    int errors=1;
    string lno="0";
    int sb=0, sc=0, cm=0, kw=0, ifs=0, elf=0, other=0;
    for(int i=0; i<token.size(); i++){
        TokenStruct& t = token[i];
        if(t.type=="lno"){
                if(sb>1)
                    cout<<"Error "<<errors++ <<" : Misplaced '{' at line "<<lno<<endl;
                if(sb<-1)
                    cout<<"Error "<<errors++ <<" : Misplaced '}' at line "<<lno<<endl;
                lno = t.value;
                sb=sc=cm=kw=other=0;
        }
        else {
            other++;
            if(other!=0 && t.value!=";") sc=0;
            if(other!=0 && t.value!=",") cm=0;
            if(other!=0 && t.type!="kw") kw=0;
        }
        if(t.type=="par"){
            if(t.value=="{") sb++;
            else if(t.value=="}") sb--;
        }
        if(t.type == "sep"){
            if(t.value==";") {
                sc++;
                if(sc>1)
                    cout<<"Error "<<errors++ <<" : Duplicate \";\" at line "<<lno<<endl;
            }
            else if(t.value==",") {
                cm++;
                if(cm>1)
                    cout<<"Error "<<errors++ <<" : Duplicate \",\" at line "<<lno<<endl;
            }
        }
        else if(t.type == "kw" && t.value!="if" && t.value!="else" &&t.value!="for" && t.value!="while"&& t.value!="return"){
            kw++;
            if(kw>1)
                cout<<"Error "<<errors++ <<" : Duplicate keywords at line "<<lno<<endl;
        }
        else if(t.type=="kw" && t.value=="if"){
                ifs=1;
        }
        else if(t.type=="kw" && t.value=="else" && token[i+1].value=="if"){
            if(ifs==0)
                cout<<"Error "<<errors++ <<" : Unmatched 'else if' at line "<<lno<<endl;
            i++; ifs=0; elf=1;
        }
        else if(t.type=="kw" && t.value=="else"){
            if(ifs==0 && elf==0)
                cout<<"Error "<<errors++ <<" : Unmatched 'else' at line "<<lno<<endl;
            ifs=elf=0;
        }
    }
}
// Main function
int main() {
    //freopen("output.txt", "w", stdout);
    plainC();
    //fist step is in function lexemes
    if (lexemes() != 0) {
        cerr<<"Ërror opening file"<<endl;
    }
    tokenize();
    //for(const auto& token : tokens){
      //  cout<<token.first<<" "<<token.second<<"  ";
    //}
    generateSymbolTable();
    detectErrors(); // step 2
    userChoice();

    return 0;
}
