cmake_minimum_required(VERSION 4.1)
project(Bank_System)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bank_System
        " clsRegisterLogins.h"
        clsAddNewClient.h
        clsAddNewUsersScreen.h
        clsBankClient.h
        clsClientListScreen.h
        clsDate.h
        clsDeleteClientScreen.h
        clsDeleteUserScreen.h
        clsDepositScreen.h
        clsFindClientScreen.h
        clsFindUserScreen.h
        clsInputValidate.h
        clsLoginScreen.h
        clsMainScreen.h
        clsManageUsersMenu.h
        clsPerson.h
        clsScreen.h
        clsString.h
        clsTotalBalancesScreen.h
        clsTransactionsMenue.h
        clsUpdateClientScreen.h
        clsUpdateUserScreen.h
        clsUsers.h
        clsUsersListScreen.h
        clsUtility.h
        clsWithdrawScreen.h
        Global.h
        main.cpp
        clsLoginRegister.h)
