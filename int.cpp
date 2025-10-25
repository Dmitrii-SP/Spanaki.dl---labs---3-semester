#include <iostream>
#include <bitset>
#include <climits>
using std::cout;
using std::bitset;
using std::cin;
using std::endl;

template <typename T>
void print(T value) {
    const int bits = sizeof(T) * CHAR_BIT;
    bitset<bits> binary_representation(value);
    cout << binary_representation << endl;
}

int main() {
    cout << "Size int: " << sizeof(int) << " byte\n\n";

    int positive, negative;

    cout << "positive: ";
    cin >> positive;
    cout << "negative: ";
    cin >> negative;


    cout << "\n" << positive << ":   "; print(positive);

    cout << negative << ":   "; print(negative);

    union {
        int signed_value;
        unsigned int unsigned_value;
    } bytes;

    bytes.signed_value = positive;
    cout << positive << ":    " << bytes.unsigned_value << "  ";
    print(bytes.unsigned_value);

    bytes.signed_value = negative;
    cout << negative << ":    " << bytes.unsigned_value << "  ";
    print(bytes.unsigned_value);

    int maxInt = INT_MAX;
    cout << "INT_MAX = " << maxInt << endl;
    cout << "INT_MAX + 1 = " << maxInt + 1 << endl;

    unsigned int maxUInt = UINT_MAX;
    cout << "UINT_MAX = " << maxUInt << endl;
    cout << "UINT_MAX + 1 = " << maxUInt + 1 << endl;
    cout << "UINT_MAX - 1 = " << maxUInt - 1 << endl;

    return 0;
}