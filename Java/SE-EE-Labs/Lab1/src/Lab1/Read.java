package Lab1;
import java.io.File;
import java.util.*;
class Reader {
	File input;
	Reader(String fileName) {
	input = new File(fileName);
	}
	
	void loadList(Scanner scan, ArrayList<String> data) {
		while (scan.hasNextLine())
		{
				data.add(scan.nextLine());	
		}
	}
}