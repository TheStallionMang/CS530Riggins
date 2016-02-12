/*  file_parser.cc
    Exception class for file_parser
    
    Team New Mexico: Arthur Flores, Christain, Jay, Nick Schneider
    Assignment Due Date: Tuesday, Feb 23rd
    
    CS530 Spring 2016
    Alan Riggins
*/ 


#include "file_parser.h"

using namespace std;

       // ctor, filename is the parameter.  A driver program will read
        // the filename from the command line, and pass the filename to
        // the file_parser constructor.  Filenames must not be hard-coded.
file_parser::file_parser(string filename){
	ifstream infile;
	string line;
	
	//if(argc != 2) print_error("There are too many arguments!"); //Captures error for arguments
	infile.open(filename.c_str(),ios::in); //reads in file
	if(!infile) file_parse_exception("File failed to open: " + filename); //There was no file, possibly place error for no file exists
	while(!infile.eof()){			//This while loop puts each line within the vector contents
		getline(infile,line);
		contents.push_back(line);
	}
	infile.close();
}
        
        // dtor
file_parser::~file_parser(){}
        
        // reads the source file, storing the information is some
        // auxiliary data structure you define in the private section. 
        // Throws a file_parse_exception if an error occurs.
        // if the source code file fails to conform to the above
        // specification, this is an error condition.     
void file_parser::read_file(){
	string delimiters = " \t";
	string comment = ".";
	for(unsigned int i=0; i < contents.size(); i++){
		s_line read_line;
		unsigned int type=0;
		string line = contents[i];
		int last = line.find_first_not_of(delimiters,0);
		int first = line.find_first_of(delimiters,last);
		string token = "";
		while(first != -1 || last != -1){
			token = line.substr(last,first-last);
			if(token.rfind(comment) != std::string::npos){ 
				// if you find a . for comment you take rest of line as comment
				type = 3;
				string tmp = token;
				last = line.find_first_not_of("",first);
				first = line.find_first_of("",last);
				if( first != -1 || last != -1){
				token = line.substr(last,first-last);
				tmp = tmp + token;
				}
				read_line.read_word(tmp,type);
				break;
			}
			if(type >= 3){	//if there are too many arguments
				cout << "Too many arguments in line blah" << endl;
				break;
			}
			read_line.read_word(token,type); // places token in correct position in struct
			last = line.find_first_not_of(delimiters,first);
			first = line.find_first_of(delimiters,last);
			type++;
			
		}	
		tokens.push_back(read_line);
	}
}
        
        // returns the token found at (row, column).  Rows and columns
        // are zero based.  Returns the empty string "" if there is no 
        // token at that location. column refers to the four fields
        // identified above.
string file_parser::get_token(unsigned int row, unsigned int column){
	if(row >= tokens.size()) file_parse_exception("No tokens exist on row: "+ row);
	switch(column){
		case 0:
			return tokens[row].label;
		case 1:
			return tokens[row].opcode;
		case 2:
			return tokens[row].operand;
		case 3:
			return tokens[row].comment;
		default:
			file_parse_exception("No token found at line: "+ row);
	}
	
}
       
        // prints the source code file to stdout.  Should not repeat 
        // the exact formatting of the original, but uses tabs to align
        // similar tokens in a column. The fields should match the 
        // order of token fields given above (label/opcode/operands/comments)
void file_parser::print_file(){
	for(unsigned int i=0;i < tokens.size(); i++){
		cout << tokens[i].label << '\t' << tokens[i].opcode << '\t' << tokens[i].operand <<
		'\t' << tokens[i].comment << endl;
	}	
}
        
        // returns the number of lines in the source code file
int file_parser::size(){
	return tokens.size();
}
        
////////////////////PRIVATE VARIABLES////////////////////////////////////

