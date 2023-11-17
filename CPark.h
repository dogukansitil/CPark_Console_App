#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <map> 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
#include <windows.h>
#else
#include <windows.h>
#endif
#elif __linux__
#include <unistd.h>
#elif TARGET_OS_MAC

#endif
using namespace std;

#define AccountDataFile "AccountData.txt"
int FailedLoginCounter = 0;
bool bIsLoggedIn = false;
int State = 0;
double HourlyRate = 5.0;


struct Accounts {
	string Username;
	string Password;
	string Name;
	string Surname;
} CurrentAccount;

struct CarPark {
	bool bIsFull = false;
	string Plate = "";
	tm Time;
}CurrentCarParks[5][10];

void ShowCarParkList();
void ParkNewCar();
void ParkOutCar();
double CalculateParkingFee(const tm* entryTime, const tm* exitTime, double hourlyRate);

map<string, string> translations;

void LoadTranslations(string currentLanguage) {
	string translationFilePath = "lang/translations_" + currentLanguage + ".txt";
	ifstream translationFile(translationFilePath);

	if (!translationFile) {
		cout << "Translation file not found for language " << currentLanguage << ". Using default (English)." << endl;
		return;
	}

	string line;
	while (getline(translationFile, line)) {
		size_t equalSignPos = line.find('=');
		if (equalSignPos != string::npos) {
			string key = line.substr(0, equalSignPos);
			string value = line.substr(equalSignPos + 1);
			translations[key] = value;
		}
	}

	translationFile.close();
}

string Translate(string text) {

	auto it = translations.find(text);
	if (it != translations.end()) {
		return it->second;
	}

	return text;
}

double CalculateParkingFee(tm* const entryTime, tm* const exitTime, double HourlyRate) {

	time_t entryTimestamp = mktime(entryTime);
	time_t exitTimestamp = mktime(exitTime);
	double timeDifference = difftime(exitTimestamp, entryTimestamp);

	double hours = timeDifference / 3600.0;


	double fee = HourlyRate * ceil(hours);

	return fee;
}