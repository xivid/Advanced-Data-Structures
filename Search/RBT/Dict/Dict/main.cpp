//
// Created by 杨志飞 on 15/5/20.
//

#include <iostream>
#include <string>
#include "Dictionary.h"
using namespace std;
class People {
    string name, province;
    int age;
    bool sex;
public:
    static const bool MALE = true, FEMALE = false;
    People() {province = "abd";}
    People(People const& p) {*this = p;}
    People(string Name, string Province, int Age, bool Sex): name(Name), province(Province), age(Age), sex(Sex) {}
    string getProvince() { return province; }
    string getName() { return name; }
};
int main() {
    Dict<string, People> Family;
    Family["Father"] = People("Yang Dejun",
                              "Shandong",
                              45,
                              People::MALE);
    Family["Mother"] = People("Zhang Shuying", "Shandong", 44, People::FEMALE);
    Family["Son"] = People("Yang Zhifei", "Shandong", 19, People::MALE);
    Family["Daughter"] = People("Yang Yifei", "Shandong", 3, People::FEMALE);
    cout << "The daughter " << Family["Daughter"].getName() << " is from " << Family["Daughter"].getProvince() << " province." << endl;
    return 0;
}