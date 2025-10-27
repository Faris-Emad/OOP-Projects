#include <iostream>
using namespace std;

/**
 * Calculator operations:
 *  - Add:           add two numbers
 *  - Subtract:      subtract two numbers
 *  - Multiply:      multiply two numbers
 *  - Divide:        divide two numbers (handle divide-by-zero)
 *  - Clear:         reset current value to zero
 *  - PrintResult:   print the current result to stdout
 */


class Calculator {
    private:
        double number = 0;
        int X = 0;
        string LastOperation;
        int setX(int Number) {
            return X = Number;
        }
        int setClear() {
            
            return (number = 0, X = 0) ;
        }
        int setAdd(int X) {
            return number += X;
        }
        int setSubtract(int X) {
            return number -= X;
        }
        int setMultiply(int X) {
            return number *= X;
        }
        double setDivide(int X) {
            if(X ==0)
                X=1;
            return number /= X;
        }
    public:
        void Clear() {
            setClear();
            LastOperation = "Clear ";
        }
        void Add(int Number) {
            setX(Number);
            setAdd(Number);
            LastOperation = "Add ";
        }
        void Subtract(int Number) {
            setX(Number);
            setSubtract(Number);
            LastOperation = "Subtract ";
        }
        void Multiply(int Number) {
            setX(Number);
            setMultiply(Number);
            LastOperation = "Multiply ";
        }
        void Divide(int Number) {
            setX(Number);
            setDivide(Number);
            LastOperation = "Divide ";
        }
        void PrintResult() {
            cout << "\nResult after " << LastOperation << X << " is " << number << endl;
        }
};

int main() {
    Calculator C;
    C.Add(10);
    C.PrintResult();
    C.Add(10);
    C.PrintResult();
    C.Add(10);
    C.PrintResult();
    C.Add(10);
    C.PrintResult();
    C.Add(10);
    C.PrintResult();
    C.Subtract(5);
    C.PrintResult();
    C.Multiply(3);
    C.PrintResult();
    C.Divide(2);
    C.PrintResult();
    C.Clear();
    C.PrintResult();
    return 0;
}