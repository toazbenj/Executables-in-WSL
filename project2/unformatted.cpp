// Header

#include <vector>
#include <string>
using std::vector;
using std::string;

void string_date_to_ints(const string& date_str, int& year_int, int& month_int, int& day_int);

void string_date_to_int_ptrs(const string& date_str, int* year_ptr, int* month_ptr, int* day_ptr);

double interest_for_month(double& balance_dub, const double& apr_dub);

double deposit(double& balance_dub, const double& amount_dub);

bool withdraw(double& balance_dub, const double& amount_dub);

void overdraft(double& balance_dub, const double& amount_dub);

int number_of_first_of_months(const string& date_early_str, const string& date_late_str);

double interest_earned(double& balance_dub, const double& apr_dub, 
                       const string& date_begin_str, const string& date_end_str);

string process_command(const string& input_str, string& prev_date_str,
                        double& balance_dub, const double& apr_dub);
                        
string process_commands(const string& input_str, const double& apr_dub);



//Implementation
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::getline;
using std::stringstream;

vector<string> split(const string& input_str, const char& delimeter_chr = '\n'){
    // Puts string elements separated by a delimeter into a vector

    stringstream ss(input_str);
    string element;
    vector<string> out_vec;

    while(getline(ss, element, delimeter_chr))
        out_vec.push_back(element);

    return out_vec;
}

void string_date_to_int_ptrs(const string& date_str, int* year_ptr, int* month_ptr, int* day_ptr){
    vector<string> split_vec = split(date_str, '-');
    vector<int> out_vec;
    transform(split_vec.begin(), split_vec.end(), back_inserter(out_vec), [](auto p){return stoi(p);});

    *year_ptr = out_vec.at(0);
    *month_ptr = out_vec.at(1);
    *day_ptr = out_vec.at(2);
}

void string_date_to_ints(const string& date_str, int& year_int, int& month_int, int& day_int){
    string_date_to_int_ptrs(date_str, &year_int, &month_int, &day_int);
}

double interest_for_month(double& balance_dub, const double& apr_dub){
    int cents_interest_int = balance_dub * (apr_dub/12);
    return cents_interest_int/100.00;
}

double deposit(double& balance_dub, const double& amount_dub){
    balance_dub += amount_dub;
    return balance_dub;
}

bool withdraw(double& balance_dub, const double& amount_dub){
    if(amount_dub < balance_dub){
        balance_dub -= amount_dub;
        return true;
    }

    return false;
}

void overdraft(double& balance_dub, const double& amount_dub){
    balance_dub -= 35;
    balance_dub -= amount_dub;
}

int number_of_first_of_months(const string& date_begin_str, const string& date_end_str){
    int year1_int, month1_int, day1_int;
    int year2_int, month2_int, day2_int;

    string_date_to_int_ptrs(date_begin_str, &year1_int, &month1_int, &day1_int);
    string_date_to_int_ptrs(date_end_str, &year2_int, &month2_int, &day2_int);

    int firsts_int;
    if (year1_int == year2_int)
        firsts_int = month2_int -month1_int;
    else    
        firsts_int = 12 * (year2_int - year1_int - 1) + (12 - month1_int) + month2_int;

    return firsts_int;
}

double interest_earned(double& balance_dub, const double& apr_dub, 
                       const string& date_begin_str, const string& date_end_str){
    int periods_int = number_of_first_of_months(date_begin_str, date_end_str);
    double balance_proxy_dub = balance_dub;
    double interest_dub = 0;

    if (balance_dub > 0){
        for(int i = 0; i < periods_int; i++){
            interest_dub += interest_for_month(balance_proxy_dub, apr_dub);
            deposit(balance_proxy_dub, interest_for_month(balance_proxy_dub, apr_dub));
        }
    }

    return interest_dub;
}

void interest_output(const string& date_str, string& prev_date_str,
                     double& balance_dub, const double& apr_dub, stringstream& ss){
    // Calculates interest for given period, formats output text, deposites interest

    if (prev_date_str != ""){
        int interest_periods_int = number_of_first_of_months(prev_date_str, date_str);
        double interest_dub = interest_earned(balance_dub, apr_dub, prev_date_str, date_str);

        if (interest_periods_int != 0){
            ss << "Since " << prev_date_str << ", interest has accrued " << interest_periods_int 
            << " times." << endl << "$" << interest_dub << " interest has been earned." << endl;
            
            deposit(balance_dub, interest_dub);
        }
    }
}

void activity_output(const string& command_str, string& amount_str,
                     double& balance_dub, const double& apr_dub, stringstream& ss){
    // Executes deposit, withdraw, and overdraft instructions, formats output text
    if (command_str == "Deposit")
        deposit(balance_dub, stod(amount_str.substr(1, amount_str.size())));

    else if (command_str == "Withdraw"){
        bool is_successful = withdraw(balance_dub, stod(amount_str.substr(1, amount_str.size())));

        if(!is_successful){
            overdraft(balance_dub, stod(amount_str.substr(1, amount_str.size())));
            ss << "Overdraft" << "!" << endl;
        }
    }
}

string process_command(const string& input_str, string& prev_date_str,
                        double& balance_dub, const double& apr_dub){
    vector<string> input_vec = split(input_str, ' ');
    string date_str = input_vec.at(0);
    string command_str = input_vec.at(1);
    string amount_str = input_vec.at(2);

    stringstream ss;
    ss << std::fixed;
    ss << std::setprecision(2);
    ss << "On " << date_str << ": Instructed to perform \"" << command_str << " " 
       << amount_str << "\"" << endl;

    interest_output(date_str, prev_date_str, balance_dub, apr_dub, ss);
    activity_output(command_str, amount_str, balance_dub,  apr_dub, ss);

    ss << "Balance: " << balance_dub << endl;
    prev_date_str = date_str;
    return ss.str();
}

string process_commands(const string& input_str, const double& apr_dub){
    vector<string> input_vec = split(input_str);
    string prev_date_str = "";
    string output_str = "";
    double balance_dub = 0;
    
    for (string str : input_vec)
        output_str += process_command(str, prev_date_str, balance_dub, apr_dub);

    return output_str;
}

int main(){
    std::string input = 
    "2016-09-02 Deposit $500\n"
    "2016-09-02 Withdraw $23.54\n"
    "2016-09-04 Withdraw $58\n"
    "2016-11-02 Deposit $200\n"
    "2017-03-02 Withdraw $1000\n"
    "2019-11-02 Deposit $5000\n"
    "2020-11-02 Deposit $500\n";

    std::string result = process_commands(input, 7);
    cout << result;
}
