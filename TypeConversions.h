#pragma once
using namespace System;
#include<cmath>
#include<string>
int charToInt(char number);
int charArrayToInt(char* charArray);
double systemStringToDouble(String^ str);
String^ addCharToSystemString(String^ str, char c);
String^ stdStringToSystemString(std::string s);
std::string addCharToStdString(std::string str, char c);
