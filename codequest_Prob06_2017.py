
def icao(char):
	if char == ' ':
		return " ";
	elif char == 'A' or char == 'a':
		return "Alpha";
	elif char == 'B' or char == 'b':
		return "B";
	elif char == 'C' or char == 'c':
		return "Charlie";
	elif char == 'D' or char == 'd':
		return "Delta";
	elif char == 'E' or char == 'e':
		return "Echo";
	elif char == 'F' or char == 'f':
		return "Foxtrot";
	elif char == 'G' or char == 'g':
		return "Golf";
	elif char == 'H' or char == 'h':
		return "Hotel";
	elif char == 'I' or char == 'i':
		return "India";
	elif char == 'J' or char == 'j':
		return "Juliet";
	elif char == 'K' or char == 'k':
		return "Kilo";
	elif char == 'L' or char == 'l':
		return "Lima";
	elif char == 'M' or char == 'm':
		return "Mike";
	elif char == 'N' or char == 'n':
		return "November";
	elif char == 'O' or char == 'o':
		return "Oscar";
	elif char == 'P' or char == 'p':
		return "Papa";
	elif char == 'Q' or char == 'q':
		return "Quebec";
	elif char == 'R' or char == 'r':
		return "Romeo";
	elif char == 'S' or char == 's':
		return "Sierra";
	elif char == 'T' or char == 't':
		return "Tango";
	elif char == 'U' or char == 'u':
		return "Uniform";
	elif char == 'V' or char == 'v':
		return "Victor";
	elif char == 'W' or char == 'w':
		return "Whiskey";
	elif char == 'X' or char == 'x':
		return "Xray";
	elif char == 'Y' or char == 'y':
		return "Yankee";
	elif char == 'Z' or char == 'z':
		return "Zulu";
	else:
		return "fuck" + char;




# open the file
with open('Prob06.in.txt') as inFile:
	# get the number of test cases
	for T in range(int(inFile.readline())):
		# get the number of lines in each test case
		for N in range(int(inFile.readline())):
			chars = str(inFile.readline());

			prev = None;

			for char in chars:
				if char == ' ':
					print(" ", end='')
				elif prev == 'space' or prev == None:
					print(icao(char), end='')
				else:
					print("-" + icao(char), end='')

				prev = char;


#done
