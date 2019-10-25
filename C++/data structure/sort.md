```
#include <iostream>
#include <vector>
#include <random>
using namespace std;

void show(vector<int> v){
    cout << "\t" ;
	for(auto i : v){
		cout << i << " " ;
	}
	cout << endl;
}

void randomInitVector(vector<int> &v){
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 100); // include 1 and 100
    
    for(auto& i : v){
    	i = uniform_dist(e1);
    }
    
    cout << "init: " << endl;
    show(v);
}

void bubbleSort(vector<int> v){
    // cout << v.size() << endl;
    cout << "============ bubbleSort ============" << endl;
    int num = v.size();
    
    for(int i = 0 ; i < num - 1 ; i++)
    {
        for(int j = 0; j < num - 1 - i; j++){
            if(v[j+1] < v[j]){
                swap(v[j+1], v[j]);
                cout << "swap: " << endl;
                show(v);
            }
        }
    }
    cout << "finish: " << endl;
    show(v);
    cout << "============ bubbleSort ============" << endl;
}

void insertSort(vector<int> v){
    cout << "============ insertSort ============" << endl;
    int num = v.size();
    
    for(int i = 1; i < num; i++){
        int temp = v[i];
        cout << "temp: " << temp << endl;
        for(int j = i - 1; j >= 0; j--){
            if(v[j] > temp){
                swap(v[j], v[j+1]);
            }
            else{
                v[j+1] = temp;
                break;
            }
        }
        show(v);
    }
    
    cout << "finish: " << endl;
    show(v);
    cout << "============ insertSort ============" << endl;
}

void selectionSort(vector<int> v){
    cout << "============ selectionSort ============" << endl;
    int num = v.size();
    int min = 101;
    int minIndex = 0;
    
    for(int i = 0; i < num - 1; i++){
        minIndex = i;
        min = 101;
        for(int j = i; j < num; j++){
            if(v[j] < min){
                min = v[j];
                minIndex = j;
            }
        }
        swap(v[i], v[minIndex]);
        cout << "min: " << min << endl;
        show(v);
    }
    
    cout << "finish: " << endl;
    show(v);
    cout << "============ selectionSort ============" << endl;
}

// 將insertSort()裡的+1-1改成+gap-gap
void shellSort(vector<int> v){
    cout << "============ shellSort ============" << endl;
    int num = v.size();
    int gap = num / 2;
    int k = 1; // gap 縮減次數
    
    while(gap != 0){
        cout << "k: " << k << " ,gap: " << gap << endl;
        for(int i = gap; i < num; i++){ // 這個i++ 不能改+=gap
            int temp = v[i];
            cout << "temp: " << temp << endl;
            for(int j = i - gap; j >= 0; j-=gap){
                if(v[j] > temp){
                    swap(v[j], v[j+gap]);
                }
                else{
                    v[j+gap] = temp;
                    break;
                }
            }
            show(v);
        } 
        k++;
        gap /= 2;
        cout << "-----------------------------------" << endl;
    }
    
    
    cout << "finish: " << endl;
    show(v);
    cout << "============ shellSort ============" << endl;
}

int division(vector<int> &v, int left, int right){
    int index = left;
    for(int i = left + 1; i <= right; i++){
        if(v[i] < v[left]){
            index++;
            swap(v[i], v[index]);
        }
    }
    swap(v[index], v[left]);
    
    return index;
}

void quickSortRec(vector<int> &v, int left = 0, int right = -2){
    if(right == -2)
        right = v.size() - 1;
    if(left < right){
        int pivotIndex = division(v, left, right);
        // cout << "pivotIndex: " << pivotIndex << endl;
        cout << "pivot: " << v[pivotIndex] << endl;
        show(v);
        quickSortRec(v, left, pivotIndex - 1);
        quickSortRec(v, pivotIndex + 1, right);
    }
}

void quickSort(vector<int> v){
    cout << "============ quickSort ============" << endl;
    
    quickSortRec(v);
    
    cout << "finish: " << endl;
    show(v);
    cout << "============ quickSort ============" << endl;
}

void merge(vector<int>& v, int front, int mid, int end){
    vector<int> leftArr(v.begin() + front, v.begin() + mid + 1);
    vector<int> rightArr(v.begin() + mid + 1, v.begin() + end + 1);

    cout << "front: " << front << " ,mid: " << mid << ", end: " << end << endl;
    show(leftArr);
    show(rightArr);
    
    int idx = front, lidx = 0, ridx = 0;
    int leftLen = leftArr.size();
    int rightLen = rightArr.size();
    
    while ((lidx < leftLen) && (ridx < rightLen)){
        
        if (leftArr[lidx] < rightArr[ridx]){
            v[idx] = leftArr[lidx];
            lidx += 1;
        }
        else{
            v[idx] = rightArr[ridx];
            ridx += 1;
        }
        idx += 1;
    }

    while(lidx < leftLen){
        v[idx] = leftArr[lidx];
        lidx += 1; 
        idx += 1;
    }
    while(ridx < rightLen){
        v[idx] = rightArr[ridx];
        ridx += 1; 
        idx += 1;
    }
    show(v);
}

void mergeSortRec(vector<int>& v, int front, int end){
    
    if(front < end){
        int mid = (front + end) / 2;
        mergeSortRec(v, front, mid);
        mergeSortRec(v, mid + 1, end);
        merge(v, front, mid, end);
    }
    
}

void mergeSort(vector<int> v){
    cout << "============ mergeSort ============" << endl;
    
    int len = v.size();
    mergeSortRec(v, 0, len - 1);
    
    cout << "finish: " << endl;
    show(v);
    cout << "============ mergeSort ============" << endl;
}

int main()
{
    int num = 10;
    vector<int> v(num, 0); 
    randomInitVector(v);
    
    // bubbleSort(v);
    // insertSort(v);
    // selectionSort(v);
    // shellSort(v);
    // quickSort(v);
    mergeSort(v);

    return 0;
}
```