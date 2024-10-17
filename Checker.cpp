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

    // Warning tolerances (5% of upper limit)
    static constexpr float TEMP_WARNING_TOLERANCE = 0.05f * TEMP_MAX;
    static constexpr float SOC_WARNING_TOLERANCE = 0.05f * SOC_MAX;
    static constexpr float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX;

    BatteryMon(float f_temp, float f_soc, float f_ChargeRate)
        : m_Temp(f_temp),
          m_SoC(f_soc),
          m_ChargeRate(f_ChargeRate),
          m_statusupdated(false),
          m_warningStatusUpdated(false)
    {
        // Checking the individual parameters' state
        m_TempOk = checkParams(m_Temp, TEMP_MIN, TEMP_MAX);
        m_SoCOk = checkParams(m_SoC, SOC_MIN, SOC_MAX);
        m_ChargeRateOk = checkParams(m_ChargeRate, CHARGE_RATE_MIN, CHARGE_RATE_MAX);

        // Checking overall battery health
        m_BatteryHealth = m_TempOk && m_SoCOk && m_ChargeRateOk;

        // Printing the battery state
        printBatteryHealth();

        // Checking and printing warnings
        printWarnings();
    }

    // Returns the overall status of the battery
    bool isBatteryOk() const { return m_BatteryHealth; }

    //---Range Checker (pure function)---//
    bool checkParams(float f_parameter, float f_minLimit, float f_maxLimit) const
    {
        return (f_parameter >= f_minLimit && f_parameter <= f_maxLimit);
    }
    //------------------------------------//

    // Warning checker
    bool checkWarning(float f_parameter, float f_minLimit, float f_maxLimit, float f_tolerance) const
    {
        return (f_parameter >= f_minLimit && f_parameter <= (f_minLimit + f_tolerance)) ||
               (f_parameter >= (f_maxLimit - f_tolerance) && f_parameter <= f_maxLimit);
    }

    // Helper function to print error messages
    void printErrorMessage(bool condition, const string& message)
    {
        if (!condition && !m_statusupdated)
        {
            cout << message << "\n";
            m_statusupdated = true;
        }
    }

    // Helper function to print warnings
    void printWarningMessage(bool condition, const string &message)
    {
        if (condition && !m_warningStatusUpdated)
        {
            cout << message << "\n";
            m_warningStatusUpdated = true;
        }
    }

    // Function to print battery health
    void printBatteryHealth()
    {
        printErrorMessage(m_TempOk, "Temperature out of range!");
        printErrorMessage(m_SoCOk, "State of Charge out of range!");
        printErrorMessage(m_ChargeRateOk, "Charge Rate out of range!");
    }

    // Function to print warnings
    void printWarnings()
    {
        bool tempWarning = checkWarning(m_Temp, TEMP_MIN, TEMP_MAX, TEMP_WARNING_TOLERANCE);
        bool socWarning = checkWarning(m_SoC, SOC_MIN, SOC_MAX, SOC_WARNING_TOLERANCE);
        bool chargeRateWarning = checkWarning(m_ChargeRate, CHARGE_RATE_MIN, CHARGE_RATE_MAX, CHARGE_RATE_WARNING_TOLERANCE);

        printWarningMessage(tempWarning, "Warning: Temperature approaching limit!");
        printWarningMessage(socWarning, "Warning: State of Charge approaching limit!");
        printWarningMessage(chargeRateWarning, "Warning: Charge Rate approaching limit!");
    }

private:
    bool m_TempOk, m_SoCOk, m_ChargeRateOk // individual parameters status
        , m_BatteryHealth                  // Overall Battery health
        , m_statusupdated, m_warningStatusUpdated;  // Flags for status updates
    // Member variables to store the charging parameters
    float m_Temp, m_SoC, m_ChargeRate;
};

int main()
{
    // Unit test cases
    BatteryMon test1(25.0f, 50.0f, 0.5f); // Expected: All OK
    assert(test1.isBatteryOk() == 1);

    BatteryMon test2(50.0f, 85.0f, 0.7f); // Expected: Temperature out of range
    assert(test2.isBatteryOk() == 0);

    BatteryMon test3(40.0f, 85.0f, 0.7f); // Expected: SOC out of range
    assert(test3.isBatteryOk() == 0);

    BatteryMon test4(40.0f, 40.0f, 0.9f); // Expected: Charge rate out of range
    assert(test4.isBatteryOk() == 0);

    BatteryMon test5(-5.0f, 10.0f, 0.9f); // Expected: All out of range, but only Temp will be printed
    assert(test5.isBatteryOk() == 0);

    // Test case for warnings
    BatteryMon test6(43.0f, 78.0f, 0.75f); // Expected: All within warning limits
    assert(test6.isBatteryOk() == 1);

    cout << "All unit tests passed!\n";
    return 0;
}
