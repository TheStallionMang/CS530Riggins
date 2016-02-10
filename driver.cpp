#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "file_parser.h"

using namespace std;


int main(int argc, char** argv) {
		file_parser p(argv[1]);
		p.read_file();
		p.print_file();
		cout << p.get_token(0, 0) << endl;
		cout << p.get_token(0, 1) << endl;
		cout << p.get_token(0, 2) << endl;
		cout << p.get_token(0, 3) << endl;
		cout << p.size() << endl;
		
		return 0;
}
