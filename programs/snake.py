import tkinter as tk;
import random;
import time;



WIDTH = HEIGHT = 800;
POPULATION = 200;

# returns a hex color between #000 and #FFF in the form of a string
def randomColor():
    return ("#%03x" % random.randint(0, 0xFFF));
    



class Ball:
    # constructor
    def __init__(self, canvas, x, y, r):
        self.canvas = canvas;
        self.shape = canvas.create_oval(x - r, y - r, x + r, y + r, fill = randomColor());
        self.xv = self.yv = 0;
        self.x = x;
        self.y = y;
        
    def move(self):
        self.x += self.xv;
        self.y += self.yv;
        self.canvas.move(self.shape, self.xv, self.yv);
        


window = tk.Tk();


canvas = tk.Canvas(window, width = WIDTH, height = HEIGHT, bg = "white");
canvas.pack();
window.wm_title("Snake");

balls = [];
for count in range(POPULATION):
    x = random.randint(0, WIDTH);
    y = random.randint(0, HEIGHT);
    r = random.randint(1, 10);
    balls.append(Ball(canvas, x, y, r));

def chase(event):
    xm, ym = event.x, event.y;

    for t in range(POPULATION):
        if (t == 0):
            balls[t].xv = 0.2 * (xm - balls[t].x);
            balls[t].yv = 0.2 * (ym - balls[t].y);
        else:
            balls[t].xv = 0.2 * (balls[t - 1].x - balls[t].x);
            balls[t].yv = 0.2 * (balls[t - 1].y - balls[t].y);
        balls[t].move();
    window.update();
    
    
canvas.bind("<Motion>", chase);


window.mainloop();          
