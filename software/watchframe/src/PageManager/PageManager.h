#ifndef _PAGEMANAGER_H_
#define _PAGEMANAGER_H_

#include "Page_type.h"
#include "Page_Application.h"
#include "Page_MainMenu.h"
#include "Page_Watchface.h"
#include "../Utils/Utils.h"
#include "WiFi.h"

extern uint8_t switch_interface;
void Page_Init();
void Page_Event_Updata();
void Page_Loop();

/**
 * @brief software configuration
 *
 * bit 0:Connect wifi to automatically synchronize time
 * bit 1:auto sleep
 * bit 2:
 * bit 3:
 * bit 4:
 * bit 5:
 * bit 6:
 * bit 7:
 * bit 8:
 * bit 9:
 *
 */
extern EventGroupHandle_t local_setting;

extern QueueHandle_t goto_sleep_queue_handle;

/**
 * @brief Create a notification object
 *
 * @param details The character to display
 * @param delay standing time
 */
void create_notification(char *details, uint32_t delay);

#endif /* _PAGEMANAGER_H_ */
