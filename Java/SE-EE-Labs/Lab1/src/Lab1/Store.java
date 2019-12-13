package Lab1;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

class Store {
	PrintWriter pwr;
	void delDuplicates(ArrayList<String> data) {
		for(int i = 0; i < data.size()-1; i++) {
 	       	if(((data.get(i)).equals(data.get(i+1)))) {
 	       	 data.remove(i);
 	       	}
 	      }
	}
	void showList(String fileName, ArrayList<String> data) {
		try {
			File file = new File(fileName);
			pwr = new PrintWriter(file);
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		}
	     for(int i = 0; i < data.size(); i++) {
	    	 System.out.println(data.get(i));
 	       	pwr.println(data.get(i));
 	      }
	     pwr.close();
	     data.clear();
	}
}