#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

/* 1) Template function: calibrateValue
   factor is a char "numerical" value (e.g. '2'). We interpret digit chars as their numeric value.
*/
template<typename S>
S calibrateValue(const S &x, char factor) {
    double factorVal;
    if (isdigit(static_cast<unsigned char>(factor))) factorVal = (factor - '0');
    else factorVal = static_cast<int>(factor); /* fallback */
    return static_cast<S>(x * static_cast<S>(factorVal));
}

/* 2) adjustReading: add offset (default 1.25) to a double pointed by value */
void adjustReading(double *value, double offset = 1.25) {
    if (value) *value += offset;
}

/* 3) clampReading: clamp in-place to [0,100] */
void clampReading(double &r) {
    if (r < 0.0) r = 0.0;
    else if (r > 100.0) r = 100.0;
}

/* 4) computeDifference: a - b */
double computeDifference(int a, double b) {
    return static_cast<double>(a) - b;
}

int main() {
    int intSensor;
    double dblSensor;

    // i) read inputs using cin
    cout << "Enter integer sensor reading: ";
    if (!(cin >> intSensor)) return 1;
    cout << "Enter double sensor reading: ";
    if (!(cin >> dblSensor)) return 1;

    // ii) calibrate both readings by 2 (pass char '2')
    int intCal = calibrateValue<int>(intSensor, '2');
    double dblCal = calibrateValue<double>(dblSensor, '2');

    // formatting: right-aligned, width 10, precision 4
    cout << fixed << setprecision(4);

    cout << "\nAfter calibration:\n";
    cout << right << setw(10) << static_cast<double>(intCal) << "   (calibrated integer)\n";
    cout << right << setw(10) << dblCal << "   (calibrated double)\n";

    // iii) convert calibrated int to double
    double intAsDouble = static_cast<double>(intCal);

    // iv) adjustReading twice
    adjustReading(&intAsDouble);                // default offset 1.25
    adjustReading(&dblCal, 3.4);                // offset 3.4

    cout << "\nAfter adjustment:\n";
    cout << right << setw(10) << intAsDouble << "   (adjusted from int)\n";
    cout << right << setw(10) << dblCal << "   (adjusted double)\n";

    // v) clamp both adjusted readings
    clampReading(intAsDouble);
    clampReading(dblCal);

    cout << "\nAfter clamping:\n";
    cout << right << setw(10) << intAsDouble << "   (clamped int-as-double)\n";
    cout << right << setw(10) << dblCal << "   (clamped double)\n";

    // vi) convert int-as-double back to int
    int finalInt = static_cast<int>(intAsDouble);
    cout << "\nFinal integer sensor (converted back):\n";
    cout << right << setw(10) << static_cast<double>(finalInt) << "   (printed with precision 4)\n";

    // vii) compute difference between clamped double and integer
    double diff = computeDifference(finalInt, dblCal);
    cout << "\nDifference (int - double):\n";
    cout << right << setw(10) << diff << "\n";

    return 0;
}