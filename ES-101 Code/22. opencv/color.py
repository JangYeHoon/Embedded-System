import cv2
import numpy as np

# 색상에 대한 최소치 최대치를 입력한다.
# 지정된 최소 최대치사이에 있는 데이터를 이용하여 색상을 판단한다.

# Blue
#lowerBound=np.array([97,100,117])
#upperBound=np.array([117,255,255])

# RED
lowerBound=np.array([170,50,0])
upperBound=np.array([179,255,255])

# Green
#lowerBound=np.array([50,100,100])
#upperBound=np.array([70,255,255])

# 카메라를 사용하기 위해 cap 변수를 선언하며 /dev/video0 카메라를 사용한다.
cam= cv2.VideoCapture(0)

#카메라 생성 확인
if cam.isOpened() == False: 
    print ('Can\'t open the CAM(%d)' % (0))
    exit()
	
# 인식된 색상 정보를 더욱더 정확하게 확인하기 위해서 mask 작업시 사용되는 numpy 형태의 배열이다.
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))

while True:
	# 선언된 카메라를 이용하여 ret과 img 를 읽어온다.
    ret, img=cam.read()

    # 입력된 BGR 형태의 이미지를 HSV 형태의 이미지로 변환한다.
	# HSV (Hue, Saturation, value)는 색상, 채도, 밝기 데이터를 사용하여 색상을 나타낸다. 
    imgHSV= cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
    # 마스크를 생성한다.
    mask=cv2.inRange(imgHSV,lowerBound,upperBound)
	# 5x5 형태의 np 구조를 이용하여 색상정보를 인식한 데이터를 추출한다.
	# maskOpen 과정 까지만 하였을때 파란색이 많이 나타나는 경우 무수히 많은 박스가 생성된다 최대크기 5x5
    maskOpen=cv2.morphologyEx(mask,cv2.MORPH_OPEN,kernelOpen)
	
	# 20x20 형태의 np 구조를 이용하여 5x5 형태에서 인식된 색상 데이터를 합치는 역할을 한다.
	# 밀집된 5x5 크기의 색상 인식 데이터를 합쳐 나타나게 되어 최종 상태에 이른다.
    maskFinal=cv2.morphologyEx(maskOpen,cv2.MORPH_CLOSE,kernelClose)
	# 완성된 mask 데이터를 이용하여 x,y,w,h 데이터를 추출 한다.
    conts,h=cv2.findContours(maskFinal.copy(),cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
    
	# 추출된 x,y,w,h 데이터를 이용하여, 사각형을 그린다.
    for i in range(len(conts)):
        x,y,w,h=cv2.boundingRect(conts[i])
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255), 2)
	# 이미지를 표시한다. 
    cv2.imshow("Color_Detection",img)
    if cv2.waitKey(10) >= 0:
     break;
cv2.destroyAllWindows()

