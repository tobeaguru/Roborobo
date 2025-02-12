#define DEFAULT_SPEED   255

void taskProcessCmd(void *pvParameters) {
  char cmd, led;
  char blocked = 0;

  for (;;) {
    if (xQueueReceive(queueCmd, &cmd, portMAX_DELAY) == pdPASS) {
      led = 'g';
      
      if (cmd == 'B') {
        blocked = 1;
        led = 'r';
        xQueueSend(queueLed, (void *)&led, portMAX_DELAY);
        continue;
      } else if (cmd == 'U') {
        blocked = 0;
      }

      if (blocked && (cmd == 'q' || cmd == 'w' || cmd == 'e')) {
        continue;
      }

      switch(cmd) {
        case 'q':
          robo.move_left_forward(DEFAULT_SPEED);
          break;
        case 'w':
          robo.move_forward(DEFAULT_SPEED);
          break;
        case 'e':
          robo.move_right_forward(DEFAULT_SPEED);
          break;
        case 'a':
          robo.move_left(DEFAULT_SPEED);
          break;
        case 's':
          robo.move_stop();
          break;
        case 'd':
          robo.move_right(DEFAULT_SPEED);
          break;
        case 'z':
          robo.move_left_backward(DEFAULT_SPEED);
          break;
        case 'x':
          robo.move_backward(DEFAULT_SPEED);
          break;
        case 'c':
          robo.move_right_backward(DEFAULT_SPEED);
          break;
        case '[':
          robo.move_left_rotate(DEFAULT_SPEED);
          led = 'b';
          break;
        case ']':
          robo.move_right_rotate(DEFAULT_SPEED);
          led = 'b';
          break;
      }
      xQueueSend(queueLed, (void *)&led, portMAX_DELAY);
    }
  }
}