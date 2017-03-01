import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;//arrayList and .sort()


/*numbers given in order (ascending and/or descending)
*DV Tate Testa
*3-17-2015
*/
public class Project3{

 public static String valleySortLine(String line) {
  ArrayList<Integer> nums = new ArrayList<Integer>();
  for (String ridge : line.split(" ")) // process/re-sort
   nums.add(Integer.parseInt(ridge));

  Collections.sort(nums); // sort in ascending order
  Collections.reverse(nums); // put into descending order
  //Integer[] finishedArr = new Integer[nums.size()];
  ArrayList<Integer> left = new ArrayList<Integer>();
  ArrayList<Integer> right = new ArrayList<Integer>();
  for (int i = 0; i <= nums.size() - 1; i++) { // valey sort
   if (i % 2 == 0)
    left.add(nums.get(i));
   else
    right.add(nums.get(i));
  }
  Collections.reverse(right);
  for (int i = 0; i <= right.size() - 1; i++)
   left.add(right.get(i));

  // convert to string
  String result = "";
  for (int i = 0; i <= nums.size() - 1; i++) {
   result += left.get(i);
   result += " ";
  }
  return result;
 }
 // MAIN:
 public static void main(String[] args) throws IOException {
  //Scanner keyboard = new Scanner(System.in);
  //String fileName = keyboard.nextLine();
  File myFile = new File("Prob03.in.txt"); // get file
  System.out.println("File Exists? " + myFile.exists());
  System.out.println(myFile);
  Scanner inputFile = new Scanner(myFile);

  String line;
  while(inputFile.hasNext()) {
   line = inputFile.nextLine();
   //System.out.println(line);
   System.out.println(valleySortLine(line));
  }
  inputFile.close();
  //keyboard.close();
 }
}
