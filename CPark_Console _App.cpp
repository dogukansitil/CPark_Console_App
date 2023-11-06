#include "CPark.h"

//K.Adi , Sifre , Max Yanlis Giris Hakki, Otoparkin kaç katli olacagi ve her katta kaç araç olacagi gibi degiskenler tanimlandi
const string adminUsername = "Admin";
const string adminPassword = "Admin";
const int maxLoginAttempts = 3;
const int floors = 5;
const int spotsPerFloor = 10;

//Araç girisinde programin kayit edecegi veriler struct ile tanimlandi
struct Car {
    string plate;
    time_t entryTime;
};
//Programa 5 Kat ve her katta 10 araç olacagini belirten matrix tanimlandi
struct ParkingLot {
    Car cars[5][10];
};
//Karsilama ekrani yaziari
void welcomeScreen() {
    cout << "Hos geldiniz!" << endl;
}
//K.adi ve Sifre dogrulamasinin yapildigi fonksiyon while loop ve if kullanildi
bool login() {
    string username, password;
    int loginAttempts = 0;
    //3 Giristen az hatali islem yapildiysa kullanici adi ve Sifre girmemize izin veren ekran
    while (loginAttempts < maxLoginAttempts) {
        cout << "Kullanici Adi: ";
        cin >> username;
        cout << "Sifre: ";
        cin >> password;
        //Eger K.adi ve Sifre yukarida belirtilen ile ayni ise true döner
        if (username == adminUsername && password == adminPassword) {
            return true;
        }
        //Eger K.adi ve Sifre yukarida belirtilen ile ayni degil ise uyari verip tekrar giris yapmamizi ister
        else {
            loginAttempts++;
            cout << "Yanlis giris yaptiniz. Tekrar deneyiniz. Toplam 3 hatali giristen sonra program kapanacaktir " << endl;
        }
    }
    //Eger K.adi ve Sifre yukarida belirtilen ile ayni ise false döner
    return false;
}
//Programi derlerken online bir editör kullandigim için CLS fonksiyonlarini çalistiramadim bu yüzden ekrani temizletmek için Stackoverflowdan buldugum bu fonsiyonu kullandim
void clearScreen() {
    cout << string(100, '\n');
}
//Basarili giris ardindan bize programimizin 4 tane çalisan fonksiyonundan hangisini seçmemizi istedigi ekran 
void displayMenu() {
    cout << "1. Park Halindeki Araclarin Listesi" << endl;
    cout << "2. Park Halindeki Arac Cikisi" << endl;
    cout << "3. Yeni Arac Girisi" << endl;
    cout << "4. Cikisi" << endl;
}
//Otoparkta mevcut bütün araçlar?n listesini veren fonksiyonumuz
void displayCars(const ParkingLot& parkingLot) {
    for (int floor = 0; floor < floors; floor++) {
        for (int spot = 0; spot < spotsPerFloor; spot++) {
            if (!parkingLot.cars[floor][spot].plate.empty()) {
                cout << "Kat " << floor + 1 << ", Park Yeri " << spot + 1 << " - Plaka: " << parkingLot.cars[floor][spot].plate << " Park Halinde Giris: " << ctime(&parkingLot.cars[floor][spot].entryTime);
            }
        }
    }
}
//2. Park Halindeki Araç Çikisi fonksiyonuna girildiginde izlenecek yol, eger bos ise aracin plakasinin ve girisin yapildigi saatin kaydi, eger dolu ise hata ekrani ve displayMenu'ye dönüs
void parkCar(ParkingLot& parkingLot) {
    int floor, spot;
    cout << "Kat numarasini girin: ";
    cin >> floor;
    floor--;

    if (floor < 0 || floor >= floors) {
        cout << "Gecersiz kat numarasi!" << endl;
        return;
    }
    //Kattaki tüm slotlarin dolu olmasi durumunda bu kat dolu hatasini yoklayan fonksiyon
    bool isFull = true;
    for (int spot = 0; spot < spotsPerFloor; spot++) {
        if (parkingLot.cars[floor][spot].plate.empty()) {
            isFull = false;
            break;
        }
    }
    
    if (isFull) {
        cout << "Bu katta bos park yeri kalmamistir!" << endl;
        Sleep(200);
        return;
    }

    cout << "Park yeri numarasini girin: ";
    cin >> spot;
    spot--;

    if (spot < 0 || spot >= spotsPerFloor) {
        cout << "Gecersiz park yeri numarasi!" << endl;
        return;
    }

    if (!parkingLot.cars[floor][spot].plate.empty()) {
        cout << "Bu park yeri dolu!" << endl;
        return;
    }

    cout << "Plaka: ";
    cin >> parkingLot.cars[floor][spot].plate;
    parkingLot.cars[floor][spot].entryTime = time(0);
}
//3.Seçenek araç çikisi yapan fonksiyon
void exitCar(ParkingLot& parkingLot) {
    int floor, spot;
    cout << "Kat numarasini girin: ";
    cin >> floor;
    floor--;

    if (floor < 0 || floor >= floors) {
        cout << "Gecersiz kat numarasi!" << endl;
        return;
    }

    cout << "Cikis yapilacak park yeri numarasini girin: ";
    cin >> spot;
    spot--;

    if (spot < 0 || spot >= spotsPerFloor) {
        cout << "Gecersiz park yeri numarasi!" << endl;
        return;
    }

    if (parkingLot.cars[floor][spot].plate.empty()) {
        cout << "Bu park yeri bos!" << endl;
        return;
    }
    //Aracin giris yaptigi zaman ile suanki zaman arasindaki farki saptamak için time_t kullanildi
    time_t currentTime = time(0);
    double duration = difftime(currentTime, parkingLot.cars[floor][spot].entryTime);

    cout << "Arac plakas?: " << parkingLot.cars[floor][spot].plate << endl;
    cout << "Toplam park suresi: " << duration << " saniye" << endl;
    cout << "Ucret: " << duration * 0.1 << " TL" << endl;
    //Park yerinin temizlendigi yer
    parkingLot.cars[floor][spot] = {};  
        cout << "Arac cikisi tamamlandi." << endl;
}

//Otoparkin bos bir sekilde acilip sirasiyla fonksiyonlari islettigimiz ekran
int main() {
    ParkingLot parkingLot = {};

    while (true) {
        clearScreen();
        welcomeScreen();
        if (!login()) {
            return 0;
        }

        int choice;

        while (true) {
            clearScreen();
            cout << "Hos geldiniz, " << adminUsername << endl;
            displayMenu();
            cout << "Seciminizi yapin: ";
            cin >> choice;

            switch (choice) {
            case 1:
                clearScreen();
                cout << "Park Halindeki Araclar:" << endl;
                displayCars(parkingLot);
                cin.ignore();
                cout << "Ana menuye donmek icin Enter tusuna basin...";
                cin.get();
                break;
            case 2:
                clearScreen();
                cout << "Park Yeri Cikisi:" << endl;
                exitCar(parkingLot);
                cin.ignore();
                cout << "Park cikisi basari ile yapildi. Ana menuye donmek icin Enter tusuna basin...";
                cin.get();
                break;
            case 3:
                clearScreen();
                cout << "Yeni Arac Girisi:" << endl;
                parkCar(parkingLot);
                cin.ignore();
                cout << "Arac girisi basari ile yapildi. Ana menuye donmek icin Enter tusuna basin...";
                cin.get();
                break;
            case 4:
                cin.ignore();
                cout << "Programdan cikis yapiliyor iyi gunler...";
                cin.get();
                return 0;
            default:
                cout << "Gecersiz secenek!" << endl;
            }
        }
    }
    return 0;
}