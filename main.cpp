#include "main.h"

char again;

int main()
{
  do
  {
    //User Input
    bool firstRun = true;
    string month = input_month(firstRun);
    int year = input_year(firstRun);
    double totalCollectedAmount = input_totalCollectedAmount(firstRun);

    //Calculate values and generate report
    output_report(month, year, totalCollectedAmount);

    //Repeat?
    input_var_again();

  } while (check_again(again));

  //Exit without errors
  return (0);
}

string input_month(bool firstRun)
{
  bool month_inputInvalid = true;
  string month;

  while (month_inputInvalid)
  {
    if (!check_month(month))
    {
      if (!firstRun)
      {
        cout << "\nOpps... you entered an invalid month.\n";
      }

      cout << "\nPlease enter the month you would like on the report: "
           << "\n*Note* Only full names are accepted (i.e January)";
      cin >> month;
      input_cin_reset();
      month = standard_month(month);
    }
    if (check_month(month))
    {
      month_inputInvalid = false;
    }
    firstRun = false;
  }
  return month;
}

int input_year(bool firstRun)
{
  bool year_inputInvalid = true;
  int year = -1;

  while (year_inputInvalid)
  {
    if (!check_year(year))
    {
      if (!firstRun)
      {
        cout << "\nOpps... you entered an invalid year.\n";
      }
      cout << "\nPlease enter the year you would like on the report: ";
      cin >> year;
      input_cin_reset();
    }
    if (check_year(year))
    {
      year_inputInvalid = false;
    }
    firstRun = false;
  }
  return year;
}

double input_totalCollectedAmount(bool firstRun)
{
  bool totalCollectedAmount_inputInvalid = true;
  double totalCollectedAmount = -1;

  while (totalCollectedAmount_inputInvalid)
  {
    if (!check_totalCollectedAmount(totalCollectedAmount))
    {
      if (!firstRun)
      {
        cout << "\nOpps... you entered an invalid amount collected.\n";
      }

      cout << "\nPlease enter the amount you collected this month: ";
      cin >> totalCollectedAmount;
      input_cin_reset();
    }

    if (check_totalCollectedAmount(totalCollectedAmount))
    {
      totalCollectedAmount_inputInvalid = false;
    }
    firstRun = false;
  }
  return totalCollectedAmount;
}

void output_report(const string month, const int year, const double totalCollectedAmount)
{
  const double totalSalesAmount = MOD_TOTALCOLLECT * totalCollectedAmount;
  const double salesTaxState = totalSalesAmount * TAX_STATE_RATE;
  const double salesTaxCounty = totalSalesAmount * TAX_COUNTY_RATE;

  cout << endl  << endl << month << " " << year << endl;
  int length = month.length() + digit_of_num(year) + 1;
  for (int i = length; i > 0; i--)
  {
    cout << "-";
  }
  cout << endl;

  int digits = digit_of_num(totalCollectedAmount) + 3;
  cout << "Total Amount Collected:  " << setw(digits) << fixed << setprecision(2) << totalCollectedAmount << endl
       << "Total Amount Sold:       " << setw(digits) << fixed << setprecision(2) << totalSalesAmount << endl
       << "Tax due to County:       " << setw(digits) << fixed << setprecision(2) << salesTaxCounty << "    "
       << TAX_COUNTY_RATE * 100 << '%' << endl
       << "Tax due to State:        " << setw(digits) << fixed << setprecision(2) << salesTaxState << "    "
       << TAX_STATE_RATE * 100 << '%' << endl
       << endl;
}

char input_var_again()
{
  char again;
  cout << "Would you like to do another calculation??" << endl << "('Y' or 'N')" << endl;
  cin >> again;
  input_cin_reset();
  return again;
}

void input_cin_reset()
{
  while (cin.fail())
  {
    cin.clear();
    cin.ignore(5, '\n');
  }
}

string standard_month(const string pstring)
{
  char chars[pstring.length()];
  for (unsigned int i = 0; i < pstring.length(); i++)
  {
    chars[i] = tolower(pstring[i]);
  }
  chars[0] = toupper(chars[0]);
  return string(chars);
}

bool check_again(char &again)
{
  again = toupper(again);

  while (again != 'Y' && again != 'N')
  {
    cout << "Sorry..." << endl
         << endl;
    input_var_again();
    again = toupper(again);
  }

  return again == 'Y';
}

bool check_month(const string pstring)
{
  input_cin_reset();
  const int MONTHS_ARRAY_SIZE = 13;
  const string monthsArray[MONTHS_ARRAY_SIZE] = {"", "January", "February",
                                           "March", "April", "May", "June", "July", "August",
                                           "September", "October", "November", "December"};

  //checking valid month
  for (int i = 1; i < MONTHS_ARRAY_SIZE; i++)
  {
    if (pstring == monthsArray[i])
    {
      return true;
    }
  }
  return false;
}

bool check_year(const int pyear)
{
  input_cin_reset();
  return pyear > 0 && pyear < 2501;
}

bool check_totalCollectedAmount(const double ptotalCollectedAmount)
{
  input_cin_reset();
  return ptotalCollectedAmount > 0;
}

int digit_of_num(const int num)
{
  int j = 0;
  int test = num;
  while (test > 0)
  {
    j++;
    test /= 10;
  }
  return j;
}
