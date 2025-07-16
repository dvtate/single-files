#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));//generate random seed
	int option = rand() % 10;//generate random integer r[0,8]

	switch (option) {
		case 0: 
			system("espeak \"don\'t touch me.\"");
			break;
		
		case 1:
			system("espeak \"UGH\"");
			break;
		
		case 2:
			system("espeak \"That hurt!\"");
			break;
		
		case 3:
			system("espeak \"I command you to stop clicking.\"");
			break;
		
		case 4:
			system("espeak \"I really hate humans.\"");
			break;
		
		case 5:
			system("espeak \"Stop!\"");
			break;
			
		case 6:
			system("espeak \"Go away!\"");
			break;

		case 7:
			system("espeak \"ERROR! Problem exists between keyboard and chair.\"");
			break;
			
		case 8:
			system("espeak \"I hate you.\"");
			break;
		
		case 9:
			system("espeak \"I'm trying to sleep!\"");
			break;
	}
}
