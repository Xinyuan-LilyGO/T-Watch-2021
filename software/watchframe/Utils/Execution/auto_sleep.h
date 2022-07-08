#pragma once

enum wake_up_reason_t
{
    WAKE_UP_REASON_WRIST_UP = 0,
    WAKE_UP_REASON_DOUBLE_TAG = 1,
    WAKE_UP_REASON_SCREEN = 2,
};

void auto_sleep_start(void);
void auto_sleep_set_time(uint32_t delay);
void auto_sleep_set_wake_up(wake_up_reason_t reason, bool Enable);
void auto_sleep_close(void);
void auto_sleep_updeta(void);
void wait_auto_sleep(void);