#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <timers.h>

#include <Roborobo.h>

Roborobo robo;

TimerHandle_t timerCheckDistance;
QueueHandle_t queueCmd, queueLed;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ;
  }

  robo.pixels.begin();

  // Queue
  queueCmd = xQueueCreate(2, sizeof(char));
  queueLed = xQueueCreate(2, sizeof(char));

  // Task 
  if (xTaskCreate(taskGetCmd, "GetCmd", 128, NULL, 2, NULL) != pdPASS) {
    Serial.println("task GetCmd wasn't created.");
  }

  if (xTaskCreate(taskProcessCmd, "PorcessCmd", 128, NULL, 2, NULL) != pdPASS) {
    Serial.println("task ProcessCmd wasn't created.");
  }

  if (xTaskCreate(taskControlLed, "Led", 128, NULL, 2, NULL) != pdPASS) {
    Serial.println("task ControlLed wasn't created.");
  }

  // Timer
  timerCheckDistance = xTimerCreate("CheckDistance", pdMS_TO_TICKS(200), pdTRUE, (void *)0, cbCheckDistance);
  if (timerCheckDistance != NULL) {
    xTimerStart(timerCheckDistance, 0);
  } else {
    Serial.println("timer CheckDistance wasn't created.");
  }
}

void loop() {

}
