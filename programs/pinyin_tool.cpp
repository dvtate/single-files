#include <iostream> //std::cin, std::cout, std::getline(), std::string, 
#include <sstream> //std::stringstream
#include <inttypes.h> //fixed width integer types

uint16_t firstVowel(const std::string& word); ///returns index of first vowel
uint8_t getTone(std::string& word); ///returns the tone of the word and removes tone indicator
void convertToPinyin(const uint8_t tone, std::string& word); ///adds accent to vowel
void printWords(std::string* words, const size_t numWords); ///calls all other funcions and prints the pinyin
size_t countSpaces(const std::string& text); // counts the number of spaces in a string

// 拼音工具 (pinyin tone tool)
// converts numbered pinyin with numbers to pinyin with tone indicators.
//   eg - ni3 hao3 => nǐ hǎo


int main(){
	// get the text
	std::string py;
	std::cout <<"\nEnter numbered pinyin:\n";
	std::getline(std::cin, py);
	
	//use a stringstream to split the string by spaces (into relative words)
	std::stringstream ss(py);


	size_t numWords = countSpaces(py) + 2; // adding 2 more words just in case...
	std::string words[numWords];

	//split string by spaces into the array
	for (uint16_t i = 0; std::getline(ss, py, ' '); i++) 
		words[i] = py;
	
	//show the results.
	std::cout <<"\nPinyin tones:\n";
	printWords(words, numWords);//give the solution.
	std::cout <<"\n";
}

//get tone number from the end of the word
uint8_t getTone(std::string& word){
	
	
	int16_t lCh = word.length() - 1; //start at last character

	//search for numerals 1-4
	if (word.at(lCh) == '0') {
		word.erase(word.begin() + lCh);
		return 0;
	} if (word.at(lCh) == '1') {
		word.erase(word.begin() + lCh);
		return 1;
	} if (word.at(lCh) == '2') {
		word.erase(word.begin() + lCh);
		return 2;
	} if (word.at(lCh) == '3') {
		word.erase(word.begin() + lCh);
		return 3;
	} if (word.at(lCh) == '4') {
		word.erase(word.begin() + lCh);
		return 4;
	}

	//keep searching
	while (lCh >= 0) {
		if (word.at(lCh) == '0') { //is this acceptable?
			word.erase(word.begin() + lCh);
			return 0;
		} if (word.at(lCh) == '1') {
			word.erase(word.begin() + lCh);
			return 1;
		} if (word.at(lCh) == '2') {
			word.erase(word.begin() + lCh);
			return 2;
		} if (word.at(lCh) == '3') {
			word.erase(word.begin() + lCh);
			return 3;
		} if (word.at(lCh) == '4') {
			word.erase(word.begin() + lCh);
			return 4;
		}
		lCh--;
	}
	//found no numerals in the word...
	return 0;//tone 0 means English tone, (tones omitted)
}

//returns index of first vowel in a word
uint16_t firstVowel(const std::string& word){
	for (uint16_t i = 0; i < word.length(); i++)
		if (word.at(i)=='a' || word.at(i)=='e' || word.at(i)=='i' || word.at(i)=='o' || word.at(i)=='u' || word.at(i)=='v')
			return i;

	return 0;//no vowels found, passing the index of a non vowel is ok.
}

//convert a word to pinyin
void convertToPinyin(const uint8_t tone, std::string& word){
	if (!tone) //tone0 means no conversion
		return; 

	// not efficient, but I'm lazy.
	const std::string // tone tables 
		pya[5] = { "a", "ā", "á", "ǎ", "à"	},
		pye[5] = { "e", "ē", "é", "ě", "è"	},
		pyi[5] = { "i", "ī", "í", "ǐ", "ì"	},
		pyo[5] = { "o", "ō", "ó", "ǒ", "ò"	},
		pyu[5] = { "u", "ū", "ú", "ǔ", "ù"	},
		pyv[5] = { "ü", "ǖ", "ǘ", "ǚ", "ǜ"	};

	// get index of vowel to modify
	uint16_t vowelIndex = firstVowel(word); 

	if (word.at(vowelIndex) == 'a') {
		word.erase(word.begin() + vowelIndex);	//erase vowel
		word.insert(vowelIndex, pya[tone]);		//insert appropriate accented vowel 
	} else if (word.at(vowelIndex) == 'e') {
		word.erase(word.begin() + vowelIndex);
		word.insert(vowelIndex, pye[tone]);
	} else if (word.at(vowelIndex) == 'i') {
		word.erase(word.begin() + vowelIndex);
		word.insert(vowelIndex, pyi[tone]);
	} else if (word.at(vowelIndex) == 'o') {
		word.erase(word.begin() + vowelIndex);
		word.insert(vowelIndex, pyo[tone]);
	} else if (word.at(vowelIndex) == 'u') {
		word.erase(word.begin() + vowelIndex);
		word.insert(vowelIndex, pyu[tone]);
	} else if (word.at(vowelIndex) == 'v') {
		word.erase(word.begin() + vowelIndex);
		word.insert(vowelIndex, pyv[tone]);
	}
	// note, non-vowels aren't modified :)
}

// converts to pinyin and prints to terminal
void printWords(std::string* words, const size_t numWords){
	size_t i = 0;
	while (i < numWords && words[i] != "") {
		convertToPinyin(getTone(words[i]), words[i]);
		std::cout <<words[i] <<" ";
		i++;
	}
}

// used to estimate the number of words
size_t countSpaces(const std::string& text){
	size_t ret = 0;
	for (size_t i = 0; i < text.length(); i++)
		if (text.at(i) == ' ')
			ret++;

	return ret;

}
