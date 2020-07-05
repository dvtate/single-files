#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	// ret
	int lines = 0, bytes = 0, words = 0;
	char inspace = 0;
	FILE* file = argc == 1 ? stdin : fopen(argv[0], "r");
	char c;
	while ((c = fgetc(file)) != EOF) {
		bytes++;
		if (c == ' ' && !inspace) {
			words++;
			inspace = 1;	
		} else if (c == '\n' && !inspace) {
			words++;
			lines++;
			inspace = 1;
		} else if (c == '\n') {
			lines++;	
		} else if (c != '\n' && c != ' ') {
			inspace = 0;
		}
	}
	if (!inspace)
		words++;
	
	printf("Lines: %d\nWords: %d\nBytes: %d\n", lines, words, bytes);
}
