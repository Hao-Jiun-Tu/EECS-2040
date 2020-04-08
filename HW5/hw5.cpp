//
//  main.cpp
//  HW5
//
//  Created by Jonathan Hao-Cheng Ku on 2019/12/10.
//  Copyright © 2019 Jonathan Hao-Cheng Ku. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, r;

typedef struct _radixSort{
    int sort, left;
}radixSort;

long long Merge(int arr[], int aux[], int low, int mid, int high){
    int k = low, i = low, j = mid + 1;
    long long inversion = 0;
    
    while(i <= mid && j <= high){
        if(arr[i] <= arr[j]){
            aux[k++] = arr[i++];
        }else{
            aux[k++] = arr[j++];
            inversion += (mid - i + 1);
        }
    }
    while(i <= mid)
        aux[k++] = arr[i++];
    for(int i = low; i <= high; i++)
        arr[i] = aux[i];
    
    return inversion;
}
long long MergeSort(int arr[], int aux[], int low, int high){
    if(low == high)
        return 0;
    
    int mid = (low + ((high - low) >> 1));
    long long inversion = 0;
    
    inversion += MergeSort(arr, aux, low, mid);
    inversion += MergeSort(arr, aux, mid + 1, high);
    inversion += Merge(arr, aux, low, mid, high);
    
    return inversion;
}

int main(int argc, const char * argv[]) {
    
    while(cin >> n >> r){
        vector<radixSort> sequence(n);
        queue<radixSort> bin[r];
        int arr[n], aux[n];
        int max = 0, pass = 0;
        
        for(int i = 0; i < n; i++){
            int num;
            cin >> num;
            sequence[i].sort = num;
            sequence[i].left = num;
            arr[i] = num;
            aux[i] = num;
            if(num > max)
                max = num;
        }
        
        cout << MergeSort(arr, aux, 0, n - 1) << endl;
        
        while(max != 0){
            max = (max - (max % r)) / r;
            pass++;
        }

        for(int p = 0; p < pass; p++){
            int b = 0;
            
            for(int q = 0; q < n; q++){
                int order = 0;
                order = sequence[q].left % r;
                sequence[q].left = (sequence[q].left - sequence[q].left % r) / r;
                bin[order].push(sequence[q]);
            }
            for(int r = 0; r < n; r++){
                while(bin[b].size() == 0)
                    b++;
                
                sequence[r] = bin[b].front();
                bin[b].pop();
            }
            cout << sequence[0].sort << " " << sequence[n - 1].sort << endl;
        }
    }
    return 0;
}
