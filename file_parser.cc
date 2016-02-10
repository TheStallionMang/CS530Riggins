/*  file_parser.cc
    Exception class for file_parser
    
    Team New Mexico: Arthur Flores, Christain, Jay, Nick
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
	for(unsigned int i=0; i < contents.size(); i++){
		s_line read_line;
		string word;
		char *c = &contents[i][0];
		bool comment = false;
		unsigned int type = 0;
		
		while(*c != '\n'){
			if( *c == '.'){
				comment = true;
				type = 3;
			}
			else if(isspace(*c) && type != 3){ //This detects a space
				read_line.read_word(word,type);
				while(isspace(*c)) c++;
				type++;
			}
			else{
				word += *c;
			}
			c++;
			if(type > 3) file_parse_exception("Too many tokens on line: "+ i); //convert i to string for error
		} // end while loop
		read_line.read_word(word,type);
		tokens.push_back(read_line);	
	}//end for loop


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
	for(int i=0;i < tokens.size(); i++){
		cout<<token[i].label << '\t' << token[i].opcode << '\t' << token[i].operand << '\t' << token[i].comment << endl;
		
	}

}
        
        // returns the number of lines in the source code file
int file_parser::size(){
	return tokens.size();
}
        
////////////////////PRIVATE VARIABLES////////////////////////////////////

