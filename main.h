/**
*    \brief This program calculates the sales tax due to the state/county at the end of each month
*    by inputing the total amount in dollars collected. Report will be print with the month and year input
*    by the user.
*
*    \author Kristopher J Sewell
*    \version 0.0.4
*
*/
#ifndef MAIN_H_TAX_CALC_G
#define MAIN_H_TAX_CALC_G

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>

using namespace std;

static const float TAX_STATE_RATE = 0.06500;
static const float TAX_COUNTY_RATE = 0.02750;
static const double MOD_TOTALCOLLECT = 1/(TAX_COUNTY_RATE + TAX_STATE_RATE + 1);

/**
*    \brief Evaluates if the variable "month" is within normal values.
*
*    \param string string containing month
*    \return true or false
*/
bool check_month(string);

/**
*    \brief Evaluates if the variable "year" is within normal values.
*
*    \param integer integer between 1 - 2500
*    \return true or false
*/
bool check_year(int);

/**
*    \brief Evaluates if the variable "totalCollectedAmount" is within normal values.
*
*    \param double double floating point value
*    \return true or false
*/
bool check_totalCollectedAmount(double);

/**
*    \brief Evaluates if the variable "again" is within normal values.
*
*    \param char character reference
*    \return true or false
*/
bool check_again(char &);

/**
*    \brief Checks to see if the user would like to run the program again.
*
*/
char input_var_again();

/**
*    \brief Clears the cin object of an error and flushes the buffer.
*
*/
void input_cin_reset();

/**
*    \brief Determines the county/state taxes due based on argument values.
*    Additionally Formats and prints to console the information in a report.
*
*    \param string month
*    \param int year
*    \param double double floating point value in dollars
*/
void output_report(string, int, double);

/**
*    \brief Gets from the user the month to include on the report.
*
*    \param boolean flag denoting first run
*    \return string containing the month
*/
string input_month(bool);

/**
*    \brief Gets from the user the year to include on the report.
*
*    \param boolean flag denoting first run
*    \return integer value representing the year
*/
int input_year(bool);

/**
*    \brief Gets from the user total collected revenue to be evaluated.
*
*    \param boolean flag denoting first run
*    \return double floating point number
*/
double input_totalCollectedAmount(bool);

/**
*    \brief Formats the month string into a standardized format with the first character capitalized
*    and the remaining characters in lowercase.
*
*    \param string string value of a month
*    \return corrected string
*/
string standard_month(string);

/**
*    \brief Function takes an integer and determines how many decimal places the integer has.
*
*    \param num integer value being evaluated
*    \return integer value representing number of digits
*/
int digit_of_num(int);

#endif