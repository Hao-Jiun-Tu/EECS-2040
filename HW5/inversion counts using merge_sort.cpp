#include <iostream>

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

int main()
{
    int size;
    int *arr, *tmp;
    while(cin >> size)
    {
        arr = new int [size];
        tmp = new int [size];
        for(int i = 0; i < size; ++i)
            cin >> arr[i];

        cout << merge_sort(arr, tmp, 0, size - 1) << endl;

    }
    return 0;
}
//Network Address: https://www.youtube.com/watch?v=k9RQh21KrH8
