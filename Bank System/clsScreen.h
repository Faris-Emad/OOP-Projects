#pragma once
#include <iostream>
#include "clsUsers.h"
#include "Global.h"
#include "clsDate.h"


using namespace std;

class clsScreen
{
protected :
    static void _DrawScreenHeader(string Title,string SubTitle ="") {
        clsDate Date;
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.GetUserName();
        cout << "\n\t\t\t\t\tDate: ";
        Date.Print();
        cout << endl;
    }


    static bool CheckAccessRights(clsUser::UserAccess Permission) {
    
        if (!CurrentUser.CheckAccessPermission(Permission)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }


};

