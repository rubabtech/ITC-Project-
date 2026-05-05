#include<iostream>
using namespace std;

// ========================================================
//    UNIVERSITY PARKING MANAGEMENT SYSTEM
//    Subject: ITC (Introduction to Computing)
//    Topics: char arrays, cin/cout, for/while/do-while, arrays
// ========================================================

const int MAX = 10;

// Char arrays (no string library) for vehicle types & plates
char plates[MAX][15];
char types[MAX][10];   // bike, car, van, scooty
int  hours[MAX];
bool occupied[MAX];
int  totalSlots = MAX;

// ---- Helper: compare two char arrays ----
bool charEqual(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

// ---- Helper: copy char array ----
void charCopy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') { dest[i] = src[i]; i++; }
    dest[i] = '\0';
}

// ---- Helper: length of char array ----
int charLen(char a[]) {
    int i = 0;
    while (a[i] != '\0') i++;
    return i;
}

// ---- Initialize all slots as empty ----
void initSlots() {
    for (int i = 0; i < MAX; i++) {
        occupied[i] = false;
        plates[i][0] = '\0';
        types[i][0]  = '\0';
        hours[i]     = 0;
    }
}

// ---- Display all slots ----
void displaySlots() {
    cout << "\n========================================\n";
    cout << "        PARKING SLOTS STATUS            \n";
    cout << "========================================\n";
    cout << "Slot\tStatus\t\tType\t\tPlate\t\tHours\n";
    cout << "----\t------\t\t----\t\t-----\t\t-----\n";

    for (int i = 0; i < MAX; i++) {
        cout << " " << i+1 << "\t";
        if (occupied[i]) {
            cout << "OCCUPIED\t" << types[i] << "\t\t" << plates[i] << "\t\t" << hours[i];
        } else {
            cout << "EMPTY\t\t---\t\t---\t\t---";
        }
        cout << "\n";
    }
    cout << "========================================\n";
}

// ---- Park a vehicle ----
void parkVehicle() {
    // Find empty slot using while loop
    int slot = -1;
    int i = 0;
    while (i < MAX) {
        if (!occupied[i]) { slot = i; break; }
        i++;
    }

    if (slot == -1) {
        cout << "\n[!] Sorry! Parking is FULL. No empty slot available.\n";
        return;
    }

    char plate[15], type[10];
    int  hrs;

    cout << "\n--- Park New Vehicle ---\n";
    cout << "Enter vehicle plate number: ";
    cin  >> plate;

    cout << "Enter vehicle type (bike/car/van/scooty): ";
    cin  >> type;

    // Validate type using charEqual
    bool valid = false;
    char t1[]="bike", t2[]="car", t3[]="van", t4[]="scooty";
    if (charEqual(type,t1)||charEqual(type,t2)||charEqual(type,t3)||charEqual(type,t4))
        valid = true;

    if (!valid) {
        cout << "[!] Invalid vehicle type! Use: bike, car, van, scooty\n";
        return;
    }

    cout << "Enter parking hours: ";
    cin  >> hrs;

    // Store data
    charCopy(plates[slot], plate);
    charCopy(types[slot],  type);
    hours[slot]    = hrs;
    occupied[slot] = true;

    cout << "\n[+] Vehicle parked successfully at Slot " << slot+1 << "!\n";
}

// ---- Remove (exit) a vehicle ----
void removeVehicle() {
    char plate[15];
    cout << "\n--- Remove Vehicle ---\n";
    cout << "Enter plate number to remove: ";
    cin  >> plate;

    bool found = false;
    for (int i = 0; i < MAX; i++) {
        if (occupied[i] && charEqual(plates[i], plate)) {
            // Calculate fee
            int fee = 0;
            char t1[]="bike", t2[]="scooty", t3[]="car", t4[]="van";
            if      (charEqual(types[i], t1)||charEqual(types[i], t2)) fee = hours[i] * 20;
            else if (charEqual(types[i], t3))                          fee = hours[i] * 50;
            else if (charEqual(types[i], t4))                          fee = hours[i] * 80;

            cout << "\n[*] Vehicle Found at Slot " << i+1 << "\n";
            cout << "    Type  : " << types[i]  << "\n";
            cout << "    Hours : " << hours[i]  << "\n";
            cout << "    Fee   : Rs. " << fee    << "\n";

            // Clear slot
            occupied[i]  = false;
            plates[i][0] = '\0';
            types[i][0]  = '\0';
            hours[i]     = 0;

            cout << "[+] Vehicle removed. Slot " << i+1 << " is now free.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "[!] Plate number not found!\n";
}

// ---- Search vehicle ----
void searchVehicle() {
    char plate[15];
    cout << "\n--- Search Vehicle ---\n";
    cout << "Enter plate number: ";
    cin  >> plate;

    bool found = false;
    for (int i = 0; i < MAX; i++) {
        if (occupied[i] && charEqual(plates[i], plate)) {
            cout << "\n[*] Vehicle found at Slot " << i+1 << "\n";
            cout << "    Plate : " << plates[i] << "\n";
            cout << "    Type  : " << types[i]  << "\n";
            cout << "    Hours : " << hours[i]  << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "[!] Vehicle not found!\n";
}

// ---- Count vehicles by type ----
void countByType() {
    int bikes=0, cars=0, vans=0, scooties=0;
    char t1[]="bike", t2[]="car", t3[]="van", t4[]="scooty";

    // do-while loop
    int i = 0;
    do {
        if (occupied[i]) {
            if      (charEqual(types[i], t1)) bikes++;
            else if (charEqual(types[i], t2)) cars++;
            else if (charEqual(types[i], t3)) vans++;
            else if (charEqual(types[i], t4)) scooties++;
        }
        i++;
    } while (i < MAX);

    cout << "\n--- Vehicle Count by Type ---\n";
    cout << "  Bikes    : " << bikes     << "\n";
    cout << "  Cars     : " << cars      << "\n";
    cout << "  Vans     : " << vans      << "\n";
    cout << "  Scooties : " << scooties  << "\n";
    cout << "  Total    : " << bikes+cars+vans+scooties << "\n";
}

// ---- MAIN ----
int main() {
    initSlots();
    int choice;

    cout << "\n  Welcome to University Parking Management System\n";

    // Main menu using do-while
    do {
        cout << "\n============ MAIN MENU ============\n";
        cout << " 1. View All Parking Slots\n";
        cout << " 2. Park a Vehicle\n";
        cout << " 3. Remove Vehicle (Exit)\n";
        cout << " 4. Search Vehicle\n";
        cout << " 5. Count Vehicles by Type\n";
        cout << " 6. Exit Program\n";
        cout << "===================================\n";
        cout << "Enter your choice: ";
        cin  >> choice;

        switch(choice) {
            case 1: displaySlots();   break;
            case 2: parkVehicle();    break;
            case 3: removeVehicle();  break;
            case 4: searchVehicle();  break;
            case 5: countByType();    break;
            case 6: cout << "\nThank you! Goodbye!\n"; break;
            default: cout << "[!] Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
