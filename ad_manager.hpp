
#ifndef __AD_MANAGER_H__ 
#define __AD_MANAGER_H__

#include <iostream>
#include <vector>
#include "company.hpp"

#define MAX_TIME 60
#define MAX_CMP_NAME 20
#define MAX_CMP_MESS 100
#define MAX_CMP_BID 10

using std::vector;

enum State { ADD, ARDU, SAVE, READ, FLSH, EXIT };

class AdManager { 
    vector<Company> companyAds;
    vector<std::string> serialPorts;

    vector<string> splitString(std::string text, std::string delimiter);
public:
    /* Constructor. */
    AdManager(vector<std::string> serialPorts);

    /* Adds a company to the companyAds vector. */
    void am_add_company(Company company);

    /* Connects to COM ports and sends the company ads through. */
    void am_send_ad_to_serial();

    /* Reads file. */
    void am_read_file(const char* text);

    /* Saves to file. */
    void am_save_file(const char* text);

    /* Returns the size of companyAds vector */
    int am_company_size();

    /* Clears the company_ads */
    void am_flush_cmp_vector();
};

#endif