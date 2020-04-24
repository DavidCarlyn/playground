import tkinter as tk

class Chat(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.create_widgets()

    def create_widgets(self):
        lbl = tk.Label(self.master, text="Chat")
        lbl.pack()

        self.text_component = tk.Frame(self.master)
        
        self.scroll_bar = tk.Scrollbar(self.text_component)
        self.scroll_bar.pack(side=tk.RIGHT, fill=tk.Y)

        self.chat_log = tk.Listbox(self.text_component)
        self.chat_log.pack(side=tk.LEFT, fill=tk.BOTH)

        self.scroll_bar.config(command=self.chat_log.yview)

        self.text_component.pack()

        self.log_button = tk.Button(self.master, text="Send", command=self.send_text)
        self.log_button.pack(side=tk.LEFT)

        self.text_entry = tk.Entry(self.master)
        self.text_entry.pack(side=tk.RIGHT, fill=tk.X)

    def send_text(self):
        self.chat_log.insert(tk.END, self.text_entry.get())
        self.text_entry.delete(0, tk.END)
        self.chat_log.see(self.chat_log.size())