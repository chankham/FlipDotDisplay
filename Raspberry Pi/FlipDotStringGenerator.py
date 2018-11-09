import sys
import PIL.Image
import serial

def convert():
    if len(sys.argv) == 1:
        print("Usage: ./convert <image(s)>")
        return

    for arg in sys.argv[1:]:
        # Read the input image and convert it to a 30x15 pixel grayscale image.
        image = PIL.Image.open(arg)
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
        return output

def splitByWindow():
    s = convert()
   
    window = [[], [], [], [], [], []]
    for x in range(15):
        for y in range(6):
            window[y]+=(s[y*5+x*30: y*5+x*30 + 5])
            
    return window

def sendToArduinos():
    ids = []
    data = splitByWindow()
    for i in range(6):
        ids.append( i+1);
    #serialport = serial.Serial("/dev/serial0", baudrate=9600, timeout=3.0)
    #while True:
    for i in range(6):
        s = "#" + str(ids[i]) + " " + ''.join(data[i]) 
        print(s)
    
if __name__ == "__main__":
    sendToArduinos()

