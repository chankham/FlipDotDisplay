import sys
import PIL.Image
import serial

def proc(arg):
    #print("ptocessing " + arg)
    # Read the input image and convert it to a 30x15 pixel grayscale image.
    image = PIL.Image.open('/home/pi/Desktop/testingServer/FlipDotWebsite/public/real_image/' + arg.lower())
    image = image.resize((30, 15), resample=PIL.Image.NEAREST)

    # One-dimensional binary output array.
    output = [0] * image.width * image.height

    # Read each input pixel and add a 0 or 1 to the output array.
    for y in range(image.height):
        for x in range(image.width):
            color = image.getpixel((x, y))
            value = 1 if color[0] == 0 else 0
            output[y * image.width + x] = str(value)
            
    # Debug print.
    for y in range(image.height):
        for x in range(image.width):
           
            print(output[y * image.width + x], end='')
        print()
    print()
    #print(dataToSendBack)
    #print((''.join(output)))
##    window = [[], [], [], [], []]
##    for x in range(15):
##        for y in range(6):
##            window[y]+=(output[y*5+x*30: y*5+x*30 + 5])
##    ids = []
##    print(window)
##    for i in range(6):
##        ids.append( i+1);
##    for i in range(2):
##        s = "#" + str(ids[i]) + " " + ''.join(window[i]) 
##        print(s)
    
    return output


def convert():
    o = []
##    if len(sys.argv) == 1:
##        print("Usage: ./convert <image(s)>")
##        return
##        
##    else:    
    #for arg in sys.argv[1:]:
    o.append(proc('christmas_tree0.png'))
    print(o)
    return o
def splitByWindow():
    s = convert()
    wind= []
    for t in s:
        window = [[], [], [], [], [], []]
        for x in range(15):
            for y in range(6):
                window[y]+=(t[y*5+x*30: y*5+x*30 + 5])
        print(window)
        wind.append(window)
    
    return wind

def sendToArduinos():
    #if len(sys.argv) > 1 and sys.argv[1] == "clock":
##    from datetime import datetime as dt
##    prevMin = dt.now().minute
##    serialport = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)
##    while True:
##        if dt.now().minute != prevMin:
##            prevMin = dt.now().minute
##            curr = (dt.now().hour % 12) * 100
##            curr += dt.now().minute
##            print("Sending to Arduino: ", curr)
##            serialport.write(str.encode(str(curr)))
##            while True:
##                s = serialport.readline()
##                print(s)
##                if s.decode("utf-8").strip() == str(curr):
##                    print("Confirmed")
##                    break
##            
##    if True:
##        1
##    else:
    ids = []
    data = splitByWindow()
    for i in range(6):
        ids.append( i+1);
    serialport = serial.Serial("/dev/ttyUSB0", baudrate=9600, timeout=3.0)
    serialport.flushInput()
    serialport.write("stating".encode());
    print(serialport.readline())
    #while True:
    import time
    #print(data)

    for d in data:
        for i in range(6):
            
            s = "#" + str(ids[i]) + " " + ''.join(d[i]) 
            print(s)
            print(serialport.write(s.encode()))
            print(serialport.write(str(ids[i]).encode()+"\n".encode("utf-8")))
            p=b''
            while("Processing" not in p.decode()):
                p=serialport.readline()
                print(p)
            #time.sleep(1)
    ws=b''
    while ws.decode().strip() != "Dsone":
        print("here")
        ws=serialport.readline()
        print(ws)
    serialport.close()
    print("done transmitting")
    
if __name__ == "__main__":
    
## 
##    
    try:
        sendToArduinos()
        sys.stdout.flush()
    except:
        traceback.print_stack()
        print("error")
        #sys.stdout.flush()

   
