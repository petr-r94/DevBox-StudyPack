package mergesort.queue.ru;

public class Lab2 {
	static int[] sortMas;
    static int N=50;
	public static void main(String[] args) {
		Queue_gen struct = new Queue_gen();
		struct.showQueue();
		struct.addElem(45);
		struct.showQueue();
		struct.addElem(135);
		struct.showQueue();
		struct.clrQueue();
		struct.showQueue();
		struct.addElem(7);
		struct.showQueue();
		struct.addElem(78);
		struct.showQueue();
		struct.addElem(2);
		struct.showQueue();
		struct.delElem(1);
		struct.showQueue();
		struct.addElem(222);
		struct.showQueue();
		struct.delElem(3);
		struct.showQueue();
		struct.addElem(322);
		struct.addElem(54);
		struct.addElem(78);
		struct.addElem(98);
		struct.showQueue();
		struct.delElem(2);
		struct.showQueue();

		sortMas = Mas_gen.gen(sortMas, N);
		System.out.print(Integer.MAX_VALUE);
		//System.out.println();
		//System.out.println("COUNT= " + sortMas.length);
		//System.out.print("Origin: ");
		Mas_gen.showData(sortMas, "ORIGIN.TXT");
		System.out.println(" ");
		Sort sort = new Sort();
		//System.out.println("-----------------");
		sort.mergeSort(sortMas, 0, N-1);
		//System.out.println("-----------------");
		//System.out.print("Sort: ");
		Mas_gen.showData(sortMas, "SORT.TXT");
		//System.out.println();
		//System.out.println("COUNT= " + sortMas.length);

	}

}
