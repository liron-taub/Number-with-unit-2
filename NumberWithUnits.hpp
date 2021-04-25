
#ifndef UNTITLED5_NUMBERWITHUNITS_HPP
#define UNTITLED5_NUMBERWITHUNITS_HPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>


using namespace std;

namespace ariel {

    class NumberWithUnits {
    private:
        static map<string, double> unit;
        double num;
        string s;

    public:
        NumberWithUnits(double number, const string &str);

        static double convert(double num, const string &from, const string &to);

        static bool checkUnit(const string &check);

        static void read_units(ifstream &path);

        NumberWithUnits operator+(const NumberWithUnits &other) const;

        NumberWithUnits &operator+=(const NumberWithUnits &other);

        NumberWithUnits operator+();

        NumberWithUnits operator-(const NumberWithUnits &other) const;

        NumberWithUnits operator-();

        NumberWithUnits operator-=(const NumberWithUnits &other);

        friend bool operator==(const NumberWithUnits &c1, const NumberWithUnits &c2);

        friend bool operator!=(const NumberWithUnits &c1, const NumberWithUnits &c2);

        friend bool operator>=(const NumberWithUnits &c1, const NumberWithUnits &c2);

        friend bool operator>(const NumberWithUnits &c1, const NumberWithUnits &c2);

        friend bool operator<=(const NumberWithUnits &c1, const NumberWithUnits &c2);

        friend bool operator<(const NumberWithUnits &c1, const NumberWithUnits &c2);

        friend NumberWithUnits operator*(const NumberWithUnits &c1, const double &c2);

        friend NumberWithUnits operator*(const double &c1, const NumberWithUnits &c2);


        NumberWithUnits &operator++();

        NumberWithUnits operator++(int dummy);

        NumberWithUnits &operator--();

        NumberWithUnits operator--(int dummy);

        friend ostream &operator<<(ostream &os, const NumberWithUnits &c);

        friend istream &operator>>(istream &is, NumberWithUnits &c);


    };

}


#endif //UNTITLED5_NUMBERWITHUNITS_HPP
