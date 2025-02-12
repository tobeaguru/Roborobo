void taskControlLed(void *pvParameters) {
  char cmd = 'g';

  xQueueSend(queueLed, (void *)&cmd, portMAX_DELAY);
  
  for (;;) {
    if (xQueueReceive(queueLed, &cmd, portMAX_DELAY) == pdPASS) {
      robo.pixels.clear();

      switch(cmd) {
        case 'r':
          robo.pixels.setPixelColor(0, robo.pixels.Color(200, 0, 0));
          break;
        case 'g':
          robo.pixels.setPixelColor(0, robo.pixels.Color(0, 200, 0));
          break;
        case 'b':
          robo.pixels.setPixelColor(0, robo.pixels.Color(0, 0, 200));
        default:
          break;
      }
      
      robo.pixels.show();
    }
  }
}