#include <string>
#include <vector>
using std::string;
using std::vector;

void string_date_to_ints(const string& date_str, int& year_int, int& month_int,
                         int& day_int);

void string_date_to_int_ptrs(const string& date_str, int* year_ptr,
                             int* month_ptr, int* day_ptr);

double interest_for_month(double& balance_dub, const double& apr_dub);

double deposit(double& balance_dub, const double& amount_dub);

bool withdraw(double& balance_dub, const double& amount_dub);

void overdraft(double& balance_dub, const double& amount_dub);

int number_of_first_of_months(const string& date_early_str,
                              const string& date_late_str);

double interest_earned(double& balance_dub, const double& apr_dub,
                       const string& date_begin_str,
                       const string& date_end_str);

string process_command(const string& input_str, string& prev_date_str,
                       double& balance_dub, const double& apr_dub);

string process_commands(const string& input_str, const double& apr_dub);
