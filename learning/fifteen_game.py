import tkinter as tk;
import random;


class Application(tk.Frame):
    def __init__(self, master = None):
        tk.Frame.__init__(self, master);
        self.grid();
        self.createWidgets();        

    def handle(self, number, neighbors):
        for n in neighbors:
            if self.buttons[n]["text"] == "":
                self.buttons[n]["text"] = self.buttons[number]["text"];
                self.buttons[number]["text"] = "";
                print("HANDLE CALLED!!!");
        
    
    def scramble(self):   
        for x in range(10000):
            self.functions[random.randint(0,15)];
    
    def createWidgets(self):

        self.functions = [lambda: self.handle(0, (2,5)), lambda: self.handle(1, (1,3,6)),
                          lambda: self.handle(2, (2,4,7)), lambda: self.handle(3, (3,8)),
                          lambda: self.handle(4, (1,6,9)), lambda: self.handle(5, (5,2,7,10)),
                          lambda: self.handle(6, (6,3,8,11)), lambda: self.handle(7, (7,4,12)),
                          lambda: self.handle(8, (5,10,13)), lambda: self.handle(9, (9,6,11,14)),
                          lambda: self.handle(10, (10,12,7,15)), lambda: self.handle(11, (8,16,11)),
                          lambda: self.handle(12, (9,14)), lambda: self.handle(13, (13,10,15)),
                          lambda: self.handle(14, (14,16,11)), lambda: self.handle(15, (12,15))];

        i = 0;
        self.buttons = [];    
        for x in range(4):
            for y in range(4):
                self.buttons.append(tk.Button(self, text = str(i + 1), command = self.functions[i-1], height = 3, width = 10));
                if x == 3 and y == 3:
                    self.buttons[-1]["text"] = "";
                    self.buttons[-1].grid(row = x, column = y);
                    break;
                    
                self.buttons[-1].grid(row = x, column = y);
                i = i + 1;
        
        
        #self.buttons[-1].grid
        self.scramble_btn = tk.Button(self, text = "scramble", command = self.scramble, height = 2, width = 10);
        self.scramble_btn.grid(row = 4, column = 0);
    
        
app = Application();

app.master.title("fifteen game");

app.mainloop();
