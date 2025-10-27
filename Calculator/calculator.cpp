#include <iostream>
using namespace std;

/**
 * Calculator operations:
 *  - Add:           add two numbers
 *  - Subtract:      subtract two numbers
 *  - Multiply:      multiply two numbers
 *  - Divide:        divide two numbers (handle divide-by-zero)
 *  - Clear:         reset current value to zero
 *  - GetFinalResults: return the current result/value
 *  - PrintResult:   print the current result to stdout
 */


class Calculator {
    private:
        int number = 0;
        int X = 0;
        int setX(int Number) {
            return X = Number;
        }
        int setClear() {
            return (number = 0, X = 0) ;
        }
        int setAdd(int X) {
            return number += X;
        }
    public:
        void Clear() {
            setClear();
        }
        void Add(int Number) {
            setX(Number);
            setAdd(Number);
        }
        void PrintResult() {
            cout << "\nResult after adding " << X << " is " << number << endl;
        }
};

int main() {
    Calculator C;
    C.Clear();
    C.Add(1);
    C.PrintResult();
    C.Add(1);
    C.PrintResult();
    C.Clear();
    C.PrintResult();
    return 0;
}