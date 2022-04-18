#include <iostream>
#include "Graph.h"
#include "Movie_Vertex.h"

using namespace std;


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