import tkinter as tk

class MainWindow(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()
        
    def create_widgets(self):
        self.button = tk.Button(self)
        self.button["text"] = "Create Window!"
        self.button["command"] = self.command
        self.button.pack()

    def command(self):
        new_window = Window(master=self.master)

class Window(tk.Toplevel):
    def __init__(self, master=None):
        super().__init__(master=master)
        self.master = master
        self.create_widgets()
        
    def create_widgets(self):
        self.button = tk.Button(self)
        self.button["text"] = "Click Here!"
        self.button["command"] = self.command
        self.button.pack()

    def close(self):
        self.destroy()

    def command(self):
        print("Button has been pushed!")