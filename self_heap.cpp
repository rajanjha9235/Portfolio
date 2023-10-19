#include <bits/stdc++.h>
using namespace std;

// Class for MAx heap
class Max_heap
{
    // A pointer pointing to the elements in array in the heap
    int *arr;

    // Maximum possible size of max heap
    int max_size;

    // No. of elements in max heap currently
    int heap_size;

public:
    // Constructor Function
    Max_heap(int max_size);

    // Heaify the sub-tree taking the given index as a root
    void heapify_max(int);

    int current_size()
    {
        return heap_size;
    }
    // Based on 0 based indexing
    int parent_index(int i)
    {
        return (i - 1) / 2;
    }
    int left_index(int i)
    {
        return (2 * i + 1);
    }
    int right_index(int i)
    {
        return (2 * i + 2);
    }

    // Insert the node at end of heap and take it to its correct position
    void insert(int val);

    // Delete the root node from heap and arrange the heap
    int delete_from_heap();
    
    // Increade the value of key at given index to some new value
    void increase_key( int i, int new_val);


    void print_heap()
    {
        for (int i = 0; i < heap_size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Construcutor to initialise the heap
Max_heap::Max_heap(int total_size)
{
    heap_size = 0;
    max_size = total_size;
    arr = new int[total_size];
}

// Insert the node at end of heap(array) and take it to its correct position by swapping with parent node
void Max_heap::insert(int val)
{

    // Heap is full
    if (heap_size == max_size)
    {
        cout << "\nOverflow : Could not insert\n";
        return;
    }
	
	// Increase the size of array & insert element to last index of array
    heap_size++;
    int i = heap_size - 1;  // Because of 0 based indexing
    arr[i] = val;

    // Check newly inserted node with its parent and swap it if greater than parent
    while (i != 0 && arr[parent_index(i)] < arr[i])
    {
        swap(arr[i], arr[parent_index(i)]);
        i = parent_index(i);
    }
}

// Heaify the sub-tree taking the given index as a root it goes upside down
void Max_heap::heapify_max(int i)
{
    int l = left_index(i);
    int r = right_index(i);
    int largest = i;        // Assuming that given index as largest

    // Check with the left child
    if (l < heap_size && arr[l] > arr[i])
        largest = l;

    // If above condition true then largest = l else largest = i and checking for the right child
    if (r < heap_size && arr[r] > arr[largest])
        largest = r;

    // If largest is changed then swap that & call heapify function again for the largest
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify_max(largest);
    }
}

// Delete the root node and then fix that using heapify
int Max_heap::delete_from_heap()
{
    // If only one element is there in heap
    if (heap_size == 1)
    {
        heap_size--;
        return arr[0];
    }

    int root = arr[0];
    // store the last element of the array and decrement the heap_size
    arr[0] = arr[heap_size - 1];
    heap_size--;

    // Then fix the root node using heapify function
    heapify_max(0);

    return root;
}


// Increase the value of key at given index to some new value
void Max_heap::increase_key( int i, int new_val){

	// step-1. Store the new value at given index
	arr[i] = new_val;
	
	// step-2. Check with the parent and swap if greater than parent
	while( i!= 0 && arr[i] > arr[parent_index(i)]){
		swap(arr[i], arr[parent_index(i)]);
		i = parent_index(i);
	}
}



// It takes array as a input and convert it to heap taking i as a root
void heap_sort_heapify(int arr[], int n, int i){

    // n - size of array & i - index at which heapify occurs 
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(arr[largest] < arr[left] && left < n){
        largest = left;
    }
    // cout<<"largest for i = "<<i<<", "<<largest<<" ";
    if(arr[largest]<arr[right] && right < n){
        largest = right;
    }
    // cout<<"largest i = "<<i<<", "<<largest<<" "<<endl;


// If there is any change in the largest index then swap that 
    if(largest != i){
        swap(arr[largest], arr[i]);
        heap_sort_heapify(arr,n,largest);
    }

}


// To sort the array in ascending order
void heap_Sort(int arr[], int n){

// First make that array a heap using heapify function 
    for(int i = n/2 - 1; i >= 0; i--){
        heap_sort_heapify(arr,n,i);
    }

    int size = n;

    while(size >0){
        // step 1. Swap root node to last node of heap and reduce the size. so,that heavier element is on last
        swap(arr[size - 1],arr[0]);
        size--;

        // Step 2. Make it a heap by using heapify from root
        heap_sort_heapify(arr,size,0);
    }
}


int main()
{
    Max_heap h(15);

    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);
    h.insert(90);
    h.insert(40);

    h.print_heap();
    cout << "Current Size = " << h.current_size() << endl;

    cout << "\nDeleted element = " << h.delete_from_heap() << endl;
    h.print_heap();
    
    cout << "\nDeleted element = " << h.delete_from_heap() << endl;
    h.print_heap();
    cout << "\nCurrent Size = " << h.current_size() << endl;
    
    cout<<"\nAfter increasing the key "<<endl;
    h.increase_key(2,90);
    h.print_heap();


    int array[] = {50,30,40,60,20};
    int n = sizeof(array)/sizeof(int);

    heap_Sort(array,n);
    cout<<"\nPrinting the Sorted array by heap sort :"<<n<<endl;
    for(int i = 0;i < n;i++)
    cout<<array[i]<<" ";
    cout<<endl;
}
