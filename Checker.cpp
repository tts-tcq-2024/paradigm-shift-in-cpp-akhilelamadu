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
    static constexpr float CHARGE_RATE_MAX = 0.8f;

    BatteryMon(float f_temp, float f_soc, float f_ChargeRate):
        m_Temp(f_temp),
        m_SoC(f_soc),
        m_ChargeRate(f_ChargeRate)
    {

        m_TempOk = checkTemp();
        m_SoCOk = checkSoc();
        m_ChargeRateOk = checkChargeRate();
        m_BatteryHealth = m_TempOk && m_SoCOk && m_ChargeRateOk;
        printBatteryHealth();
    }

    //---Range Checkers(pure functions)---//
    uint8_t checkTemp() const
    {
        return (m_Temp < TEMP_MIN || m_Temp > TEMP_MAX) ? 0 : 1;
    }

    uint8_t checkSoc() const
    {
        return (m_SoC < SOC_MIN || m_SoC > SOC_MAX) ? 0 : 1;
    }

    uint8_t checkChargeRate() const
    {
        return (m_ChargeRate > CHARGE_RATE_MAX) ? 0 : 1;
    }
    //------------------------------------//

    // Helper function to print error messages
    void printErrorMessage(bool condition, const string& message) const {
        if (!condition) {
            cout << message << "\n";
        }
    }

    // Function to print battery health
    void printBatteryHealth() const {
        printErrorMessage(m_TempOk, "Temperature out of range!");
        printErrorMessage(m_SoCOk, "State of Charge out of range!");
        printErrorMessage(m_ChargeRateOk, "Charge Rate out of range!");
    }

private:
    bool m_TempOk, m_SoCOk, m_ChargeRateOk, m_BatteryHealth;
    float m_Temp, m_SoC, m_ChargeRate;
};

int main()
{
    // Unit test cases
    BatteryMon test1(25.0f, 50.0f, 0.5f); // Expected: All OK
    assert(test1.checkTemp() == 1);
    assert(test1.checkSoc() == 1);
    assert(test1.checkChargeRate() == 1);

    BatteryMon test2(50.0f, 85.0f, 0.7f); // Expected: Temperature and SOC out of range
    assert(test2.checkTemp() == 0);
    assert(test2.checkSoc() == 0);
    assert(test2.checkChargeRate() == 1);

    BatteryMon test3(-5.0f, 10.0f, 0.9f); // Expected: All out of range
    assert(test3.checkTemp() == 0);
    assert(test3.checkSoc() == 0);
    assert(test3.checkChargeRate() == 0);

    cout << "All unit tests passed!\n";
    return 0;
}
