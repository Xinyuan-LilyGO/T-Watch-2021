#include "week.h"

const String DAY_NAMES[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int Day(int y, int m, int d)
{
    int i;
    int r = 0;                                              //储存1900到该天的闰年个数
    int a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30}; //m给每出月的天数

    if (y >= 1900 && m > 0 && m < 13 && d > 0 && d < 32)
    {
        for (i = 1900; i <= y; i++) //计算闰年的个数
        {
            if (i % 400 == 0 || i % 100 != 0 && i % 4 == 0)
                r++;
        }
        for (i = 0; i < m - 1; i++) //统计当年1月1日到当月的天数
        {
            d += a[i];
        }
        if ((y % 400 == 0 || y % 100 != 0 && y % 4 == 0) && m < 3) //如果当年是闰年但不到二月就不能算进去
            r--;
        return (365 * (y - 1900) + r + d) % 7;
    }
    else
        return -1;
}