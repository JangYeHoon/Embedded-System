# Embedded System 실습 코드

목차

[1. ES-101 Code](#es-101-code)

[2. Linux Code](#linux-code)



## ES-101 Code

ES-101 실습 장비에서 작성했던 실습 예제 코드

운영체제는 ES-101에서 제공하는 Soda

디바이스 드라이버 실습은 native라는 폴더에 응용 프로그램 제공(디바이스드라이버_native 폴더)

- [1. module_exam](ES-101%20Code/1.%20module_exam)
  - 간단한 모듈 프로그램
- [1. led_module](ES-101%20Code/1.%20led_module)
  - gpio를 이용해 led를 전부 키고 끄는 모듈 프로그램
- [1. switch_module](ES-101%20Code/1.%20switch_module)
  - gpio를 이용해 모듈 등록시 눌려 있는 스위치를 알려줌
- [2. printk_exam](ES-101%20Code/2.%20printk_exam)
  - thread를 생성해 30초 동안 다양한 레벨의 로그를 출력
- [3. linked_list](ES-101%20Code/3.%20linked_list)
  - 커널에서 제공하는 kmalloc을 이용한 링크드리스트 실습
- [4. kfifo_exam](ES-101%20Code/4.%20kfifo_exam)
  - 커널에서 제공하는 kfifo를 이용한 실습
- [5. mem_exam](ES-101%20Code/5.%20mem_exam)
  - 커널에서 제공하는 kmalloc과 vmalloc을 이용한 실습
- [6. timer_module](ES-101%20Code/6.%20timer_module)
  - 간단한 timer 모듈 프로그램. 딱 한번만 로그 출력
- [6. timer_module_2](ES-101%20Code/6.%20timer_module_2)
  - timer_module을 변형해 4초마다 로그를 계속 출력
- [7. led_timer](ES-101%20Code/7.%20led_timer)
  - 2초마다 한번씩 led를 전부 키고 끄고를 반복
- [8. kthread_exam](ES-101%20Code/8.%20kthread_exam)
  - thread를 하나 생성해 1초마다 로그를 출력
- [9. led_kthread](ES-101%20Code/9.%20led_kthread)
  - 진수 연산을 이용해 led의 앞에서 부터 켜져서 1초마다 옆의 led가 켜짐
- [10. switch_interrput](ES-101%20Code/10.%20switch_interrupt)
  - interrput를 이용한 switch와 led 제어 모듈
  - switch gpio와 대응하는 interrput를 만듬
  - switch가 눌리면 interrput 발생
  - 눌린 switch 번호에 맞는 led가 켜짐
- [11. pir_interrupt](ES-101%20Code/11.%20pir_interrupt)
  - interrupt를 이용한 pir 제어 모듈
  - pir의 gpio를 interrupt로 등록
  - 지나가는게 탐지되면 pir_detect 출력, 아니면 pir not detect 출력
- [11. pir_condition](ES-101%20Code/11.%20pir_condition)
  - condition변수를 이용한 pir interrupt 제어 모듈 실습
  - condition변수를 이용하여 지나가는게 탐지될 때만 출력
- [12. driver_exam](ES-101%20Code/12.%20driver_exam)
  - 간단한 디바이스 드라이버 실습
- [13. simple_buffer](ES-101%20Code/13.%20simple_buffer)
  - 응용 프로그램과 디바이스 드라이버끼리 문자열을 주고받는 실습
- [14. led_driver](ES-101%20Code/14.%20led_driver)
  - 1초마다 led가 하나씩 켜지는 디바이스 드라이버 실습
- [15. switch_driver](ES-101%20Code/15.%20switch_driver)
  - switch를 이용해 led를 제어하는 디바이스 드라이버 실습
  - switch를 interrupt에 등록해 switch가 눌리는지 확인
  - 눌리면 led를 키고 thread를 이용해 switch가 눌러져있는지 확인하여 led를 제어
- [16. pir_driver](ES-101%20Code/16.%20pir_driver)
  - 12번의 pir 모듈을 디바이스 드라이버로 구현
- [17. misc_driver](ES-101%20Code/17.%20misc_driver)
  - 간단한 misc driver 실습
- [18. led_misc_driver](ES-101%20Code/18.%20led_misc_driver)
  - 1초마다 led를 하나씩 키는 misc driver
- [19. led_misc_driver_2](ES-101%20Code/19.%20led_misc_driver_2)
  - ioctl을 이용해 등록한 ioctl을 하나씩 수행하는 misc driver
- [20. touch_driver](ES-101%20Code/20.%20touch_driver)
  - 어느 패드가 touch되었는지 체크하여 출력하는 디바이스 드라이버
  - 디바이스 드라이버는 touch가 되었는지 감지
  - 응용 프로그램은 1초마다 ioctl을 이용해 디바이스 드라이버로부터 touch의 결과를 받아 출력
- [21. static_hello](ES-101%20Code/21.%20static_hello)
  - hello 메시지를 출력하는 공유 라이브러리 실습
  - 메모리 중복 문제를 해결하기 위해 위치 독립적인 코드로 생성
  - 프로그램 배포시 해당 공유 라이브러리도 함께 배포
  - 리눅스의 오브젝트 파일 포맷은 ELF로 섹션이나 세그먼트만 다름
  - ELF 공유 라이브러리는 동적으로 적재
  - 실행 프로그램과 공유 라이브러리간 함수 호출은 PLT와 GOT를 통해 해결
- [21. led_static](ES-101%20Code/21.%20led_static)
  - led를 이용한 공유 라이브러 실습
  - led_misc_driver를 활용하는 공유 라이브러리
  - 드라이버에 접근하는 응용 프로그램의 내용을 공유 라이브러리에 포함
  - 일반 응용프로그램에서는 저수준 입출력 함수가 아닌 공유 라이브러리에서 제공하는 함수를 이용
- [22. opencv](ES-101%20Code/22.%20opencv)
  - opencv를 이용한 영상 처리 실습
  - [cam.py](ES-101%20Code/22.%20opencv/cam.py)
    - 카메라 장치 작동 실습
  - [motion.py](ES-101%20Code/22.%20opencv/motion.py)
    - 카메라의 처음 화면에서 변화하는 화면을 감지
    - 변화된 부분을 박스로 처리
    - GrayScale, 블러링, 가우시안 블러 사용
  - [color.py](ES-101%20Code/22.%20opencv/color.py)
    - 인식할 색상의 범위를 지정
    - 지정한 색상이 나오면 해당 영역 박스로 처리
  - [face.py](ES-101%20Code/22.%20opencv/face.py)
    - 영상에서 얼굴을 탐지
    - 얼굴은 박스로 처리
    - cascading classifiers 사용



## Linux Code

ES-101 실습 장비가 아닌 우분투 환경에서 진행했던 실습 코드

- [1. basic_module](Linux%20Code/1.%20basic_module)
  - 로그만 출력하는 간단한 모듈 프로그램
- [2. driver_exam](Linux%20Code/2.%20driver_exam)
  - 각 함수 별로 로그를 출력하는 간단한 디바이스 드라이버
- [3. timer_module](Linux%20Code/3.%20timer_module)
  - 4초마다 로그를 출력하는 타이머 모듈 프로그램
- [4. kthread_module](Linux%20Code/4.%20kthread_module)
  - thread를 이용한 모듈 프로그램
  - thread를 하나 생성해 4초마다 kfifo안에 값을 추가
  - thread가 종료될 때 kfifo안의 모든 값 출력
- [5. device_driver_add](Linux%20Code/5.%20device_driver_add)
  - 더하기를 수행하는 디바이스 드라이버
  - 응용 프로그램에서 0~9 사이의 랜덤한 값 2개를 디바이스에 보내줌
  - 디바이스 드라이버는 받은 2개의 값을 더함
  - 더한 결과 값을 다시 응용 프로그램에게 전달
- [6. device_driver_char](Linux%20Code/6.%20device_driver_char)
  - 문자열에서 알파벳의 수를 찾아내는 디바이스 드라이버
  - 응용 프로그램에서 입력받은 문자열을 디바이스에 전달
  - 디바이스 드라이버는 문자열에서 알파벳의 개수를 알아냄
  - 알파벳의 개수를 응용 프로그램에게 전달

