#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;


template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


bool is_line_safe(ifstream* infile) {
	string line;
	getline(*infile, line);
	int direction = 0;
	int last_num = -1;
	size_t start_pos = 0;
	size_t end_pos = 0;



	while (end_pos != string::npos) {
		
		end_pos = line.find(' ', start_pos + 1);
		int num = stoi(line.substr(start_pos, end_pos));

		if (last_num >= 0) {
			if (abs(num - last_num) > 3) return false;
			if (num - last_num == 0) 	 return false;
			
			int current_direction = sgn(num - last_num);
			bool swapped_direction =    (current_direction == 1 and direction == -1) 
									or (current_direction == -1 and direction == 1);

			if (swapped_direction) return false;
			direction = direction == 0 ? current_direction : direction;
		}

		last_num = num;
		start_pos = end_pos;
	}

	return true;
}


bool check_inputs(int& last_input, int& current_input, int& direction, int& error_count) {



	bool is_valid = true;

	is_valid = is_valid and not (abs(current_input - last_input) > 3);
	is_valid = is_valid and not (current_input - last_input == 0);
	
	int current_direction = sgn(current_input - last_input);
	bool swapped_direction =    (current_direction == 1 and direction == -1) 
							or (current_direction == -1 and direction == 1);
	is_valid = is_valid and not swapped_direction;
	is_valid = is_valid or last_input == -1;

	if (not is_valid) {
		if (error_count > 0) return false;
		error_count += 1;
	} else {
		if (last_input != -1)
			direction = direction == 0 ? current_direction : direction;
		last_input = current_input;
	}



	return true;
}




vector<int> next_line(ifstream* infile) {
	string line;
	getline(*infile, line);

	size_t start_pos = 0;
	size_t end_pos = 0;
	vector<int> result;

	while (end_pos != string::npos) {
		end_pos = line.find(' ', start_pos + 1);
		int num = stoi(line.substr(start_pos, end_pos));
		result.push_back(num);
		start_pos = end_pos;
	}

	return result;
}


int part_two(string input_path) {

	int result = 0;

	ifstream infile(input_path);

	

	
	while(not infile.eof()) {
		vector<int> inputs = next_line(&infile);

		int error_count = 0;
		int last_input = -1;
		int direction = 0;
		bool forwards_works = true;
		bool backwards_works = true;

		for (int i = 0; i < inputs.size(); ++i)
		{
			if (not check_inputs(last_input, inputs[i], direction, error_count))  {
				forwards_works = false; break;
			}

		}

		error_count = 0;
		last_input = -1;
		direction = 0;

		for (int i = inputs.size() - 1; i >= 0; --i)
		{
			if (not check_inputs(last_input, inputs[i], direction, error_count))  {
				backwards_works = false; break;
			}
		}
		

		bool is_valid = forwards_works || backwards_works;
		
		if (is_valid)
			result++;
	}

	infile.close();

	return result;
}





int part_one(string input_path) {
	ifstream infile(input_path);

	int result = 0;

	
	while(not infile.eof()) {
		result += is_line_safe(&infile);
	}

	return result;
}


int main() {
	cout << part_one("input.txt") << "\n";
	cout << part_two("input.txt") << "\n";
}