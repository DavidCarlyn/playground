import tkinter as tk
from window import Window
from tic_tac_toe import TicTacToe

class MainWindow(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()
        
    def create_widgets(self):
        self.games = GameMenu(self.master)
        self.games.pack()

        self.quit_button = tk.Button(self)
        self.quit_button["text"] = "Quit"
        self.quit_button["command"] = self.close
        self.quit_button.pack()

    def close(self):
        self.master.destroy()

class GameMenu(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.create_widgets()

    def create_widgets(self):
        tk.Button(self, text="Play Tic Tac Toe", command=self.play_game).pack()
        tk.Button(self, text="Print Hi", command=lambda: print("hi")).pack()

    def play_game(self):
        self.game_window = Window(self.master)
        self.tic_tac_toe_panel = TicTacToe(self.game_window)


class App(tk.Frame):
    def __init__(self):
        self.root = tk.Tk()
        self.main_window = MainWindow(master=self.root)

    def run(self):
        self.main_window.mainloop()