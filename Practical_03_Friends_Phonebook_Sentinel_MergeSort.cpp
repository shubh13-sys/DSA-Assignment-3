#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX = 100;

void display(const vector<string>& name, const vector<string>& mobile) {
    if (name.empty()) {
        cout << "\nPhone book is empty.\n";
        return;
    }

    cout << "\n============================================\n";
    cout << "             FRIEND PHONE BOOK\n";
    cout << "============================================\n";
    cout << "Name\t\tMobile Number\n";
    cout << "--------------------------------------------\n";
    for (size_t i = 0; i < name.size(); i++)
        cout << name[i] << "\t\t" << mobile[i] << endl;
    cout << "============================================\n";
}

int sentinelSearch(vector<string>& name, const string& key) {
    int n = static_cast<int>(name.size());
    if (n == 0)
        return -1;

    string last = name[n - 1];
    name[n - 1] = key;

    int i = 0;
    while (name[i] != key)
        i++;

    name[n - 1] = last;

    if (i < n - 1 || last == key)
        return i;
    return -1;
}

void merge(vector<string>& name, vector<string>& mobile, int left, int mid, int right) {
    vector<string> leftName(name.begin() + left, name.begin() + mid + 1);
    vector<string> leftMobile(mobile.begin() + left, mobile.begin() + mid + 1);
    vector<string> rightName(name.begin() + mid + 1, name.begin() + right + 1);
    vector<string> rightMobile(mobile.begin() + mid + 1, mobile.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < static_cast<int>(leftName.size()) &&
           j < static_cast<int>(rightName.size())) {
        if (leftName[i] <= rightName[j]) {
            name[k] = leftName[i];
            mobile[k] = leftMobile[i];
            i++;
        } else {
            name[k] = rightName[j];
            mobile[k] = rightMobile[j];
            j++;
        }
        k++;
    }

    while (i < static_cast<int>(leftName.size())) {
        name[k] = leftName[i];
        mobile[k] = leftMobile[i];
        i++;
        k++;
    }

    while (j < static_cast<int>(rightName.size())) {
        name[k] = rightName[j];
        mobile[k] = rightMobile[j];
        j++;
        k++;
    }
}

void mergeSort(vector<string>& name, vector<string>& mobile, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(name, mobile, left, mid);
        mergeSort(name, mobile, mid + 1, right);
        merge(name, mobile, left, mid, right);
    }
}

void insertFriend(vector<string>& name, vector<string>& mobile) {
    if (static_cast<int>(name.size()) >= MAX) {
        cout << "\nPhone book is full. Cannot insert friend.\n";
        return;
    }

    string newName, newMobile;
    cout << "\nEnter friend's name: ";
    cin >> newName;

    if (sentinelSearch(name, newName) != -1) {
        cout << "\nFriend already exists in the phone book.\n";
        return;
    }

    cout << "Enter mobile number: ";
    cin >> newMobile;
    name.push_back(newName);
    mobile.push_back(newMobile);
    mergeSort(name, mobile, 0, static_cast<int>(name.size()) - 1);
    cout << "\nFriend inserted successfully.\n";
}

void deleteFriend(vector<string>& name, vector<string>& mobile) {
    if (name.empty()) {
        cout << "\nPhone book is empty. Nothing to delete.\n";
        return;
    }

    string deleteName;
    cout << "\nEnter name of friend to delete: ";
    cin >> deleteName;

    int position = sentinelSearch(name, deleteName);
    if (position == -1) {
        cout << "\nFriend not found in phone book.\n";
        return;
    }

    name.erase(name.begin() + position);
    mobile.erase(mobile.begin() + position);
    cout << "\nFriend deleted successfully.\n";
}

void searchFriend(vector<string>& name, const vector<string>& mobile) {
    if (name.empty()) {
        cout << "\nPhone book is empty.\n";
        return;
    }

    string searchName;
    cout << "\nEnter name of friend to search: ";
    cin >> searchName;

    int position = sentinelSearch(name, searchName);
    if (position != -1) {
        cout << "\n============================================\n";
        cout << "             FRIEND FOUND\n";
        cout << "============================================\n";
        cout << "Name          : " << name[position] << endl;
        cout << "Mobile Number : " << mobile[position] << endl;
        cout << "============================================\n";
    } else {
        cout << "\nFriend not found in phone book.\n";
    }
}

int main() {
    vector<string> name, mobile;
    int n;

    cout << "Enter number of friends: ";
    cin >> n;
    if (n < 0 || n > MAX) {
        cout << "Invalid number of friends.\n";
        return 1;
    }

    for (int i = 0; i < n; i++) {
        string friendName, friendMobile;
        cout << "\nEnter name of friend " << i + 1 << ": ";
        cin >> friendName;
        cout << "Enter mobile number: ";
        cin >> friendMobile;
        name.push_back(friendName);
        mobile.push_back(friendMobile);
    }

    if (name.size() > 1)
        mergeSort(name, mobile, 0, static_cast<int>(name.size()) - 1);

    cout << "\nPhone book after Merge Sort:";
    display(name, mobile);

    int choice;
    do {
        cout << "\n\n============================================\n";
        cout << "              PHONE BOOK MENU\n";
        cout << "============================================\n";
        cout << "1. Insert Friend\n2. Delete Friend\n";
        cout << "3. Search Friend (Sentinel Search)\n";
        cout << "4. Display Phone Book\n5. Sort Phone Book (Merge Sort)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertFriend(name, mobile); break;
            case 2: deleteFriend(name, mobile); break;
            case 3: searchFriend(name, mobile); break;
            case 4: display(name, mobile); break;
            case 5:
                if (name.size() > 1) {
                    mergeSort(name, mobile, 0, static_cast<int>(name.size()) - 1);
                    cout << "\nPhone book sorted successfully using Merge Sort.\n";
                } else {
                    cout << "\nNot enough friends to sort.\n";
                }
                break;
            case 6: cout << "\nExiting Phone Book. Goodbye!\n"; break;
            default: cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
