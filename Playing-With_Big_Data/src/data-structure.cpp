#include "data-structure.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

void skip(std::istream &in, int n) {
    for(int i{0}; i < n; ++i) {
        in.ignore(4096, '\t');
    }
}

std::istream& operator>>(std::istream &in, Data &data) {
    // char tp[MAX_LENGTH]{0};
    std::string tp;
    std::getline(in, tp, '\t'); // 1
    if(tp != "0" && tp != "1") {
        return in;
    }
    data.sale = bool(std::stoi(tp));
    skip(in, 2);
    std::getline(in, tp, '\t'); // 4
    data.timestamp = std::stoll(tp);
    skip(in, 1);
    std::getline(in, tp, '\t'); // 6
    data.price = std::stod(tp);
    std::getline(in, tp, '\t'); // 7
    data.age_group = tp;
    skip(in, 2);
    std::getline(in, tp, '\t'); // 10
    data.gender = tp;
    skip(in, 9);
    std::getline(in, tp, '\t'); // 20
    data.product_id = tp;
    skip(in, 2);
    std::getline(in, tp, '\n'); // 23
    data.user_id = tp;
    return in;
}

std::ostream& operator<<(std::ostream &out, Data &data) {
    out << SEPERATOR << "User ID: " << data.user_id << "\n";
    out << "Product ID: " << data.product_id << "\n";
    out << "Timestamp: " << data.timestamp << "\n";
    out << "Price: " << data.price << "\n";
    out << "Age Group: " << data.age_group << "\n";
    out << "Gender: " << data.gender << "\n";
    out << "Sale: " << data.sale << "\n" << SEPERATOR;
    return out;
}

// struct Data {
//     bool sale;
//     std::string product_id;
//     int64_t timestamp;
//     double price;
//     std::string age_group;
//     std::string gender;
//     std::string user_id;

//     // bool operator<(Data b);
//     friend std::ostream& operator<<(std::ostream&, Data&);
//     friend std::istream& operator>>(std::istream&, Data&);
// };

void DataStructure::get(std::string user_id, std::string product_id, int64_t timestamp) {
    std::cout << SEPERATOR << data[user_id][product_id][timestamp].sale << SEPERATOR;
}