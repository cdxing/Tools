import tkinter

from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg, NavigationToolbar2Tk)
# Implement the default Matplotlib key bindings.
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure
from PIL import Image
import math

import numpy as np
import matplotlib.pyplot as plt
import sympy

root = tkinter.Tk()
root.title('FXT Setup - FXT 7.2 GeV Run18')
root.geometry("1024x768")

my_canvas = tkinter.Canvas(root, width=1024, height=768, bg="white")
my_canvas.pack(pady=160)

x_offset = 180
y_offset = 80
# Create Line
# my_canvas.create_line(x1, y1, x2, y2, fill="color")
# my_canvas.create_line(0, 100, 300, 100, fill="red")
# Create Rectangle
# my_canvas.create_rectangle(x1, y1, x2, y2, fill="color")
# Rectangle: (x1, y1) Top Left
# Rectangle: (x2, y2) Bottom Right
my_canvas.create_rectangle(200+x_offset, 60+y_offset, 600+x_offset, 190+y_offset, fill="lightgray") # TPC
my_canvas.create_rectangle(190+x_offset, 30+y_offset, 610+x_offset, 40+y_offset, fill="orange") # TOF
my_canvas.create_rectangle(22+x_offset, 160+y_offset, 25+x_offset, 245+y_offset, fill="magenta") # EPD
# my_canvas.create_rectangle(127+x_offset, 30+y_offset, 130+x_offset, 140+y_offset, fill="blue") # eTOF
# my_canvas.create_rectangle(200+x_offset, 130+y_offset, 600+x_offset, 190+y_offset, fill="pink") # iTPC
my_canvas.create_text(310+x_offset, 100+y_offset, width=200, fill="blue", text="Time Projection Chamber (TPC)")
my_canvas.create_text(310+x_offset, 20+y_offset, width=200, fill="black", text="Time Of Flight (TOF)")
my_canvas.create_text(22+x_offset, 150+y_offset, width=200, fill="magenta", text="Event Plane Detector (EPD)")
# my_canvas.create_text(120+x_offset, 25+y_offset, width=200, fill="black", text="endcap Time Of Flight (eTOF)")

my_canvas.create_line(600+x_offset, 0+y_offset, 600+x_offset, 250+y_offset, arrow="first", fill="black") # Target
my_canvas.create_text(600+x_offset, 260+y_offset, width=200, fill="black", text="200")
my_canvas.create_text(610+x_offset, 280+y_offset, width=200, fill="black", text="West")
# my_canvas.create_text(630+x_offset, 10+y_offset, width=200, fill="black", text="eta = 0")
my_canvas.create_line(400+x_offset, 0+y_offset, 400+x_offset, 250+y_offset, arrow="first", fill="black") # TPC Center
my_canvas.create_text(400+x_offset, 260+y_offset, width=200, fill="black", text="z=0")
my_canvas.create_text(390+x_offset, 200+y_offset, width=200, fill="black", text="60")
my_canvas.create_text(385+x_offset, 70+y_offset, width=200, fill="black", text="190")
my_canvas.create_text(200+x_offset, 260+y_offset, width=200, fill="black", text="-200")
my_canvas.create_text(25+x_offset, 260+y_offset, width=200, fill="black", text="-375")
my_canvas.create_text(20+x_offset, 280+y_offset, width=200, fill="black", text="East")
my_canvas.create_text(445+x_offset, 20+y_offset, width=200, fill="black", text="Radius (cm)")
my_canvas.create_line(-30+x_offset, 250+y_offset, 600+x_offset, 250+y_offset, arrow="first", fill="black") # Beam Line
my_canvas.create_text(-20+x_offset, 260+y_offset, width=200, fill="black", text="(cm)")
my_canvas.create_text(450+x_offset, 290+y_offset, width=210, fill="black", text="Target located at Z = +200 cm")
angle_in_radians = 2.87782
line_length = 500
center_x = 600
center_y = 250
end_x = center_x + line_length * math.cos(angle_in_radians)
end_y = center_y - line_length * math.sin(angle_in_radians)
my_canvas.create_line(center_x+x_offset, center_y+y_offset, end_x+x_offset, end_y+y_offset, arrow="last", fill="red") # 7.2 GeV eta_CM: -2.02
my_canvas.create_line(center_x+x_offset, center_y+y_offset, 500+x_offset, 280+y_offset, arrow="first", fill="blue") # 7.2 GeV eta_CM: -2.02
# my_canvas.create_text(400+x_offset, 180+y_offset, width=200, angle=165+180, fill="red", text="7.2 GeV #eta_{CM} = -2.02")



my_label = tkinter.Label(root, text='41' + u'\u00b0', font=("Helvetica", 32)).pack(pady=10+y_offset)
# sp_sqrt.plot()
# embedding matplotlib to tkinter
# fig = Figure(figsize=(5, 4), dpi=100)
# t = np.arange(0, 3, .01)
# fig.add_subplot(111).plot(t, 2 * np.sin(2 * np.pi * t))
#
# my_canvas = FigureCanvasTkAgg(fig, master=root)  # A tk.DrawingArea.
# my_canvas.draw()
#
# # pack_toolbar=False will make it easier to use a layout manager later on.
# toolbar = NavigationToolbar2Tk(my_canvas, root, pack_toolbar=False)
# toolbar.update()
#
#
# my_canvas.mpl_connect(
#     "key_press_event", lambda event: print(f"you pressed {event.key}"))
# my_canvas.mpl_connect("key_press_event", key_press_handler)
#
# button = tkinter.Button(master=root, text="Quit", command=root.quit)

# Packing order is important. Widgets are processed sequentially and if there
# is no space left, because the window is too small, they are not displayed.
# The canvas is rather flexible in its size, so we pack it last which makes
# sure the UI controls are displayed as long as possible.
# button.pack(side=tkinter.BOTTOM)
# toolbar.pack(side=tkinter.BOTTOM, fill=tkinter.X)
# my_canvas.get_tk_widget().pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=1)
#



root.mainloop()
