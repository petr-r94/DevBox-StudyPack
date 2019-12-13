package Lab1;
import java.util.*;
import java.io.*;
public class Lab1 {
	public static void main(String args[]) {
		try {
		ArrayList<String> data1 = new ArrayList<String>();
		ArrayList<String> data2 = new ArrayList<String>();
		ArrayList<String> data3 = new ArrayList<String>();
		Reader first = new Reader("input1.txt"); /* "args[0]" */
		Reader second = new Reader("input2.txt");/* "args[1]" */
		Scanner scan1 = new Scanner(first.input);
		Scanner scan2 = new Scanner(second.input);
		first.loadList(scan1, data1); scan1.close();
		second.loadList(scan2, data2); scan2.close();
		
		Store storage = new Store();
		Distribute dist = new Distribute();
		
		dist.distrib(data1, data2, data3);
		storage.delDuplicates(data3);
		storage.showList("RESULT1.txt", data3);
		
		dist.distrib(data2, data1, data3);
		storage.delDuplicates(data3);
		storage.showList("RESULT2.txt", data3);
		
		dist.mix(data1,data2,data3);
		storage.delDuplicates(data3);
		storage.showList("RESULT3.txt", data3);
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		}	
	}
}