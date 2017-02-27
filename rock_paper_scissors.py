## rock paper scissors
## DV Tate Testa
import random;


def randomChoice():
  options = ["rock","paper","scissors"];
  rChoice = random.randint(0,2);
  return(options[rChoice]);


# main
print("r=rock\np=paper\ns=scissors\nq=quit\n"); # explain game
hands = {'r':'rock', 'p':'paper', 's':'scissors'}; # what are choices what do the mean
again = True;
while again:
  hand = raw_input('Your Choice:');
  comp = randomChoice();
  if hands.has_key(hand) and hands[hand]==comp:
    print('sorry, we both chose %s'%(comp));
  elif hand == 'r':
    if comp == 'scissors':
      print("Your rock beat my %s"%(comp));
    else:
      print('My %s beat your %s'%(comp,hands[hand]));
  elif hand == 'p':
    if comp == 'rock':
      print("Your paper beat my %s"%(comp));
    else:
      print('My %s beat your %s'%(comp,hands[hand]));
  elif hand == 's':
    if comp == 'paper':
      print("Your scissors beat my %s"%(comp));
    else:
      print('My %s beat your %s'%(comp,hands[hand]));
  elif hand == 'q':
    again = False;
    print("GAME OVER");
  elif hand == '':
    print("Can't you type?");
  else:
    print("Sorry, I didn't understand %s."%(hand));
