import tkinter as tk

class Window(tk.Toplevel):
    def __init__(self, master=None):
        super().__init__(master=master)
        self.master = master

    def close(self):
        self.destroy()