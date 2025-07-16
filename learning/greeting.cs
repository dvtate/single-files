using System;

class Dav {

	string name; 

	bool noname = false;//default = no-loop

	static void Main(){//run once @ start-up

		Console.WriteLine ("Hi, What's your name?");//output to console

		name = Console.ReadLine ();//get response from console

		if (name == "") { // if zero-length string
			noname = true;
			Console.WriteLine("Can't you type?");
		} else {
			Console.Write ("Hey, "); 
			Console.Write (name);
			Console.Write (", I hope you have a nice day.");
		}

		while (noname == true) {//prompt the user for input until they type/*replace with  for loop and Bang loop*/

			Console.WriteLine("GIVE ME INPUT!");
			name = Console.ReadLine();
			if (name == "") {
				noname = true;
			} else {
				noname = false;
				Console.Write ("hey, "); 
				Console.Write (name); 
				Console.Write (", I hope you die in a hole."); // an attitude
			}

		}
		Console.Read(); // prevents console from auto exit (winshit problem)
	}
}
