#include <iostream>
#include <stdexcept>
#ifndef LIST
#define LIST
template <typename T>
class List
{
private:
    T *arr;
    int i; // index of last  cell available
    int s; // size of arr
    void resize();
    int partition(int start, int end);
    void quickSortAlgorithm(int start, int end);
    void swap(T &a, T &b);
    void mergeSortAlgorithm(int const begin, int const end);
    void merge(int const left, int const mid,
               int const right);

public:
    List(int n = 1);
    List(T *arr, int size);
    T &operator[](int);
    friend std::ostream &operator<<(std::ostream &out, const T &l);
    void append(T item);
    void insertionSort();
    inline void quickSort() { quickSortAlgorithm(0, this->i - 1); }
    inline int size() const { return i; }
    inline void mergeSort() { mergeSortAlgorithm(0, this->i - 1); }
    void remove(int);
    T pop();
    ~List();
};
#endif

template <typename T>
void List<T>::remove(int ind)
{

    if (ind < 0 || ind > this->size())
        throw std::invalid_argument("Index inaccessible");

    if (this->size() == 1)
    {
        this->i = 0;
    }
    else if (this->size() - 1 == ind)
    {
        this->i--;
    }
    else
    {
        for (int i = ind; i <= this->size() - 2; i++)
        {
            this->operator[](i) = this->operator[](i + 1);
        }
        this->i--;
    }
}

template <typename T>
List<T>::List(int n)
{
    if (n < 1)
        throw std::invalid_argument("Cant' create list with size 0");
    i = 0;
    s = n;
    this->arr = new T;
}

template <typename T>
List<T>::List(T *arr, int s)
{
    this->s = s * 2;
    this->arr = new T[this->s];
    for (this->i = 0; i < this->s - 1; i++)
        this->arr[i] = arr[i];
}
template <typename T>
List<T>::~List()
{
    // !!MEMORY LEAK
    // delete[] arr;
}
template <typename T>
T &List<T>::operator[](int i)
{
    if (i >= this->i)
        throw std::invalid_argument("Cant acces that index");
    return arr[i];
}

template <typename T>
std::ostream &operator<<(std::ostream &out, List<T> &l)
{
    out << '[';
    for (int i = 0; i < l.size(); i++)
    {
        if (i == l.size() - 1)
        {
            out << l[i] << ']';
            break;
        }
        out << l[i] << ',';
    }
    if (l.size() == 0)
    {
        out << ']';
    }
    return out;
}

template <typename T>
void List<T>::resize()
{
    this->s *= 2;
    T *newArr = new T[this->s];
    // memcpy(newArr, this->arr, this->s * sizeof(T));
    for (int i = 0; i < this->s; i++)
        newArr[i] = arr[i];

    // !!! MEMTORY LEAK DUNNO WHAT TO DO
    // delete[] this->arr;
    this->arr = newArr;
}

template <typename T>
void List<T>::append(T item)

{
    // if there any space availabel resize arr
    if (this->i >= this->s - 1)
        this->resize();

    arr[this->i] = item;
    this->i++;
}
template <typename T>
T List<T>::pop()
{
    return arr[--i];
}

template <typename T>
void List<T>::insertionSort()
{
    int i, key, j;
    for (i = 1; i < this->size(); i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
int List<T>::partition(int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

template <typename T>
void List<T>::quickSortAlgorithm(int start, int end)
{

    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(start, end);

    // Sorting the left part
    quickSortAlgorithm(start, p - 1);

    // Sorting the right part
    quickSortAlgorithm(p + 1, end);
}

template <typename T>
void List<T>::mergeSortAlgorithm(int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSortAlgorithm(begin, mid);
    mergeSortAlgorithm(mid + 1, end);
    merge(begin, mid, end);
}

template <typename T>
void List<T>::swap(T &a, T &b)
{
    T copy = a;
    a = b;
    b = copy;
}

template <typename T>
void List<T>::merge(int const left, int const mid,
                    int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    T *leftArray = new T[subArrayOne],
      *rightArray = new T[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    auto indexOfSubArrayOne = 0,   // Initial index of first sub-array
        indexOfSubArrayTwo = 0;    // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
