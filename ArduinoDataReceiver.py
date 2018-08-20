# A program that receives data from Arduino connected to port PORT_NAME.
# Data is sent in up to 5 bytes packages including newline byte.
# Newline character has to be sent at the end of data package


import serial
from sys import argv
from sys import exit
from time import asctime

BAUD_RATE = 9600
PORT_NAME = "COM3"

def main():
    filename = "measures.txt"

    if len(argv) >= 2:
        filename = argv[1]

    try:
        with serial.Serial(PORT_NAME, BAUD_RATE) as ser:
            buff = ''
            count = 0
            while True:
                data = ser.readline().decode('utf-8').rstrip('r')
                count += 1
                buff += asctime() + ': ' + data
				
                if count >= 5:
                    count = 0
                    with open(filename, 'w+') as measures:
                        measures.write(buff)
    except serial.SerialException:
        exit("Connection problem")


if __name__ == "__main__":
    main()