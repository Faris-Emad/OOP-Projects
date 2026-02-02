#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"
#include  "clsDate.h"
using namespace std;




class clsUser : public clsPerson  {
    private:
        inline  static const string SEPARATOR = "#//#";
        enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
        enMode _Mode;
        string _UserName;       // Username
        string _Password;       // Password
        int _Permissions = 0; // User permissions (using UserAccess)
        bool _MarkForDelete = false;  // Flag for deletion

        static clsUser _ConvertLineToUserObject(string line) {
            vector<string> vUsersData = clsString::SplitString(line, SEPARATOR);
            return clsUser(enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2],
                vUsersData[3], vUsersData[4], vUsersData[5], stoi(vUsersData[6]));
        }

        static string _ConverUserObjectToLine(clsUser User) {
            string DataLine = "";
            DataLine += User.FirstName() + SEPARATOR;
            DataLine += User. LastName() + SEPARATOR;
            DataLine += User.Email() + SEPARATOR;
            DataLine += User.Phone() + SEPARATOR;
            DataLine += User._UserName + SEPARATOR;
            DataLine += User._Password + SEPARATOR;
            DataLine += to_string(User._Permissions);
            return DataLine;
        }
        static vector<clsUser>  _LoadUsersDataFromFile() {
            vector<clsUser> _vUsers;
            fstream MyFile;
            MyFile.open("Users.txt", ios::in);
            if(MyFile.is_open()) {
                string Line;
                while (getline(MyFile, Line)) {
                    clsUser User = _ConvertLineToUserObject(Line);
                    _vUsers.push_back(User);
                }
                MyFile.close();

            }
            return _vUsers;
        }



        static void _SaveUsersDataToFile(vector<clsUser> _vUsers) {
            fstream MyFile;
            MyFile.open("LoginRegister.txt", ios::out); // Open file for writing (overwrites existing)
            string DataLine;
            if(MyFile.is_open()) {
                for(clsUser& U : _vUsers) {
                    if(U._MarkForDelete == false) {
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                    }

                }
                MyFile.close();
            }
        }
        void _Update() {
            vector<clsUser> _vUsers;
            _vUsers = _LoadUsersDataFromFile();
            for(clsUser& U : _vUsers) {
                if(U._UserName == _UserName){
                    U = *this;
                    break;
                }
            }
            _SaveUsersDataToFile(_vUsers);
        }
        void _AddNew() {
            _AddDateLineToFile(_ConverUserObjectToLine(*this));
        }

        void _AddDateLineToFile(string stDateLine) {
            fstream MyFile;
            MyFile.open("Users.txt", ios::out | ios::app); 
            if(MyFile.is_open()) {
                MyFile << stDateLine << endl;
                MyFile.close();
            }
        }
        static clsUser _GetEmptyUserObject() {
            return clsUser(enMode::EmptyMode, "", "", "", "", "","", 0);
        }
        string _PrepareLogInRecord( ) {
                string LoginRecord = "";
                LoginRecord += clsDate::GetSystemDateTimeString() + SEPARATOR;
                LoginRecord += _UserName + SEPARATOR;
                LoginRecord += _Password + SEPARATOR;
                LoginRecord += to_string(_Permissions);
                return LoginRecord;
        }

    public:
        clsUser(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string UserName, string Password,
            int Permissions) : clsPerson(FirstName, LastName, Email, Phone) {
            _Mode = Mode;
            _UserName = UserName;
            _Password = Password;
            _Permissions = Permissions;
        }
        bool IsEmpty() {
            return (_Mode == enMode::EmptyMode);
        }
        bool MarkedForDeleted() {
            return _MarkForDelete;
        }
        string GetUserName() {
            return _UserName;
        }
        void SetUserName(string UserName) {
            _UserName = UserName;
        }
        void SetPassword(string Password) {
            _Password = Password;
        }
        string GetPassword() {
            return _Password;
        }
        void SetPermissions(int Permissions) {
            _Permissions = Permissions;
        }
        int GetPermissions() {
            return _Permissions;
        }
        static clsUser Find(string UserName) {
            vector <clsUser> vUsers;
            fstream MyFile;
            MyFile.open("Users.txt", ios::in);
            if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLineToUserObject(Line);
                if(User._UserName == UserName) {
                MyFile.close();
                return User;
                }
                vUsers.push_back(User);
            }
            MyFile.close();

            }
            return _GetEmptyUserObject();
        }
        static clsUser Find(string UserName, string Password) {
            vector <clsUser> vUsers;
            fstream MyFile;
            MyFile.open("Users.txt", ios::in);
            if(MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLineToUserObject(Line);
                if(User._UserName == UserName && User._Password == Password) {
                MyFile.close();
                return User;
                }
                vUsers.push_back(User);
            }
            MyFile.close();

            }
            return _GetEmptyUserObject();
        }
        static bool IsUserExist(string UserName) {
            clsUser User = clsUser::Find(UserName);
            return (!User.IsEmpty());
        }
        static bool IsUserExist(string UserName, string Password) {
            clsUser User = clsUser::Find(UserName, Password);
            return (!User.IsEmpty());
        }
        enum enSaveResults {svFailedEmptyObject =0, svSucceeded = 1, svFailedUserNameExists = 2};
        enSaveResults Save() {
            switch (_Mode) {
                case enMode::EmptyMode: {
                    return enSaveResults::svFailedEmptyObject;
                    break;
                }
                case enMode::UpdateMode: {
                    _Update();
                    return enSaveResults::svSucceeded;
                    break;
                }
                case enMode::AddNewMode: {
                    if(clsUser::IsUserExist(_UserName)) {
                        return enSaveResults::svFailedUserNameExists;
                    }
                    else {
                        _AddNew();
                        _Mode = enMode::UpdateMode;
                        return enSaveResults::svSucceeded;
                    }
                    break;
                }

                default:   
                    return enSaveResults::svFailedEmptyObject;

            }
        }
        static clsUser GetAddNewUserObject(string UserName) {
            return clsUser(enMode::AddNewMode, "", "", "","", UserName, "",0);
        }
        bool Delete() {
            vector <clsUser> _vUsers = _LoadUsersDataFromFile();
            for(clsUser& U : _vUsers) {
                if (U._UserName == _UserName)
                {
                    U._MarkForDelete = true;
                    break;
                }  
            }
            _SaveUsersDataToFile(_vUsers);
            *this = _GetEmptyUserObject();
            return true;
        }
        
        static vector <clsUser> GetUsersList() {
            return _LoadUsersDataFromFile();
        }
        enum UserAccess {
            FullAccess = -1,
            ShowClientList = 1,    // View client list
            AddNewClient = 2,      // Add new client
            DeleteClient = 4,      // Delete client
            UpdateClient = 8,      // Update client information
            FindClient = 16,       // Find client
            Transactions = 32,     // Perform financial transactions
            ManageUsers = 64       // Manage users
        };
        bool CheckAccessPermission(UserAccess Permissions) {
            if(this->_Permissions == UserAccess::FullAccess)
                return true;
            if((Permissions & this->_Permissions) == Permissions)
                return true;
            else 
                return false;
        }

        void RegisterLogin() {
            string stDateLine = _PrepareLogInRecord();
            fstream MyFile;
            MyFile.open("LoginRegister.txt", ios::out | ios::app);
            if(MyFile.is_open()) {
                MyFile << stDateLine << endl;
                MyFile.close();
            }
        }
        struct UserLoginData {
            string DateTime;
            string UserName;
            string Password;
            string Permissions;
        };

        static vector <UserLoginData> GetUsersLoginList() {
            vector <UserLoginData> vUsersLoginData =  _LoadUsersLoginDataFromFile();
            for(UserLoginData& U : vUsersLoginData) {
                UserLoginData ULoginData;
                ULoginData.DateTime = clsDate::GetSystemDateTimeString();
                ULoginData.UserName = U.UserName;
                ULoginData.Password = U.Password;
                ULoginData.Permissions = U.Permissions;
                vUsersLoginData.push_back(ULoginData);
            }
            return vUsersLoginData;
        }

        static UserLoginData _ConvertLineToUserSturct(string line) {
            vector<string> vUsersData = clsString::SplitString(line, SEPARATOR);
            UserLoginData loginData;
            loginData.DateTime = clsDate::GetSystemDateTimeString();
            loginData.UserName = vUsersData[4];
            loginData.Password = vUsersData[5];
            loginData.Permissions = vUsersData[6];
            return loginData;
        }

        static vector<UserLoginData> _LoadUsersLoginDataFromFile() {
            vector<UserLoginData> _vUsers;
            fstream MyFile;
            MyFile.open("LoginRegister.txt", ios::in);
            if(MyFile.is_open()) {
                string Line;
                while (getline(MyFile, Line)) {
                    UserLoginData User = _ConvertLineToUserSturct(Line);
                    _vUsers.push_back(User);
                }
                MyFile.close();

            }
            return _vUsers;
        }

};

