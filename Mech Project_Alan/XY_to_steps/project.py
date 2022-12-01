from picamera.array import PiRGBArray
from picamera import PiCamera
import serial,time
import cv2
import RPi.GPIO as gpio

gpio.setmode(gpio.BCM)
gpio.setup(3, gpio.IN)


        
zx=5
zy=345

xbox1 = 245
xbox2 = 390

ybox1 = 130
ybox2 = 480

objectlocation = (0, 0)


def main():
    zero()
    
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.framerate = 32
    rawCapture = PiRGBArray(camera, size=(640, 480))

    time.sleep(0.1)
    #sys.stdout = open("/home/pi/Documents/myLog.log","w")
    #sys.stderr = open("/home/pi/Documents/myLogErr.log","w")


    # kit.servo[0].angle = 90
    # tracker = EuclideanDistTracker() # could be used to track multiple objects


    object_detector = cv2.createBackgroundSubtractorMOG2(history=10, varThreshold=5)
    # threshold higher means it picks up fewer false positives, history takes into account past frames?

    frametracker = 0
    go = False
    


    while True:

        objectlocation = (0, 0)
        x, y, w, h = 0,0,0,0

        
        for frame in camera.capture_continuous(rawCapture, format = "bgr", use_video_port=True):
            frametracker += 1
            image = frame.array



            height, width = camera.resolution
            #frame = cv2.flip(frame, -1) # Flip camera vertically
            # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            # only look at region of interest (roi)
            # here I'm setting to full resolution, but if there was only a portion
            # of screen that could have objects, could reduce this
            roi = image[ybox1:ybox2, xbox1:xbox2] # seems to be height range, width?
            mask = object_detector.apply(roi)

            # remove everything below 254 (get only white
            # not sure this is needed
            #_, mask = cv2.threshold(mask, 128, 255, cv2.THRESH_BINARY)

            # object detection
            # contours is each identified area, hierarchy tells you information about which is inside another
            # RETR_EXTERNAL only grabs the outer contours, not any inside other ones
            contours, hierarchy =cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            detections = []
            biggest_index = 0
            biggest_area = 0
            ind = 0
            for cnt in contours:
                #calc area and ignore small
                area = cv2.contourArea(cnt)
                if area > 150:
                    #cv2.drawContours(roi, [cnt], -1, (0, 255, 0), 2)
                    x,y,w,h = cv2.boundingRect(cnt)
                    detections.append([x,y,w,h])
                    area = w*h
                    if area > biggest_area:
                        biggest_area = area
                        biggest_index = ind
                    ind = ind + 1

            # draw rect around biggest contour
            #print(detections)
            if (len(detections) > 0):
                x,y,w,h = detections[biggest_index]
                objectlocation = (x+w/2-zx, zy-(y+h/2))
                frametracker = 1
                #print('x: ' + str(x) + ', w: ' + str(w))
            # tracking
            # a way to keep track of which object is which, but I only care about the
            # biggest object in scene.
            # boxes_ids = tracker.update(detections)
            # print(boxes_ids)	
                #head_angle = remap(float(x+(float(w)/2.0)), IN_MIN,IN_MAX,OUT_MIN,OUT_MAX)
            #cv2.imshow('frame', frame) # running imshow when launched from cron will break!
            # cv2.imshow("Mask",mask)
            # cv2.imshow('gray', gray)
            j=int(x+(w/2))
            k=int(y+(h/2))

            cv2.rectangle(roi, (x,y), (x+w, y+h), (0, 255, 0), 3)
            cv2.rectangle(roi, (j, k), (j+2, k+2), (0, 0, 255), 5)
            cv2.rectangle(roi, (zx, zy), (zx+2, zy+2), (0, 0, 255), 5)

            cv2.rectangle(image, (xbox1, ybox1), (xbox2, ybox2), (255, 0, 0), 3)
            if frametracker >= 15 and objectlocation != (0, 0) and go:
                print(objectlocation)
                
                ##
                
                #ser.write(b"move")
                cmd="move"
                print(1)
                arduino.write(cmd.encode())
                if (cmd == "move"):
                    #cmd=input("Enter X target : ")
                    cmd=str(objectlocation[0])
                    arduino.write(cmd.encode())
                    #cmd=input("Enter Y target : ")
                    cmd=str(objectlocation[1])
                    arduino.write(cmd.encode())
                    print(3)
                #time.sleep(0.1) #wait for arduino to answer
                print(2)
                #while arduino.inWaiting()==0: pass 
                answer=""
                while (answer != "finish"):
                    #print(4,"Arduino: ",answer)
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline().decode('utf-8').rstrip()
                        print(5, answer)
                    print("Arduino: ",answer)
                    arduino.flushInput() #remove data after reading
            else:
                print("stopped")
            
            cv2.imshow("Frame", image)       
            rawCapture.truncate(0)
            
            key = cv2.waitKey(1) # if 0 pause until a key is pressed
            if key == 27: #esacpe
                objectlocation = (0, 0)
                x, y, w, h = 0,0,0,0
                if go == True:
                    go = False
                    break
                go = True
            elif key == 32:
                zero()


        cv2.destroyAllWindows()
def zero():
    # script for proper zeroing
    #ser.write(b"zero")
    #wait()
    cmd="zero"
    time.sleep(1)
    arduino.write(cmd.encode())
    #time.sleep(0.1) #wait for arduino to answer
    #while arduino.inWaiting()==0: pass 
    answer=""
    
    while (answer != "finish"):
        #print(3)
        if  arduino.inWaiting()>0:
            answer=arduino.readline().decode('utf-8').rstrip()
            print("Arduino:",answer)
    
    print(answer)
    arduino.flushInput() #remove data after reading

def wait():
    line = ""
    while line != "finish":
        line = ser.readline().decode('utf-8').rstrip()

        
    



if __name__ == "__main__":
    #ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    #ser.reset_input_buffer()
    print('Running. Press CTRL-C to exit.')
    
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                main()
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")
    

