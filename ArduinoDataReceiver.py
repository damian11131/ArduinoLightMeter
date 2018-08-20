import serial


BAUD_RATE = 9600
PORT_NAME = "COM3"
FILENAME = "measures.txt"

def main():
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
                with open(FILENAME, 'w+') as measures:
                    measures.write(buff)


if __name__ == "__main__":
    main()