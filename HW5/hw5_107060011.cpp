#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long int merge(int* arr, int* tmp, int front, int mid, int end)
{
    int i, j, k;
    long long int inv_cnt = 0;

    i = front,
    j = mid,
    k = front;

    while((i <= mid - 1) && (j <= end))
    {
        if(arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else{
            tmp[k++] = arr[j++];
            inv_cnt += (mid - i);
        }
    }
    while(i <= mid - 1)
        tmp[k++] = arr[i++];

    while(j <= end)
        tmp[k++] = arr[j++];

    for(i = front; i <= end; i++)
        arr[i] = tmp[i];

    return inv_cnt;
}

long long int merge_sort(int* arr, int* tmp, int front, int end)
{
    long long int inv_cnt = 0;
    int mid;
    if(front < end){
        mid = (front + end) / 2;
        inv_cnt += merge_sort(arr, tmp, front, mid);
        inv_cnt += merge_sort(arr, tmp, mid+1, end);
        inv_cnt += merge(arr, tmp, front, mid+1, end);
    }
    return inv_cnt;
}
int main(){
    int n, r;
    while(cin >> n >> r){
        vector<int> ass(n);
        queue<int> bin[r];
        int *arr = new int [n];
        int *tmp = new int [n];

        int max = -1;

        for(int i = 0; i < n; i++){
            int num;
            cin >> num;
            ass[i] = num;
            arr[i] = num;

            if(num > max)
                max = num;
        }

        cout << merge_sort(arr, tmp, 0, n - 1) << endl;

        int exp = 1;
        while(max != 0){
            for(int i = 0; i < n; i++){
                bin[(ass[i] / exp) % r].push(ass[i]);
            }
            int b = 0;
            for(int i = 0; i < n; i++){
                while(bin[b].empty()) b++;

                ass[i] = bin[b].front();
                bin[b].pop();
            }
            cout << ass.front() << " " << ass.back() << endl;
            max /= r;
            exp *= r;
        }
    }
    return 0;
}
