#include <iostream> //std::cout
#include <unistd.h> //usleep()

/// prints time and waits 0.25seconds
void printTimeCR( //please excuse my Danish abbreviations
	unsigned int dag,
	unsigned int t,
	unsigned int min,
	unsigned int sek,
	unsigned int kvSek
);

int main(){

	for (unsigned int day = 0; 1; day++)//infinite loop (unless it reaches the limit of unsigned int at which point it would loop back around)
		for (unsigned int hr = 0; hr < 24; hr++)//24 hours in a day
			for (unsigned int min = 0; min < 60; min++)//60 minutes in an hour
				for (unsigned int sec = 0; sec < 60; sec++)//60 seconds in a minute
					for (unsigned int quarterSec = 0; quarterSec < 4; quarterSec++)//quarter seconds for the spinner.
						printTimeCR(day, hr, min, sec, quarterSec);
}

///prints time and waits 0.25 seconds
void printTimeCR(
	unsigned int dag,
	unsigned int t,
	unsigned int min,
	unsigned int sek,
	unsigned int kvSek
){
	char spin; // spinny-thing character
	switch (kvSek) { // set spinny thing character
		//NOTE: characters are contained in single quotes (not double quotes)
		case 0: spin = '-'; break;
		case 1: spin = '\\'; break;
		case 2: spin = '|'; break;
		case 3: spin = '/'; break;
	}
	
	// print it out:
	std::cout <<"\rTime since start: " <<dag <<" days " <<t <<" hours " <<min <<" minutes " <<sek <<" seconds (" <<spin <<")   ";
	
	//wait:
	usleep(0.25 * 1000000); // do nothing for 0.25 seconds (takes time in micro-seconds)
}
