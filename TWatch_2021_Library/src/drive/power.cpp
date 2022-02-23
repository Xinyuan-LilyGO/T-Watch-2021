#include "./TWatch_hal.h"

#if defined(TWatch_HAL_Power)
/* Quantity comparison meter */
/*                      0%   10%    20%   30%  40%    50%   60%   70%   80%   90%  100% */
const float Qcm[11] = {3.00, 3.45, 3.68, 3.74, 3.77, 3.79, 3.82, 3.92, 3.98, 4.06, 4.12};

void TWatchClass::Power_Init()
{
    pinMode(TWATCH_PWR_ON, OUTPUT);
    pinMode(TWATCH_BAT_ADC, INPUT);
    digitalWrite(TWATCH_PWR_ON, HIGH);
}

void TWatchClass::Power_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        if (_power_cnt < POWER_UPDATA_CYCLE)
        {
            _pow_temp[_power_cnt] = analogRead(TWATCH_BAT_ADC);
            _power_cnt++;
        }
        else
        {
            tw_bubble_sort(_pow_temp, POWER_UPDATA_CYCLE);

            for (uint8_t i = 1; i < (POWER_UPDATA_CYCLE - 2); i++)
            {
                _power_sub += _pow_temp[i];
            }
            _power_sub = _power_sub / (POWER_UPDATA_CYCLE - 2);

            if (_pow_temp[POWER_UPDATA_CYCLE - 1] - _power_sub > 5)
            {
                _ischarge = true;
            }
            else if (_power_sub - _pow_temp[0] > 5)
            {
                _ischarge = false;
            }
            else
            {
                _ischarge = false;
            }
            _pow_cur_vol = (((_power_sub * 3.3) / 4096) + 0.04) * 2;
            _power_sub = 0;
            _power_cnt = 0;
        }

        Millis = millis;
    }
}
float TWatchClass::Get_Power_Percent()
{
    int8_t i = 10;
    while (_pow_cur_vol <= Qcm[i])
    {
        if (i == 0)
            break;
        else
            i--;
    }

    float vol_section = abs(Qcm[i + 1] - Qcm[i]);

    _pow_percent = (i * 10) + (((_pow_cur_vol - Qcm[i]) * 10) / vol_section);

    return _pow_percent;
}
uint8_t TWatchClass::Get_Power()
{

    uint16_t b = 0;
    uint8_t n = 20;
    // measure n times
    for (uint8_t i = 0; i < n; i++)
    {
        b = b + analogRead(TWATCH_BAT_ADC);
    }
    b = b / n;

    float vol = ((b * 3.3) / 4096 + 0.1);
    vol = vol < 1.4 ? 0 : (vol - 1.4) / 0.6 * 100;
    return constrain(vol, 0, 100);
}

#endif