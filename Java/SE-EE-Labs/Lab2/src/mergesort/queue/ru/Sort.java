package mergesort.queue.ru;
public class Sort {
	int[] temp = new int[Lab2.N];

	public void mergeSort(int[] data, int left, int right) {
		if (left < right) {
			int mid = (left + right) / 2;
			//System.out.print("Mid: " + "[ " + data[mid] + " ] ");
			//System.out.print("Left: " + "[ " + data[left] + " ] ");
			//System.out.println("Right: " + "[ " + data[right] + " ] ");
			mergeSort(data, left, mid);
			mergeSort(data, mid + 1, right);
			merge(data, left, mid, right);
		}
	}

	private void merge(int[] data, int left, int mid, int right) {
		int indexLeft_1 = left;
		int indexLeft_2 = left;
		int indexMid = mid + 1;
		int k;
		while ((indexLeft_1 <= mid) && (indexMid <= right)) {
			if (data[indexLeft_1] <= data[indexMid]) {
				temp[indexLeft_2] = data[indexLeft_1];
				indexLeft_1++;
			} else {
				temp[indexLeft_2] = data[indexMid];
				indexMid++;
			}
			indexLeft_2++;
		}
		if (indexLeft_1 > mid)
			for (k = indexMid; k <= right; k++) {
				temp[indexLeft_2] = data[k];
				indexLeft_2++;
			}
		else
			for (k = indexLeft_1; k <= mid; k++) {
				temp[indexLeft_2] = data[k];
				indexLeft_2++;
			}
		for (k = left; k <= right; k++)
			data[k] = temp[k];
	}
}
