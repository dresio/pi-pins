#include <iostream>
#include <fstream>

//used for sleep function during testing. Remove for final builds
#include <unistd.h>

#define R1 5
#define G1 13
#define B1 6
#define R2 12
#define G2 16
#define B2 23

#define OE 4    //output enable
#define CLK 17
#define LAT 21

#define ADDR_A 22
#define ADDR_B 26
#define ADDR_C 27
#define ADDR_D 20
//#define ADDR_E 24     //only used on 64 pixel tall displays

int pins[] = {R1, G1, B1, R2, G2, B2, OE, CLK, LAT, ADDR_A, ADDR_B, ADDR_C, ADDR_D};
int numPins = sizeof(pins)/sizeof(int);

class Pin
{
    private: 
        std::string directionName;
        std::string valueName;

        std::ofstream enableFile;
        std::ofstream directionFile;
        std::ofstream valueFile;

    public:
        Pin(int pinNum)
        {
            enableFile.open("/sys/class/gpio/export");
            enableFile << std::to_string(pinNum);
            enableFile.close();

            directionName = "/sys/class/gpio/gpio" + std::to_string(pinNum) + "/direction";
            valueName = "/sys/class/gpio/gpio" + std::to_string(pinNum) + "/value";
        }
};

void enable()
{
    std::ofstream enablePin("/sys/class/gpio/export");

    for(int i = 0; i < numPins; i++)
    {
        enablePin << std::to_string(pins[i]);
    }

    enablePin.close();
}

void setOutput()
{
    for(int i = 0; i < numPins; i++)
    {
        std::string fileName = "/sys/class/gpio/gpio" + std::to_string(pins[i]) + "/direction";
        std::ofstream pinMode(fileName);
        pinMode << "out";
        pinMode.close();
    }
}

void disable()
{
    std::ofstream disablePin("/sys/class/gpio/export");

    for(int i = 0; i < numPins; i++)
    {
        disablePin << pins[i];
    }

    disablePin.close();
}

std::string pinSelect(int pinNum)
{
    std::string pin = "/sys/class/gpio/gpio" + std::to_string(pinNum) + "/value";
    std::cout << pin << std::endl;
    return pin;
}

int main()
{
    enable();
    setOutput();

    //variables for pins used
    std::ofstream pinR1(pinSelect(R1));
    std::ofstream pinOE(pinSelect(OE));
    std::ofstream pinCLK(pinSelect(CLK));
    std::ofstream pinADDR_A(pinSelect(ADDR_A));
    std::ofstream pinLAT(pinSelect(LAT));
    
    pinOE << "1";
    pinOE.close();
    pinR1 << "1";
    pinR1.close();

    pinADDR_A << "1";
    pinADDR_A.close();

    pinLAT << "1";
    pinLAT.close();

    //running a few clock cycles to see what happens
    pinCLK << "1";
    pinCLK.close();
    
    pinCLK.open(pinSelect(CLK));
    pinCLK << "0";
    pinCLK.close();

    pinCLK.open(pinSelect(CLK));
    pinCLK << "1";
    pinCLK.close();

    pinCLK.open(pinSelect(CLK));
    pinCLK << "0";
    pinCLK.close();

    pinCLK.open(pinSelect(CLK));
    pinCLK << "1";
    pinCLK.close();

    pinCLK.open(pinSelect(CLK));
    pinCLK << "0";
    pinCLK.close();

    //wait 5 seconds
    std::cout << "on" << std::endl;
    usleep(5000000);
    std::cout << "off" << std::endl;

    pinOE.open(pinSelect(R1));
    pinOE << "0";
    pinOE.close();

    pinR1.open(pinSelect(OE));
    pinR1 << "0";
    pinR1.close();

    pinADDR_A.open(pinSelect(ADDR_A));
    pinADDR_A << "0";
    pinADDR_A.close();

    disable();

    return 0;
}