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
bool check_totalCollectedAmount(double);
bool check_again(char &);

void input_var_again();
void input_cin_reset();
void output_report(string,int,double);

string input_month(bool);
int input_year(bool);
double input_totalCollectedAmount(bool);
string standard_month(string);
double round_num(double);
int digit_of_num(int);

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
*    \brief This program calculates the sales tax due to the state/county at the end of each month
*    by inputing the total amount in dollars collected. Report will be print with the month and year input
*    by the user.
*
*    \author Kristopher J Sewell
*    \version 0.0.3
*
*/
int main(){
do {
    string  month;
    int     year;
    double  totalCollectedAmount;

    //User Input
    bool firstRun = true;
    month = input_month(firstRun);
    year = input_year(firstRun);
    totalCollectedAmount = input_totalCollectedAmount(firstRun);



    //Calculate values and generate report

    output_report(month,year,totalCollectedAmount);


    //Repeat?
    input_var_again();

} while (check_again(again));



//Exit without errors
return(0);

}




/**
*    \brief Gets from the user the month to include on the report.
*
*    \param boolean flag denoting first run
*    \return string containing the month
*/
string input_month(bool firstRun){
    bool month_inputInvalid = true;
    string month;

    while (month_inputInvalid){
        if (!check_month(month)){
            if (!firstRun){
                cout << "\nOpps... you entered an invalid month.\n";
            }

            cout << "\nPlease enter the month you would like on the report: " <<
                    "\n*Note* Only full names are accepted (i.e January)";
            cin >> month;
            input_cin_reset();
            month = standard_month(month);
        }
        if (check_month(month)){
            month_inputInvalid = false;
        }
        firstRun = false;
    }
    return month;
}

/**
*    \brief Gets from the user the year to include on the report.
*
*    \param boolean flag denoting first run
*    \return integer value representing the year
*/
int input_year(bool firstRun){
   bool year_inputInvalid = true;
   int year = -1;

   while (year_inputInvalid){
        if (!check_year(year)){
            if (!firstRun){
                cout << "\nOpps... you entered an invalid year.\n";
            }
            cout << "\nPlease enter the year you would like on the report: ";
            cin >> year;
            input_cin_reset();
        }
        if (check_year(year)){
            year_inputInvalid = false;
        }
        firstRun = false;
    }
    return year;
}

/**
*    \brief Gets from the user total collected revenue to be evaluated.
*
*    \param boolean flag denoting first run
*    \return double floating point number
*/
double input_totalCollectedAmount(bool firstRun){
    bool totalCollectedAmount_inputInvalid = true;
    double totalCollectedAmount = -1;

    while (totalCollectedAmount_inputInvalid){
        if (!check_totalCollectedAmount(totalCollectedAmount)){
            if (!firstRun){
                cout << "\nOpps... you entered an invalid amount collected.\n";
            }

            cout << "\nPlease enter the amount you collected this month: ";
            cin >> totalCollectedAmount;
            input_cin_reset();
        }

        if (check_totalCollectedAmount(totalCollectedAmount)){
            totalCollectedAmount_inputInvalid = false;
        }
        firstRun = false;
    }
    return totalCollectedAmount;
}

/**
*    \brief Determines the county/state taxes due based on argument values.
*    Additionally Formats and prints to console the information in a report.
*
*    \param string month
*    \param int year
*    \param double double floating point value in dollars
*/
void output_report(string month,int year,double totalCollectedAmount){
    double  totalSalesAmount,
            salesTaxState,
            salesTaxCounty;


    totalSalesAmount = MOD_TOTALCOLLECT * totalCollectedAmount; //This is now the sales amount without tax
    salesTaxState = totalSalesAmount * TAX_STATE_RATE;
    salesTaxCounty = totalSalesAmount * TAX_COUNTY_RATE;

    totalSalesAmount = round_num(totalSalesAmount);
    salesTaxCounty = round_num(salesTaxCounty);
    salesTaxState = round_num(salesTaxState);

    int digits;
    digits = digit_of_num(totalCollectedAmount) + 3;

    //how long is the report header
    int length = month.length() + digit_of_num(year) + 1;

    cout    << endl << endl << month << " " << year << endl;
    for (int i = length; i >0; i--){
        cout << "-";
    }
    cout << endl;

    cout    << "Total Amount Collected:  " << setw(digits) << fixed << setprecision(2) << totalCollectedAmount << endl
            << "Total Amount Sold:       " << setw(digits) << fixed << setprecision(2) << totalSalesAmount << endl
            << "Tax due to County:       " << setw(digits) << fixed << setprecision(2) << salesTaxCounty << "    "
                        << TAX_COUNTY_RATE*100 << '%' <<endl
            << "Tax due to State:        " << setw(digits) << fixed << setprecision(2) << salesTaxState << "    "
                        << TAX_STATE_RATE*100 << '%' <<endl << endl;




}

/**
*    \brief Checks to see if the user would like to run the program again.
*
*/
void input_var_again(){
    cout << "Would you like to do another calculation??" << endl;
    cout << "('Y' or 'N')" << endl;
    cin >> again;
    input_cin_reset();
}

/**
*    \brief Clears the cin object of an error and flushes the buffer.
*
*/
void input_cin_reset(){
    if (cin.fail()){
        cin.clear();
        cin.ignore(5,'\n');
    }
}

/**
*    \brief Formats the month string into a standardized format with the first character capitalized
*    and the remaining characters in lowercase.
*
*    \param string string value of a month
*    \return corrected string
*/
string standard_month(string pstring){
    for (unsigned int i = 0; i < pstring.length();i++){
        pstring[i] = tolower(pstring[i]);
    }
    pstring[0] = toupper(pstring[0]);
    return pstring;
}

/**
*    \brief Evaluates if the variable "again" is within normal values.
*
*    \param char character reference
*    \return true or false
*/
bool check_again(char & again){

    again = toupper(again);

    while (again != 'Y' && again != 'N'){
        cout << "Sorry..." << endl << endl;
        input_var_again();
        again = toupper(again);
    }


    if (again == 'Y'){
        return true;

    } else if (again == 'N'){
        return false;
    }

    return false; //should never reach here.
                  //Provided to terminate program just in case.
}

/**
*    \brief Evaluates if the variable "month" is within normal values.
*
*    \param string string containing month
*    \return true or false
*/
bool check_month(string pstring){
    input_cin_reset();
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

/**
*    \brief Evaluates if the variable "year" is within normal values.
*
*    \param integer integer between 1 - 2500
*    \return true or false
*/
bool check_year(int pyear){
    input_cin_reset();
    if (pyear > 0 && pyear < 2501){

        return true;
    }
    else {
        return false;
    }
}

/**
*    \brief Evaluates if the variable "totalCollectedAmount" is within normal values.
*
*    \param double double floating point value
*    \return true or false
*/
bool check_totalCollectedAmount(double ptotalCollectedAmount){
    input_cin_reset();
    if (ptotalCollectedAmount > 0){

        return true;
    }
    else {
        return false;
    }
}

/**
*    \brief  This function takes a double floating point number and rounds the value to the nearest two
*            decimal places.
*
*    \param double double floating point value
*    \return double floating point rounded to the nearest two decimal places
*/
double round_num(double num){
    double fraction = num - floor(num);

    if (fraction > 0.4999999){
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

/**
*    \brief Function takes an integer and determines how many decimal places the integer has.
*
*    \param num integer value being evaluated
*    \return integer value representing number of digits
*/
int digit_of_num(int num){
    int j = 0;
    for (; num > 0;num /= 10){
        j++;
    }
    return j;
}
