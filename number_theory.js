
function genPrimes(end) {
	const range = [];
	for (let i = 2; i < end; i++)
		range.push(i);
		
	const marks = [];
	
	return range.filter(n => {
		if (!marks[n]) {
			for (let k = n ** 2; k < end; k += n)
				marks[k] = true;
			return true;
		}
	});
}

function isPrime(n) {
	for (let i = 2; i <= Math.sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;	
}


// n'th prime number
function p(n, primes) {
	return (primes || genPrimes(2 ** ((2 ** n) - 1)))[n];
}

Math.factorial = n => n > 1n ? n * Math.factorial(n-1n) : 1n;

// 
function gcd(a, b) {
	r = a%b;
	return r? gcd(b,r) : b;
}

fcgs = () => {
	const ps = genPrimes(10000000);
	const d = n => p(n + 1, ps) - p(n, ps);
	
	console.log('n\tp\td');
	for (let i = 0; i < 100; i++) {
		console.log(`${i}\t${p(i, ps)}\t${d(i)}`);
	}
};


	/*
	let prevGap = 0;
	let count = 0;
	for (let i = 0; i < 10000; i++) {
		const g = d(i);
		console.log(g);
		if (g != prevGap) {
//			console.log('diff');
			prevGap = g;
			count = 1;
		} else if (count >= 4) {
			console.log("n = ", i);
			count++;
		} else {
			count++;
		}
	}
	*/
