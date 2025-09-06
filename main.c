/* --------------------------------------------------------------
   Application 1 
   John Crawford 
   Real Time Systems - Fa 2025
   AI Use: None used - Only the Provided lines & google for how to define the xtask (no actual code used, just to find if it needed to be within main or defined like a function)
---------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_0

void beacon(void *pvParameters){
    int beacon_status = 1; // led starts on :D

    while (1){
        // Log uptime (ms since scheduler started)
        printf("Beacon Active - Time: %lu ms\n",(unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS)); // same line as the printf ms counter basically - tracks time from beginning of LED
        gpio_set_level(LED_PIN, beacon_status); // sets LED status
        vTaskDelay(pdMS_TO_TICKS(250)); // 250ms Delay for 500ms period
        beacon_status = !beacon_status; // flip the bit of LED status so next iteration it turns to the opposite state
    }  
}

void print_task(void *pvParameters){
    while(1){
        printf("Telemetry Responsive - System Status: Enjoying the Planetary View, Time=%lu ms\n", (unsigned long)(xTaskGetTickCount()*portTICK_PERIOD_MS)); 
        vTaskDelay(pdMS_TO_TICKS(10000));  // 10 seconds
    }
}

void app_main() {
    gpio_reset_pin(LED_PIN);  //set GPIO for LED - used define earlier so we can use any pin without having to hardcode everywhere
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // LED GPIO Pin is an output not an input 
    
    xTaskCreate(print_task, "PrintTask", 2048, NULL, 1, NULL); // begin BLINK & PRINT task simultaneously 
    xTaskCreate(beacon, "BeaconTask", 2048, NULL, 1, NULL);

}

