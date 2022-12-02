from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import RPi.GPIO as gpio

gpio.setmode(gpio.BCM)
gpio.setup(3, gpio.IN)




xbox1 = 220
xbox2 = 410

ybox1 = 20
ybox2 = 480

objectlocation = (0, 0)


def main():
    
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.framerate = 32
    rawCapture = PiRGBArray(camera, size=(640, 480))

    time.sleep(0.1)
    #sys.stdout = open("/home/pi/Documents/myLog.log","w")
    #sys.stderr = open("/home/pi/Documents/myLogErr.log","w")

    IN_MIN = 30.0
    IN_MAX = 160.0
    OUT_MIN = 160.0
    OUT_MAX = 30.0

    head_angle = 90.0
    head_angle_ave = 90.0
    head_angle_alpha = 0.25


    # kit.servo[0].angle = 90
    # tracker = EuclideanDistTracker() # could be used to track multiple objects


    object_detector = cv2.createBackgroundSubtractorMOG2(history=10, varThreshold=5)
    # threshold higher means it picks up fewer false positives, history takes into account past frames?

    frametracker = 1

    
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

            objectlocation = ((x+w)/2, (y+h)/2)
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
        cv2.rectangle(roi, (x,y), (x+w, y+h), (0, 255, 0), 3)
        cv2.rectangle(image, (xbox1, ybox1), (xbox2, ybox2), (255, 0, 0), 3)
        
        cv2.imshow("Frame", image)       
        rawCapture.truncate(0)
        
        key = cv2.waitKey(1) # if 0 pause until a key is pressed
        if key == 27: #esacpe
            break

    cv2.destroyAllWindows()

# map one range to another
def remap(x, in_min, in_max, out_min, out_max):

    x_diff = x - in_min

    out_range = out_max - out_min

    in_range = in_max - in_min
    temp_out = x_diff * out_range/in_range + out_min
    #print('x: ' + str(x) + ', temp_out: ' + str(temp_out))
    if out_max < out_min:
        temp = out_max
        out_max = out_min
        out_min = temp

    if temp_out > out_max:
        return out_max
    elif temp_out < out_min:
        return out_min
    else:
        return temp_out




if __name__ == "__main__":
    while True:
        if  gpio.input(3):
            main()

