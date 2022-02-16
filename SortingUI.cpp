#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//Implemented my own queue class
class queue {
    public:
        int *arr;
        int front,rear,size;
        unsigned capacity;
        queue(){
            front = rear = size = 0;
            capacity = 100;
            rear = capacity - 1;
            arr = new int[capacity];
        }
        int empty(queue* q);
        void enqueue(queue* q, int a);
        int dequeue(queue* q);
};

int isFull(queue* q)
{
    return (q->size == q->capacity);
}

int queue::empty(queue *q){
    return (q->size==0);
}
void queue::enqueue(queue *q, int a){
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = a;
    q->size = q->size + 1;
}

int queue::dequeue(queue *q){
    int a = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;
    return a;
}

vector<int> buildList();
void printVector(vector<int> unsorted);
void insertionSort(vector<int> unsorted);
void selectionSort(vector<int> unsorted);
void bubbleSort(vector<int> unsorted);
void quickSort(vector<int> &unsorted, int low, int high);
int partition(vector<int> &unsorted, int low, int high);
void radixSort(vector<int> unsorted);
void swap(int *a, int *b);

int main(){
    int choice = 0;
    int input = 0;
    vector<int> original;
    //MENU. Continuosly runs until 6 (exit program) is selected
    while(input != 6){
        cout<<"M E N U"<<endl;
        cout<<"Input Data (0), Insertion Sort (1), Selection Sort (2), Bubble Sort (3), Quick Sort (4), Radix Sort (5) Exit Program (6)"<<endl;
        cout<<"Choose?"<<endl;
        cin>>input;
        switch(input){
            case 0:
                original = buildList(); //build the list
                break;
            case 1:
                insertionSort(original); //insertion sort
                break;
            case 2:
                selectionSort(original); //selection
                break;
            case 3:
                bubbleSort(original); //names are self-evident
                break;  
            case 4:
                quickSort(original, 0, (original.size()-1));
                printVector(original);
                break;
            case 5:
                radixSort(original);
                break;
            case 6:
                break;
            default:
                cout<<"Incorrect menu option!"<<endl;
        }
    }
    return 0;
}

void swap(int *a, int *b) { //helper function to swap two indices
  int t = *a;
  *a = *b;
  *b = t;
}
vector<int> buildList(){ //builds the vector to be sorted
    vector<int> temp;
    string inp;
    cin.ignore();
    getline(cin,inp,'\n');
    string word;
    for (istringstream is(inp); is >> word; )
    {
        temp.push_back(stoi(word));
    }
    return temp;
}
void printVector(vector<int> unsorted){ //prints the vector
    int k = 0;
    while(k < unsorted.size()){
        cout<<unsorted[k]<<" ";
        k++;
    }
    cout<<endl;
}

void insertionSort(vector<int> unsorted){ 
    for(int i = 1,j; i < unsorted.size(); i++){
        int tmp = unsorted[i];
        for(j=i; j>0 && tmp < unsorted[j-1]; j--){
            unsorted[j] = unsorted[j-1];
        }
        unsorted[j] = tmp;
    }
    printVector(unsorted);
}

void selectionSort(vector<int> unsorted){
    int n = unsorted.size();
    for(int i=0,j,least; i< n-1; i++){
        for(j=i+1, least = i; j<n; j++){
            if(unsorted[j] < unsorted[least]){
                least = j;
            }
        }
        int temp = unsorted[least];
        unsorted[least] = unsorted[i];
        unsorted[i] = temp;
    }
    printVector(unsorted);
}
void bubbleSort(vector<int> unsorted){
    int n = unsorted.size();
    for(int i = 0; i < n-1; i++){
        for(int j=n-1; j>i; --j){
            if(unsorted[j] < unsorted[j-1]){
                int temp = unsorted[j];
                unsorted[j] = unsorted[j-1];
                unsorted[j-1] = temp;
            }
        }
    }
    printVector(unsorted);
}

void quickSort(vector<int> &unsorted, int low, int high){
    if (low < high) {
        int pi = partition(unsorted, low, high); 
        quickSort(unsorted, low, pi - 1);
        quickSort(unsorted, pi + 1, high);
    } 
}

int partition(vector<int> &unsorted, int low, int high){
    int pivot = unsorted[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (unsorted[j] <= pivot){
            i++;
            swap(&unsorted[i], &unsorted[j]);
        }
    }
    swap(&unsorted[i + 1], &unsorted[high]);
    return (i + 1);
}

void radixSort(vector<int> unsorted){
    int n = unsorted.size();
    register int d,j,k,factor;
    const int radix = 10;
    const int digits = 10;
    queue *queues[radix] = {new queue, new queue, new queue, new queue, new queue, new queue, new queue, new queue, new queue, new queue}; //Array of queue arrays for radix sort
    for(d=0,factor = 1; d<digits; factor *= radix, d++){
        for(j=0; j<n; j++){
            queues[(unsorted[j] / factor) % radix]->enqueue(queues[(unsorted[j] / factor) % radix], unsorted[j]);
        }
        for(j=k=0;j<radix;j++){
            while(!queues[j]->empty(queues[j])){
                unsorted[k++] = queues[j]->dequeue(queues[j]);
            }
        }
    }
    printVector(unsorted);
}