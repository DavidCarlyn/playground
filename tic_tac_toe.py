import tkinter as tk

class Token:
    def __init__(self, x, y, x2, y2, is_circle=True, thickness=2, padding=4):
        self.x1 = x + padding
        self.x2 = x2 - padding
        self.y1 = y + padding
        self.y2 = y2 - padding
        self.is_circle = is_circle
        self.thickness = thickness
    
    def draw(self, canvas):
        if self.is_circle:
            canvas.create_oval(self.x1, self.y1, self.x2, self.y2, fill="green")
            canvas.create_oval(self.x1 + self.thickness, self.y1 +self.thickness, self.x2 - self.thickness, self.y2 -self.thickness, fill="black")
        else:
            canvas.create_line(self.x1, self.y1, self.x2, self.y2, fill="green", width=self.thickness)
            canvas.create_line(self.x2, self.y1, self.x1, self.y2, fill="green", width=self.thickness)

class TicTacToe(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.canvas_width = 400
        self.canvas_height = 400
        self.is_circle = True
        self.create_widgets()

    def create_widgets(self):
        self.reset_button = tk.Button(self.master, text="Reset")
        self.reset_button["command"] = self.reset
        self.reset_button.pack()
        self.quit_button = tk.Button(self.master, text="Quit")
        self.quit_button["command"] = self.master.destroy
        self.quit_button.pack()
        self.game_label = tk.Label(self.master, text="Tic Tac Toe")
        self.game_label.pack()
        self.canvas = tk.Canvas(self.master, width=self.canvas_width, height=self.canvas_height, borderwidth=0, highlightthickness=0, bg="black")
        self.canvas.pack()
        self.create_board()

    def create_board(self):
        thickness = self.canvas_width * 0.02
        self.x1 = int((self.canvas_width / 3) - thickness / 2)
        self.canvas.create_line(self.x1, 0, self.x1, self.canvas_height, width=thickness, fill="green")
        self.x2 = int((self.canvas_width * (2/3)) - thickness / 2)
        self.canvas.create_line(self.x2, 0, self.x2, self.canvas_height, width=thickness, fill="green")
        self.y1 = int((self.canvas_height / 3) - thickness / 2)
        self.canvas.create_line(0, self.y1, self.canvas_width, self.y1, width=thickness, fill="green")
        self.y2 = int((self.canvas_height * (2/3)) - thickness / 2)
        self.canvas.create_line(0, self.y2, self.canvas_width, self.y2, width=thickness, fill="green")
        self.canvas.bind("<Button-1>", self.handle_mouse_click)

    def handle_mouse_click(self, event):
        print(f"({event.x}, {event.y})")
        x1 = 0
        x2 = 0
        if event.x < self.x1:
            x1 = 0
            x2 = self.x1
        elif event.x < self.x2:
            x1 = self.x1
            x2 = self.x2
        else:
            x1 = self.x2
            x2 = self.canvas_width

        y1 = 0
        y2 = 0
        if event.y < self.y1:
            y1 = 0
            y2 = self.y1
        elif event.y < self.y2:
            y1 = self.y1
            y2 = self.y2
        else:
            y1 = self.y2
            y2 = self.canvas_height

        token = Token(x1, y1, x2, y2, thickness=self.canvas_width * 0.02, is_circle=self.is_circle)
        token.draw(self.canvas)
        self.is_circle = not self.is_circle

    def reset(self):
        self.canvas.destroy()
        self.canvas = tk.Canvas(self.master, width=self.canvas_width, height=self.canvas_height, borderwidth=0, highlightthickness=0, bg="black")
        self.canvas.pack()
        self.create_board()