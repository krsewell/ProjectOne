#ifndef MONTH_H_TAX_CALC_G
#define MONTH_H_TAX_CALC_G

#include <iostream>
#include <map>

using namespace std;

const class Month 
{
    public:
        Month(const char*);
        Month(const int);
        Month(const short);
        
        const void output(ostream&);
        const Month* next();
        const Month* prev();
    
    private:
        const short month_value;
        const static map<int,string> months;

        static short sts(const char*);
};

#endif