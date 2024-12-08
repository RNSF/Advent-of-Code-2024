
#include <array>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


typedef struct puzzle_t {
	string contents;
	size_t width;
} puzzle_t;

array<char, 4> LETTERS = {'X', 'M', 'A', 'S'};


bool has_letter_at(puzzle_t puzzle, char letter, int pos_x, int pos_y)
{
	if (pos_x < 0 or pos_x >= puzzle.width or pos_y < 0 or pos_y >= puzzle.width) return false;
	return puzzle.contents[pos_x + pos_y * puzzle.width] == letter;
}

bool search_word(puzzle_t puzzle, int index, int pos_x, int pos_y, int dir_x, int dir_y) {
	if (index >= 4) return true;
	if (not has_letter_at(puzzle, LETTERS[index], pos_x, pos_y)) return false;
	return search_word(puzzle, index + 1, pos_x + dir_x, pos_y + dir_y, dir_x, dir_y);
}



puzzle_t get_puzzle(string input_path) {
	ifstream infile(input_path);

	puzzle_t puzzle;
	
	while (not infile.eof()) {
		string line;
		getline(infile, line);
		puzzle.contents.append(line);
		puzzle.width = line.size();
	}

	infile.close();

	return puzzle;
}

int part_one(string input_path) {
	
	int result = 0;
	puzzle_t puzzle = get_puzzle(input_path);

	for (int i = 0; i < puzzle.contents.size(); ++i)
	{
		char c = puzzle.contents[i];
		if (c != 'X') continue;
	    int pos_x = i % puzzle.width;
	    int pos_y = i / puzzle.width;

	    for (int dx = -1; dx <= 1; ++dx)
    	for (int dy = -1; dy <= 1; ++dy)
	    {
	    	if (dx == 0 and dy == 0) continue;
	    	result += search_word(puzzle, 1, pos_x + dx, pos_y + dy, dx, dy);
	    }
	}

	
	
	return result;
}


int part_two(string input_path) {
	int result = 0;
	puzzle_t puzzle = get_puzzle(input_path);

	for (int i = 0; i < puzzle.contents.size(); ++i)
	{
		char c = puzzle.contents[i];
		if (c != 'A') continue;
	    int pos_x = i % puzzle.width;
	    int pos_y = i / puzzle.width;

	    bool hasC1 = 	(		has_letter_at(puzzle, 'M', pos_x - 1, pos_y - 1)
				    		and has_letter_at(puzzle, 'S', pos_x + 1, pos_y + 1))
				    	or (	has_letter_at(puzzle, 'S', pos_x - 1, pos_y - 1)
				    		and has_letter_at(puzzle, 'M', pos_x + 1, pos_y + 1));

    	bool hasC2 = 	(		has_letter_at(puzzle, 'M', pos_x - 1, pos_y + 1)
				    		and has_letter_at(puzzle, 'S', pos_x + 1, pos_y - 1))
				    	or (	has_letter_at(puzzle, 'S', pos_x - 1, pos_y + 1)
				    		and has_letter_at(puzzle, 'M', pos_x + 1, pos_y - 1));

	    result += hasC1 and hasC2;
	}

	
	
	return result;
}

int main() {
	cout << part_one("input.txt") << "\n";
	cout << part_two("input.txt") << "\n";
}