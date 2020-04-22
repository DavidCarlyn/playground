import tkinter as tk
from window import Window
from window import MainWindow

class App(tk.Frame):
    def __init__(self):
        self.root = tk.Tk()
        self.main_window = MainWindow(master=self.root)

    def run(self):
        self.main_window.mainloop()