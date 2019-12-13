package mergesort.queue.ru;

public class Queue_gen {
	private int[] massiv;
	private final int startCell = 0;
	private int addCell;

	Queue_gen() {
		massiv = new int[1];
		addCell = 1;
		System.out.println("Queue Initialize...");
	}

	void addElem(int val) {
		int[] extension = new int[addCell + 1];
		moveElems(massiv, extension, startCell, addCell);
		extension[addCell] = val;
		massiv = extension;
		System.out.println("Added Elem = " + val + " ");
		System.out.println("-----------------");
		addCell++;
	}

	void delElem(int offset) {
		if (offset > getQueueLen()) {
			System.out.println("ERROR!!! Too much delete offset");
			System.out.println("Execute Next Valid Operation");
			System.out.println("-----------------");
			return;
		}
		else {
		int cut = getQueueLen()+1-offset;
		int[] cutting = new int[cut];
		moveElems(massiv, cutting, startCell+offset, cut);
		massiv=cutting;
		addCell-=offset;
		System.out.println("Deleting " + offset + " Elements");
		System.out.println("-----------------");
		}
	}

	void clrQueue() {
		int[] empty = new int[1];
		massiv = empty;
		addCell = 1;
		System.out.println("Queue is Cleaning...");
		System.out.println("-----------------");
	}

	int getTailElem() {
		int elem = 0;
		if (addCell == 1) {
			return elem;
		} else
			elem = massiv[getQueueLen()];
		return elem;
	}

	int getHeadElem() {
		int elem = 0;
		if (addCell == 1) {
			return elem;
		} else
			elem = massiv[startCell + 1];
		return elem;
	}

	int getQueueLen() {
		int len = addCell - 1;
		return len;
	}

	void moveElems(int[] from, int[] to, int position, int count) {
		for (int i = 0; i < count; i++) {
			to[i] = from[i+position];
		}
	}

	void showQueue() {
		System.out.println("Now Length = " + getQueueLen());
		System.out.println("Tail Elem = " + getTailElem());
		System.out.println("Head Elem = " + getHeadElem());
		System.out.print("Root <- ");
		for (int i = startCell + 1; i < getQueueLen()+1; i++) {
			System.out.print("[ " + massiv[i] + " ] ");
		}
		System.out.println(" ");
		System.out.println("-----------------");
	}
}
