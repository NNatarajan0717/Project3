#include <iostream>
#include <queue>
using namespace std;

void quickSort(double arr[], int low, int high);
double partition(double arr[], int low, int high);

int main() {
    queue<double> q;
    q.push(4.19);
    q.push(5.0);
    q.push(4.11);
    q.push(4.79);
    q.push(4.37);
    q.push(4.83);
    q.push(4.17);
    q.push(4.44);
    q.push(4.26);
    q.push(4.01);
    double arr[q.size()];
    int originalSize = q.size();
    for(int i = 0; i < originalSize; i++){
        arr[i] = q.front();
        q.pop();
    }
    for(int i = 0; i < sizeof(arr); i++){
        cout<< arr[i];
    }
    int m = sizeof(arr)/sizeof(arr[0]);
    int low = 0;
    int high = m-1;
    quickSort(arr, low, high);

    return 0;
}

void quickSort(double arr[], int low, int high) {
    if(low < high){
        double pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1.0);
        quickSort(arr, pivot + 1.0, high);
    }

}


double partition(double arr[], int low, int high){
    double pivot = arr[low];
    int up = low;
    int down = high;
    while(up < down){
        for(int i = up; i < high; i++){
            if(arr[up] > pivot){
                break;
            }
            up += 1;
            for(int j = high; j > low; j--){
                if(arr[down] < pivot){
                    break;
                }
                down -= 1;
            }
            if(up < down) {
                swap(arr[up], arr[down]);
            }
        }
    }
    swap(arr[low],arr[down]);
    return down;
}