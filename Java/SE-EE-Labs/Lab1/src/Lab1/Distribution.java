package Lab1;
import java.util.ArrayList;

class Distribute {
	void distrib(ArrayList<String> data1, ArrayList<String> data2, ArrayList<String> data3) {
		for(int i = 0; i < data1.size(); i++) {
 	       	if(find(data1.get(i), data2)==false) { 
 	       		data3.add(data1.get(i));
 	       	}
 	      }
	}
	
	void mix(ArrayList<String> data1, ArrayList<String> data2, ArrayList<String> data3) {
		for(int i = 0; i < data1.size(); i++) {
 	       	if(find(data1.get(i), data2)==true) { 
 	       		data3.add(data1.get(i));
 	       	}
 	      }
	}
    boolean find(String str, ArrayList<String> data) {
    	boolean flag=false;
    	for(int i=0; i< data.size(); i++) {
    		if(str.equals(data.get(i))) flag=true;
    	}
    	return flag;
    }
}