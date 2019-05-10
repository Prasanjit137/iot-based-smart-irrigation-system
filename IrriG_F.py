import telepot
import serial
import picamera
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

ser = serial.Serial('/dev/ttyACM0',9600) #COM port location and Baud rate

def operation(msg):
    global sendPhoto
    global chat_id

    chat_id = msg['chat']['id']
    command =  msg['text']

    print ("Message recieved from " + str(chat_id))

    if command =='Photo':
        sendPhoto = True

    elif command =='Start':
        bot.sendMessage(chat_id,'Welcome to IriG')
        
    elif command =='Value':
        while(ser.inWaiting() > 0):
            dat=ser.readline().decode().strip()
            print(dat)
        bot.sendMessage(chat_id,'Value : ' +str(dat))
    
    else:
        bot.sendMessage(chat_id,'Invalid command')
def capture():
    print ("Capturing photo...")
    camera = picamera.PiCamera()
    camera.capture('./photo.jpg')
    camera.close()
    print ("Sending photo to " + str(chat_id))
    bot.sendPhoto(chat_id, photo = open('./photo.jpg','rb'))

bot = telepot.Bot('API Token for the telegram Bot')
bot.message_loop(operation)

print ("Bot ready!")

sendPhoto = False

try:
    while True:
        if sendPhoto == True:
            sendPhoto = False
            capture()

except KeyboardInterrupt:
#while 0:
    GPIO.cleanup()

    
