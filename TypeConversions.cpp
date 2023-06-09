#include"TypeConversions.h"
int charToInt(char number) {
	if (number == '0') {
		return 0;
	}
	else if (number == '1') {
		return 1;
	}
	else if (number == '2') {
		return 2;
	}
	else if (number == '3') {
		return 3;
	}
	else if (number == '4') {
		return 4;
	}
	else if (number == '5') {
		return 5;
	}
	else if (number == '6') {
		return 6;
	}
	else if (number == '7') {
		return 7;
	}
	else if (number == '8') {
		return 8;
	}
	else if (number == '9') {
		return 9;
	}
	else if (number == '+') {
		return 1;
	}
	else if (number == '-') {
		return -1;
	}
	else {
		return NULL;
	}
}
int charArrayToInt(char* charArray) {
	int mul = 1;
	int number = 0;
	int size = 0;
	int i = 0;
	while (charArray[i] != '\0') {
		size++;
		i++;
	}
	for (i = size - 1; i >= 0; i--) {
		number += charToInt(charArray[i]) * mul;
		mul *= 10;
	}
	return number;
}
double systemStringToDouble(String^ str) {
	double mul = 1;
	double number = 0;
	int size = 0;
	int i = 0;
	while (str[i] != '.') {
		size++;
		i++;
	}
	for (i = size - 1; i >= 0; i--) {
		if (str[i] == '+') {

		}
		else if (str[i] == '-') {

		}
		else {
			number += charToInt(str[i]) * mul;
			mul *= 10;
		}

	}
	mul = 0.1;
	for (i = size + 1; i < size + 7; i++) {
		if (i < str->Length) {
			if (str[i] == 'e') {
				int power = 0;
				power += 10 * charToInt(str[i + 2]);
				power += charToInt(str[i + 3]);
				number *= pow(10, -1.0 * power);
				break;
			}
			number += charToInt(str[i]) * mul;
			mul /= 10;
		}
	}
	if (str[0] == '-') {
		number *= -1;
	}
	return number;
}
String^ addCharToSystemString(String^ str, char c) {
	if (c == 'a') return str += "a";
	if (c == 'b') return str += "b";
	if (c == 'c') return str += "c";
	if (c == 'd') return str += "d";
	if (c == 'e') return str += "e";
	if (c == 'f') return str += "f";
	if (c == 'g') return str += "g";
	if (c == 'h') return str += "h";
	if (c == 'i') return str += "i";
	if (c == 'j') return str += "j";
	if (c == 'k') return str += "k";
	if (c == 'l') return str += "l";
	if (c == 'm') return str += "m";
	if (c == 'n') return str += "n";
	if (c == 'o') return str += "o";
	if (c == 'p') return str += "p";
	if (c == 'q') return str += "q";
	if (c == 'r') return str += "r";
	if (c == 's') return str += "s";
	if (c == 't') return str += "t";
	if (c == 'u') return str += "u";
	if (c == 'v') return str += "v";
	if (c == 'w') return str += "w";
	if (c == 'x') return str += "x";
	if (c == 'y') return str += "y";
	if (c == 'z') return str += "z";
	if (c == 'A') return str += "A";
	if (c == 'B') return str += "B";
	if (c == 'C') return str += "C";
	if (c == 'D') return str += "D";
	if (c == 'E') return str += "E";
	if (c == 'F') return str += "F";
	if (c == 'G') return str += "G";
	if (c == 'H') return str += "H";
	if (c == 'I') return str += "I";
	if (c == 'J') return str += "J";
	if (c == 'K') return str += "K";
	if (c == 'L') return str += "L";
	if (c == 'M') return str += "M";
	if (c == 'N') return str += "N";
	if (c == 'O') return str += "O";
	if (c == 'P') return str += "P";
	if (c == 'Q') return str += "Q";
	if (c == 'R') return str += "R";
	if (c == 'S') return str += "S";
	if (c == 'T') return str += "T";
	if (c == 'U') return str += "U";
	if (c == 'V') return str += "V";
	if (c == 'W') return str += "W";
	if (c == 'X') return str += "X";
	if (c == 'Y') return str += "Y";
	if (c == 'Z') return str += "Z";
	if (c == ' ') return str += " ";
	if (c == '+') return str += "+";
	if (c == '-') return str += "-";
	if (c == '.') return str += ".";
	if (c == '0') return str += "0";
	if (c == '1') return str += "1";
	if (c == '2') return str += "2";
	if (c == '3') return str += "3";
	if (c == '4') return str += "4";
	if (c == '5') return str += "5";
	if (c == '6') return str += "6";
	if (c == '7') return str += "7";
	if (c == '8') return str += "8";
	if (c == '9') return str += "9";
	return str += "$";

}
String^ stdStringToSystemString(std::string s) {
	String^ str = "";
	for (int i = 0; i < s.size(); i++) {
		str = addCharToSystemString(str, s[i]);
	}
	return str;
}
std::string addCharToStdString(std::string str, char c) {
	if (c == 'a') return str += "a";
	if (c == 'b') return str += "b";
	if (c == 'c') return str += "c";
	if (c == 'd') return str += "d";
	if (c == 'e') return str += "e";
	if (c == 'f') return str += "f";
	if (c == 'g') return str += "g";
	if (c == 'h') return str += "h";
	if (c == 'i') return str += "i";
	if (c == 'j') return str += "j";
	if (c == 'k') return str += "k";
	if (c == 'l') return str += "l";
	if (c == 'm') return str += "m";
	if (c == 'n') return str += "n";
	if (c == 'o') return str += "o";
	if (c == 'p') return str += "p";
	if (c == 'q') return str += "q";
	if (c == 'r') return str += "r";
	if (c == 's') return str += "s";
	if (c == 't') return str += "t";
	if (c == 'u') return str += "u";
	if (c == 'v') return str += "v";
	if (c == 'w') return str += "w";
	if (c == 'x') return str += "x";
	if (c == 'y') return str += "y";
	if (c == 'z') return str += "z";
	if (c == 'A') return str += "A";
	if (c == 'B') return str += "B";
	if (c == 'C') return str += "C";
	if (c == 'D') return str += "D";
	if (c == 'E') return str += "E";
	if (c == 'F') return str += "F";
	if (c == 'G') return str += "G";
	if (c == 'H') return str += "H";
	if (c == 'I') return str += "I";
	if (c == 'J') return str += "J";
	if (c == 'K') return str += "K";
	if (c == 'L') return str += "L";
	if (c == 'M') return str += "M";
	if (c == 'N') return str += "N";
	if (c == 'O') return str += "O";
	if (c == 'P') return str += "P";
	if (c == 'Q') return str += "Q";
	if (c == 'R') return str += "R";
	if (c == 'S') return str += "S";
	if (c == 'T') return str += "T";
	if (c == 'U') return str += "U";
	if (c == 'V') return str += "V";
	if (c == 'W') return str += "W";
	if (c == 'X') return str += "X";
	if (c == 'Y') return str += "Y";
	if (c == 'Z') return str += "Z";
	if (c == ' ') return str += " ";
	return str += "$";
}