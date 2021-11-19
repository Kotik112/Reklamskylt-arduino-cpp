/* TODO:
    - Int input får inte vara minus. (company.cpp)

 */

#include <iostream>
#include <string>
#include <vector>
#include <stdbool.h> // Behövs detta i c++ ens?
#include "ad_manager.hpp"
#include "menu.hpp"
#include "serial.h"

using namespace std;

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
    /* for (auto port: ports){
        cout << port << endl;
    } */

    // Create ad manager and send in ports
    auto am = AdManager(ports);

    men_entry(am);

    // Read file
    am.readFile();


/*     auto test_ad = Company("Danial", "LGG", 10000000);
    auto test_ad1 = Company("Google1", "Googolplex1", 1500);
    am.addCompany(test_ad);
    am.addCompany(test_ad1);
    am.sendAdsToSerial(); */

    
    return 0;
}



