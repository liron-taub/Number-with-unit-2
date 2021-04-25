#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

map<string, double> NumberWithUnits::unit;

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);//go over the string
    string unit;
    while(getline(ss, unit, delim)) {
        elems.push_back(unit);
    }
    return elems;
}


NumberWithUnits::NumberWithUnits(double number, const string &str) {//I set it as const because I do not change the value, and I put & for the prevent copy by value
    if (checkUnit(str)) {
        num = number;
        s = str;
    } else {
        throw std::invalid_argument(str + " unit is not allowed");
    }
}
//A function that checks if a particular unit exists
bool NumberWithUnits::checkUnit(const string &check) {
    return unit.count(check + ":" + check) != 0;// Check if the unit itself already exists then returns true else false
}


void NumberWithUnits::read_units(ifstream &path) {
    double firstNum = NAN;
    string unit1;
    double secNum = NAN;
    string unit2;

    string line;
    if (path.is_open()) {
        while (getline(path, line)) {//Read the next line into the line variable
            unsigned int i = 0;
            string temp;

            // read the first number and convert it to int
            while (('0' <= line[i] && line[i] <= '9') || line[i] == '.') {
                temp += line[i++];
            }
            firstNum = stod(temp);//Saves the value into the variable

            // skip the ' ' until the first letter
            while (line[i] == ' ') {
                i++;
            }

            // read the first letter and convert it to int
            temp = "";
            while ('A' <= line[i] && line[i] <= 'z') {
                temp += line[i++];
            }
            unit1 = temp;//Saves the value into the variable

            // skip the ' ' and '=' until the first number
            while (line[i] == ' ' || line[i] == '=') {
                i++;
            }

            // read the second number and convert it to int
            temp = "";
            while (('0' <= line[i] && line[i] <= '9') || line[i] == '.') {
                temp += line[i++];
            }
            secNum = stod(temp);//Saves the value into the variable

            // skip the ' ' until the first letter
            while (line[i] == ' ') {
                i++;
            }

            // read the second letter and convert it to int
            temp = "";
            while ('A' <= line[i] && line[i] <= 'z') {
                temp += line[i++];
            }
            unit2 = temp;//Saves the value into the variable

//Calculation of conversions
            unit[unit1 + ":" += unit2] = secNum / firstNum;
            unit[unit2 + ":" += unit1] = firstNum / secNum;
        }
        path.close();


        map < string, double > ::iterator it1;
        map < string, double > ::iterator it2;

        for (it1 = unit.begin(); it1 != unit.end(); it1++) {
            vector <string> temp = split(it1->first, ':');
            string from1 = temp[0];
            string to1 = temp[1];

            for (it2 = unit.begin(); it2 != unit.end(); it2++) {
                temp = split(it2->first, ':');
                string from2 = temp[0];
                string to2 = temp[1];

                if (to1 == from2 && from1 != from2) {
                    unit[from1 + ":" += to2] = unit[it2->first] * unit[it1->first];
                    unit[to2 + ":" += from1] = 1 / (unit[it2->first] * unit[it1->first]);
                }
            }
        }
    }
}

//A converting function
double NumberWithUnits::convert(double num, const string &from, const string &to) {
    string units = from + ":" + to;
    if (unit.count(units) == 0) {
        throw std::invalid_argument("Units do not match - ["+from+"] cannot be converted to ["+to+"]");
    }
    double factor = unit[units];//If the unit exists, then go to the contents of the unit
    return num * factor;
}


NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
    double numplus = convert(other.num, other.s, s);
    return NumberWithUnits(num + numplus, s);
}

NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other) {
    double numplus = convert(other.num, other.s, s);
    num += numplus;
    return *this;//Changes the original and therefore returns the *this

}

NumberWithUnits NumberWithUnits::operator+() {
    return NumberWithUnits{num, s};
}

NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const {
    double numplus = convert(other.num, other.s, s);
    return NumberWithUnits(num - numplus, s);

}

NumberWithUnits NumberWithUnits::operator-() {
    return NumberWithUnits{-num, s};
}


NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &other) {
    double numplus = convert(other.num, other.s, s);
    num -= numplus;
    return *this;//Changes the original and therefore returns the *this

}


NumberWithUnits &NumberWithUnits::operator++() {
    ++num;
    return *this;
}

NumberWithUnits NumberWithUnits::operator++(int dummy) {
    NumberWithUnits temp{num, s};
    num++;
    return temp;
}

NumberWithUnits &NumberWithUnits::operator--() {
    --num;
    return *this;

}

NumberWithUnits NumberWithUnits::operator--(int dummy) {
    NumberWithUnits temp{num, s};
    num--;
    return temp;

}

namespace ariel {
    const float TOLERANCE = 0.001;

    bool operator==(const NumberWithUnits &c1, const NumberWithUnits &c2) {
        double numeuals = NumberWithUnits::convert(c2.num, c2.s, c1.s);
        return abs(numeuals - c1.num) < TOLERANCE;
    }

    bool operator!=(const NumberWithUnits &c1, const NumberWithUnits &c2) {
        return !(c1 == c2);
    }

    bool operator>=(const NumberWithUnits &c1, const NumberWithUnits &c2) {
        return c1 == c2 || c1 > c2;
    }

    bool operator>(const NumberWithUnits &c1, const NumberWithUnits &c2) {
        double numeuals = NumberWithUnits::convert(c2.num, c2.s, c1.s);
        return (c1.num - numeuals) >= TOLERANCE;

    }

    bool operator<=(const NumberWithUnits &c1, const NumberWithUnits &c2) {
        return c1 == c2 || c1 < c2;
    }

    bool operator<(const NumberWithUnits &c1, const NumberWithUnits &c2) {
        double numeuals = NumberWithUnits::convert(c2.num, c2.s, c1.s);
        return (numeuals - c1.num) >= TOLERANCE;

    }

    NumberWithUnits operator*(const NumberWithUnits &c1, const double &c2) {
        return NumberWithUnits(c2 * c1.num, c1.s);
    }

    NumberWithUnits operator*(const double &c1, const NumberWithUnits &c2) {
        return NumberWithUnits(c1 * c2.num, c2.s);
    }

    ostream &operator<<(ostream &os, const NumberWithUnits &c) {
        return (os << c.num << '[' << c.s << ']');
    }

    istream &operator>>(istream &is, NumberWithUnits &c) {
        string str;
        getline(is, str, ']'); //Calls from IS to STR until he sees]

        string num;
        string unitIn;
        unsigned int i = 0;

        while (' ' == str[i]){
            i++;
        }

        while (('0' <= str[i] && str[i] <= '9') || '+' == str[i] || '-' == str[i] || '.' == str[i]){
            num += str[i++];
        }

        while (' ' == str[i] || str[i] == '['){
            i++;
        }

        while ('A' <= str[i] && str[i] <= 'z'){
            unitIn += str[i++];
        }

        if (!NumberWithUnits::checkUnit(unitIn)) {
            throw std::invalid_argument(unitIn + " is invalid unit");
        }
        c = NumberWithUnits(stod(num), unitIn);
        return is;
    }
}




