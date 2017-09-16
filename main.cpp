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
bool check_again(char &);
string standard_month(string);
double round_num(double);

void get_input_var_again();
void input_cin_reset();
void output_report(string,int,double);

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
            input_cin_reset();
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
            input_cin_reset();
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
            input_cin_reset();
        }

        if (check_totalCollectedAmount(totalCollectedAmount)){
            totalCollectedAmount_inputInvalid = false;
        }
        firstRun = false;
    }

    //Calculate values and generate report

    output_report(month,year,totalCollectedAmount);


    //Repeat?
    get_input_var_again();

} while (check_again(again)); // 'N' is not evaluated. any value other then 'Y' will end the program.



//Exit without errors
return(0);

}





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

    for (int i = 100000000,j=0; i > 10; i=i/10,j++){
        if(totalCollectedAmount < i){
            digits = 11 - j;
        }
    }
    if (totalCollectedAmount > 10000000000){
        digits = 11;
    }

    //how long is the report header
    int length = month.length() + to_string(year).length() + 1;

    cout    << endl << endl << month << " " << year << endl;
    for (int i = length; i >0; i--){
        cout << "-";
    }
    cout << endl;

    cout    << "Total Amount Collected:  " << setw(digits) << fixed << setprecision(2) << totalCollectedAmount << endl
            << "Total Amount Sold:       " << setw(digits) << fixed << setprecision(2) << totalSalesAmount << endl
            << "Tax due to County:       " << setw(digits) << fixed << setprecision(2) << salesTaxCounty << "    " << TAX_COUNTY_RATE*100 << '%' <<endl
            << "Tax due to State:        " << setw(digits) << fixed << setprecision(2) << salesTaxState << "    " << TAX_STATE_RATE*100 << '%' <<endl << endl;




}


void get_input_var_again(){
    cout << "Would you like to do another calculation??" << endl;
    cout << "('Y' or 'N')" << endl;
    cin >> again;
    input_cin_reset();
}


void input_cin_reset(){
    if (cin.fail()){
        cin.clear();
        cin.ignore(5,'\n');
    }
}


string standard_month(string pstring){
    for (unsigned int i = 0; i < pstring.length();i++){
        pstring[i] = tolower(pstring[i]);
    }
    pstring[0] = toupper(pstring[0]);
    return pstring;
}


bool check_again(char & again){

    again = toupper(again);

    while (again != 'Y' && again != 'N'){
        cout << "Sorry..." << endl << endl;
        get_input_var_again();
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


bool check_year(int pyear){
    input_cin_reset();
    if (pyear > 0 && pyear < 2501){

        return true;
    }
    else {
        return false;
    }
}


bool check_totalCollectedAmount(float ptotalCollectedAmount){
    input_cin_reset();
    if (ptotalCollectedAmount > 0){

        return true;
    }
    else {
        return false;
    }
}


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
