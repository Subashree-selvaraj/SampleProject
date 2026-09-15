#include <iostream>
using namespace std;

class Calculator {
public:
    float add(float a, float b) { return a + b; }
    float subtract(float a, float b) { return a - b; }
    float divide(float a, float b) {
        if (b == 0) {
            cout << "Error: Division by zero" << endl;
            return 0;
        }
        return a / b;
    }
};

int main() {
    Calculator calc;
    float a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    cout << "Sum: " << calc.add(a, b) << endl;
    cout << "Difference: " << calc.subtract(a, b) << endl;
    cout << "Quotient: " << calc.divide(a, b) << endl;
    return 0;
}