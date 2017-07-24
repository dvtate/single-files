#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace mutilator {
	const uint8_t L_REF_MUTILATOR = 11; // number of numberals
	const char baseNumerals[62] = { // base 62 numerals
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
		'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	char *mutilateVarName(const char *cur_name) {
		static uint64_t uniqueID = 0;
		uint64_t id_cpy = uniqueID;

		char mut[L_REF_MUTILATOR];

		int8_t i;
		for (i = L_REF_MUTILATOR - 1; i >= 0; i--) {
			mut[i] = baseNumerals[id_cpy % 62];
			id_cpy /= 62;
			if (id_cpy == 0) break;
		}
		



		char* ret = (char*) calloc(strlen(cur_name) + 3 + L_REF_MUTILATOR, sizeof(char));

		strcat(ret, " ");
		strcat(ret, cur_name);
		strcat(ret, "#");
		strcat(ret, mut + i); // + i means dont include zeros (not set)

		uniqueID++;

		return ret;
		
	}
}

int main() {
	for (;;) {
		char* p = mutilator::mutilateVarName("_");
		printf("%s\n",p);
		free(p);
	}

}
