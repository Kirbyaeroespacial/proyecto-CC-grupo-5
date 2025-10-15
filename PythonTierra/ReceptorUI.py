import serial
from tkinter import *
from tkinter import font

# --- Serial setup ---
device = 'COM7'
mySerial = serial.Serial(device, 9600, timeout=1)

# --- Button callbacks ---
def iniClick():
    mensaje = 'i\n'
    mySerial.write(mensaje.encode('utf-8'))


def stopClick():
    mensaje = 'p\n'
    mySerial.write(mensaje.encode('utf-8'))

def reanClick():
    mensaje = 'r\n'
    mySerial.write(mensaje.encode('utf-8'))

# --- Main window ---
window = Tk()
window.title("Control Satélite")
window.geometry("850x300")
window.configure(bg="#1e1e2f")  # Fondo oscuro
window.resizable(False, False)

# --- Fonts ---
title_font = font.Font(family="Inter", size=22, weight="bold")
button_font = font.Font(family="Inter", size=14, weight="bold")

# --- Title Label ---
tituloLabel = Label(
    window, text="Control Satélite", font=title_font, 
    bg="#1e1e2f", fg="#ffffff"
)
tituloLabel.pack(pady=(30, 40))

# --- Frame for buttons ---
btn_frame = Frame(window, bg="#1e1e2f")
btn_frame.pack(pady=10)

# --- Style helper ---
def create_btn(master, text, command):
    return Button(
        master, text=text, command=command,
        font=button_font, bg="#4b6cb7", fg="white",
        activebackground="#6b8dd6", activeforeground="white",
        bd=0, relief=RIDGE, padx=20, pady=15, width=18
    )

# --- Buttons (same size) ---
IniButton = create_btn(btn_frame, "Iniciar transmisión", iniClick)
stopButton = create_btn(btn_frame, "Parar transmisión", stopClick)
reanButton = create_btn(btn_frame, "Reanudar", reanClick)

# --- Place buttons evenly ---
IniButton.grid(row=0, column=0, padx=10)
stopButton.grid(row=0, column=1, padx=10)
reanButton.grid(row=0, column=2, padx=10)

# --- Run the app ---
window.mainloop()
