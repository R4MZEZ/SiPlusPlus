#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>

using namespace std;

static std::map<string, string> types = {
        {"char", "'a'"}, {"char16_t", "'b'"},
        {"char32_t" , "'c'"}, {"signed char", "'!'"},
        {"signed short int", "-32767"}, {"signed int", "-2147483647"},
        {"signed long int", "−922337203685477"}, {"signed long long int", "−922337203685477"},
        {"unsigned char", "'0'"}, {"unsigned short int", "65535"},
        {"unsigned int", "4294967295"}, {"unsigned long int", "4294967295"},
        {"unsigned long long int", "18446744073709551"}, {"float", "-123.123f"},
        {"double", "-123.4123"}, {"long double", "412.1341"},
        {"bool", "1"}
    };

static std::set<string> operations = {"+", "-", "*", "/"};

void read_type(ifstream* fin, string* var){
	while((*fin).is_open()){
		getline(*fin, *var);
		if (types.count(*var) == 1){
			cout << "Type '" << *var << "' correct!\n";
			break;
		}else{
			cout << "Type '" << *var << "' does not exist!\n";
		}
	}
}

void read_operation(ifstream* fin, string* oper){
	while((*fin).is_open()){
		getline(*fin, *oper);
		if (operations.count(*oper) == 1){
			cout << "Operation '" << *oper << "' correct!\n";
			break;
		}else{
			cout << "Operation '" << *oper << "' does not exist!\n";
		}
	}
}

int main(void){
    string type1, type2, operation;
	ifstream fin("src/input.txt");
    read_type(&fin, &type1);
	read_type(&fin, &type2);
	read_operation(&fin, &operation);

	ofstream fout("output/func.cpp");
	fout << "#include <iostream>" << endl;
	fout << "int main(void) {"<< endl;
	fout << "\t" << type1 << " var1 = " << types[type1] << ";" << endl;
	fout << "\t" << type2 << " var2 {" << types[type2] << "};" << endl;
	fout << "\tstd::cout << var1 << \"" << operation <<  "\" << var2 << \" = \" << var1 " << operation << " var2 << std::endl;"<< endl;
	fout << "\treturn 0;" << endl;
	fout << "}" << endl;
	fout.close();
	return 0;
}
