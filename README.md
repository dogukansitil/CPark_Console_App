
# Parking Management System

This program is written to simulate a parking management system. Users can log in and perform operations such as listing cars in the parking lot, parking a new car, and removing a parked car.

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)
3. [Used Variables](#used-variables)
4. [Functions](#functions)
5. [Screenshots](#screenshots)
6. [Translation Support](#translation-support)

## Installation

To ensure the proper functioning of the program, you can follow the steps below:

1. Have a C++ compiler.
2. Install the required libraries: `iostream`, `string`, `fstream`, `sstream`, `ctime`, `conio.h`, and `map`.
3. Download the relevant files and add them to your project.
4. Check the platform-specific library definitions at the beginning of the code.

## Usage

The program expects users to log in by selecting their language. After a successful login, it presents the user with the parking management menu. In this menu, there are options such as listing cars, parking a new car, removing a car, and exiting the program.

## Used Variables

- **FailedLoginCounter**: Keeps track of the number of failed login attempts.
- **bIsLoggedIn**: A boolean flag indicating whether a user is currently logged in.
- **State**: Represents the current state of the program.
- **HourlyRate**: Represents the hourly parking rate.

**Structs:**

- **Accounts**: Holds user account information such as username, password, name, and surname.
- **CarPark**: Represents the state of a parking space, including whether it's full, the plate of the parked car, and the time of entry.

## Functions

- **ShowCarParkList()**: Displays the list of cars parked in the parking lot.
- **ParkNewCar()**: Parks a new car in the parking lot.
- **ParkOutCar()**: Removes a parked car from the parking lot.
- **CalculateParkingFee(const tm* entryTime, const tm* exitTime, double hourlyRate)**: Calculates the parking fee based on entry and exit times.
- **LoadTranslations(string currentLanguage)**: Loads translations from a language file.
- **Translate(string text)**: Translates the given text using the loaded translations.
- **CalculateParkingFee(tm* const entryTime, tm* const exitTime, double HourlyRate)**: Calculates the parking fee based on entry and exit times.

## Screenshots

Below are screenshots taken during the runtime of the program:

![Screenshot 2023-11-17 at 16 35 10](https://github.com/dogukansitil/CPark_Console_App/assets/30118304/ea467444-6d90-44c4-b507-1bd205edf6cc)
![Screenshot 2023-11-17 at 16 35 39](https://github.com/dogukansitil/CPark_Console_App/assets/30118304/4019f1d2-ec18-43fc-a03e-e407e02eff18)
![Screenshot 2023-11-17 at 16 35 56](https://github.com/dogukansitil/CPark_Console_App/assets/30118304/c607a467-0e44-49ad-bc00-c7b9fcc2b179)


## Translation Support

The program provides translation support for the user interface in various languages. Users can select their language before running the program. The default language is English, but you can add your own translations by editing the language files.
