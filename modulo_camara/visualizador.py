import cv2
import serial

# Abre el puerto serial
ser = serial.Serial('COM3', 115200)

# Crea una ventana de OpenCV para mostrar la imagen
cv2.namedWindow('Image', cv2.WINDOW_NORMAL)

while True:
    # Lee los datos de la imagen desde el puerto serial
    data = ser.read(160 * 120)

    # Convierte los datos a una matriz NumPy de 120x160 elementos
    img = bytearray(data)
    img = np.array(img).reshape(120, 160)

    # Convierte la imagen a color y la muestra en la ventana
    img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    cv2.imshow('Image', img)
    cv2.waitKey(1)
