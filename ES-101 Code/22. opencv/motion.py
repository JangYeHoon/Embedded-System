import time
import cv2
 
# 카메라를 사용하기 위해 cap 변수를 선언하며 /dev/video0 카메라를 사용한다.
cam = cv2.VideoCapture(0)

# 카메라 생성 확인
if cam.isOpened() == False:
    print ('Can\'t open the CAM(%d)' % (0))
    exit()
# 첫 화면을 저장할 변수를 선언
firstFrame = None
while True:
	# 선언된 카메라를 이용하여 ret과 img를 읽는다.
    ret, img=cam.read()
 
	# 입력된 BGR 형태의 이미지를 Gray 형태의 이미지로 변환한다.
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	# 블러링 필터를 적용한다 GaussianBlur 는 이미지의 가우스 노이즈를 제거하는데 가장 효과적인 필터이다.
	# 인자값으로는 이미지, 블러 필터, 시그마 X값
	# 이미지는 현재 그레이 스케일 형태의 이미지를 사용한다.
	# 블러 필터의 적용 값은 21, 21이다. 두개의 값이 달라도 되지만 무조건 홀수 값이어야 한다.
	# SigmaX 값은 = 0 으로 설정한다. SigmaY의 값은 자동으로 0 으로 설정되어있다.
	# SigmaX 값을 0 으로 입력한것은 GaussianBlur 기능만 사용하기 위해서다.
    gray = cv2.GaussianBlur(gray, (21, 21), 0)
 
	# firstFrame 상태가 None 일때
    # 가우스 블러 처리된 데이터를 firstFrame 변수에 넣는다.
    if firstFrame is None:
        firstFrame = gray
        continue
	# 첫 화면과 현재 화면을 비교하여 판단한다.
    frameDelta = cv2.absdiff(firstFrame, gray)
	# 판단된 데이터를 통해 thresh 값을 적용하여 흑백을 반전 시킨다.
    thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]
 
	# 추출된 thresh 데이터에서 더욱더 선명하게 나타낸다.
    thresh = cv2.dilate(thresh, None, iterations=2)
	# 완성된 thresh 데이터를 이용하여 x,y,w,h 데이터를 추출 한다.
    conts,h= cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
 
	# 추출된 x,y,w,h 데이터를 이용하여, 사각형을 그린다.
    for i in range(len(conts)):
        x,y,w,h=cv2.boundingRect(conts[i])
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255), 2)
		
    cv2.imshow("Motion Detect", img)
    if cv2.waitKey(10) >= 0:
        break;
 
cam.release()
cv2.destroyAllWindows()

