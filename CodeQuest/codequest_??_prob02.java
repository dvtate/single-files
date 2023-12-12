import java.util.Scanner;
import java.io.*;

public class Prob02{

  public static void processHand(String hand)
  {
    char suit;
    //Suits
    int numClubs = 0;
    int numSpades = 0;
    int numHearts = 0;
    int numDiamonds = 0;
    int retvalLength;
    int cardLength;
    int numTwo = 0;
    int numThree = 0;
    int numFour = 0;
    int numFive = 0;
    int numSix = 0;
    int numSeven = 0; 
    int numEight = 0;
    int numNine = 0;
    int numTen = 0;
    int numJacks = 0;
    int numQueens = 0;
    int numKings = 0;
    int numAces = 0; 
    for(String card: hand.split(" "))
    {
       
      //System.out.println(retval);
      //System.out.println(card.length()); 
      
      // this is where we need to count up the card values
      
      
      cardLength = card.length();
      suit = card.charAt(cardLength - 1);
      char cardValue = card.charAt(cardLength - 2);
      switch(suit)
      {
        case 'H': case 'h': numHearts++; break;
        case 'D': case 'd': numDiamonds++; break;
        case 'S': case 's': numSpades++; break;
        case 'C': case 'c': numClubs++; break;
      }
      switch(cardValue)
      {
        case 'A': numAces++; break;
        case '2': numTwo++; break;
        case '3': numThree++; break;
        case '4': numFour++; break;
        case '5': numFive++; break;
        case '6': numSix++; break;
        case '7': numSeven++; break;
        case '8': numEight++; break;
        case '9': numNine++; break;
        case '0': numTen++; break;
        case 'J': numJacks++; break;
        case 'Q': numQueens++; break;
        case 'K': numKings++; break;
      }
     
    
   } 
  int red = numHearts + numDiamonds;
    int black = numSpades + numClubs;
    System.out.println("Red " + red);
    System.out.println("Black " + black);
    System.out.println("Hearts " + numHearts);
    System.out.println("Clubs " + numClubs);
    System.out.println("Diamonds " + numDiamonds);
    System.out.println("Spades " + numSpades);
    System.out.println("2- " + numTwo);
    System.out.println("3- " + numThree);
    System.out.println("4- " + numFour);
    System.out.println("5- " + numFive);
    System.out.println("6- " + numSix);
    System.out.println("7- " + numSeven);
    System.out.println("8- " + numEight);
    System.out.println("9- " + numNine);
    System.out.println("10- " + numTen);
    System.out.println("Jacks- " + numJacks);
    System.out.println("Queens- " + numQueens);
    System.out.println("Kings- " + numKings);
  }
  public static void main(String[] args)throws IOException
  {
    //Scanner keyboard = new Scanner(System.in);
    //String fileName = keyboard.nextLine();
    File myFile = new File("Prob02.in.txt");
    System.out.println("File Exists? " + myFile.exists());
    System.out.println("myFile");
    Scanner inputFile = new Scanner(myFile);
    String line;
    int handNumber = 1;
    while(inputFile.hasNext())
    {
      line = inputFile.nextLine();
      //System.out.println(line);
      System.out.println(" ");
      System.out.println("HAND " + handNumber++);
      processHand(line);
      
      
     
      }
    }
    
  }


