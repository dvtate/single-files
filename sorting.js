
function insertionSort(a) {
	for (let i = 0; i < a.length; i++) {
		for (let j = i; j >= 0; j--) {
			// swap into position
		}
	}
}

function selectionSort(a) {
	for (let i = 0; i < a.length; i++) {
		for (let j = i; j < a.length; j++) {
			// swap from position
		}
	}
}

function mergeSort(a) {
	// Merge results
	function merge(a, b) {
		// State vars
		let ai = 0, bi = 0;
		const ret = [];
		
		// Merge until one set empties
		while (ai < a.length && bi < b.length) {
			if (a[ai] < b[bi]) {
				ret.push(a[ai]);
				ai++;
			} else {
				ret.push(b[bi]);
				bi++;
			}
		}
		
		// Put rest of last set into ret
		if (ai === a.length) {
			ret.push(...b.slice(bi));
		} else {
			ret.push(...a.slice(ai));
		}
		
		return ret;
	}
	
	// Divide and conquer
	if (a.length > 1) {
		return merge(
			mergeSort(a.slice(0, a.length / 2)),
			mergeSort(a.slice(a.length / 2, a.length)),
		);
	} else {
		return a;	
	}	
}

function quickSort(a) {
	function swap(items, leftIndex, rightIndex){
		var temp = items[leftIndex];
		items[leftIndex] = items[rightIndex];
		items[rightIndex] = temp;
	}

	function partition(items, left, right) {
		var pivot   = items[Math.floor((right + left) / 2)], //middle element
		    i       = left, //left pointer
		    j       = right; //right pointer
		while (i <= j) {
		    while (items[i] < pivot) {
		        i++;
		    }
		    while (items[j] > pivot) {
		        j--;
		    }
		    if (i <= j) {
		        swap(items, i, j); //swap two elements
		        i++;
		        j--;
		    }
		}
		return i;
	}
	
	function quickSort(items, left, right) {
		var index;
		if (items.length > 1) {
		    index = partition(items, left, right); //index returned from partition
		    if (left < index - 1) { //more elements on the left side of the pivot
		        quickSort(items, left, index - 1);
		    }
		    if (index < right) { //more elements on the right side of the pivot
		        quickSort(items, index, right);
		    }
		}
		return items;
	}
	// first call to quick sort
	var result = quickSort(items, 0, items.length - 1);
	
	return result;
}

const randList = [];
for (let i = 0; i < 50; i++) {
	const n = Math.floor(Math.random() * 20);
	randList.push(n);
}

console.log('orig', randList);
console.log('merge sort', mergeSort(randList));
console.log('quick sort', mergeSort(randList));



function orderColors(colors) {
	const swap = (a, i1, i2) => {
		const tmp = a[i1];
		a[i1] = a[i2];
		a[i2] = tmp;
	};

	let index = 0;
	
	// sort reds
	for (let i = 0; i < colors.length; i++)
		if (colors[i] === 'red')
			swap(colors, index++, i);
	
	// sort
	for (let i = index; i < colors.length; i++)
		if (colors[i] === 'white')
			swap(colors, index++, i);

	return colors;
}

const randClrs = [];
for (let i = 0; i < 50; i++) {
	const c = ['red', 'white', 'blue'][Math.floor(Math.random() * 3)];
	randClrs.push(c);
}

console.log('clrs', randClrs);
console.log('counting sort', orderColors(randClrs));
