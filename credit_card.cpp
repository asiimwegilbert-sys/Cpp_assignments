/*
    Credit Card Number Validation
    Reads a credit card number and tells the user whether it is
    VALID or INVALID.
*/

#include <iostream>
using namespace std;

// ----- Function prototypes ------
bool isValid(long long number);
int sumOfDoubleEvenPlace(long long number);
int getDigit(int number);
int sumOfOddPlace(long long number);
bool prefixMatched(long long number, int d);
int getSize(long long d);
long long getPrefix(long long number, int k);


int main() {
    long long cardNumber;

    cout << "Enter a credit card number as a long integer: ";
    cin >> cardNumber;

    if (isValid(cardNumber)) {
        cout << cardNumber << " is valid." << endl;
    } else {
        cout << cardNumber << " is invalid." << endl;
    }

    return 0;
}


// Return true if the card number is valid
bool isValid(long long number) {
    int size = getSize(number);

    // Rule 1: must have between 13 and 16 digits
    if (size < 13 || size > 16) {
        return false;
    }

    // Rule 2: must start with a recognised card-issuer prefix
    bool prefixOk = prefixMatched(number, 4)  ||  // Visa
                    prefixMatched(number, 5)  ||  // MasterCard
                    prefixMatched(number, 37) ||  // American Express
                    prefixMatched(number, 6);     // Discover
    if (!prefixOk) {
        return false;
    }

    // Rule 3: the Luhn checksum must be divisible by 10
    int total = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);
    return (total % 10 == 0);
}


// Get the result from Step 2 of the Luhn algorithm:
// double every 2nd digit counting from the right, 
// collapse any two-digit results, and add them all up.
int sumOfDoubleEvenPlace(long long number) {
    int sum = 0;
    long long n = number;
    bool isEvenPosition = false;
    // Rightmost digit is position 1 (an ODD position), so it must
    // NOT be doubled. We only start doubling from the 2nd digit.

    while (n > 0) {
        int digit = static_cast<int>(n % 10); // peel off the rightmost digit

        if (isEvenPosition) {
            sum += getDigit(digit * 2); // double it, then collapse to 1 digit
        }

        isEvenPosition = !isEvenPosition; // flip for the next digit
        n /= 10;                          // remove the digit we just used
    }

    return sum;
}


// Return this number if it is a single digit, otherwise, return
// the sum of the two digits (e.g. 16 -> 1 + 6 -> 7)
int getDigit(int number) {
    if (number < 10) {
        return number;
    } else {
        return number / 10 + number % 10;
    }
}


// Return sum of odd-place digits in number (from the right)
int sumOfOddPlace(long long number) {
    int sum = 0;
    long long n = number;
    bool isOddPosition = true; // rightmost digit (position 1) is odd

    while (n > 0) {
        int digit = static_cast<int>(n % 10);

        if (isOddPosition) {
            sum += digit; // odd-place digits are added as-is, no doubling
        }

        isOddPosition = !isOddPosition;
        n /= 10;
    }

    return sum;
}


// Return true if the digit(s) d is a prefix for number
// e.g. prefixMatched(4388576018410707, 4) -> true
//      prefixMatched(4388576018410707, 37) -> false
bool prefixMatched(long long number, int d) {
    int sizeOfD = getSize(d);
    return getPrefix(number, sizeOfD) == d;
}


// Return the number of digits in d
int getSize(long long d) {
    if (d == 0) {
        return 1; // the number 0 still counts as having 1 digit
    }

    int size = 0;
    while (d > 0) {
        size++;
        d /= 10;
    }
    return size;
}


// Return the first k digits from number.
// If number has fewer than k digits, just return number unchanged.
long long getPrefix(long long number, int k) {
    int size = getSize(number);

    if (size <= k) {
        return number;
    }

    // Divide by 10 the right number of times to chop off the
    // extra digits at the end, leaving only the first k digits.
    long long divisor = 1;
    for (int i = 0; i < size - k; i++) {
        divisor *= 10;
    }
    return number / divisor;
}
