void cbCheckDistance(void *pvParameters) {
  int distance;
  char cmd;

  distance = robo.ultrasonic.read();
  cmd = distance <= 15 ? 'B' : 'U';
  xQueueSend(queueCmd, (void *)&cmd, portMAX_DELAY);
}