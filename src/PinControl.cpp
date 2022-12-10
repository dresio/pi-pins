#include <iostream>
#include <fstream>

int main()
{
    // Set the pin mode to output
    std::ofstream pinMode("/sys/class/gpio/gpio12/direction");
    pinMode << "out";
    pinMode.close();

    // Turn on the output pin
    std::ofstream pinValue("/sys/class/gpio/gpio12/value");
    pinValue << "1";
    pinValue.close();

    // Turn off the output pin
    pinValue.open("/sys/class/gpio/gpio12/value");
    pinValue << "0";
    pinValue.close();

    return 0;
}