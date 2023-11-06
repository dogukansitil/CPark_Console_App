# Parking Management System

This is a simple parking management system application. The program can keep track of parked cars in the parking lot, allow new car entries, perform car exits, and list existing cars.

## Examples
![Preview1](https://github.com/dogukansitil/CPark_Console_App/blob/main/Pics/2.png?raw=true)
![Preview2](https://github.com/dogukansitil/CPark_Console_App/blob/main/Pics/1.png?raw=true)
![Preview3](https://github.com/dogukansitil/CPark_Console_App/blob/main/Pics/3.png?raw=true)
![Preview4](https://github.com/dogukansitil/CPark_Console_App/blob/main/Pics/4.png?raw=true)

## Used Variables

- `adminUsername` and `adminPassword`: User credentials for administrator login.
- `maxLoginAttempts`: Maximum allowed login attempts for users.
- `floors`: Variable defining the number of floors in the parking lot.
- `spotsPerFloor`: Variable defining how many cars can be parked on each floor.

## Functions

- `welcomeScreen()`: Displays a welcoming screen for the user.
- `login()`: Performs user authentication by checking the username and password.
- `clearScreen()`: A function to clear the screen for better user experience.
- `displayMenu()`: Presents a menu for the user to choose the desired operation.
- `displayCars()`: Function to list the existing cars in the parking lot.
- `parkCar()`: Allows new car entry into the parking lot.
- `exitCar()`: Handles car exit from the parking lot.

## Usage

1. Start the program.
2. Perform administrator login using the `adminUsername` and `adminPassword`.
3. Select the desired operation from the main menu.
4. You can list existing cars in the parking lot, perform new car entries, or car exits.

## Example Usage

1. When the program starts, it will prompt for a username and password. When you enter the correct credentials, the main menu will be displayed.
2. You can select option 1 from the main menu to list the existing cars.
3. Select option 2 to perform a car exit.
4. Select option 3 to make a new car entry.
5. Choose option 4 to exit the program.

## Additional Notes

- The program may require the use of `Sleep` and `ctime` functions. Make sure to include the relevant libraries.

This program lays the foundation for a basic parking management application. You can add more features based on your requirements.
This README.md file will help other developers or users to better understand and use your program. It also makes your code presentation more professional and explanatory. Feel free to update the explanations and examples according to your needs.
