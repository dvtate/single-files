#include <stdio.h>
#include <time.h>


// expects ret to be a char buffer with length 8*sizeof(int)
inline void bitwise_itobin(const int n, char* ret) {
	const unsigned char l = sizeof(int) * 8;
	for (unsigned char i = 0; i < l; i++)
		ret[i - 1] = (n & (1 << i)) ? '1' : '0';
}


struct byte_t { int b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1; };
// expects ret to be a char buffer with length 8*sizeof(int)
inline void union_itobin(const int n, char* ret) {
	union {
		int n;
		struct byte_t bits[sizeof(int)];
	} conv;
	conv.n = n;	

	for (unsigned char i = 0; i < sizeof(int); i++) {
		const unsigned char ix8 = i * 8;
		const struct byte_t b = conv.bits[i];
		ret[ix8 + 0] = b.b0 ? '1' : '0';
		ret[ix8 + 1] = b.b1 ? '1' : '0';
		ret[ix8 + 2] = b.b2 ? '1' : '0';
		ret[ix8 + 3] = b.b3 ? '1' : '0';
		ret[ix8 + 4] = b.b4 ? '1' : '0';
		ret[ix8 + 5] = b.b5 ? '1' : '0';
		ret[ix8 + 6] = b.b6 ? '1' : '0';
		ret[ix8 + 7] = b.b7 ? '1' : '0';
	}

}



int main() {
	
	char s[sizeof(int) * 8 + 1];
	for (unsigned char i =0; i < sizeof(int) * 8; i++)
		s[i] = 'a';

	s[sizeof(int) * 8] = 0; // null terminated

	
/*
	int n = 0;
	for (;;) {
		printf("n:");
		scanf("%d", &n);	
		bitwise_itobin(n, s);
		printf("bin: %s\n", s);
		union_itobin(n, s);
		printf("ubin: %s\n", s);
	}
*/


	clock_t begin = clock();
	
	for (int i = -(1 << 24); i < 1 << 24; i++)
		union_itobin(i, s);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("union fxn: %f seconds\n", time_spent);

	begin = clock();

	for (int i = -(1 << 24); i < 1 << 24; i++)
		bitwise_itobin(i, s);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("bitwise fxn: %f seconds\n", time_spent);
}
