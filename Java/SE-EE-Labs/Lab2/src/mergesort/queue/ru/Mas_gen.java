package mergesort.queue.ru;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Random;

public class Mas_gen {
	static PrintWriter pwr;
	public static int[] gen(int[] data, int N) {
		data = new int[N];
		Random rand = new Random();
		for (int i = 0; i < N; i++) {
			data[i] = rand.nextInt(100);
		}
		return data;
	}

	public static void showData(int[] sortMas, String filename) {
		File file = new File(filename);
		try {
			int i=0;
			pwr = new PrintWriter(file);
			while(i<sortMas.length) {
			pwr.println(sortMas[i] + " ");
			i++;
			}
			pwr.close();
		} catch (FileNotFoundException e) {
			System.out.println("Error writing to file");
		}
		
		for (int i = 0; i < sortMas.length; i++) {
			System.out.print("[ " + sortMas[i] + " ] ");
		}
	}
}
