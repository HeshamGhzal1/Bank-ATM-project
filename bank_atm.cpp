#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
namespace BankATM
{
    enum euser_permission
    {
        pall = -1,
        pshow = 1,
        padd = 2,
        pdelet = 4,
        pupdate = 8,
        pfind = 16,
        cshow = 32,
        cadd = 64,
        cdelete = 128,
        cupdate = 256,
        cfind = 512,
        cdeposit = 1024,
        cwithdraw = 2048
    };
    struct sclient
    {
        string account_num = "";
        string pin_code = "";
        string name = "";
        string phone = "";
        double balance = 0;
    };
    struct suser
    {
        string user_name;
        string user_password;
        int permission = 0;
    };
    bool check_user_permission(suser user, int permission);
    sclient client;
    string separator = "###";
    string target;
    string client_file = "fclient.txt";
    string user_file_name = "fuser.txt";
    bool atm = 0;
    bool fast_withdraw = 0;

    int value = 5;
    short paper_value = 5;

    void show_user_menu(suser user);
    void show_main_menu(suser user);
    void login_bank_system();

    void Login_ATM_machine();

    void clear_screen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    string user_input(string out)
    {
        string input = "";
        cout << out;
        cin >> input;
        return input;
    }

    vector<string> get_string_from_file_to_vector(string file_name)
    {
        vector<string> vs;
        fstream myfile;
        myfile.open(file_name, ios::in);
        string line;
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                vs.push_back(line);
            }
        }
        myfile.close();
        return vs;
    }

    vector<string> spelt_each_word_in_string(string s)
    {
        vector<string> vs;
        size_t pos = s.find(separator);
        string word = "";
        int counter = 0;

        while ((pos = s.find(separator)) != string::npos)
        {
            word = s.substr(0, pos);
            if (word != "")
            {
                vs.push_back(word);
            }
            s = s.substr(pos + separator.length());
        }
        if (s != "")
            vs.push_back(s);
        return vs;
    }

    sclient convert_lin_data_to_record(string client)
    {
        sclient rclient;
        vector<string> vclient = spelt_each_word_in_string(client);
        rclient.account_num = vclient.at(0);
        rclient.pin_code = vclient.at(1);
        rclient.name = vclient.at(2);
        rclient.phone = vclient.at(3);
        rclient.balance = stod(vclient.at(4));

        return rclient;
    }

    void print_client_date_record(sclient client)
    {
        cout << "Client Account Number : " << client.account_num << "\n";
        cout << "Client Pin Code       : " << client.pin_code << "\n";
        cout << "Client Name           : " << client.name << "\n";
        cout << "Client Phone Number   : " << client.phone << "\n";
        cout << "Client Balance        : " << client.balance << "\n";
    }

    bool find_clients_data_by_AccountNumber(string file_name, string target, sclient &client)
    {
        vector<string> vs;
        vs = get_string_from_file_to_vector(file_name);

        for (string cl : vs)
        {
            client = convert_lin_data_to_record(cl);
            if (client.account_num == target)
            {
                return true;
            }
        }
        return false;
    }

    void write_string_from_vector_to_file(vector<string> vs, string file_name)
    {
        fstream myfile;
        myfile.open(file_name, ios::out);
        if (myfile.is_open())
        {
            for (string s : vs)
            {
                if (s != "")
                    myfile << s << "\n";
            }
        }
        myfile.close();
    }

    sclient Read_new_clint_data(sclient &client)
    {
        cout << "Enter account number : ";
        getline(cin >> ws, client.account_num);

        cout << "Enter pin code : ";
        getline(cin >> ws, client.pin_code);

        cout << "Enter client name : ";
        getline(cin, client.name);

        cout << "Enter client phone : ";
        getline(cin, client.phone);

        cout << "Enter client balance : ";
        cin >> client.balance;
        return client;
    }

    sclient Read_new_clint_data(sclient &client, string target)
    {
        client.account_num = target;

        cout << "Enter pin code : ";
        getline(cin >> ws, client.pin_code);

        cout << "Enter client name : ";
        getline(cin, client.name);

        cout << "Enter client phone : ";
        getline(cin, client.phone);

        cout << "Enter client balance : ";
        cin >> client.balance;
        return client;
    }

    string convert_record_data_to_line(sclient client)
    {
        string s;
        s += client.account_num + separator;
        s += client.pin_code + separator;
        s += client.name + separator;
        s += client.phone + separator;
        s += to_string(client.balance);
        return s;
    }

    vector<string> update_clients_data_by_AccountNumber(string file_name, string target, sclient &client)
    {
        vector<string> vs;
        vs = get_string_from_file_to_vector(file_name);

        target = user_input("Enter Account number you wont to update: ");
        cout << "\nclient Account number : [" << target << "]\n";

        if (find_clients_data_by_AccountNumber(file_name, target, client))
        {
            for (string &s : vs)
            {
                client = convert_lin_data_to_record(s);
                if (client.account_num == target)
                {
                    cout << "\n==================================\n";
                    print_client_date_record(client);
                    cout << "==================================\n";
                    cout << "\nAre you sure you wont to update the client [y]or[n] : ";
                    char answer = 'n';
                    cin >> answer;
                    if (tolower(answer) == 'y')
                    {
                        cout << "\nAccount number : [" << target << "]\n";
                        Read_new_clint_data(client, target);
                        s = convert_record_data_to_line(client);
                        write_string_from_vector_to_file(vs, file_name);
                        cout << "\nClient updated successfully\n";
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "Client Not found \n";
        }
        return vs;
    }

    void print_clint_date_record_in_form(sclient client)
    {
        cout << "\n";
        cout << '|' << left << setw(15) << client.account_num;
        cout << '|' << left << setw(10) << client.pin_code;
        cout << '|' << left << setw(25) << client.name;
        cout << '|' << left << setw(15) << client.phone;
        cout << '|' << left << setw(10) << client.balance;
        cout << '|';
        cout << "\n=================================================================================";
    }

    void show_clients_data_in_form(string file_name)
    {
        vector<string> vs;
        sclient client;
        vs = get_string_from_file_to_vector(file_name);
        cout << "\t\t\t\tlist of [" << vs.size() << "] client(s)";
        cout << "\n=================================================================================\n";
        cout << '|' << left << setw(15) << "Account Number";
        cout << '|' << setw(10) << "Pin Code";
        cout << '|' << setw(25) << "Name";
        cout << '|' << setw(15) << "Phone Number";
        cout << '|' << setw(10) << "Balance";
        cout << '|';
        cout << "\n=================================================================================";

        for (int i = 0; i < vs.size(); i++)
        {
            client = convert_lin_data_to_record(vs.at(i));
            print_clint_date_record_in_form(client);
        }
    }

    vector<string> delete_clients_data_by_AccountNumber(string file_name, string target)
    {
        vector<string> vs;
        sclient client;
        vs = get_string_from_file_to_vector(file_name);

        if (find_clients_data_by_AccountNumber(file_name, target, client))
        {
            for (string &cl : vs)
            {
                client = convert_lin_data_to_record(cl);
                if (client.account_num == target)
                {
                    print_client_date_record(client);
                    cout << "\nAre you sure you wont to delete the client [y]or[n] : ";
                    char answer = 'n';
                    cin >> answer;
                    if (tolower(answer) == 'y')
                    {
                        cl.clear();
                        write_string_from_vector_to_file(vs, file_name);
                        cout << "\nClient deleted successfully\n";
                    }
                }
            }
        }
        else
        {
            cout << "Client Not found \n";
        }
        return vs;
    }

    void print_string_to_file(string s, string file_name)
    {
        fstream myfile;
        myfile.open(file_name, ios::out | ios::app);
        if (myfile.is_open())
        {
            myfile << s;
        }
        myfile.close();
    }

    void print_Clint_data_line_to_file(string file_name)
    {
        sclient client;
        char answer = 'n';
        do
        {
            clear_screen();
            cout << "            Adding New Client \n\n";
            Read_new_clint_data(client);
            string s = convert_record_data_to_line(client) + "\n";
            print_string_to_file(s, file_name);
            cout << "\nClient added successfully\n"
                 << "\nDo you wont To add new client [ y/n] : ";
            cin >> answer;
            cout << "\n";
        } while (tolower(answer) == 'y');
    }

    void print_Clint_data_line_to_file(string file_name, string target)
    {
        sclient client;
        char answer = 'y';
        while (tolower(answer) == 'y')
        {
            clear_screen();
            cout << "            Adding New Client \n\n";
            target = user_input("Enter New Account number   : ");
            while (find_clients_data_by_AccountNumber(file_name, target, client))
            {
                char answer = 'y';

                cout << "This account is exist would you lik to enter another account number [y/N] : ";
                cin >> answer;
                if (tolower(answer) == 'y')
                {
                    cout << "\nEnter another account number : ";
                    cin >> target;
                }
                else
                {
                    return;
                }
            }
            cout << "\nAccount number : [" << target << "]\n";
            Read_new_clint_data(client, target);
            string s = convert_record_data_to_line(client) + "\n";
            print_string_to_file(s, file_name);
            cout << "\nClient added successfully\n"
                 << "\nDo you wont To add new client [ y/n] : ";
            cin >> answer;
            cout << "\n";
        };
    }

    void End_screen()
    {
        clear_screen();
        cout << "\n=======================\n";
        cout << "       End screen";
        cout << "\n=======================\n";
    }

    double Balance_deposit(sclient client)
    {
        double deposit;
        cout << "Enter value you will deposit : ";
        cin >> deposit;
        return client.balance + deposit;
    }

    vector<string> deposit_clients_balance_by_AccountNumber(string target, sclient &client)
    {
        vector<string> vs;
        vs = get_string_from_file_to_vector(client_file);

        if (find_clients_data_by_AccountNumber(client_file, target, client))
        {
            for (string &s : vs)
            {
                client = convert_lin_data_to_record(s);
                if (client.account_num == target)
                {
                    print_client_date_record(client);
                    cout << "\nAre you sure you wont to deposit [y]or[n] : ";
                    char answer = 'n';
                    cin >> answer;
                    if (tolower(answer) == 'y')
                    {
                        client.balance = Balance_deposit(client);
                        cout << "\nNew client balance =  " << client.balance << "\n";
                        s = convert_record_data_to_line(client);
                        write_string_from_vector_to_file(vs, client_file);
                        cout << "\nClient balance updated successfully\n";
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "Client Not found \n";
        }
        return vs;
    }

    int Quick_withdraw_menu()
    {
        cout << "				[1] =5       [2]=10\n";
        cout << "				[3] =50      [4]=100\n";
        cout << "				[5] =500     [6]=1000\n";
        cout << "				[7] =2000    [8]=5000\n";
        string choice = user_input("Enter your choice from 1->8 : ");
        while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8")
        {
            cout << "Invalid choice Please Enter your choice from 1->8 : ";
            cin >> choice;
        }
        if (choice == "1")
            return 5;
        else if (choice == "2")
            return 10;
        else if (choice == "3")
            return 50;
        else if (choice == "4")
            return 100;
        else if (choice == "5")
            return 500;
        else if (choice == "6")
            return 1000;
        else if (choice == "7")
            return 2000;
        else if (choice == "8")
            return 5000;
        else
            return 0;
    }
    bool paper_mony_multiplication(int value, short paper_value)
    {
        return (value == 5 || value % paper_value == 0);
    }
    int atm_withdraw(int value, short paper_value)
    {
        double withdraw;
        cout << "Please Enter multiplication of : [" << paper_value << "] : ";
        cin >> withdraw;
        while (!paper_mony_multiplication(withdraw, paper_value))
        {
            cout << "Please Enter multiplication of : [" << paper_value << "] : ";
            cin >> withdraw;
        }
        return withdraw;
    }
    double Check_enough_Balance_to_withdraw(sclient client)
    {
        double withdraw;
        do
        {
            if (atm)
            {
                if (fast_withdraw)
                {
                    withdraw = Quick_withdraw_menu();
                }
                else
                {
                    withdraw = atm_withdraw(withdraw, paper_value);
                }
            }
            else
            {
                cout << "Enter value to withdraw : ";
                cin >> withdraw;
            }

            if (withdraw > client.balance)
            {
                cout << "No enough balance ";
                cout << "Enter less value \n";
            }
        } while (withdraw > client.balance);

        return client.balance - withdraw;
    }
    vector<string> Balance_to_withdraw(string client_file, string target, sclient &client)
    {
        vector<string> vs;
        vs = get_string_from_file_to_vector(client_file);

        if (find_clients_data_by_AccountNumber(client_file, target, client))
        {
            for (string &s : vs)
            {
                client = convert_lin_data_to_record(s);
                if (client.account_num == target)
                {
                    print_client_date_record(client);
                    cout << "\nAre you sure you wont to withdraw [y]or[n] : ";
                    char answer = 'n';
                    cin >> answer;
                    if (tolower(answer) == 'y')
                    {
                        client.balance = Check_enough_Balance_to_withdraw(client);
                        cout << "\nNew client balance =  " << client.balance << "\n";
                        s = convert_record_data_to_line(client);
                        write_string_from_vector_to_file(vs, client_file);
                        cout << "\nClient balance updated successfully\n";
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "Client Not found \n";
        }
        return vs;
    }

    double sum_all_clients_balances(string client_file)
    {
        vector<string> vs;
        sclient client;
        double total_balance = 0;
        vs = get_string_from_file_to_vector(client_file);

        for (string s : vs)
        {
            client = convert_lin_data_to_record(s);
            total_balance += client.balance;
        }
        return total_balance;
    }

    void Transaction(string client_file, string target, sclient &client, string selection)
    {
        double balance_update = 0;
        if (selection == "1")
        {
            clear_screen();
            cout << "\n===================================\n";
            cout << "        client deposit screen";
            cout << "\n===================================\n";
            target = user_input("Enter Account number : ");
            deposit_clients_balance_by_AccountNumber(target, client);
            cout << endl;
        }
        else if (selection == "2")
        {
            clear_screen();
            cout << "\n===================================\n";
            cout << "       client withdraw screen";
            cout << "\n===================================\n";

            target = user_input("Enter Account number : ");
            Balance_to_withdraw(client_file, target, client);
            cout << endl;
        }
        else if (selection == "3")
        {
            clear_screen();
            cout << "\n===================================\n";
            cout << "    client Total balance screen";
            cout << "\n===================================\n";
            show_clients_data_in_form(client_file);

            cout << "\nTotal balance of all clients is : ";
            cout << sum_all_clients_balances(client_file) << "\n";
            cout << endl;
        }
    }
    string Transaction_menu()
    {
        string selection;
        clear_screen();
        cout << "\n===================================\n";
        cout << "        Transaction screen";
        cout << "\n===================================\n";

        cout << "[1] Deposit\n";
        cout << "[2] Withdraw\n";
        cout << "[3] Total balance\n";
        cout << "[4] Exit\n";

        cout << "\nWhat do you wont to do select [1 -> 4] : ";
        cin >> selection;
        while (selection != "1" && selection != "2" && selection != "3" && selection != "4")
        {
            cout << "\nInvalid choice Renter your choice from[1 -> 4] : ";
            cin >> selection;
        }

        return selection;
    }
    void show_transaction_menu()
    {
        string selection = Transaction_menu();
        Transaction(client_file, target, client, selection);
        if (selection == "4")
            return;
        cout << "Press \"ENTER\" to return to transaction menu";

        cin.ignore();
        cin.get();
        show_transaction_menu();
    }

    void project_bank(int select, suser user)
    {
        sclient client;
        string target;

        if (select == 1)
        {
            clear_screen();
            if (check_user_permission(user, cshow))
            {
                cout << "\n                        =================================\n";
                cout << "                             clients data screen         ";
                cout << "\n                        =================================\n";
                show_clients_data_in_form(client_file);
            }
            else
            {
                cout << "You dont have permission to show client\n";
            }
        }
        else if (select == 2)
        {
            clear_screen();
            if (check_user_permission(user, cadd))
            {
                cout << "\n===================================\n";
                cout << "        client add screen";
                cout << "\n===================================\n";

                print_Clint_data_line_to_file(client_file, target);
            }
            else
            {
                cout << "You dont have permission to add client\n";
            }
        }
        else if (select == 3)
        {
            clear_screen();
            if (check_user_permission(user, cdelete))
            {
                cout << "\n===================================\n";
                cout << "        client delete screen";
                cout << "\n===================================\n";

                target = user_input("Enter Account number you wont to delete : ");
                delete_clients_data_by_AccountNumber(client_file, target);
            }
            else
            {
                cout << "You dont have permission to delete client\n";
            }
        }
        else if (select == 4)
        {
            clear_screen();
            if (check_user_permission(user, cupdate))
            {
                cout << "\n===================================\n";
                cout << "        client update screen";
                cout << "\n===================================\n";

                update_clients_data_by_AccountNumber(client_file, target, client);
            }
            else
            {
                cout << "You dont have permission to update client\n";
            }
        }
        else if (select == 5)
        {
            clear_screen();
            if (check_user_permission(user, cfind))
            {
                cout << "\n===================================\n";
                cout << "        client find screen";
                cout << "\n===================================\n";

                target = user_input("Enter Account number you wont to find : ");
                if (find_clients_data_by_AccountNumber(client_file, target, client))
                {
                    cout << "\n=================================================================================\n";
                    cout << '|' << left << setw(15) << "Account Number";
                    cout << '|' << setw(10) << "Pin Code";
                    cout << '|' << setw(25) << "Name";
                    cout << '|' << setw(15) << "Phone Number";
                    cout << '|' << setw(10) << "Balance";
                    cout << '|';
                    cout << "\n=================================================================================";

                    print_clint_date_record_in_form(client);
                }
                else
                {
                    cout << "Clint Not found";
                }
            }
            else
            {
                cout << "You dont have permission to find client\n";
            }
        }
        else if (select == 6)
        {
            clear_screen();
            if (check_user_permission(user, cdeposit) || check_user_permission(user, cwithdraw))
            {
                show_transaction_menu();
            }
            else
            {
                cout << "You dont have permission to do transaction\n";
            }
        }
        else if (select == 7)
        {
            if (check_user_permission(user, padd) ||
                check_user_permission(user, pdelet) ||
                check_user_permission(user, pupdate) ||
                check_user_permission(user, pshow) ||
                check_user_permission(user, pfind) ||
                check_user_permission(user, 64))
            {
                show_user_menu(user);
            }
            else
            {
                cout << "You dont have permission to manage user\n";
            }
        }
        else
        {
            End_screen();
        }
    }
    string BANK_main_menu()
    {
        clear_screen();
        string selection;
        cout << "===================================\n";
        cout << "          main menu screen        ";
        cout << "\n===================================\n";
        cout << "[1] show client list\n";
        cout << "[2] Add new client\n";
        cout << "[3] Delete client\n";
        cout << "[4] Update client info\n";
        cout << "[5] Find client\n";
        cout << "[6] Transaction\n";
        cout << "[7] Manage user\n";
        cout << "[8] Exit\n";
        cout << "\nEnter your choice from [1 -> 8] : ";
        cin >> selection;

        while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6" && selection != "7" && selection != "8")
        {
            cout << "\nInvalid choice Renter your choice from[1->8] : ";
            cin >> selection;
        }
        return selection;
    }

    char ask_user_permission(suser user, string question)
    {
        char answer = 'n';
        cout << question << user.user_name << " ?[y]or[no] :";
        cin >> answer;
        answer = tolower(answer);
        return answer;
    }
    int add_user_permission(suser user)
    {
        int permission = 0;
        char answer = ask_user_permission(user, "Do you like to have all permission to ");

        if (answer == 'y')
        {
            cout << user.user_name << " have all permission\n";
            permission = pall;
            return permission;
        }
        else
        {
            answer = ask_user_permission(user, "Do you like to have [Show client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Show client(s)] permission\n";
                permission += 32;
            }
            answer = ask_user_permission(user, "Do you like to have [Add client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Add client(s)] permission\n";
                permission += 64;
            }
            answer = ask_user_permission(user, "Do you like to have [Delete client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Delete client(s)] permission\n";
                permission += 128;
            }
            answer = ask_user_permission(user, "Do you like to have [Update client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Update client(s)] permission\n";
                permission += 256;
            }
            answer = ask_user_permission(user, "Do you like to have [Find client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Find client(s)] permission\n";
                permission += 512;
            }
            answer = ask_user_permission(user, "Do you like to have [Deposit client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Deposit client(s)] permission\n";
                permission += 1024;
            }
            answer = ask_user_permission(user, "Do you like to have [Withdraw client(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Withdraw client(s)] permission\n";
                permission += 2048;
            }

            answer = ask_user_permission(user, "Do you like to have [Show user(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Show user(s)] permission\n";
                permission += 1;
            }

            answer = ask_user_permission(user, "Do you like to have [Add user(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Add user(s)] permission\n";
                permission += 2;
            }
            answer = ask_user_permission(user, "Do you like to have [Delete user(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Delete user(s)] permission\n";
                permission += 4;
            }

            answer = ask_user_permission(user, "Do you like to have [Update user(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Update user(s)] permission\n";
                permission += 8;
            }

            answer = ask_user_permission(user, "Do you like to have [Find user(s)] permission to ");
            if (answer == 'y')
            {
                cout << user.user_name << " have [Find user(s)] permission\n";
                permission += 16;
            }
        }
        return permission;
    }
    bool check_user_permission(suser user, int permission)
    {
        return (user.permission & permission) ? true : false;
    }
    bool password_protection(suser &user)
    {
        return (user.permission & 64) ? true : false;
    }
    string hide_password(suser &user, bool show_password)
    {
        return (show_password) ? user.user_password : "**********";
    }

    void show_main_menu(suser user)
    {
        int select = stoi(BANK_main_menu());
        project_bank(select, user);
        if (select == 8)
        {
            return;
        }
        else
        {
            cout << "\nPress \"ENTER\" to return to main menu\n";
            cin.ignore();
            cin.get();
            show_main_menu(user);
        }
    }
    string convert_record_data_to_line(suser user)
    {
        string s;
        s += user.user_name + separator;
        s += user.user_password + separator;
        s += to_string(user.permission);

        return s;
    }
    void print_client_date_record(suser user, bool show_password)
    {
        user.user_password = hide_password(user, show_password);
        cout << "User Name        : " << user.user_name << "\n";
        cout << "User password    : " << user.user_password << "\n";
        cout << "User Permission  : " << user.permission << "\n";
    }
    suser convert_user_lin_data_to_records(string user)
    {
        suser ruser;
        vector<string> vuser = spelt_each_word_in_string(user);
        ruser.user_name = vuser.at(0);
        ruser.user_password = vuser.at(1);
        ruser.permission = stoi(vuser.at(2));

        return ruser;
    }
    bool find_user_data_by_User_name(string user_file_name, string target, suser &user)
    {
        vector<string> us;
        us = get_string_from_file_to_vector(user_file_name);

        for (string usr : us)
        {
            user = convert_user_lin_data_to_records(usr);
            if (user.user_name == target)
            {
                return true;
            }
        }
        return false;
    }
    bool admin_removing_protection(suser &user, string user_file_name, string target)
    {
        return (target == "admin") ? true : false;
    }
    void print_user_date_record_in_form(suser user, bool show_password)
    {
        user.user_password = hide_password(user, show_password);

        cout << "\n";
        cout << '|' << left << setw(15) << user.user_name;
        cout << '|' << left << setw(10) << user.user_password;
        cout << '|' << left << setw(10) << user.permission;
        cout << '|';

        cout << "\n=================================================================================";
    }
    void show_user_data_in_form(string user_file_name, bool show_password)
    {
        vector<string> vs;
        suser user;

        vs = get_string_from_file_to_vector(user_file_name);
        cout << "\t\t\t\tlist of [" << vs.size() << "] User(s)";
        cout << "\n=================================================================================\n";
        cout << '|' << left << setw(15) << "User Name";
        cout << '|' << setw(10) << "Password";
        cout << '|' << setw(10) << "Permission";
        cout << '|';
        cout << "\n=================================================================================";

        for (int i = 0; i < vs.size(); i++)
        {
            user = convert_user_lin_data_to_records(vs.at(i));
            print_user_date_record_in_form(user, show_password);
        }
    }
    suser Read_new_user_data(suser &user)
    {

        cout << "Enter User Name : ";
        getline(cin >> ws, user.user_name);

        cout << "Enter User password : ";
        getline(cin >> ws, user.user_password);

        user.permission = add_user_permission(user);

        return user;
    }
    suser Read_new_user_data(suser &user, string target)
    {

        user.user_name = target;
        cout << "user name           : [" << target << "]\n";
        cout << "Enter User password : ";
        getline(cin >> ws, user.user_password);

        user.permission = add_user_permission(user);

        return user;
    }

    void print_user_data_line_to_file(string user_file_name, string target)
    {
        suser user;
        char answer = 'y';
        while (tolower(answer) == 'y')
        {
            clear_screen();
            cout << "            Adding New User \n\n";
            target = user_input("Enter New user Name   : ");

            while (find_user_data_by_User_name(user_file_name, target, user))
            {
                char answer = 'y';

                cout << "this user is exist would you lik to enter another user account [y/n] : ";
                cin >> answer;
                if (tolower(answer) == 'y')
                {
                    cout << "\nenter another user name : ";
                    cin >> target;
                }
                else
                {
                    return;
                }
            }
            Read_new_user_data(user, target);
            string s = convert_record_data_to_line(user) + "\n";
            print_string_to_file(s, user_file_name);
            cout << "\nUser added successfully\n";
            cout << "\nDo you wont To add new User [ y/n] : ";
            cin >> answer;
        };
    }
    vector<string> delete_user_data_by_Name(string user_file_name, string target, bool show_password)
    {
        vector<string> vs;
        suser user;
        vs = get_string_from_file_to_vector(user_file_name);

        if (find_user_data_by_User_name(user_file_name, target, user))
        {
            for (string &cl : vs)
            {
                user = convert_user_lin_data_to_records(cl);

                if (user.user_name == target)
                {
                    print_client_date_record(user, show_password);
                    cout << "\nAre you sure you wont to delete the User [y]or[n] : ";
                    char answer = 'n';
                    cin >> answer;
                    if (tolower(answer) == 'y')
                    {
                        cl.clear();
                        write_string_from_vector_to_file(vs, user_file_name);
                        cout << "\nUser deleted successfully\n";
                    }
                }
            }
        }
        else
        {
            cout << "User Not found \n";
        }
        return vs;
    }
    vector<string> update_user_data_by_Name(string user_file_name, string target, suser &user, bool show_password)
    {
        vector<string> vs;
        vs = get_string_from_file_to_vector(user_file_name);

        if (find_user_data_by_User_name(user_file_name, target, user))
        {
            for (string &s : vs)
            {
                user = convert_user_lin_data_to_records(s);
                if (user.user_name == target)
                {
                    cout << "\n==================================\n";
                    print_client_date_record(user, show_password);
                    cout << "==================================\n";

                    cout << "\nAre you sure you wont to update the User [" << target << "] [y] or [n] : ";
                    char answer = 'n';
                    cin >> answer;
                    if (tolower(answer) == 'y')
                    {
                        Read_new_user_data(user, target);
                        s = convert_record_data_to_line(user);
                        write_string_from_vector_to_file(vs, user_file_name);
                        cout << "\nUser updated successfully\n";
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "User Not found \n";
        }
        return vs;
    }
    void Bank_user(int select, suser user, bool show_password)
    {
        string separator = "###";
        string target;
        string user_file_name = "fuser.txt";

        if (select == 1)
        {
            clear_screen();
            if (check_user_permission(user, pshow))
            {

                cout << "\n                        =================================\n";
                cout << "                             users data screen         ";
                cout << "\n                        =================================\n";
                show_user_data_in_form(user_file_name, show_password);
            }
            else
            {
                cout << "You dont have permission to show user\n";
                cout << "Press any kay to return to user menu\n";

                cin.ignore();
                cin.get();
                show_user_menu(user);
            }
        }
        else if (select == 2)
        {
            clear_screen();
            if (check_user_permission(user, padd))
            {
                cout << "\n===================================\n";
                cout << "       user add screen";
                cout << "\n===================================\n";

                print_user_data_line_to_file(user_file_name, target);
            }
            else
            {
                cout << "You dont have permission to add user\n";
                cout << "Press any kay to return to user menu\n";

                cin.ignore();
                cin.get();
                show_user_menu(user);
            }
        }
        else if (select == 3)
        {

            clear_screen();
            if (check_user_permission(user, pdelet))
            {
                cout << "\n===================================\n";
                cout << "        user delete screen";
                cout << "\n===================================\n";

                target = user_input("Enter User Name wont to delete : ");
                if (admin_removing_protection(user, user_file_name, target))
                {
                    cout << "You dont have permission to delete this user\n";
                    cout << "Press any kay to return to user menu\n";

                    cin.ignore();
                    cin.get();
                    show_user_menu(user);
                }
                else
                {
                    delete_user_data_by_Name(user_file_name, target, show_password);
                }
            }
            else
            {
                cout << "You dont have permission to delete user\n";
                cout << "Press any kay to return to user menu\n";

                cin.ignore();
                cin.get();
                show_user_menu(user);
            }
        }
        else if (select == 4)
        {
            clear_screen();
            if (check_user_permission(user, pupdate))
            {
                cout << "\n===================================\n";
                cout << "        user update screen";
                cout << "\n===================================\n";
                target = user_input("Enter User Name you wont to update: ");
                update_user_data_by_Name(user_file_name, target, user, show_password);
            }
            else
            {
                cout << "You dont have permission to update user\n";
                cout << "Press any kay to return to user menu\n";

                cin.ignore();
                cin.get();
                show_user_menu(user);
            }
        }
        else if (select == 5)
        {
            clear_screen();
            if (check_user_permission(user, pfind))
            {
                cout << "\n===================================\n";
                cout << "        user find screen";
                cout << "\n===================================\n";

                target = user_input("Enter User Name you wont to find : ");
                if (find_user_data_by_User_name(user_file_name, target, user))
                {
                    cout << "\n=================================================================================\n";
                    print_user_date_record_in_form(user, show_password);
                }
                else
                {
                    cout << "Not found";
                }
            }
            else
            {
                cout << "You dont have permission to find user\n";
                cout << "Press any kay to return to user menu\n";

                cin.ignore();
                cin.get();
                show_user_menu(user);
            }
        }
        else
        {
            End_screen();
        }
    }
    string user_menu()
    {
        clear_screen();
        string selection;
        cout << "===================================\n";
        cout << "         Manage user menu screen        ";
        cout << "\n===================================\n";
        cout << "[1] show user list\n";
        cout << "[2] Add New user\n";
        cout << "[3] Delete user\n";
        cout << "[4] Update user\n";
        cout << "[5] Find user\n";
        cout << "[6] Main menu\n";
        cout << "\nEnter your choice from [1 -> 6] : ";
        cin >> selection;

        while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6")
        {
            cout << "\nInvalid choice Renter your choice from[1->6] : ";
            cin >> selection;
        }
        return selection;
    }
    suser user_login()
    {
        clear_screen();
        suser user;
        string user_file_name = "fuser.txt";
        string separator = "###";
        string target;
        target = user_input("Enter User Name : ");
        if (find_user_data_by_User_name(user_file_name, target, user))
        {
            cout << "Enter User password : ";
            string password;
            cin >> password;
            if (user.user_password == password)
            {
                return user;
            }
            else
            {
                cout << "Invalid password\n";
                cout << "press any kay to Relogin";

                cin.ignore();
                cin.get();
                return user_login();
            }
        }
        else
        {
            cout << "User Not found \n";
            cout << "press any kay to Relogin";

            cin.ignore();
            cin.get();
            return user_login();
        }
    }
    void show_user_menu(suser user)
    {
        bool show_password = password_protection(user);
        int select = stoi(user_menu());
        Bank_user(select, user, show_password);
    }
    void login_bank_system()
    {
        suser user = user_login();
        show_main_menu(user);
    }

    string ATM_main_menu(sclient client)
    {
        clear_screen();
        cout << "\n--------" << client.name << "----------\n";

        cout << "\n===============================\n";
        cout << "      ATM system menu ";
        cout << "\n===============================\n";
        cout << "[1] Quick withdraw\n";
        cout << "[2] Normal withdraw\n";
        cout << "[3] Deposit\n";
        cout << "[4] Chick balance\n";
        cout << "[5] Exit\n";
        string choice = user_input("Enter your choice from 1->5 : ");
        while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
        {
            cout << "Invalid choice Please Enter your choice from 1->5 : ";
            cin >> choice;
        }
        return choice;
    }
    void quick_withdraw(sclient client)
    {
        string target = client.account_num;
        fast_withdraw = 1;
        Balance_to_withdraw("fclient.txt", target, client);
        fast_withdraw = 0;
    }
    void normal_withdraw(sclient client)
    {
        string target = client.account_num;
        Balance_to_withdraw("fclient.txt", target, client);
    }
    void deposit(sclient client)
    {
        string target = client.account_num;
        deposit_clients_balance_by_AccountNumber(target, client);
    }
    void check_balance(sclient client)
    {
        print_client_date_record(client);
    }
    void project_ATM(int select, sclient client)
    {

        string target = client.account_num;

        if (select == 1)
        {
            clear_screen();
            cout << "\n                       --------" << client.name << "----------\n";

            cout << "\n                        =================================\n";
            cout << "                                 Quick withdraw       ";
            cout << "\n                        =================================\n";
            quick_withdraw(client);
        }
        else if (select == 2)
        {
            clear_screen();
            cout << "\n                       --------" << client.name << "----------\n";

            cout << "\n                        ===================================\n";
            cout << "                                   Normal withdraw";
            cout << "\n                        ===================================\n";
            normal_withdraw(client);
        }
        else if (select == 3)
        {
            clear_screen();
            cout << "\n                       --------" << client.name << "----------\n";

            cout << "\n                       ===================================\n";
            cout << "                                   Deposit screen";
            cout << "\n                       ===================================\n";

            deposit(client);
        }
        else if (select == 4)
        {
            clear_screen();
            cout << "\n                       --------" << client.name << "----------\n";

            cout << "\n                        ===================================\n";
            cout << "                                   Check Client Balance";
            cout << "\n                        ===================================\n";

            check_balance(client);
        }

        else
        {
            return;
        }
    }

    sclient ATM_client_login()
    {
        clear_screen();
        sclient client;
        string target = client.account_num;
        target = user_input("Enter User Account number : ");
        if (find_clients_data_by_AccountNumber("fclient.txt", target, client))
        {
            cout << "Enter Client pin_code : ";
            string pin_code;
            cin >> pin_code;
            if (client.pin_code == pin_code)
            {
                return client;
            }
            else
            {
                cout << "Invalid Pin_code\n";
                cout << "Press \"ENTER\" to Relogin\n";

                cin.ignore();
                cin.get();
                return ATM_client_login();
            }
        }
        else
        {
            cout << "User Not found \n";
            cout << "Press \"ENTER\" to Relogin\n";

            cin.ignore();
            cin.get();
            return ATM_client_login();
        }
    }

    void show_ATM_menu(sclient client)
    {
        int select = stoi(ATM_main_menu(client));
        project_ATM(select, client);
        if (select == 5)
        {
            return;
        }
        else
        {
            cout << "\nPress \"ENTER\" to return to main menu\n";
            cin.ignore();
            cin.get();
            show_ATM_menu(client);
        }
    }
    void Login_ATM_machine()
    {
        sclient client = ATM_client_login();

        atm = 1;
        show_ATM_menu(client);
        atm = 0;
    }

    void Select_bank_OR_ATM()
    {
        string selection;
        do
        {
            cout << "Select [1] to BANK SYSTEM .\n";
            cout << "Select [2] to ATM SYSTEM .\n";
            cout << "Enter your selection : ";
            cin >> selection;
        } while (selection != "1" && selection != "2");
        if (selection == "1")
        {
            cout << "\n-----------------------------\n";
            cout << "    WELLCOM TO BANK SYSTEM";
            cout << "\n-----------------------------\n";

            cout << "Press \"ENTER\" to continue\n";
            cin.ignore();
            cin.get();

            login_bank_system();
        }
        else if (selection == "2")
        {
            cout << "\n-----------------------------\n";
            cout << "    WELLCOM TO ATM SYSTEM";
            cout << "\n-----------------------------\n";

            cout << "Press \"ENTER\" to continue\n";
            cin.ignore();
            cin.get();
            Login_ATM_machine();
        }
    }
}
