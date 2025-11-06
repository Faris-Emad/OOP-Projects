// #include <iostream>
// using namespace std;


// class person {
//     public:
//         virtual void Print() {
//             cout << "im person" << endl;
//         }
// };

// class employee : public person {
//     public:
//         void Print() {
//             cout << "im employee" << endl;
//         }
// };

// class student : public person  {
//     public:
//         void Print() {
//             cout << "im student" << endl;
//         }
// };


// int main() {
    

    
//     employee Employee1;
//     student  Student1;
//     //Early-Static Binding: at compilation time
//     Employee1.Print();
//     Student1.Print();

//     cout << endl;
//     person * Person1 = &Employee1;
//     person * Person2 = &Student1;
    
//     //Late-Dynamic Binding: at runtime
//     Person1->Print();
//     Person2->Print();
//     return 0;
// }



#include <iostream>
using namespace std;


//Abstract Class ==> / Interface ==> / Contract.
class Mobile{
    public:
        virtual void Dial(string PhoneNumber) = 0;
        virtual void SendSMS(string Text) = 0;
        virtual void TakePicture() = 0;
};

class iPhone {

};


int main() {

    return 0;
}