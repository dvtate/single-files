

import java.io.*;
import java.util.*;


public class Prob05 {
	private static final String INPUT_FILE_NAME = "prob05.in.txt";

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
				String[] oldDonors = br.readLine().split(",");
				String[] newDonors = br.readLine().split(",");

				String[] left = new String[oldDonors.length + newDonors.length];
				String[] both = new String[oldDonors.length + newDonors.length];
				String[] noobs = new String[oldDonors.length + newDonors.length];

				int i = 0;
				for (String oldie : oldDonors)
					for (String newbie : newDonors) {
						if (oldie == null || newbie == null)
							break;
						if (oldie.equals(newbie))
							both[i++] = oldie;
					}
				i = 0;
				for (String oldie : oldDonors) {
					boolean isInlist = false;
					for (String multi : newDonors) {
						if (oldie == null || multi == null)
							break;
						if (oldie.equals(multi)) {
							isInlist = true;
							break;
						}
					}
					if (!isInlist)
						left[i++] = oldie;
				}

				i = 0;
				for (String oldie : newDonors) {
					boolean isInlist = false;
					for (String multi : oldDonors)
						if (oldie.equals(multi)) {
							isInlist = true;
							break;
						}
					if (!isInlist)
						noobs[i++] = oldie;

				}

				Array.sort(noobs);
				System.out.print(left.length != 0 ? left[0] : "");
				for (i = 1; i < left.length; i++) {
					if (left[i] == null)
						break;
					else
						System.out.print("," + left[i]);
				}
				System.out.print("\n");


				System.out.print(both.length != 0 ? both[0] : "");
				for (i = 1; i < both.length; i++) {
					if (both[i] == null)
						break;
					else
						System.out.print("," + both[i]);
				}
				System.out.print("\n");


				System.out.print(noobs.length != 0 ? noobs[0] : "");
				for (i = 1; i < noobs.length; i++) {
					if (noobs[i] == null)
						break;
					else
						System.out.print("," + noobs[i]);
				}
				System.out.print("\n");


            }

            // clean up
            br.close();
            fr.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
