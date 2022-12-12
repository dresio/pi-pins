#include <iostream>
#include <fstream>
#include <string>

//used for sleep function during testing. Remove for final builds
#include <unistd.h>

//direction values
#define OUT 0
#define IN 1

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

/** Add error checking
  if (!pin.is_open())
  {
    std::cerr << "Failed to open " << gpio_file << " for reading!" << std::endl;
    return -1;
  }*/

class Pin
{
    private: 
        int pin;

        std::string directionName;
        std::string valueName;

        // std::ofstream directionFile;
        // std::ofstream valueFileWrite;
        // std::ifstream valueFileRead;


    public:

        Pin(int pinNum)
        {
            pin = pinNum;
            std::ofstream enableFile("/sys/class/gpio/export");
            enableFile << std::to_string(pinNum);
            enableFile.close();

            directionName = "/sys/class/gpio/gpio" + std::to_string(pinNum) + "/direction";
            valueName = "/sys/class/gpio/gpio" + std::to_string(pinNum) + "/value";

            std::cout << directionName << std::endl;
            std::cout << valueName << std::endl;
        }

        ~Pin()
        {
            std::ofstream disableFile("/sys/class/gpio/unexport");
            disableFile << std::to_string(pin);
            disableFile.close();
        }

        void digitalWrite(int val)
        {
            std::ofstream valueFileWrite(valueName.c_str());

            if (!valueFileWrite.is_open())
            {
              std::cerr << "Failed to open " << valueName << " for writting!" << std::endl;
            }

            valueFileWrite << "0";

            std::cout << valueName << " << " << val << std::endl;

            valueFileWrite.close();
        }

        void setDirection(int direction)
        {
            std::ofstream directionFile(directionName.c_str());

            if (!directionFile.is_open())
            {
              std::cerr << "Failed to open " << directionName << " for writting!" << std::endl;
            }


            if(direction == OUT)
            {
                directionFile << "out";
            }
            else if (direction == IN)
            {
                directionFile << "in";
            }
            else
            {
                std::cerr << "Not a direction" << std::endl;
            }
            
            directionFile.close();

        }

        int digitalRead()
        {
            std::ifstream valueFileRead(valueName.c_str());
            std::string value;
            valueFileRead >> value;
            valueFileRead.close();
            std::cout << value << std::endl;
            // return stoi(value);
            return 0;
        }



};

// void enable()
// {
//     std::ofstream enablePin("/sys/class/gpio/export");

//     for(int i = 0; i < numPins; i++)
//     {
//         enablePin << std::to_string(pins[i]);
//     }

//     enablePin.close();
// }

// void setOutput()
// {
//     for(int i = 0; i < numPins; i++)
//     {
//         std::string fileName = "/sys/class/gpio/gpio" + std::to_string(pins[i]) + "/direction";
//         std::ofstream pinMode(fileName);
//         pinMode << "out";
//         pinMode.close();
//     }
// }

// void disable()
// {
//     std::ofstream disablePin("/sys/class/gpio/export");

//     for(int i = 0; i < numPins; i++)
//     {
//         disablePin << pins[i];
//     }

//     disablePin.close();
// }

// std::string pinSelect(int pinNum)
// {
//     std::string pin = "/sys/class/gpio/gpio" + std::to_string(pinNum) + "/value";
//     std::cout << pin << std::endl;
//     return pin;
// }

int main()
{

    // Commands used to control gpio
    /*
    echo 5 > /sys/class/gpio/export 
    cat /sys/class/gpio/gpio5/value 
    1
    cat /sys/class/gpio/gpio5/direction 
    in
    echo "out" > /sys/class/gpio/gpio5/direction 
    cat /sys/class/gpio/gpio5/direction 
    out
    echo 1 > /sys/class/gpio/gpio5/value 
    cat /sys/class/gpio/gpio5/value 
    1
    echo 0 > /sys/class/gpio/gpio5/value 
    cat /sys/class/gpio/gpio5/value 
    0
    echo 5 > /sys/class/gpio/unexport 
    */

    //echo 5 > /sys/class/gpio/export 
    std::ofstream enableFile("/sys/class/gpio/export");
    enableFile << "5";
    enableFile.close();

    //cat /sys/class/gpio/gpio5/value 
    std::ifstream valueFileRead("/sys/class/gpio/gpio5/value");
    std::string value;
    valueFileRead >> value;
    std::cout << value << std::endl;
    valueFileRead.close();

    //cat /sys/class/gpio/gpio5/direction 
    std::ifstream directionFileRead("/sys/class/gpio/gpio5/direction");
    directionFileRead >> value;
    std::cout << value << std::endl;
    directionFileRead.close();

    //echo "out" > /sys/class/gpio/gpio5/direction 
    std::ofstream directionFileWrite("/sys/class/gpio/gpio5/direction");
    directionFileWrite << "out";
    directionFileWrite.close();

    //cat /sys/class/gpio/gpio5/direction
    directionFileRead.open("/sys/class/gpio/gpio5/direction");
    directionFileRead >> value;
    std::cout << value << std::endl;
    directionFileRead.close();

    //echo 1 > /sys/class/gpio/gpio5/value
    std::ofstream valueFileWrite("/sys/class/gpio/gpio5/value");
    valueFileWrite << "1";
    valueFileWrite.close();

    //cat /sys/class/gpio/gpio5/value 
    valueFileRead.open("/sys/class/gpio/gpio5/value");
    valueFileRead >> value;
    std::cout << value << std::endl;
    valueFileRead.close();

    //echo 0 > /sys/class/gpio/gpio5/value
    valueFileWrite.open("/sys/class/gpio/gpio5/value");
    valueFileWrite << "0";
    valueFileWrite.close();

    //cat /sys/class/gpio/gpio5/value 
    valueFileRead.open("/sys/class/gpio/gpio5/value");
    valueFileRead >> value;
    std::cout << value << std::endl;
    valueFileRead.close();

    //echo 5 > /sys/class/gpio/unexport 

    std::ofstream disableFile("/sys/class/gpio/unexport");
    disableFile << "5";
    disableFile.close();

    //expected output:
    /*
    0
    out
    out
    1
    0
    */


    // Pin pinR1(R1);

    // //pinR1.setDirection(OUT);

    // // pinR1.digitalWrite(0);
    
    // std::ofstream valueFileWrite("/sys/class/gpio/gpio5/direction");


    // std::ofstream valueFileWrite("/sys/class/gpio/gpio5/value");

    // if (!valueFileWrite.is_open())
    // {
    //   std::cerr << "Failed to open " << "/sys/class/gpio/gpio5/value" << " for writting!" << std::endl;
    // }

    // valueFileWrite << "0";

    // std::cout << "/sys/class/gpio/gpio5/value" << " << " << "0" << std::endl;
            
    // valueFileWrite.close();

    // std::cout << "on" << std::endl;
    // pinR1.setDirection(IN);
    // pinR1.digitalRead();

    // //leep for 5 seconds
    // usleep(5000000);

    // pinR1.setDirection(OUT);
    // pinR1.digitalWrite(0);

    // std::cout << "off" << std::endl;
    // pinR1.setDirection(IN);
    // pinR1.digitalRead();

    // std::cout << "Program Finished" << std::endl;


    //-----------OLD CODE-------------------
    // enable();
    // setOutput();

    // //variables for pins used
    // std::ofstream pinR1(pinSelect(R1));
    // std::ofstream pinOE(pinSelect(OE));
    // std::ofstream pinCLK(pinSelect(CLK));
    // std::ofstream pinADDR_A(pinSelect(ADDR_A));
    // std::ofstream pinLAT(pinSelect(LAT));
    
    // pinOE << "1";
    // pinOE.close();
    // pinR1 << "1";
    // pinR1.close();

    // pinADDR_A << "1";
    // pinADDR_A.close();

    // pinLAT << "1";
    // pinLAT.close();

    // //running a few clock cycles to see what happens
    // pinCLK << "1";
    // pinCLK.close();
    
    // pinCLK.open(pinSelect(CLK));
    // pinCLK << "0";
    // pinCLK.close();

    // pinCLK.open(pinSelect(CLK));
    // pinCLK << "1";
    // pinCLK.close();

    // pinCLK.open(pinSelect(CLK));
    // pinCLK << "0";
    // pinCLK.close();

    // pinCLK.open(pinSelect(CLK));
    // pinCLK << "1";
    // pinCLK.close();

    // pinCLK.open(pinSelect(CLK));
    // pinCLK << "0";
    // pinCLK.close();

    // //wait 5 seconds
    // std::cout << "on" << std::endl;
    // usleep(5000000);
    // std::cout << "off" << std::endl;

    // pinOE.open(pinSelect(R1));
    // pinOE << "0";
    // pinOE.close();

    // pinR1.open(pinSelect(OE));
    // pinR1 << "0";
    // pinR1.close();

    // pinADDR_A.open(pinSelect(ADDR_A));
    // pinADDR_A << "0";
    // pinADDR_A.close();

    // disable();

    return 0;
}