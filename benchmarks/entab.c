#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Entabs string
// Overwrites s with reduced spaces
// tab_width defines conversion between tabs and spaces
// returns s
char* collapse_spaces(char* s, int tab_width) {
	// Stack of spaces
	unsigned num_spaces = 0;
	
	// Overwrite index
	unsigned ret_i = 0;
	
	// For each character
	const unsigned len = strlen(s);
	for (unsigned i = 0; i < len; i++) {
		if (s[i] == ' ') {
			// Space
			++num_spaces;
		} else if (s[i] == '\t') {
			// Tab
			num_spaces += tab_width;
		} else if (num_spaces) {
			// Transition from space to non-space
			for (unsigned j = 0; j < num_spaces / tab_width; j++)
				s[ret_i++] = '\t';
			for (unsigned j = 0; j < num_spaces % tab_width; j++)
				s[ret_i++] = ' ';
			s[ret_i++] = s[i];
			num_spaces = 0;
		} else {
			// Sequence of non space chars
			s[ret_i++] = s[i];
		}
	}
	
	// Reduce length of the string to only what's needed
	s[ret_i] = '\0';
	return s;	
}

int main(int argc, char** argv) {
	char* ptr = NULL;
	size_t len = 0;
	while (getline(&ptr, &len, stdin))
		printf("entabbed: %s\n", collapse_spaces(ptr, atoi(argv[1])));
					
}
