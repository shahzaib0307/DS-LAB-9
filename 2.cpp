#include <iostream>
#include <vector>
using namespace std;

int getMax(vector<int>& arr) {
    int mx = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > mx) mx = arr[i];
    return mx;
}

void countingSort(vector<int>& arr, int exp, bool ascending) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    if (ascending)
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
    else
        for (int i = 8; i >= 0; i--)
            count[i] += count[i + 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr, bool ascending = true) {
    int m = getMax(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(arr, exp, ascending);
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    vector<int> asc = arr, desc = arr;

    radixSort(asc, true);
    radixSort(desc, false);

    cout << "Ascending: ";
    for (int x : asc) cout << x << " ";
    cout << "\nDescending: ";
    for (int x : desc) cout << x << " ";
    return 0;
}
