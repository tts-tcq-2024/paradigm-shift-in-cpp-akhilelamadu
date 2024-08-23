#include <assert.h>
#include <iostream>
using namespace std;

//---Range Checkers(purefunctions)---//
uint8_t checkTemp(float temperature)
{
    return (temperature < 0 || temperature > 45) ?0:1;
}
//purefunction
uint8_t checkSoc(float soc)
{
    return (soc < 20 || soc > 80)?0:1;
}
//purefunction
uint8_t checkChargeRate(float chargeRate)
{
    return (chargeRate > 0.8) ?0:1;
}
//------------------------------------//

//---battery Health Checker(purefunction)---//
uint8_t batteryState(bool temperatureOk, bool socOk, bool chargeRateOk) {
  return temperatureOk&&socOk&&chargeRateOk;
}

// Helper function to print error messages
void printErrorMessage(bool condition, const string& message) {
    if (!condition) {
        cout << message << "\n";
    }
}

// Function to print battery health
void printBatteryHealth(float temperature, float soc, float chargeRate) {
    printErrorMessage(checkTemp(temperature), "Temperature out of range!");
    printErrorMessage(checkSoc(soc), "State of Charge out of range!");
    printErrorMessage(checkChargeRate(chargeRate), "Charge Rate out of range!");
}

bool batteryIsOk(float temperature, float soc, float chargeRate)
{
    bool TempState    =   checkTemp(temperature);
    bool SocState     =   checkSoc(soc);
    bool ChargeState  =   checkChargeRate(chargeRate);
    
    //return battery health(true or false)
    return batteryState(TempState, SocState, ChargeState);
}

int main() {
  
  printBatteryHealth(25, 70, 0.7);
  printBatteryHealth(50, 85, 0) ;
  
  
  assert(batteryIsOk(25, 70, 0.7)   == true);
  assert(batteryIsOk(50, 85, 0)     == false);
  
  return 0;
}
