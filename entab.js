/**
 * Converts spaces to tabs
 */
function collapseSpaces(s, tabWidth = 8) {
	let ret = '';
	let numSpaces = 0;
	let lastWasSpace = false;
	for (let i = 0; i < s.length; i++) {
		if (s[i] == ' ') {
			// Space
			numSpaces++;
			lastWasSpace = true;
		} else if (lastWasSpace) {
			// Transition from space to non-space
			for (let j = 0; j < numSpaces / tabWidth; j++)
				ret += '\t';
			for (let j = 0; j < numSpaces % tabWidth; j++)
				ret += ' ';
			ret += s[i];
			lastWasSpace = false;
			numSpaces = 0;
		} else {
			// Sequence of non space chars
			ret += s[i];
		}
	}
	
	return ret;	
}
