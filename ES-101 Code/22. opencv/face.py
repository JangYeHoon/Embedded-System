import numpy as np
import cv2

# 얼굴인식의 데이터 모델은 Opencv 제공의 Haar Object Detector 를 이용한다.

"""
Haar Object Detector 는 패턴 인식 알고리즘이다.
모든 사람들에게는 존재하는 눈, 코, 입, 귀, 얼굴 형태 등의 패턴이 입력된 데이터로
입력된 데이터의 이미지 픽셀 하나하나를 패턴에 적용시켜 어떠한 차이 또는 경계값을 추출하고 그에 따라 
사람 얼굴이다, 아니다를 판별 하게 된다.
Opencv 를 설치하게 되면 다음 haar_face의 경로에 많은 haar 패턴에 대한 데이터를 제공한다. 
"""
# haar의 데이터중 기본 정면 얼굴 데이터의 위치를 지정한다.
haar_face = '/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml'
# CascadeClassifier 함수를 이용하여 얼굴에 대한 패턴을 적용한다.
face_cascade = cv2.CascadeClassifier(haar_face)

# 카메라를 사용하기 위해 cam 변수를 선언하며 /dev/video0 카메라를 사용한다.
cam = cv2.VideoCapture(0)

# 카메라 생성 확인
if cam.isOpened() == False:
    print ('Can\'t open the CAM(%d)' % (0))
    exit()
	
while 1:
	# 선언된 카메라를 이용하여 ret과 img 를 읽어온다.
    ret, img = cam.read()
	# 읽어온 img 를 그레이스케일을 통해 회색 이미지로 변경한다.
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	# 그레이스케일된 데이터를 이용하여 얼굴 패턴 인식을 통해 판단하고 데이터를 읽어온다.
	# gray : 이때 인자값으로는 그레이스케일 된 이미지 
	# scaleFactor : 입력된 이미지를 얼마나 줄일것인지 지정하는 매개변수 
	# minNeighbors : 탐지될 데이터의 품지를 지정한다, 값이 높을수록 탐지되는 데이터는 적지만 품질이 높으며, 낮을수록 비슷한 모든 패턴을 인식하게 됩니다.
	# minSize : 가능한 최소 오브젝트 크기, 지정된 크기보다 작은 객체는 무시됨.
	# 패턴이 감지되면 x,y,w,h 로 반환합니다.
    faces = face_cascade.detectMultiScale(gray,scaleFactor=1.3,minNeighbors=1,minSize=(100,100))

	# 반환된 x,y,w,h 를 이용하여 사각형을 그린다.
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
     
	# 이미지를 표시하는 화면 구성
    cv2.imshow('img',img)
	# 사용자가 q 키를 입력 하였을때 종료된다.
    if cv2.waitKey(10) >= 0:
     break
	 
cam.release()
cv2.destroyAllWindows()

