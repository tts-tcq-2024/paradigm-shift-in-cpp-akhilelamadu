#include <iostream>
#include <cassert>
using namespace std;

class BatteryMon
{
public:
    // Constants for battery limits
    static constexpr float TEMP_MIN = 0.0f;
    static constexpr float TEMP_MAX = 45.0f;
    static constexpr float SOC_MIN = 20.0f;
    static constexpr float SOC_MAX = 80.0f;
    static constexpr float CHARGE_RATE_MIN = 0.0f;
    static constexpr float CHARGE_RATE_MAX = 0.8f;
    

    BatteryMon(float f_temp, float f_soc, float f_ChargeRate):
        m_Temp(f_temp),
        m_SoC(f_soc),
        m_ChargeRate(f_ChargeRate),
        m_statusupdated(false)
    {
        //checking the individual parameters state
        m_TempOk        = checkParams(m_Temp,TEMP_MIN,TEMP_MAX);
        m_SoCOk         = checkParams(m_SoC, SOC_MIN, SOC_MAX);
        m_ChargeRateOk  = checkParams(m_ChargeRate, CHARGE_RATE_MIN, CHARGE_RATE_MAX);
        
        //Checking Overall battery check
        m_BatteryHealth = m_TempOk && m_SoCOk && m_ChargeRateOk;

        //Printing the battery state
        printBatteryHealth();
    }

    //Returns the overall status of the batter
    bool isBatteryOk() const { return m_BatteryHealth; }
    
    
    //---Range Checker (pure function)---//
    bool checkParams(float f_parameter, float f_upperLimit, float f_lowerLimit) const
    {
        return (f_parameter < f_upperLimit || f_parameter > f_lowerLimit) ? false : true;
    }
    //------------------------------------//

    // Helper function to print error messages
    // only the first hit is printed (Same as orginal code)
    void printErrorMessage(bool condition, const string& message) {
        if (!condition && !m_statusupdated) {
            cout << message << "\n";
            m_statusupdated = true;
        }
    }

    // Function to print battery health
    void printBatteryHealth() {
        printErrorMessage(m_TempOk, "Temperature out of range!");
        printErrorMessage(m_SoCOk, "State of Charge out of range!");
        printErrorMessage(m_ChargeRateOk, "Charge Rate out of range!");
    }

private:
    bool m_TempOk, m_SoCOk, m_ChargeRateOk //individual parameters status
        , m_BatteryHealth                  //Overall Battery health
        , m_statusupdated;                 //check out of range is already updated for the battery
    //member variables to store the charging parameters
    float m_Temp, m_SoC, m_ChargeRate;
};

int main()
{
    // Unit test cases
    BatteryMon test1(25.0f, 50.0f, 0.5f); // Expected: All OK
    assert(test1.isBatteryOk() == 1);
    

    BatteryMon test2(50.0f, 85.0f, 0.7f); // Expected: Temperatureout of range
    assert(test2.isBatteryOk() == 0);

    BatteryMon test3(40.0f, 85.0f, 0.7f); // Expected: SOC out of range
    assert(test3.isBatteryOk() == 0);

    BatteryMon test4(40.0f, 40.0f, 0.9f); // Expected: Charge rate out of range
    assert(test4.isBatteryOk() == 0);
    
    BatteryMon test5(-5.0f, 10.0f, 0.9f); // Expected: All out of range, but only Temp will be printed
    assert(test5.isBatteryOk() == 0);

    cout << "All unit tests passed!\n";
    return 0;
}
