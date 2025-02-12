void taskGetCmd(void *pvParameters) {
  char cmd;

  for (;;) {
    if (Serial.available()) {
      cmd = Serial.read();
      xQueueSend(queueCmd, (void *)&cmd, portMAX_DELAY);
    }
  }
}