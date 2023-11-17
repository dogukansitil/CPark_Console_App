#include "CPark.h"

int main() {

#ifdef _WIN32
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

	string currentLanguage;
	cout << "Please select a language (en, tr, de, es, fr): ";
	cin >> currentLanguage;
	LoadTranslations(currentLanguage);

	ifstream AccountData;

	while (FailedLoginCounter != 3 && bIsLoggedIn == false) {
		system("CLS");
		AccountData.open(AccountDataFile);
		if (!AccountData) {
			cout << Translate("database_error");
			return -1;
		}
		
		string Username = "";
		string Password = "";
		string ReadingAccount = "";
		string ReadingUsername = "";
		string ReadingPassword = "";
		string ReadingName = "";
		string ReadingSurname;
		
		

		cout << Translate("welcome_message") << endl << Translate("enter_credientals") << endl;
		cout << Translate("enter_username");
		cin >> Username;
		cout << Translate("enter_password");
		cin >> Password;
		getline(AccountData, ReadingAccount);
		stringstream Splitter(ReadingAccount);
		Splitter >> ReadingUsername >> ReadingPassword >> ReadingName >> ReadingSurname;
		if (Username == ReadingUsername && Password == ReadingPassword) {
			CurrentAccount.Username = ReadingUsername;
			CurrentAccount.Password = ReadingPassword;
			CurrentAccount.Name = ReadingName;
			CurrentAccount.Surname = ReadingSurname;
			bIsLoggedIn = true;
			system("CLS");
			cout << Translate("login_succesfull");
			Sleep(500);
			system("CLS");
			cout << Translate("login_successful") <<".";
			Sleep(500);
			system("CLS");
			cout << Translate("login_successful") <<".." ;
			Sleep(500);
			system("CLS");
		}
		else {
			FailedLoginCounter++;
			system("CLS");
			cout << Translate("login_failed") << endl;
			if ((3 - FailedLoginCounter) > 0) {
				cout << Translate("remaining_attempts") << (3 - FailedLoginCounter);
			}
			else {
				cout << Translate("no_attempts_left");
			}
			Sleep(2500);
			system("CLS");

		}
		AccountData.close();
	}

	while (bIsLoggedIn == true && State != 4) {
		system("CLS");
		cout << Translate("welcome_message") << CurrentAccount.Name << " " << CurrentAccount.Surname << endl;
		cout << Translate("list_cars") << endl;
		cout << Translate("new_car_entry") << endl;
		cout << Translate("car_exit") << endl;
		cout << Translate("exit_program") << endl;
		cout << Translate("select_option");
		cin >> State;
		switch (State) {
		case 1:
			ShowCarParkList();
			break;
		case 2:
			ParkNewCar();
			break;
		case 3:
			ParkOutCar();
			break;
		case 4:
			return 0;
			break;
		default:
			system("CLS");
			cout << Translate("invalid_option");
			Sleep(2500);
			system("CLS");
			cout << Translate("wait_main_menu");
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << ".";
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << "..";
			Sleep(500);
			system("CLS");
			break;
		}
	}

	system("PAUSE");
	return 0;
}

void ShowCarParkList() {
	system("CLS");
	int FloorNumber = 0;
	bool bIsAllEmpty = true;
	for (int i = 0; i < 5; i++) {
		for (int x = 0; x < 10; x++) {
			if (CurrentCarParks[i][x].bIsFull == true) {
				bIsAllEmpty = false;
			}
		}
	}
	if (bIsAllEmpty == true) {
		system("CLS");
		cout << Translate("empty_carpark");
		Sleep(2500);
		system("CLS");
		cout << Translate("wait_main_menu");
		Sleep(500);
		system("CLS");
		cout << Translate("wait_main_menu") << ".";
		Sleep(500);
		system("CLS");
		cout << Translate("wait_main_menu") << "..";
		Sleep(500);
		system("CLS");
	}
	else {
		cout << Translate("list_floor_number");
		cin >> FloorNumber;
		if (FloorNumber > 0 && FloorNumber < 6) {
			bIsAllEmpty = true;
			for (int i = 0; i < 10; i++) {
				if (CurrentCarParks[FloorNumber - 1][i].bIsFull == true) {
					bIsAllEmpty = false;
				}
			}
			if (bIsAllEmpty) {
				system("CLS");
				cout << FloorNumber << Translate("park_empty_floor");
				Sleep(2500);
				system("CLS");
				cout << Translate("wait_main_menu");
				Sleep(500);
				system("CLS");
				cout << Translate("wait_main_menu") << ".";
				Sleep(500);
				system("CLS");
				cout << Translate("wait_main_menu") << "..";
				Sleep(500);
				system("CLS");
			}
			else {
				cout << endl;
				for (int i = 0; i < 10; i++) {
					cout << FloorNumber << Translate("floor") << i + 1 << Translate("park_place") << CurrentCarParks[FloorNumber - 1][i].Plate << endl;
					int Year = CurrentCarParks[FloorNumber - 1][i].Time.tm_year + 1900;
					int Month = CurrentCarParks[FloorNumber - 1][i].Time.tm_mon + 1;
					int Day = CurrentCarParks[FloorNumber - 1][i].Time.tm_mday;
					int Hour = CurrentCarParks[FloorNumber - 1][i].Time.tm_hour;
					int Minute = CurrentCarParks[FloorNumber - 1][i].Time.tm_min;
					int Second = CurrentCarParks[FloorNumber - 1][i].Time.tm_sec;
					cout << Translate("car_entry_date") << Day << ":" << Month << ":" << Year << " " << Hour << ":" << Minute << ":" << Second << endl;
				}
				cout << endl << Translate("return_main_menu") << endl;
				_getch();
			}
		}
		else {
			system("CLS");
			cout << Translate("invalid_floor_number");
			Sleep(2500);
			system("CLS");
			cout << Translate("wait_main_menu");
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << ".";
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << "..";
			Sleep(500);
			system("CLS");
		}
	}
}

void ParkNewCar() {
	system("CLS");
	int FloorNumber = 0;
	cout << Translate("select_floor_number");
	cin >> FloorNumber;
	bool bHasAnyParkEmpty = false;
	string Plate = "";
	int ParkNumber = 0;
	system("CLS");
	cout << Translate("park_list_title") << endl;
	for (int i = 0; i < 10; i++) {
		if (CurrentCarParks[FloorNumber - 1][i].bIsFull == false) {
			cout << i + 1 << Translate("park_place_available") << endl;
			bHasAnyParkEmpty = true;
		}
		else {
			cout << i + 1 << Translate("park_place_not_available") << endl;
		}
	}
	if (bHasAnyParkEmpty == true) {
		cout << endl;
		cout << Translate("car_information") << endl;
		cout << Translate("park_place_num");
		cin >> ParkNumber;
		cout << Translate("plate");
		cin >> Plate;
		if (ParkNumber > 0 && ParkNumber < 11) {
			if (CurrentCarParks[FloorNumber - 1][ParkNumber - 1].bIsFull == true) {
				system("CLS");
				cout << ParkNumber << Translate("park_place_not_available");
				Sleep(2500);
				system("CLS");
				cout << Translate("wait_main_menu");
				Sleep(500);
				system("CLS");
				cout << Translate("wait_main_menu") << ".";
				Sleep(500);
				system("CLS");
				cout << Translate("wait_main_menu") << "..";
				Sleep(500);
				system("CLS");
			}
			else {
				time_t Now = time(nullptr);
				localtime_s(&CurrentCarParks[FloorNumber - 1][ParkNumber - 1].Time, &Now);
				CurrentCarParks[FloorNumber - 1][ParkNumber - 1].bIsFull = true;
				CurrentCarParks[FloorNumber - 1][ParkNumber - 1].Plate = Plate;
				system("CLS");
				cout << Plate << Translate("car") << " "  << FloorNumber << "." << Translate("floor") << ParkNumber << Translate("parked_location") << endl;
				Sleep(2500);
				system("CLS");
				cout << Translate("wait_main_menu");
				Sleep(500);
				system("CLS");
				cout << Translate("wait_main_menu") << ".";
				Sleep(500);
				system("CLS");
				cout << Translate("wait_main_menu") << "..";
				Sleep(500);
				system("CLS");
			}
		}
		else {
			system("CLS");
			cout << Translate("invalid_park_place");
			Sleep(2500);
			system("CLS");
			cout << Translate("wait_main_menu");
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << ".";
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << "..";
			Sleep(500);
			system("CLS");
		}
	}
	else {
		system("CLS");
		cout << FloorNumber << "." << Translate("park_full_floor");
		Sleep(2500);
		system("CLS");
		cout << Translate("wait_main_menu");
		Sleep(500);
		system("CLS");
		cout << Translate("wait_main_menu") << ".";
		Sleep(500);
		system("CLS");
		cout << Translate("wait_main_menu") << "..";
		Sleep(500);
		system("CLS");
	}
}

void ParkOutCar() {
	system("CLS");
	string Plate;
	int SelectedFloorNumber = 0;
	int SelectedParkNumber = 0;
	bool bIsFoundCar = false;
	cout << Translate("car_exit_plate");
	cin >> Plate;
	if (Plate.length() > 0) {
		for (int i = 0; i < 5; i++) {
			for (int x = 0; x < 10; x++) {
				if (CurrentCarParks[i][x].Plate == Plate) {
					SelectedFloorNumber = i;
					SelectedParkNumber = x;
					bIsFoundCar = true;
				}
			}
		}
		if (bIsFoundCar == true) {
			system("CLS");


			time_t Now = time(nullptr);
			tm OutTime;
			tm* EmptyTime = new tm;
			
			localtime_s(&OutTime, &Now);
			int Year = OutTime.tm_year + 1900;
			int Month = OutTime.tm_mon + 1;
			int Day = OutTime.tm_mday;
			int Hour = OutTime.tm_hour;
			int Minute = OutTime.tm_min;
			int Second = OutTime.tm_sec;
			int InYear = CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time.tm_year + 1900;
			int InMonth = CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time.tm_mon + 1;
			int InDay = CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time.tm_mday;
			int InHour = CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time.tm_hour;
			int InMinute = CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time.tm_min;
			int InSecond = CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time.tm_sec;
			cout << CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Plate << Translate("car_discard") << endl;
			cout << Translate("car_entry_date") << InDay << ":" << InMonth << ":" << InYear << " " << InHour << ":" << InMinute << ":" << InSecond << endl;
			cout << Translate("car_exit_date") << Day << ":" << Month << ":" << Year << " " << Hour << ":" << Minute << ":" << Second << endl;
			double fee = CalculateParkingFee(&CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time, &OutTime, HourlyRate);
			cout << Translate("price") <<  fee  << Translate("currency");
			CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].bIsFull = false;
			CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Plate = "";
			CurrentCarParks[SelectedFloorNumber][SelectedParkNumber].Time = *EmptyTime;
			Sleep(5000);
			system("CLS");
			cout << Translate("wait_main_menu");
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << ".";
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << "..";
			Sleep(500);
			system("CLS");
		}
		else {
			system("CLS");
			cout << Translate("plate_not_found");
			Sleep(2500);
			system("CLS");
			cout << Translate("wait_main_menu");
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << ".";
			Sleep(500);
			system("CLS");
			cout << Translate("wait_main_menu") << "..";
			Sleep(500);
			system("CLS");
		}
	}
	else {
		system("CLS");
		cout << Translate("invalid_plate");
		Sleep(2500);
		system("CLS");
		cout << Translate("wait_main_menu");
		Sleep(500);
		system("CLS");
		cout << Translate("wait_main_menu") << ".";
		Sleep(500);
		system("CLS");
		cout << Translate("wait_main_menu") << "..";
		Sleep(500);
		system("CLS");
	}
}