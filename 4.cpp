#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    string name;
    double price;
    string description;
    bool available;
};

int partition(Product arr[], int low, int high) {
    double pivot = arr[high].price;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].price < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Product arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    Product p[3];
    for (int i = 0; i < 3; i++) {
        cout << "Enter product name: ";
        cin >> p[i].name;
        cout << "Enter price: ";
        cin >> p[i].price;
        cout << "Enter description: ";
        cin.ignore();
        getline(cin, p[i].description);
        cout << "Available (1 for yes, 0 for no): ";
        cin >> p[i].available;
    }

    quickSort(p, 0, 2);

    cout << "\nProducts sorted by price (ascending):\n";
    for (int i = 0; i < 3; i++)
        cout << p[i].name << " | " << p[i].price << " | " << p[i].description
             << " | " << (p[i].available ? "Available" : "Not Available") << endl;

}
