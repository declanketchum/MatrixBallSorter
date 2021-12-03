"""
SerialToGRBL.py

Currently connects to GRBL board and drives the
X-axis stepper motor to user-requested positions. 

Author: Luke Raus
"""

import serial
import serial.tools.list_ports


def main():
    baud = 115200
    grbl_port = scan_for_grbl_board()
    ard_port = scan_for_servo_arduino()

    gser = serial.Serial(port = grbl_port, baudrate = baud)
    aser = serial.Serial(port = ard_port, baudrate = baud)

    inp = 'a'
    while not inp == '':
        inp = input('type X or Y followed by a number to drive stepper, or type b/w to drop a ball: ')
        
        first = inp[0].lower()

        if first == 'x':
            gser.write(('g0 x' + inp[1:] + '\n').encode('utf-8'))
        elif first == 'y':
            gser.write(('g0 y' + inp[1:] + '\n').encode('utf-8'))
        elif first == 'b':
            aser.write(('0\n').encode('utf-8'))
        elif first == 'w':
            aser.write(('1\n').encode('utf-8'))


def scan_for_grbl_board():
    """
    Returns string of port name for connected GRBL board.
    """
    ports = serial.tools.list_ports.comports()

    for p in ports:
        if p.pid == 29987 and p.vid == 6790:
            return(p.device)

    raise Exception('GRBL device not found, unable to initialize. Check USB connection.')


def scan_for_servo_arduino():
    """
    Returns string of port name for connected servo Arduino.
    """
    ports = serial.tools.list_ports.comports()

    for p in ports:
        if p.pid == 67 and p.vid == 9025:
            return(p.device)

    raise Exception('Servo Arduino not found, unable to initialize. Check USB connection.')


if __name__ == '__main__':
    main()
