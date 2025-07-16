import tkinter as tk;
import random;
import time;


def randomColor():
    return "#%03x" % random.randint(0, 0xFFF);


class BouncyBall(object):

    
    def __init__(self, canvas, width, height, color, outline = None):
        self.canvas = canvas;        
        self.xv = random.randint(-10, 10);
        self.yv = random.randint(-10, 10);        
    
        while self.xv == 0:
            self.xv = random.randint(-10, 10);
        while self.yv == 0:
            self.yv = random.randint(-10, 10);
        
        x = random.randint(10, width - 10);
        y = random.randint(10, height - 10);
        r = random.randint(5, 25);

        self.rect = canvas.create_oval(x - r, y - r, x + r, y + r, fill = randomColor());
        
    def move(self):
        self.canvas.move(self.rect, self.xv, self.yv);
        coords = self.canvas.coords(self.rect)
        if coords[0] <= 0 or coords[2] >= WIDTH:
            self.xv = -self.xv;
        if coords[1] <= 0 or coords[3] >= WIDTH:
            self.yv = -self.yv;

                    
                
                

WIDTH = HEIGHT = 400;

window= tk.Tk();


canvas = tk.Canvas(window, width = WIDTH, height = HEIGHT, bg = "white");
canvas.grid();

window.wm_title("XD");


balls = [];
for i in range(100):
    balls.append(BouncyBall(canvas, WIDTH, HEIGHT, randomColor()));


d_counter = 0;
    
while True:
     
    for ball in balls:
        ball.move();    

    d_counter += 1;
    
    window.wm_title("XD" + 'D' * (d_counter % 25));
    
    
    
    window.update();
    time.sleep(0.01);
    
