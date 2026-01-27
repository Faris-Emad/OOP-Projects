# Bank Management System

A comprehensive C++ console-based banking management system that provides secure user authentication, client management, and transaction processing capabilities.

## Overview

The Bank Management System is designed as an Object-Oriented Programming (OOP) project that demonstrates advanced C++ concepts including inheritance, encapsulation, file handling, and modular design. The system supports multiple user roles with different permission levels and provides a complete banking solution.

## Features

### 🔐 User Management
- Secure login system with username/password authentication
- Role-based access control with permission levels
- User registration and management
- Password protection and session management

### 👥 Client Management
- Add new clients with personal and account information
- Update existing client details
- Delete client accounts
- Search and find clients by account number
- View complete client list

### 💰 Transaction Processing
- Deposit funds into client accounts
- Withdraw funds from client accounts
- View total balances across all accounts
- Transaction history and validation

### 📊 Reporting
- Client list display with account details
- User management reports
- Total system balances
- Search and filter capabilities

## System Architecture

### Core Classes

#### `clsPerson` (Base Class)
- Contains basic person information (name, email, phone)
- Serves as foundation for client and user classes

#### `clsBankClient` : `clsPerson`
- Manages client account information
- Handles account numbers, PIN codes, and balances
- Provides CRUD operations for client data

#### `clsUser` : `clsPerson`
- Manages system users with authentication
- Handles permissions and access control
- Supports different user roles

#### Screen Classes
- `clsLoginScreen` - Authentication interface
- `clsMainScreen` - Primary navigation menu
- `clsClientListScreen` - Client listing interface
- `clsTransactionsMenue` - Transaction operations
- `clsManageUsersMenu` - User administration

### Data Storage

The system uses text files for data persistence:
- `Clients.txt` - Client account information
- `Users.txt` - User credentials and permissions

Data format uses `#//#` as field separator for easy parsing.

## Installation & Setup

### Prerequisites
- C++14 or higher compiler
- CMake (version 4.1 or higher)
- Windows/Linux operating system

### Build Instructions

1. **Clone or download the project**
   ```bash
   cd "Bank System"
   ```

2. **Build using CMake**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the application**
   ```bash
   ./Bank_System
   ```

   Or on Windows:
   ```bash
   Bank_System.exe
   ```

### Quick Start Scripts

The project includes convenience scripts:
- `run.sh` - Linux/macOS execution script
- `run.ps1` - PowerShell execution script

## Usage Guide

### First-Time Setup

1. The system will prompt for login credentials
2. Default admin credentials are stored in `Users.txt`
3. Create initial user accounts through the management menu

### Main Navigation

The main menu provides access to:
1. **List Clients** - View all client accounts
2. **Add New Client** - Create new client accounts
3. **Delete Client** - Remove client accounts
4. **Update Client** - Modify client information
5. **Find Client** - Search for specific clients
6. **Transactions** - Access deposit/withdrawal functions
7. **Manage Users** - User administration
8. **Exit** - Logout and exit system

### Permission System

Users have different permission levels:
- **Full Access** - All system features
- **Transaction Only** - Deposit/withdrawal operations
- **View Only** - Read access to client data
- **Custom** - Combination of specific permissions

## File Structure

```
Bank System/
├── main.cpp                 # Application entry point
├── CMakeLists.txt          # Build configuration
├── Global.h                # Global variables and declarations
├── Core Classes/
│   ├── clsPerson.h         # Base person class
│   ├── clsBankClient.h     # Client management
│   ├── clsUsers.h          # User management
│   └── clsLoginScreen.h    # Authentication
├── Screen Classes/
│   ├── clsMainScreen.h     # Main navigation
│   ├── clsClientListScreen.h
│   ├── clsTransactionsMenue.h
│   └── clsManageUsersMenu.h
├── Utility Classes/
│   ├── clsScreen.h         # Base screen functionality
│   ├── clsUtility.h        # Helper functions
│   ├── clsString.h         # String manipulation
│   ├── clsDate.h           # Date handling
│   └── clsInputValidate.h  # Input validation
├── Data Files/
│   ├── Clients.txt         # Client database
│   └── Users.txt           # User database
└── Scripts/
    ├── run.sh              # Linux execution
    └── run.ps1             # Windows execution
```

## Technical Specifications

### Programming Language
- **C++14** with modern OOP principles
- Standard Library usage for I/O and data structures

### Design Patterns
- **Inheritance** - Person base class for Client/User
- **Encapsulation** - Private data with public interfaces
- **Static Methods** - Data loading and file operations
- **Enum Types** - Menu options and modes

### Data Management
- Text file-based persistence
- Delimited string format for records
- In-memory caching for performance
- Automatic file saving on data changes

### Security Features
- Password-based authentication
- Permission-based access control
- Input validation and sanitization
- Session management

## Development Notes

### Code Organization
- Header-only implementation for simplicity
- Clear separation of concerns
- Consistent naming conventions
- Modular design for maintainability

### Error Handling
- Input validation throughout the system
- File operation error checking
- Graceful failure handling
- User-friendly error messages

### Performance Considerations
- Efficient file I/O operations
- Minimal memory footprint
- Fast data access patterns
- Optimized string operations

## Future Enhancements

### Planned Features
- [ ] GUI interface using Qt or similar
- [ ] Database integration (SQLite/MySQL)
- [ ] Network support for multi-user access
- [ ] Advanced reporting and analytics
- [ ] Transaction history and audit trails
- [ ] Account types and interest calculation
- [ ] Loan management system
- [ ] Mobile application support

### Technical Improvements
- [ ] Exception handling implementation
- [ ] Unit testing framework integration
- [ ] Configuration file support
- [ ] Logging system implementation
- [ ] Data encryption for security
- [ ] Backup and recovery features

## Contributing

This project serves as an educational example of OOP principles in C++. When contributing:

1. Follow existing code style and conventions
2. Maintain proper class hierarchy and relationships
3. Ensure proper input validation
4. Test thoroughly before submitting changes
5. Update documentation as needed

## License

This project is provided for educational purposes. Feel free to use, modify, and distribute according to your needs.

## Support

For questions, issues, or suggestions regarding this Bank Management System:

1. Review the documentation thoroughly
2. Check the code comments for implementation details
3. Test with sample data files
4. Ensure proper build environment setup

---

**Project Version**: 1.0  
**Last Updated**: January 2026  
**Developer**: OOP Projects Team  
**Language**: C++14  
**Platform**: Cross-platform (Windows/Linux)