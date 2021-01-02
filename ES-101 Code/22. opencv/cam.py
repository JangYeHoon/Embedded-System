import cv2
import time 

# 카메라를 사용하기 위해 cam 변수를 선언하며 /dev/video1 카메라를 사용한다.
cam = cv2.VideoCapture(0)

# 카메라 생성 확인
if cam.isOpened() == False:
    print ('Can\'t open the CAM(%d)' % (0))
    exit()
	
while(True):
	# read 함수를 이용하여 현재 카메라의 화면을 읽어온다,
    ret, frame = cam.read()
	# 읽어온 이미지 데이터를 새창을 통해 출력한다.
    cv2.imshow('frame', frame)
	# cv2.imshow 함수를 사용할 때에는 반드시 종료되는 시점을 확인해야된다.
	# cv2.waitKey 함수를 이용하여 종료되는 시점을 설정해야만 cv2.imshow 함수에서 에러가 나지 않는다.
	# 키보드의 아무런 키만 입력되면 종료된다.
    if cv2.waitKey(10) >= 0:
       break;
# Open했던 /dev/video1 를 닫는다.
cam.release()
#이름이 frame으로 설정된 화면을 닫는다.
cv2.destroyWindow('frame')

