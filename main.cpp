/* TODO:
    - Lägg till main menu.
    - Swap på arduinon. (VG)
    - Save to file i AdManager.
    - Exposed blir sträng
    - Readme.txt

    - BETA TESTA KODEN O FIXA
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "ad_manager.hpp"
#include "serial.h"

using namespace std;

void flush_file() {
    std::ofstream ofs;
    ofs.open("ads.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void print_menu(void) {
    cout << "#############################" << endl;
    cout << "####### MAIN MENU ###########" << endl;
    cout << "#                           #" << endl;
    cout << "#    SELECT OPTION BELOW    #" << endl;
    cout << "#   1. Add Adversistment    #" << endl;
    cout << "#   2. Export Ads to Ardu   #" << endl;
    cout << "#   3. Flush file           #" << endl;
    cout << "#   4. Exit                 #" << endl;
    cout << "#                           #" << endl;
    cout << "#############################" << endl << endl;
}

string take_str_input(const char* text) {
    char company[25];
    cout << text << endl;
    cin >> company;
    return company;
}

int take_int_input(const char* text) {
    char company[25];
    cout << text << endl;
    cin >> company;
    return atoi(company);
}


void create_company(AdManager& am) {
    string company = take_str_input("Enter company name: ");
    string message = take_str_input("Enter message: ");
    int bid = take_int_input("Enter your bid: ");
    auto new_company = Company(company, message, bid);
    new_company.writeToFile();
    am.addCompany(new_company);

}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Error. You must specify the port number." << endl;
        return -1;
    }

    // Split args and stick them in a vector
    vector<string> ports;

    for (int i = 1; i < argc; i++) {
        // check argv[i]
        string portName(argv[i]);

        // Test each arg to ensure it matches "COM*"
        if (portName == "COM1" || portName == "COM2" || portName == "COM3" || portName == "COM4" || portName == "COM5") {
            ports.push_back("\\\\.\\" + portName);
        }
        else {
            cerr << "Error. Your options are 'COM1', 'COM2', 'COM3', 'COM4' or 'COM5' (Case sensitive): '" << portName << "'" << endl;
            return -1;
        }
    }
    auto am = AdManager(ports);
    flush_file();


    while(true) {
        int answer = 0;
        print_menu();
        cout << "Enter your choice: " << endl;
        cin >> answer;

        //
        if (answer == 1) {
            if(am.am_company_size() > 5) {
                cerr << "Max 5 entries." << endl;
                continue;
            }
            create_company(am);
        }
        else if (answer == 2) {
            am.sendAdsToSerial();
        }
        else if (answer == 3) {
            am.readFile();
        }
        else if (answer == 4) {
            exit(0);
        }
        else {
            cerr << "Choices are 1 to 4." << endl;
        }
    }
    
    return 0;
}



