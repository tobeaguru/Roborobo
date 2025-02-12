# simple implementation of DIYGO AI 자율주행 자동차 of Roborobo  
Adruino code for Roborobo RC-Car and python code for remote controller with webcam

scratch나 micropython을 통한 python 코드를 사용해 보았다면, 보다 직관적이고 효율적인 C 코드도 
가볍게 경험해 보면 배움에 도움이 될 것이라 생각 됩니다. 8/16bit mcu에서도 OS를 사용하면 
향후 32/64bit AP 영역에서도 동일한 개념이 사용되기 때문에 일을 분할하고 메시지를 통해서
협업하는 기본적인 동작을 해당 코드를 통해서 맛 볼 수 있습니다.

기본적인 동작은 확인을 했습니다. 해당 코드를 기반으로 기능 추가에 도움이 되었으면 합니다.

# Arduino and Python Code
+ In Arduino, install the following libraries
  * Ultrasonic
  * Adafruit_NeoPixel
  * FreeRTOS
    
+ In Python, install the following libraries
  * opencv2
  * numpy
  * pyqt5
  * requests
  * serial
 
# 동작 방식
+ Arduino Side
  * FreeRTOS를 사용해서 Task를 분리(코드 참조)
  * 해당 Task는 메시지 Queue에서 명령을 기다림
  * 명령을 받으면 상응하는 명령 수행
  * 거리 감지는 일정 주기로 실행해서 Led를 통해 상태를 알려줌

+ Python Side
  * 좌우측 프레임으로 분해해 좌측은 웹캠, 우측은 동작 제어(마우스나 키보를 통해)
  * 키보드 매팅
    - q w e (좌상 상 우상)
    - a s d (왼쪽 정지 오른쪽)
    - z x c (좌하 하 우하)
    - [ ] (좌측회전 우측회전)
