#include "month.h"

const class Month 
{
    public:
        Month::Month(const char* chars) : month_value{sts(chars)} {}
        Month::Month(const int month_int) : month_value{month_int} {}
        Month::Month(const short month_sht) : month_value{month_sht} {}

        Month::~Month()
        {
            delete &months;
        }

        const void Month::output(ostream&) {}
        
        const Month* Month::next() {
            return new Month(1 + month_value);
        }

        const Month* Month::prev() {
            return new Month(-1 + month_value);
        }

    
    private:
        const short month_value;
        const static map<int,string> months; 

        static short sts(const char* chars){

        }
}