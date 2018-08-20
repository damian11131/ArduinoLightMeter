# A program that receives data from Arduino connected to port PORT_NAME.
# Data is sent in up to 5 bytes packages including newline byte.
# Newline character has to be sent at the end of data package


import serial
from sys import argv
from sys import exit

BAUD_RATE = 9600
PORT_NAME = "COM3"
filename = "measures.txt"

def main():
    global filename

    if len(argv) >= 2:
        filename = argv[1]

    try:
        with serial.Serial(PORT_NAME, BAUD_RATE) as ser:
            buff = ''
            while True:
                data = ser.readline().decode('utf-8').rstrip('r')
                buff += data

                count = 0
                for i in range(len(buff)):
                    if buff[i] == '\n':
                        count += 1
                if count >= 5:
                    with open(filename, 'w+') as measures:
                        measures.write(buff)
    except serial.SerialException:
        exit("You didn't connect Arduino")


if __name__ == "__main__":
    main()