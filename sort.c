#include <cs3050.h>

void bubblesort(void *array, 
				size_t nitems, 
				size_t size, 
				int (*CompareFunc)(const void *, const void*))
{
	for (int i=0;i<nitems;i++)
	{
		for (int j=0;j<nitems-1;j++)
		{
			void * item1 = array + j*size;
			void * item2 = array + (j+1)*size;
			if (CompareFunc(item1,item2)>0)
			{
				Swap(item1,item2,size);
			}
		}
	}
}

void insertionsort(void *array, 
				size_t nitems, 
				size_t size, 
				int (*CompareFunc)(const void *, const void*))
{
	void *temp_item_holder = malloc(size); //holds the item that will be put into correct position
	if (temp_item_holder == NULL) { //in case memory allocation for temp fails
		return;
	}

	for (size_t i = 1; i < nitems; i++) { //start from second item because for insertion sort we first assume first item is sorted, so it will end up in the correct position after the rest of the sort
		void *current_item_pointer = array + (i * size); //must multiply by size because it is a void pointer (compiler doesnt know size)
		Copy(temp_item_holder, current_item_pointer, size); //copy current iterated element to the temp holder we created

		size_t j = i; //initialize J for use in the second loop, starting shifting from element the current iteration the outside loop is on (i)

		while (j > 0) { //this loop performs the shifting until the correct position for the temp_item_holder (into which it needs to be inserted) is found by the loop
			void *previous_item_pointer = array + ((j-1) * size); //create pointer to previous element of the current one so it can be used to compare and thus know whether a shift needs to happen or nott
			if (CompareFunc(previous_item_pointer, temp_item_holder) > 0){
				Copy(array + (j * size), previous_item_pointer, size); //shift element in the array one to the right if its greater than the previous element
			}
			else {
				break; //this means the correct position where the element needs to be inserted has been found (previous element is not greater than cuurent)
			}
			j = j - 1; //used to look at all element to the left of the current element, to find correct position (make sure we get to the start of the list from every position)
	}
	Copy(array + (j * size), temp_item_holder, size); //insert the element into the now found correct position
}
free(temp_item_holder); //free memory that was allocated earluer to avoid memory leaks
}
