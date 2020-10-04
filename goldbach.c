#include <stdio.h>
#include <inttypes.h>


uint8_t isPrime(int num) 
{

	if(num <= 1)
		return 0;

	for (int i = 2; i <= num / 2; i++)
		if (num % i == 0)
			return 0;

	return 1;

}

// a brute force approach to goldbach's conjecture
void conjecture(unsigned start, unsigned stop)
{

	// only even numbers
	for (unsigned i = start; i <= stop; i += 2)

		// try every reasonable combination of numbers
		for (unsigned n1 = 2; n1 < i / 2 + 1; n1++) // limit first number to prevent duplicates
			for (unsigned n2 = 2; n2 < i - 1; n2++)

				// if matches desired conditions, print the solution
				// note: the order of tests, best performance -> worst performance
				if (n1 + n2 == i && isPrime(n2) && isPrime(n1))
					printf("%3i = %3i + %3i\n", i, n1, n2);

}


int main()
{
	conjecture(2, 2000);
}
