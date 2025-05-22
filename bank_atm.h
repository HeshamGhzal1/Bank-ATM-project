#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
namespace BankATM {

enum euser_permission {
    pall = -1, pshow = 1, padd = 2, pdelet = 4, pupdate = 8, pfind = 16,
    cshow = 32, cadd = 64, cdelete = 128, cupdate = 256, cfind = 512,
    cdeposit = 1024, cwithdraw = 2048
};

struct sclient {
    std::string account_num = "";
    std::string pin_code = "";
    std::string name = "";
    std::string phone = "";
    double balance = 0;
};

struct suser {
    std::string user_name;
    std::string user_password;
    int permission = 0;
};

// Global variable declarations
extern sclient client;
extern std::string separator;
extern std::string target;
extern std::string client_file;
extern std::string user_file_name;
extern bool atm;
extern bool fast_withdraw;
extern int value;
extern short paper_value;

// Function declarations
bool check_user_permission(suser user, int permission);
void show_user_menu(suser user);
void show_main_menu(suser user);
void login_bank_system();
void Login_ATM_machine();
void clear_screen();
std::string user_input(std::string out);
std::vector<std::string> get_string_from_file_to_vector(std::string file_name);
std::vector<std::string> spelt_each_word_in_string(std::string s);
sclient convert_lin_data_to_record(std::string client);
void print_client_date_record(sclient client);
bool find_clients_data_by_AccountNumber(std::string file_name, std::string target, sclient &client);
void write_string_from_vector_to_file(std::vector<std::string> vs, std::string file_name);
sclient Read_new_clint_data(sclient &client);
sclient Read_new_clint_data(sclient &client, std::string target);
std::string convert_record_data_to_line(sclient client);
std::vector<std::string> update_clients_data_by_AccountNumber(std::string file_name, std::string target, sclient &client);
void print_clint_date_record_in_form(sclient client);
void show_clients_data_in_form(std::string file_name);
std::vector<std::string> delete_clients_data_by_AccountNumber(std::string file_name, std::string target);
void print_string_to_file(std::string s, std::string file_name);
void print_Clint_data_line_to_file(std::string file_name);
void print_Clint_data_line_to_file(std::string file_name, std::string target);
void End_screen();
double Balance_deposit(sclient client);
std::vector<std::string> deposit_clients_balance_by_AccountNumber(std::string target, sclient &client);
int Quick_withdraw_menu();
bool paper_mony_multiplication(int value, short paper_value);
int atm_withdraw(int value, short paper_value);
double Check_enough_Balance_to_withdraw(sclient client);
std::vector<std::string> Balance_to_withdraw(std::string client_file, std::string target, sclient &client);
double sum_all_clients_balances(std::string client_file);
void Transaction(std::string client_file, std::string target, sclient &client, std::string selection);
std::string Transaction_menu();
void show_transaction_menu();
void project_bank(int select, suser user);
std::string BANK_main_menu();
char ask_user_permission(suser user, std::string question);
int add_user_permission(suser user);
bool password_protection(suser &user);
std::string hide_password(suser &user, bool show_password);
std::string convert_record_data_to_line(suser user);
void print_client_date_record(suser user, bool show_password);
suser convert_user_lin_data_to_records(std::string user);
bool find_user_data_by_User_name(std::string user_file_name, std::string target, suser &user);
bool admin_removing_protection(suser &user, std::string user_file_name, std::string target);
void print_user_date_record_in_form(suser user, bool show_password);
void show_user_data_in_form(std::string user_file_name, bool show_password);
suser Read_new_user_data(suser &user);
suser Read_new_user_data(suser &user, std::string target);
void print_user_data_line_to_file(std::string user_file_name, std::string target);
std::vector<std::string> delete_user_data_by_Name(std::string user_file_name, std::string target, bool show_password);
std::vector<std::string> update_user_data_by_Name(std::string user_file_name, std::string target, suser &user, bool show_password);
void Bank_user(int select, suser user, bool show_password);
std::string user_menu();
suser user_login();
std::string ATM_main_menu(sclient client);
void quick_withdraw(sclient client);
void normal_withdraw(sclient client);
void deposit(sclient client);
void check_balance(sclient client);
void project_ATM(int select,sclient client);
sclient ATM_client_login();
void Select_bank_OR_ATM();


} // namespace BankATM