import java.io.IOException;
import java.nio.file.*;
import java.util.*;

public class BinaryDiagnostic {
    public static void main(String[] args) {
        // read file
        String fileName = "input.txt";
        String fileContents = "";
        ArrayList<String> lineList;
        try {
            fileContents = new String(Files.readAllBytes(Paths.get(fileName)));
            // remove newline characters and map to an array list
            String[] lines = fileContents.split("\n");
            // map to array list
            lineList = new ArrayList<String>(Arrays.asList(lines));
            // remove whitespace from each line
            for (int i = 0; i < lineList.size(); i++) {
                lineList.set(i, lineList.get(i).trim());
            }
        } catch (IOException e) {
            lineList = new ArrayList<String>();
            e.printStackTrace();
        }

        HashMap<Integer, Integer> countsOfOneMap = new HashMap<Integer, Integer>();
        for (int i = 0; i < lineList.get(0).length(); i++) {
            for (String string : lineList) {
                if (string.charAt(i) == '1') {
                    if (countsOfOneMap.containsKey(i)) {
                        countsOfOneMap.put(i, countsOfOneMap.get(i) + 1);
                    } else {
                        countsOfOneMap.put(i, 1);
                    }
                }
            }
        }

        // part 1
        int gamma[] = new int[countsOfOneMap.size()];
        int epsilon[] = new int[countsOfOneMap.size()];
        for (int key : countsOfOneMap.keySet()) {
            if (countsOfOneMap.get(key) >= 500) {
                gamma[key] = 1;
                epsilon[key] = 0;
            } else {
                gamma[key] = 0;
                epsilon[key] = 1;
            }
        }

        StringBuilder gammaString = new StringBuilder();
        StringBuilder epsilonString = new StringBuilder();
        for (int i = 0; i < gamma.length; i++) {
            gammaString.append(gamma[i]);
            epsilonString.append(epsilon[i]);
        }
        System.out.format("%d\n", Integer.parseInt(gammaString.toString(), 2) * Integer.parseInt(epsilonString.toString(), 2));

        // part 2

        // oxygen is most common, c02 is least
        ArrayList <String> lineCopy = new ArrayList<String>(lineList);
        ArrayList <String> temp = new ArrayList<String>();
        for (int i = 0; i < lineCopy.get(0).length(); i++) {
            char mostNumberAtI = countsOfOneMap.get(i) >= 500 ? '1' : '0';
            for (String string : lineCopy) {
                // check if the ith bit of string if it is most NumberAtI
                if (string.charAt(i) == mostNumberAtI) {
                    temp.add(string);
                }
            }

            lineCopy.clear();
            lineCopy.addAll(temp);
            temp.clear();
            if (lineCopy.size() == 1) {
                System.out.println("break");
                break;
            }
        }

        String oxygenString = lineCopy.get(0);
        // convert to binary then decimal
        int oxygen = Integer.parseInt(oxygenString, 2);
        System.out.format("%d\n", oxygen);

        // repeat for c02
        lineCopy.clear();
        lineCopy.addAll(lineList);
        temp.clear();
        for (int i = 0; i < lineCopy.get(0).length(); i++) {
            temp.clear();
            char leastNumberAtI = countsOfOneMap.get(i) <= 500 ? '1' : '0';
            for (String string : lineCopy) {
                if (string.charAt(i) == leastNumberAtI) {
                    temp.add(string);
                }
            }

            lineCopy.clear();
            lineCopy.addAll(temp);
            if (lineCopy.size() == 1) {
                System.out.println("break");
                break;
            }
        }
        
        for (String string : lineCopy) {
            // convert to binary then decimal
            int c02 = Integer.parseInt(string, 2);
            System.out.format("%d\n", c02 * oxygen);
        }
            
    }

}