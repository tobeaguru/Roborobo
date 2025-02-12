import sys
import cv2
import requests
import numpy as np
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QGridLayout, QVBoxLayout, QHBoxLayout, QLabel
from PyQt5.QtCore import QThread, pyqtSignal, Qt
from PyQt5.QtGui import QImage, QPixmap
import serial

class VideoThread(QThread):
    change_pixmap_signal = pyqtSignal(np.ndarray)

    def run(self):
        url = "http://192.168.4.1:81/stream"
        stream = requests.get(url, stream=True)
        bytes = b''

        for chunk in stream.iter_content(chunk_size=1024):
            bytes += chunk
            a = bytes.find(b'\xff\xd8')
            b = bytes.find(b'\xff\xd9')
            if a != -1 and b != -1:
                jpg = bytes[a:b+2]
                bytes = bytes[b+2:]
                img = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
                if img is not None:
                    self.change_pixmap_signal.emit(img)

class DirectionController(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.ser = serial.Serial('COM3', 115200)  # Adjust COM port and baud rate as needed

    def initUI(self):
        main_layout = QHBoxLayout()
        
        # Video frame
        self.video_label = QLabel()
        self.video_label.setFixedSize(640, 480)
        main_layout.addWidget(self.video_label)

        # Direction buttons
        grid = QGridLayout()
        directions = [
            ('Up-Left', 0, 0, 'q'),
            ('Up', 0, 1, 'w'),
            ('Up-Right', 0, 2, 'e'),
            ('Left', 1, 0, 'a'),
            ('Stop', 1, 1, 's'),
            ('Right', 1, 2, 'd'),
            ('Down-Left', 2, 0, 'z'),
            ('Down', 2, 1, 'x'),
            ('Down-Right', 2, 2, 'c')
        ]

        for text, row, col, code in directions:
            button = QPushButton(text)
            button.clicked.connect(lambda _, c=code: self.send_direction(c))
            grid.addWidget(button, row, col)
            button.setShortcut(code)

        main_layout.addLayout(grid)
        self.setLayout(main_layout)
        self.setWindowTitle('Controller with Video Stream')
        self.show()

        # Start video thread
        self.thread = VideoThread()
        self.thread.change_pixmap_signal.connect(self.update_image)
        self.thread.start()

    def send_direction(self, code):
        self.ser.write(code.encode())

    def update_image(self, cv_img):
        qt_img = self.convert_cv_qt(cv_img)
        self.video_label.setPixmap(qt_img)

    def convert_cv_qt(self, cv_img):
        rgb_image = cv2.cvtColor(cv_img, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb_image.shape
        bytes_per_line = ch * w
        convert_to_Qt_format = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
        p = convert_to_Qt_format.scaled(self.video_label.width(), self.video_label.height(), Qt.KeepAspectRatio)
        return QPixmap.fromImage(p)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = DirectionController()
    sys.exit(app.exec_())