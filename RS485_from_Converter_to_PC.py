import serial

try:
    # Open serial port
    ser = serial.Serial(
        port="COM4",
        baudrate=9600,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=1.0
    )
except serial.SerialException as e:
    print(f"Error: {e}")

print(f"Listening...")

while True:
    if ser.in_waiting:
        data = ser.read(ser.in_waiting)
        text = data.decode("utf-8")
        print(text.strip())

    
