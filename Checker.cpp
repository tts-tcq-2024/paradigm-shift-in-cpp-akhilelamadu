#include <assert.h>
#include <iostream>
using namespace std;

class BatteryMon
{
    public:
        
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
        
        //---Range Checkers(purefunctions)---//
        uint8_t checkTemp()
        {
            return (m_Temp < 0 || m_Temp > 45) ?0:1;
        }

        uint8_t checkSoc()
        {
            return (m_SoC < 20 || m_SoC > 80)?0:1;
        }
     
        uint8_t checkChargeRate()
        {
            return (m_ChargeRate > 0.8) ?0:1;
        }
        //------------------------------------//
        
        // Helper function to print error messages
        void printErrorMessage(bool condition, const string& message) {
            if (!condition) {
                cout << message << "\n";
            }
        }
        
        // Function to print battery health
        void printBatteryHealth() {
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
 
      BatteryMon new_var(50,85,0);
      return 0;
    }
