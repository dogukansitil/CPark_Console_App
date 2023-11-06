#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
//64 Bit
#include <windows.h>
#else
//32 Bit
#include <windows.h>
#endif
#elif __linux__
#include <unistd.h>
#endif



using namespace std;