/**
 * @file calculator.cpp
 * Simple calculator with basic arithmetic, clear, undo, and print helpers.
 */
#include <iostream>
using namespace std;

class Calculator {
    private:
        float _Result = 0;
        float _LastNumber = 0;
        string _LastOperation = "Clear";
        float _PerviousResult = 0;

        bool _IsZero(float Number) {
            return (Number == 0) ;
        }
    public:
        void Add(float Number) {
            _LastNumber = Number;
            _PerviousResult = _Result;
            _LastOperation = "Adding";
            _Result += Number;
        }
        void Subtract(float Number) {
            _LastNumber = Number;
            _PerviousResult = _Result;
            _LastOperation = "Subtracting";
            _Result -= Number;
        }
        void Divide(float Number) {
            _LastNumber = Number;
            if(_IsZero(Number)) {
                Number = 1;
            }
            _PerviousResult = _Result;
            _LastOperation = "Divideing";
            _Result /= Number;
        }
        void Multiply(float Number) {
            _LastNumber = Number;
            _PerviousResult = _Result;
            _LastOperation = "Multiplying";
            _Result *= Number;
        }
        float GetFinalResults() {
            return _Result;
        }
        void Clear() {
            _LastNumber = 0;
            _PerviousResult = 0;
            _LastOperation = "Clear";
            _Result = 0;
        }

        void CancelLastOperation(){
            _LastNumber = 0;
            _LastOperation = "Cancel Last Operation";
            _Result = _PerviousResult;
        }

        void PrintResult() {
            cout << "Result " ;
            cout << "After " << _LastOperation << " " << _LastNumber << " is: " << _Result << endl;
        } 

        
};

int main() {
    Calculator C;
    C.Add(5);
    C.PrintResult();
    C.Multiply(3);
    C.PrintResult();
    C.Subtract(2);
    C.PrintResult();
    C.Divide(4);
    C.PrintResult();
    C.Clear();
    C.PrintResult();
    C.Add(10);
    C.PrintResult();
    C.CancelLastOperation();
    C.PrintResult();
    return 0;
}