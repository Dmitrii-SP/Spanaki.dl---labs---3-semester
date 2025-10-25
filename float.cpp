#include <iostream>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <cstdint>
using namespace std;

void show_float_bits(float num) {
    uint32_t bits;
    memcpy(&bits, &num, sizeof(float));

    cout << "Number: " << num << " ---" << endl;
    cout << "Full Binary Form (32 bits): " << bitset<32>(bits) << endl;

    uint32_t sign = (bits >> 31) & 1;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    cout << "Sign Bit: " << sign << " (" << (sign ? "Negative" : "Positive") << ")" << endl;
    cout << "Exponent (8 bits): " << bitset<8>(exponent) << " = " << exponent << " (Bias 127)" << endl;
    cout << "Mantissa (23 bits): " << bitset<23>(mantissa) << endl;

    if (exponent != 0 && exponent != 255) {
        int exp = exponent - 127;
        float mantissa_val = 1.0f;
        for (int i = 22; i >= 0; i--) {
            if (mantissa & (1 << i)) {
                mantissa_val += pow(2.0f, -(23 - i));
            }
        }
        float calculated = (sign ? -1.0f : 1.0f) * mantissa_val * pow(2.0f, exp);
        cout << "Calculated Value: " << (sign ? "-" : "") << mantissa_val << " * 2^" << exp << " = " << calculated << endl;
    }
    cout << "------------------------------------------------------------------------------------\n" << endl;
}

void check_one_gap() {
    cout << "~~~~~~~~~~~~~ Task 2: Find Numbers with Spacing >= 1 ~~~~~~~~~~~~~\n" << endl;

    float x = 1.0f;
    float prev_x = x;

    while (true) {
        float next = nextafterf(x, INFINITY);
        if (next - x >= 1.0f) {
            cout << "First numbers a and b with spacing >= 1:" << endl;
            cout << "a = " << fixed << setprecision(1) << x << endl;
            cout << "b = " << next << endl;
            cout << "b - a = " << (next - x) << endl;
            break;
        }
        x *= 2.0f;
    }

    x = 1.0f;
    while (x + 1.0f != x) {
        x *= 2.0f;
    }
    cout << "\nNumber x0 where x + 1 equals x:" << endl;
    cout << "x0 = " << x << endl;
    cout << "x0 + 1 = " << (x + 1.0f) << endl;
    cout << "Check: (x0 + 1 == x0) is " << ((x + 1.0f) == x ? "True" : "False") << endl;
    cout << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;
}

void show_add_order_problem() {
    cout << "~~~~~~~~~~~~~ Task 3: Showing Non-Associativity ~~~~~~~~~~~~~ \n" << endl;

    float a = 1e20f; float b = -1e20f; float c = 1.0f;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    
    float result1 = (a + b) + c;
    float result2 = a + (b + c);

    cout << "(a + b) + c = " << result1 << endl;
    cout << "a + (b + c) = " << result2 << endl;
    cout << "(a + b) + c == a + (b + c)? " << (result1 == result2 ? "Yes" : "No") << endl;
    cout << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;
}


void check_series_stop() {
    cout << "~~~~~~~~~~~~~ Task 4: Harmonic Series 'Stops' ~~~~~~~~~~~~~ \n" << endl;

    float sum = 0.0f;
    int k = 1;

    while (true) {
        float term = 1.0f / k;
        float new_sum = sum + term;

        if (new_sum == sum) {
            cout << "k = " << k << endl;
            cout << "Final Sum = " << sum << endl;
            cout << "Last Term 1/k = " << term << endl;
            break;
        }

        sum = new_sum;
        k++;
    }
    cout << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;
}

void compare_sum_order() {
    cout << "~~~~~~~~~~~~~ Task 5: Summing Forwards vs. Backwards ~~~~~~~~~~~~~" << endl;

    float sum = 0.0f;
    int k = 1;
    while (true) {
        float new_sum = sum + 1.0f / k;
        if (new_sum == sum) break;
        sum = new_sum;
        k++;
    }

    int start = 1;
    int end = k + 100;

    float forward_sum = 0.0f;
    for (int i = start; i <= end; i++) {
        forward_sum += 1.0f / i;
    }

    float backward_sum = 0.0f;
    for (int i = end; i >= start; i--) {
        backward_sum += 1.0f / i;
    }

    cout << "Sum from 1 to " << end << ":" << endl;
    cout << "Summing Forward: " << forward_sum << endl;
    cout << "Summing Backward: " << backward_sum << endl;
    cout << "Difference: " << (forward_sum - backward_sum) << endl;
    cout << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;
}

void test_equal_sign() {
    cout << "~~~~~~~~~~~~~ Task 6: Float Equality Check (using ==) ~~~~~~~~~~~~~ \n" << endl;

    float x = 0.000000002f; float z = 0.000000001f; float t = x + z; float y = 0.000000003f;
    
    cout << "\nExample: 0.000000002 + 0.000000001 == 0.000000003?" << endl;
    cout << "0.000000002 + 0.000000001 gives " << setprecision(20) << t << endl;
    cout << "Value 0.000000003 is " << y << endl;
    cout << "Result: x + z == y is " << (t == y ? "Yes" : "No") << endl;
    
    float a = 5.0f;
    float b = 5.0f;
    cout << "\nExample: a = 5.0, b = 5.0" << endl;
    cout << "Result: a == b is " << (a == b ? "Yes" : "No") << endl;
    cout << endl;
}

int main() {
    cout << fixed << setprecision(10);
    
    float user_num;
    cout << "~~~~~~~~~~~~~ Task 1: Float Binary Structure ~~~~~~~~~~~~~ \n" << endl;
    cout << "Enter float number: ";
    cin >> user_num;
    
    show_float_bits(user_num);

    check_one_gap(); show_add_order_problem(); check_series_stop(); compare_sum_order(); test_equal_sign();

    return 0;
}