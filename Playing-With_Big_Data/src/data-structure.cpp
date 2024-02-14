#include "data-structure.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

const int32_t MAX_PROFIT_OUTPUT{10};

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

void DataStructure::get(std::string &user_id, std::string &product_id, int64_t timestamp) {
    std::cout << SEPERATOR << data[user_id][product_id][timestamp].sale << "\n" << SEPERATOR;
}

void DataStructure::purchased(std::string &user_id) {
    std::cout << SEPERATOR;
    for(auto &product : data[user_id]) {
        for(auto &timestamp : product.second) {
            if(!timestamp.second.sale) continue;
            Data &dt = timestamp.second;
            std::cout << dt.product_id << " " << dt.timestamp << " " 
                      << dt.price << " " << dt.age_group << " " 
                      << dt.gender << "\n";
        }
    }
    std::cout << SEPERATOR;
}

void DataStructure::clicked(std::string &p1, std::string &p2) {
    std::cout << SEPERATOR;
    for(auto &user : data) {
        if(user.second.count(p1) && user.second.count(p2)) {
            std::cout << user.first << "\n";
        }
    }
    std::cout << SEPERATOR;
}

void DataStructure::profit(int64_t time, double rate) {
    std::cout << SEPERATOR;
    int fited_user_number{0};
    for(auto &user : data) {
        int32_t sales_number{0}, click{0};
        for(auto &product : user.second) {
            for(auto timestamp = product.second.lower_bound(time); timestamp != product.second.end(); ++timestamp) {
                sales_number += (*timestamp).second.sale;
                click++;
            }
        }
        if(click != 0 && double(sales_number) / click >= rate) {
            std::cout << user.first << "\n";
            fited_user_number++;
            if(fited_user_number >= MAX_PROFIT_OUTPUT) {
                break;
            }
        }
    }
    std::cout << SEPERATOR;
}

void DataStructure::insert(Data &dt) {
    data[dt.user_id][dt.product_id][dt.timestamp] = dt;
}