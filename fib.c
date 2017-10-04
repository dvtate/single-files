#include <stdio.h> // scanf, printf
#include <math.h> // NAN


// returns the nth fibonacci number
unsigned int fib(unsigned char n) {
	unsigned v1 = 0, v2 = 1;

	// recycle n
	// for every other n on n -> 0
	while (n > 0) {
	
		// add odd to even
		v2 += v1;
		n--;

		// if last one return it
		if (n == 0)
			return v2;

		// add even to odd
		v1 += v2;
		n--;

	}

	// loop ended, must be last one
	return v1;	

}

// returns the nth fibonacci number
//TODO:implement this... not too hard..
float fibquo(unsigned char n) {
	if (n <= 1)
		return NAN;

	float v1 = 0.0, v2 = 1.0f;

	// recycle n
	// for every other n on n -> 0
	while (n > 0) {
	
		// add odd to even
		v2 += v1;
		n--;

		// if last one return it
		if (n == 0)
			return v2 / v1;
		// add even to odd
		v1 += v2;
		n--;

	}

	// loop ended, must be last one
	return v1 / v2;

}


int main() {

	// get number of rows for table
	unsigned n;
	printf("Enter max n (1 to quit): ");
	scanf("%u", &n);

	// if they enter a 1 then quit
	if (n == 1)
		return 0;


	// print table header
	printf("%3s%12s%16s\n", "N", "fibonacci", "quotient");
	printf("===============================\n");

	// print each row
	for (unsigned i = 0; i < n; i++)
		printf("%3u%12u%16f\n", i, fib(i), fibquo(i));


}
