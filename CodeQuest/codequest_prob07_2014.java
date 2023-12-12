import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;//arrayList and .sort()
import java.util.*;
/**Morse Code translator
*-Summary: 
* Translates text to morse code until it reaches
* "END OF TRANSMISSION" where it translates morse to text
*-Date: 4-29-2015
*/

public class solution7 {

	public static boolean txt2morse = true;//changes after "END OF TRANSMISSION"

	public static String translate(String ln){

		String translated = "";//the translated line
		if (ln == "END OF TRANSMISSION") 
			return ln;
		//txt->morse
		if(ln.charAt(0) != '='){//not given morse. All morse starts w/ '='
			boolean isNewLine = true;//prevents trailing "___" by putting in front not back
			boolean isSpace = false;//tells not to use "___" when a new word uses "_______"
			for(String letter: ln.split("")) {//split by char
				if(!isNewLine && !isSpace) 
					translated += "____";
				isSpace = false;
				switch(letter) {
					//space: new word, not new letter
					case " ": 
						translated += "_______";
						isSpace = true;
						break;
					//letters:
					case "a": case "A": translated += "=_==="; break;//*-
					case "b": case "B": translated += "====_=_=_="; break;//-***
					case "c": case "C": translated += "===_=_===_="; break;//-*-*
					case "d": case "D": translated += "===_=_="; break;//-**
					case "e": case "E": translated += "="; break;//*
					case "f": case "F": translated += "=_=_===_="; break;//**-*
					case "g": case "G": translated += "===_===_="; break;//--*
					case "h": case "H": translated += "=_=_=_="; break;//****
					case "i": case "I": translated += "=_="; break;//**
					case "j": case "J": translated += "=_===_===_==="; break;//*---
					case "k": case "K": translated += "===_=_==="; break;//-*-
					case "l": case "L": translated += "=_===_=_="; break;//*-** 
					case "m": case "M": translated += "===_==="; break;//--
					case "n": case "N": translated += "===_="; break;//-*
					case "o": case "O": translated += "===_===_==="; break;//---
					case "p": case "P": translated += "=_===_===_="; break;//*--*
					case "q": case "Q": translated += "===_===_=_==="; break;//--*-
					case "r": case "R": translated += "=_===_="; break;//*-*
					case "s": case "S": translated += "=_=_="; break;//***
					case "t": case "T": translated += "==="; break;//-
					case "u": case "U": translated += "=_=_==="; break;//**-
					case "v": case "V": translated += "=_=_=_==="; break;//***-
					case "w": case "W": translated += "=_===_==="; break;//*--
					case "x": case "X": translated += "===_=_=_==="; break;//-**-
					case "y": case "Y": translated += "===_=_===_==="; break;//-*--
					case "z": case "Z": translated += "===_===_=_="; break;//--**
					//numbers:
					case "1": translated += "=_===_===_===_==="; break;//*----
					case "2": translated += "=_=_===_===_==="; break;//**---
					case "3": translated += "=_=_=_===_==="; break;//***--
					case "4": translated += "=_=_=_=_==="; break;//****-
					case "5": translated += "=_=_=_=_="; break;//*****
					case "6": translated += "===_=_=_=_="; break;//-****
					case "7": translated += "===_===_=_=_="; break;//--***
					case "8": translated += "===_===_===_=_="; break;//---**
					case "9": translated += "===_===_===_===_="; break;//----*
					case "0": translated += "===_===_===_===_==="; break;//-----      
				}
				isNewLine = false;
			}
		} else {//morse->txt
			for (String word: ln.split("_______")) //separrate words
				for (String letter: word.split("___")) //separate letters
					switch (letter) {
						//letters:
						case "=_===": translated += "a"; break;
						case "====_=_=_=": translated += "b"; break;
						case "===_=_===_=": translated += "c"; break;
						case "===_=_=": translated += "d"; break;
						case "=": translated += "e"; break;
						case "=_=_===_=": translated += "f"; break;
						case "===_===_=": translated += "g"; break;
						case "=_=_=_=": translated += "h"; break;
						case "=_=": translated += "i"; break;
						case "=_===_===_===": translated += "j"; break;
						case "===_=_===": translated += "k"; break;
						case "=_===_=_=": translated += "l"; break;
						case "===_===": translated += "m"; break;
						case "===_=": translated += "n"; break;
						case "===_===_===": translated += "o"; break;
						case "=_===_===_=": translated += "p"; break;
						case "===_===_=_===": translated += "q"; break;
						case "=_===_=": translated += "r"; break;
						case "=_=_=": translated += "s"; break;
						case "===": translated += "t"; break;
						case "=_=_===": translated += "u"; break;
						case "=_=_=_===": translated += "v"; break;
						case "=_===_===": translated += "w"; break;
						case "===_=_=_===": translated += "x"; break;
						case "===_=_===_===": translated += "y"; break;
						case "===_===_=_=":translated+="z";break;
						//numbers:
						case "=_===_===_===_===": translated += "1"; break;
						case "=_=_===_===_===": translated += "2"; break;
						case "=_=_=_===_===": translated += "3"; break;
						case "=_=_=_=_===": translated += "4"; break;
						case "=_=_=_=_=": translated += "5"; break;
						case "===_=_=_=_=": translated += "6"; break;
						case "===_===_=_=_=": translated += "7"; break;
						case "===_===_===_=_=": translated += "8"; break;
						case "===_===_===_===_=": translated += "9"; break;
						case "===_===_===_===_===": translated += "0"; break;
					}      

				translated += " "; // add space between words
  
		}

		return translated;
	}

	public static void main(String[] args) throws IOException {//fio
		// get file
		File myFile = new File("Prob07.in.txt");
		System.out.println("File Exists--" + myFile.exists());

		Scanner inputFile = new Scanner(myFile);

		String line;
	
		// process the file
		while (inputFile.hasNext()) {
			line = inputFile.nextLine();
			if (line == "END OF TRANSMISSION") 
				System.out.println("END OF TRANSMISSION");
			else 
				System.out.println(translate(line));
		}
		inputFile.close();
	} 
}
