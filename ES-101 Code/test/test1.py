import wiringpi as wp
import time
import RPi.GPIO as GPIO
import smbus 
import math
import Adafruit_SSD1306
import spidev
import threading
import os
import sys
import cv2
from PIL import Image
from shiftr_74HC595.shiftr_74HC595 import ShiftRegister

fndPid = 0
swPid = 0
sht20Pid = 0
mpuPid = 0
touchPid = 0
oledPid = 0
psdPid = 0
rledPid = 0
servoPid = 0
piezoPid = 0
camPid = 0
pirPid = 0
pir_first = 0

def led_control(data):
    if data == 0:
        wp.digitalWrite(4,1)
    elif data == 1:
        wp.digitalWrite(5,1)
    elif data == 2:
        wp.digitalWrite(6,1)
    elif data == 3:
        wp.digitalWrite(31,1)
    elif data == 4:
        wp.digitalWrite(4,0)
    elif data == 5:	
        wp.digitalWrite(5,0)
    elif data == 6:
        wp.digitalWrite(6,0)
    elif data == 7:
        wp.digitalWrite(31,0)

def switch_data():
    swPid = os.getpid()
    if wp.digitalRead(7)==1:
        print("sw1 pushed!\n")
    if wp.digitalRead(0)==1:
        print("sw2 pushed!\n")
    if wp.digitalRead(2)==1:
        print("sw3 pushed!\n")
    if wp.digitalRead(3)==1:
        print("sw4 pushed!\n")
        time.sleep(0.1)

def fnd_control():
    fndPid = os.getpid()
    data = 1
    shift_register = ShiftRegister(0,5,6)
    for i in range(10):
        if data == 1:
            shift_register.setOutput(0,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(1,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(2,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(3,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(4,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(5,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(6,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(7,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(0,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(1,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(2,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(3,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(4,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(5,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(6,GPIO.HIGH)
            shift_register.latch()
            shift_register.setOutput(7,GPIO.HIGH)
            shift_register.latch()
        else:
            shift_register.setOutput(0,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(1,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(2,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(3,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(4,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(5,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(6,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(7,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(0,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(1,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(2,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(3,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(4,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(5,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(6,GPIO.LOW)
            shift_register.latch()
            shift_register.setOutput(7,GPIO.LOW)
            shift_register.latch()
        data = ~data
        time.sleep(0.5)

def read_byte(i2c_bus,adr):
    return i2c_bus.read_byte_data(0x68, adr)

def read_word(i2c_bus,adr):
    high = i2c_bus.read_byte_data(0x68, adr)
    low = i2c_bus.read_byte_data(0x68, adr+1)
    val = (high << 8) + low
    return val

def read_word_2c(i2c_bus,adr):
    val = read_word(i2c_bus,adr)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val 

def dist(a,b):
    return math.sqrt((a*a)+(b*b))

def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)

def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)

def mpu6050_control():
    mpuPid = os.getpid()
    bus.write_byte_data(0x68, 0x6b, 0)
    time.sleep(1)
    print("--------------------------------------------------------")
    print("=>gyro data")
    print("---------")
    gyro_xout = read_word_2c(bus,0x43)
    gyro_yout = read_word_2c(bus,0x45)
    gyro_zout = read_word_2c(bus,0x47)
    time.sleep(0.5)
    print("gyro_xout: ", gyro_xout, " scaled: ", (gyro_xout / 131))
    print("gyro_yout: ", gyro_yout, " scaled: ", (gyro_yout / 131))
    print("gyro_zout: ", gyro_zout, " scaled: ", (gyro_zout / 131))
    print("")
    print("=>accelerometer data")
    print("------------------")
    accel_xout = read_word_2c(bus,0x3b)
    accel_yout = read_word_2c(bus,0x3d)
    accel_zout = read_word_2c(bus,0x3f)
    time.sleep(0.5)
    accel_xout_scaled = accel_xout / 16384.0
    accel_yout_scaled = accel_yout / 16384.0
    accel_zout_scaled = accel_zout / 16384.0
    print("accel_xout: ", accel_xout, " scaled: ", accel_xout_scaled)
    print("accel_yout: ", accel_yout, " scaled: ", accel_yout_scaled)
    print("accel_zout: ", accel_zout, " scaled: ", accel_zout_scaled)
    print("x rotation: " , get_x_rotation(accel_xout_scaled, accel_yout_scaled, accel_zout_scaled))
    print("y rotation: " , get_y_rotation(accel_xout_scaled, accel_yout_scaled, accel_zout_scaled))
    print("--------------------------------------------------------")
    
def sht20_control():
    sht20Pid = os.getpid()
    bus.write_byte(0x40, 0xFE)
    time.sleep(0.5)
    bus.write_byte(0x40, 0xE5)

    data0 = bus.read_byte(0x40)
    data1 = bus.read_byte(0x40)

    temp = data0 * 256 + data1
    cTemp = -46.85 + ((temp *175.72) / 65536.0)

    bus.write_byte(0x40, 0xF5)
    time.sleep(0.5)
        
    data0 = bus.read_byte(0x40)
    data1 = bus.read_byte(0x40)

    humi = data0 * 256 + data1
    humi = -6 + ((humi*125.0)/65536.0)
    print("temp : %.2f C" %cTemp)
    print("humi : %.2f %%\n" %humi)

def touch_control():
    touchPid = os.getpid()
    data = bus.read_byte_data(0x1b,0x03)
    if data == 0x01:
        print("Touch 1 pushed")
    elif data == 0x02:
        print("Touch 2 pushed")
    else:
        print("Nothing Pushed")
    time.sleep(0.5)

def oled_control():
    oledPid = os.getpid()
    RST = 24
    disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
    disp.begin()
    disp.clear()
    disp.display()
    if disp.height == 64:
        image = Image.open('happycat_oled_64.ppm').convert('1')
    else:
        image = Image.open('happycat_oled_32.ppm').convert('1')
    disp.image(image)
    disp.display()

def psd_control():
    psdPid = os.getpid()
    adc_num = 0
    time.sleep(0.5)
    r = spi.xfer2([6|(adc_num>>2), (adc_num & 3) << 6, 0])
    adcout = ((r[1] & 15) << 8) + r[2]
    dist = 10000 / (adcout * 434 * 5 / 4096 - 46)
    if dist > 80.0:
        dist = 80
    if dist < 0:
        dist = 80
    print("psd distance %.2f cm" %dist)

def adc_control(adc_num):    
    r = spi.xfer2([6|(adc_num>>2), (adc_num & 3) << 6, 0])
    adcout = ((r[1] & 15) << 8) + r[2]
    return adcout
                
def rgb_led_control():
    rledPid = os.getpid()
    while True:
        data = 0
        for i in range(10):
            pwm.set_duty_cycle(0, data)
            data = data + 10
            time.sleep(0.1)
        pwm.set_duty_cycle(0, 0)
        data = 0
        for i in range(10):
            pwm.set_duty_cycle(1, data)
            data = data + 10
            time.sleep(0.1)
        pwm.set_duty_cycle(1, 0)
        data = 0
        for i in range(10):
            pwm.set_duty_cycle(2, data)
            data = data + 10
            time.sleep(0.1)
        pwm.set_duty_cycle(2, 0)

def servo_control():
    servoPid = os.getpid()
    servo_data = 2
    while True:
        pwm.set_duty_cycle(3, servo_data) # -1 for all channels
        pwm.set_duty_cycle(4, servo_data)
        servo_data = servo_data + 1
        if servo_data > 13:
            servo_data = 2
        time.sleep(1)
    

def piezo_control():
    piezoPid = os.getpid()
    scale = [ 261.63, 294.67, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25 ] 
    GPIO.setup(12, GPIO.OUT)
    p = GPIO.PWM(12, 100)
    p.start(100) 
    p.ChangeDutyCycle(90) 
    for i in range(8):
        p.ChangeFrequency(scale[i])
        time.sleep(1)

def cam_control():
    cam = cv2.VideoCapture(0)

    if cam.isOpened() == False:
        print ('Can\'t open the CAM(%d)' % (1))
        exit()
	
    while True:
        ret, frame = cam.read()
        cv2.imshow('frame', frame)
        cv2.waitKey(10)

    cam.release()
    cv2.destroyWindow('frame')

def pir_detect(self):
    print("pir Detect!\n")
    
def pir_control(pir_first):
    if pir_first==0:
        GPIO.add_event_detect(7,GPIO.RISING,callback=pir_detect)
        pir_first=1
    time.sleep(0.5)

wp.wiringPiSetup()

wp.pinMode(4,1)
wp.pinMode(5,1)
wp.pinMode(6,1)
wp.pinMode(31,1)#led

wp.pinMode(7,0)
wp.pinMode(0,0)
wp.pinMode(2,0)
wp.pinMode(3,0)#switch

wp.pinMode(30,1)
wp.pinMode(21,1)
wp.pinMode(22,1)#fnd

wp.pinMode(10,1)
wp.digitalWrite(10,0)

bus = smbus.SMBus(1)#i2c

spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz=500000#spi

GPIO.setmode(GPIO.BCM)
GPIO.setup(7,GPIO.IN,pull_up_down=GPIO.PUD_UP)

led_data = 0

#fnd_thread = threading.Thread(target=fnd_control)
#sw_thread = threading.Thread(target=switch_data)
#sht20_thread = threading.Thread(target=sht20_control)
#mpu_thread = threading.Thread(target=mpu6050_control)
#touch_thread = threading.Thread(target=touch_control)
#oled_thread = threading.Thread(target=oled_control)
#psd_thread = threading.Thread(target=psd_control)
#piezo_thread = threading.Thread(target=piezo_control)
cam_thread = threading.Thread(target=cam_control)
#pir_thread = threading.Thread(target=pir_control)

#fnd_thread.start()
#sw_thread.start()
#sht20_thread.start()
#mpu_thread.start()
#touch_thread.start()
#oled_thread.start()
#psd_thread.start()
#piezo_thread.start()
cam_thread.start()
#pir_thread.start()

while True:
    select = int(input("1: led\n2: switch\n3: sht20\n4: mpu6050\n5: touch\n6: oled\n7: psd\n8: piezo\n9: pir\n10: fnd\n11: exit\n"))
    if select == 1:
        for i in range(8):
            led_control(led_data)
            led_data = led_data + 1
            time.sleep(0.5)   
    elif select == 2:                   
        for i in range(20):
            switch_data()
            time.sleep(0.5)   
    elif select == 3:
        for i in range(20):
            sht20_control()
    elif select == 4:
        for i in range(20):
            mpu6050_control()
    elif select == 5:
        for i in range(20):
            touch_control()
    elif select == 6:
        oled_control()
    elif select == 7:
        for i in range(20):
            psd_control()
    elif select == 8:
        for i in range(2):
            piezo_control()
    elif select == 9:
        for i in range(20):
            pir_control(pir_first)
            if pir_first==0:
                pir_first=1
        pir_first = 0
        GPIO.remove_event_detect(7)
    elif select == 10:
        fnd_control()
    elif select == 11:
        break;

#os.popen("kill -9 "+str(fndPid))
#os.popen("kill -9 "+str(swPid))
#os.popen("kill -9 "+str(sht20Pid))
#os.popen("kill -9 "+str(mpuPid))
#os.popen("kill -9 "+str(touchPid))
#os.popen("kill -9 "+str(oledPid))
#os.popen("kill -9 "+str(psdPid))
#os.popen("kill -9 "+str(rledPid))
#os.popen("kill -9 "+str(servoPid))
#os.popen("kill -9 "+str(piezoPid))
os.popen("kill -9 "+str(camPid))
#os.popen("kill -9 "+str(pirPid))
sys.exit(0)    
