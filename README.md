# Embedded System 실습 코드

목차

[1. ES-101 Code](##ES-101 Code)

[2. Linux Code](##Linux Code)



## ES-101 Code

ES-101 실습 장비에서 작성했던 실습 예제 코드

운영체제는 ES-101에서 제공하는 Soda

## Linux Code

ES-101 실습 장비가 아닌 우분투 환경에서 진행했던 실습 코드

- [1. basic_module](Linux Code/1. basic_module)
  - 로그만 출력하는 간단한 모듈 프로그램
- [2. driver_exam](Linux Code/2. driver_exam)
  - 각 함수 별로 로그를 출력하는 간단한 디바이스 드라이버
- [3. timer_module](Linux Code/3. timer_module)
  - 4초마다 로그를 출력하는 타이머 모듈 프로그램
- [4. kthread_module](Linux Code/4. kthread_module)
  - thread를 이용한 모듈 프로그램
  - thread를 하나 생성해 4초마다 kfifo안에 값을 추가
  - thread가 종료될 때 kfifo안의 모든 값 출력
- [5. device_driver_add](Linux Code/5. device_driver_add)
  - 더하기를 수행하는 디바이스 드라이버
  - 응용 프로그램에서 0~9 사이의 랜덤한 값 2개를 디바이스에 보내줌
  - 디바이스 드라이버는 받은 2개의 값을 더함
  - 더한 결과 값을 다시 응용 프로그램에게 전달
- [6. device_driver_char](Linux Code/6. device_driver_char)
  - 문자열에서 알파벳의 수를 찾아내는 디바이스 드라이버
  - 응용 프로그램에서 입력받은 문자열을 디바이스에 전달
  - 디바이스 드라이버는 문자열에서 알파벳의 개수를 알아냄
  - 알파벳의 개수를 응용 프로그램에게 전달

