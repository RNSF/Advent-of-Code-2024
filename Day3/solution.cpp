
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int part_one(string input_path) {
	ifstream infile(input_path);

	int result = 0;
	string line;


	
	while(not infile.eof()) {
		size_t start_pos = 0;
		getline(infile, line);

		while (true) {
			start_pos = line.find("mul", start_pos);
			if (start_pos == string::npos) break;
			start_pos += 3;
			if (line[start_pos] != '(') continue;
			start_pos++;
			size_t end_pos = start_pos;
			while(isdigit(line[end_pos]) and end_pos < line.size()) end_pos++;
			if (end_pos >= line.size()) break;
			if (line[end_pos] != ',') {start_pos = end_pos; continue;}
			int num1 = stoi(line.substr(start_pos, end_pos));
			end_pos++;
			if (end_pos >= line.size()) break;


			start_pos = end_pos;
			while(isdigit(line[end_pos]) and end_pos < line.size()) end_pos++;
			if (end_pos >= line.size()) break;
			if (line[end_pos] != ')') {start_pos = end_pos; continue;}
			int num2 = stoi(line.substr(start_pos, end_pos));
			end_pos++;
			start_pos = end_pos;
			result += num1 * num2;
			if (end_pos >= line.size()) break;
		}
		
	}

	return result;
}


int part_two(string input_path) {
	ifstream infile(input_path);

	int result = 0;
	bool is_enabled = true;
	string line;
	
	
	
	while(not infile.eof()) {
		size_t pos = 0;
		getline(infile, line);

		size_t next_dont = line.find("don't()");
		size_t next_do = line.find("do()");

		while (true) {



			if (not is_enabled) {
				next_do = line.find("do()", pos);
				if (next_do == string::npos) break;
				pos = next_do + 4;
				is_enabled = true;

				next_dont = line.find("don't()", pos);
			}

			// FIND mul(
			pos = line.find("mul(", pos);
			if (pos == string::npos) {
				if (next_dont != string::npos) is_enabled = false;
				break;
			}

			pos += 4;
			if (next_dont != string::npos and pos >= next_dont) {is_enabled = false; continue;}
			

			// FIND X,Y
			size_t num1_start = pos;

			while(isdigit(line[pos]) and pos < line.size() - 1) pos++;
			if (pos >= line.size()) break;
			if (next_dont != string::npos and pos >= next_dont) {is_enabled = false; continue;}
			int num1 = stoi(line.substr(num1_start, pos));
			if (line[pos] != ',') continue;
			pos++;
			if (pos >= line.size()) break;


			size_t num2_start = pos;
			while(isdigit(line[pos]) and pos < line.size() - 1) pos++;
			if (pos >= line.size()) break;
			if (next_dont != string::npos and pos >= next_dont) {is_enabled = false; continue;}
			int num2 = stoi(line.substr(num2_start, pos));
			if (line[pos] != ')') continue;
			pos++;

			result += num1 * num2;

			if (pos >= line.size()) break;
		}
		
	}

	return result;
}


int main() {
	cout << part_one("input.txt") << "\n";
	cout << part_two("input.txt") << "\n";
}