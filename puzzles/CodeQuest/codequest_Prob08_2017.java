import java.util.*;
import java.io.*;

public class Prob08 {
    private static final String INPUT_FILE_NAME = "Prob08.in.txt";

    public static void main(String[] args) {
        try {
            // prepare to read the file
            File inFile = new File(INPUT_FILE_NAME);
            FileReader fr = new FileReader(inFile);
            BufferedReader br = new BufferedReader(fr);
            String inLine = null;

            // get the number of test cases
            int T = Integer.parseInt(br.readLine());

            // loop through test cases
            while (T-- > 0) {
                    inLine = br.readLine();
                    String[] nums = inLine.split(" ");
                    double dist = Double.parseDouble(nums[0]),
                        vel = Double.parseDouble(nums[1]);

		            double hours = dist * 1000000 / vel;

                    int days = (int) (hours / 24),
                        hrs = (int) (hours % 24),
                        mins = (int) ((hours * 60 ) % 60),
                        secs = (int) Math.round((hours * 60 * 60) % 60);

                    System.out.println("Time to Mars: " + days + " days, " + hrs
                                        + " hours, " + mins + " minutes, " + secs
                                        + " seconds");

            }

            // clean up
            br.close();
            fr.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
