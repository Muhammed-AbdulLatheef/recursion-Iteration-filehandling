#include <iostream>
#include <iomanip>


template<typename S>
S calibrateValue(const S &x, char factor) {
    double factorVal;
    if (isdigit(static_cast<unsigned char>(factor))) factorVal = (factor - '0');
    else factorVal = static_cast<int>(factor); /* fallback */
    return static_cast<S>(x * static_cast<S>(factorVal));
}


void adjustReading(double *value, double offset = 1.25) {
    if (value) *value += offset;
}


void clampReading(double &r) {
    if (r < 0.0) r = 0.0;
    else if (r > 100.0) r = 100.0;
}


double computeDifference(int a, double b) {
    return static_cast<double>(a) - b;
}

int main() {
    cout << std::fixed << std::setprecision(4) << std::right;

    int intSensor;
    double dblSensor;

    
    cout << "Enter integer sensor reading: ";
    cin >> intSensor
    cout << "Enter double sensor reading: ";
    cin >> dblSensor

    
    int intCal = calibrateValue<int>(intSensor, '2');
    double dblCal = calibrateValue<double>(dblSensor, '2');

}