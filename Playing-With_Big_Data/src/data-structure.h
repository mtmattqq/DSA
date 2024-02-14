#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

/// 1       2                    3                            4
/// <Sale>, <SalesAmountInEuro>, <time_delay_for_conversion>, <click_timestamp>,
/// 5                  6                7                    8              9
/// <nb_clicks_1week>, <product_price>, <product_age_group>, <device_type>,<audience_id> ,
/// 10                 11               12 13 14 15 16 17 18    19  
/// <product_gender>, <product_brand>, <product_category(1-7)> ,<product_country>, 
/// 20              21              22           23
/// <product_id>, <product_title>, <partner_id>, <user_id>

/// What we need 
/// sale, product_id, click_timestamp, price, age_group, gender, user_id

#include <string>
#include <cstdint>
#include <map>

#define SEPERATOR "********************\n"

struct Data {
    bool sale;
    std::string product_id;
    int64_t timestamp;
    double price;
    std::string age_group;
    std::string gender;
    std::string user_id;

    // bool operator<(Data b);
    friend std::ostream& operator<<(std::ostream&, Data&);
    friend std::istream& operator>>(std::istream&, Data&);
};

class DataStructure {
public:
    void get(std::string, std::string, int64_t);
    void insert(Data);
private:
    // user_id, product_id, timestamp
    std::map<std::string, std::map<std::string, std::map<int64_t, Data>>> data;
};

#endif