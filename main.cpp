#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>

using namespace std;

char again;                                             //used to repeat program.
const float TAX_STATE_RATE = 0.06500;
const float TAX_COUNTY_RATE = 0.02750;
const double MOD_TOTALCOLLECT = 0.915331807780320366;   //Value removes tax from totalCollectedAmount
                                                        //       1/(countytax + statetax + 1)


bool check_month(string);
bool check_year(int);
bool check_totalCollectedAmount(float);
string standard_month(string);
double round_num(double);

/*
    Feature list:   *ask the user for the   month (string)
                                            year (integer)
                                            money collected for that month (float) [i.e.sales + taxes]
                    *calculate the state taxes as well as the county taxes
                    *enable them to repeat the above process
                    [n]state sales tax is 6.5%
                    [n]county sales tax is 2.75%
                    *output month, year, total collected, sales, county sales tax,
                    state sales tax and total sales tax.
                    *collected == amount of sales plus county tax plus state tax
*/
/**
    This program calculates the sales tax due to the state/county at the end of each month
    by inputing the total amount in dollars collected. Report will be print with the month and year input
    by the user.

    @author Kristopher J Sewell
    @version 0.0.3

*/
int main()
{
do {
    string  month = "";
    int     year = -1;
    double  totalCollectedAmount = -1;
    bool    month_inputInvalid,
            year_inputInvalid,
            totalCollectedAmount_inputInvalid;
    //Assume that user provides invalid data

    month_inputInvalid = year_inputInvalid = totalCollectedAmount_inputInvalid = true;


    //User Input
    bool firstRun = true;
    while (month_inputInvalid){
        if (!check_month(month)){
            if (!firstRun){
                cout << "\nOpps... you entered an invalid month.\n";
            }

            cout << "\nPlease enter the month you would like on the report: " <<
                    "\n*Note* Only full names are accepted (i.e January)";
            cin >> month;
            cin.ignore(5,'\n');
            month = standard_month(month);
        }
        if (check_month(month)){
            month_inputInvalid = false;
        }
        firstRun = false;
    }

    firstRun = true;
    while (year_inputInvalid){
        if (!check_year(year)){
            if (!firstRun){
                cout << "\nOpps... you entered an invalid year.\n";
            }
            cout << "\nPlease enter the year you would like on the report: ";
            cin >> year;
            cin.ignore(5,'\n');
        }
        if (check_year(year)){
            year_inputInvalid = false;
        }
        firstRun = false;
    }

    firstRun = true;
    while (totalCollectedAmount_inputInvalid){
        if (!check_totalCollectedAmount(totalCollectedAmount)){
            if (!firstRun){
                cout << "\nOpps... you entered an invalid amount collected.\n";
            }

            cout << "\nPlease enter the amount you collected this month: ";
            cin >> totalCollectedAmount;
            cin.ignore(5,'\n');
        }

        if (check_totalCollectedAmount(totalCollectedAmount)){
            totalCollectedAmount_inputInvalid = false;
        }
        firstRun = false;
    }

    //Calculate values
    double  totalSalesAmount,
            salesTaxState,
            salesTaxCounty;


    totalSalesAmount = MOD_TOTALCOLLECT * totalCollectedAmount; //This is now the sales amount without tax
    salesTaxState = totalSalesAmount * TAX_STATE_RATE;
    salesTaxCounty = totalSalesAmount * TAX_COUNTY_RATE;

    totalSalesAmount = round_num(totalSalesAmount);
    salesTaxCounty = round_num(salesTaxCounty);
    salesTaxState = round_num(salesTaxState);

    //validate calculated data

    if (totalCollectedAmount == totalSalesAmount + salesTaxCounty + salesTaxState){
        cout << "good";
    } else {
        cout    << "There was an error with the calculation" << endl
                << "totalCollectedAmount: " << setprecision(9) << totalCollectedAmount << endl
                << "totalSalesAmount: " << setprecision(9) << totalSalesAmount << endl
                << "salesTaxCounty: " << setprecision(9) << salesTaxCounty << endl
                << "salesTaxState: " << setprecision(9) << salesTaxState << endl;
    }



    //generate report
    //format "%.2lf %.2lf"

    cout << '|' << month << year << '|' << endl;
    //cout << month.length() + year.length() + 3;
    int length = 0;
    for (int i = 0; i < length;i++){
        cout << '-';
    }


    //Repeat?
    cout << "Would you like to do another calculation??" << endl;
    cout << "('Y' or 'N')" << endl;
    cin >> again;
    cin.ignore(5,'\n');
} while (again == 'Y'); // 'N' is not evaluated. any value other then 'Y' will end the program.

return 0;
}


string standard_month(string pstring){
    for (unsigned int i = 0; i < pstring.length();i++){
        pstring[i] = tolower(pstring[i]);
    }
    pstring[0] = toupper(pstring[0]);
    return pstring;
}

bool check_month(string pstring){
    const int MONTHS_ARRAY_SIZE = 13;
    string monthsArray[MONTHS_ARRAY_SIZE] = {"","January","February",
        "March","April","May","June","July","August",
        "September","October","November","December"};

    //checking valid month
    for (int i = 1; i < MONTHS_ARRAY_SIZE;i++) {
        if (pstring == monthsArray[i]){
            return true;
        }
    }
    return false;
}

bool check_year(int pyear){
    if (pyear > 0 && pyear < 2501){
        return true;
    }
    else {
        return false;
    }
}

bool check_totalCollectedAmount(float ptotalCollectedAmount){
    if (ptotalCollectedAmount > 0){
        return true;
    }
    else {
        return false;
    }
}

double round_num(double num){
    double fraction = num - floor(num);

    if (fraction > 0.49999){
        num *= 100;
        num = ceil(num);
        num *= 0.01;
        return num;
    }
    else {
        num *= 100;
        num = floor(num);
        num *= 0.01;
        return num;
    }
}
