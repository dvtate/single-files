#turtle fun
#DV Tate Testa

from turtle import *;

def draw_reg_poly(t_navn, dist, side_num, color, x0, y0, num_dash=0):
  '''draw regular polygon
  'params: turtle name, side length, number of sides, color, x, y, number of dashes.
  'returns: draws the described polygon
  '''
  num_dash = int(num_dash);
  if num_dash > 1:
    angle = ((side_num - 2.0) / side_num) * 180;
    angle = 180 - angle;
    dash_len = int(dist / (num_dash * 2));
    t_navn.color(color);
    t_navn.penup();
    t_navn.goto(x0, y0);
    t_navn.pendown();
    
    for i in range(side_num):
      t_navn.write(i);#
      for d in range(num_dash):
        t_navn.penup();
        t_navn.forward(dash_len);
        t_navn.pendown();
        t_navn.forward(dash_len);
      t_navn.left(angle);
  else: #no dashes
    if num_dash != 0:
      t_navn.color("red");
      t_navn.write("*invalid dash number");
    t_navn.color(color);
    angle = ((side_num - 2.0) / side_num) * 180;
    angle = 180 - angle;
    t_navn.color(color);
    t_navn.penup();
    t_navn.goto(x0, y0);
    t_navn.pendown();
    for i in range(side_num):
      t_navn.write(i); # vertex number
      t_navn.forward(dist);
      t_navn.left(angle);
  return;


def paint_canvas(window_object,background_color):
  #change the window background color
  window_object.bgcolor(background_color);
  return;
  
def draw_rectangle(t_obj, x0, y0, x1, y1, color, pen_size):
  '''draw a rect that connects two points
  'params: turtle object, x1, y1, x2, y2, color, pen thickness
  'returns: graphics
  '''
  t_obj.color(color);
  t_obj.pensize(pen_size);
  t_obj.penup();
  t_obj.goto(x0, y0); #start at 1st point
  t_obj.pendown();
  t_obj.goto(x0, y1); #move to 2nd point
  t_obj.goto(x1, y1); #move to 3rd point
  t_obj.goto(x1, y0); #move to 4th point
  t_obj.goto(x0, y0); #go back to start
  return;
def draw_x(t_obj, x0, y0, x1, y1, color, pen_size):
  '''draw an x between two points
  'params: turtle object, x1, y1, x2, y2, color, pen thickness
  'returns: graphics
  '''
  t_obj.color(color);
  t_obj.pensize(pen_size);
  t_obj.penup();
  t_obj.goto(x0, y0); # start @1st point
  t_obj.pendown();
  t_obj.goto(x1, y1); # opposite corner
  t_obj.penup();
  t_obj.goto(x0, y1); # start @1st point
  t_obj.pendown();
  t_obj.goto(x1, y0); # opposite corner
  return;
def create_masterpiece():
  '''combines functions
  'Params:
  '	None
  'Returns:
  '	Graphics
  '''
  wn = Screen();
  wn.bgcolor('lightgreen');
  # when you click on the graphics window, the program stops and the window is cleared
  wn.exitonclick() # this must be used to stop your program OR runaway program
  
  # call the Turtle constructor method to construct/create a turtle object named t
  t = Turtle();
  t.pensize(2);# set the width of the pen
  t.speed(200);# speed up the drawing
  paint_canvas(wn, 'hotpink');
  draw_rectangle(t, -200, -200, 200, 200, 'red', 20);
  #draw_rectangle(t, -100, -80, 90, 150, 'green', 1);
  draw_x(t, -200, -200, 200, 200, 'green', 3);
  draw_reg_poly(t, 20, 6, 'blue', 50, 5, 3);
  draw_reg_poly(t, 20, 6, 'gold', -100, -5);
  draw_reg_poly(t, 25, 5, 'purple', 2, 50, 4);
  draw_reg_poly(t, 30, 3, 'brown', -10, -50, 3);
  return;
 
#------------MAIN:
create_masterpiece();
