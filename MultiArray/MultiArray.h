#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class MultiArray {
private:
    struct Array {
        string name;
        vector<T> data;
    };

    vector<Array> arrays;

public:

    MultiArray() {}

    MultiArray(int numArrays, const vector<string>& names, const vector<int>& sizes) {
        if (numArrays != names.size() || numArrays != sizes.size()) {
            throw invalid_argument("Invalid number of arrays, names, or sizes");
        }

        for (int i = 0; i < numArrays; ++i) {
            arrays.push_back({ names[i], vector<T>(sizes[i]) });
        }
    }

    MultiArray(const MultiArray& other) {
        arrays = other.arrays;
    }

    vector<Array> getArrays() {
        return this->arrays;
    }

    void loadFromFile(string arrName, string fileName) {
        // find array in arrays with arrName
        auto iterator = find_if(arrays.begin(), arrays.end(), [arrName](const Array& arr) {
            return arr.name == arrName;
            });

       
        if (iterator != arrays.end()) {
            //read array data from fileName.txt
            ifstream file(fileName);
            T value;
            int i = 0;
            while (file >> value && i < iterator->data.size()) {
                iterator->data[i++] = value;
            }
            file.close();
        }
        else {
            throw invalid_argument("Array not found");
        }
    }
    
    T* subArray(string name, int startIndex, int endIndex, int step = 1) {
        auto iterator = find_if(arrays.begin(), arrays.end(), [name](const Array& arr) {
            return arr.name == name;
            });

        if (iterator != arrays.end()) {
            
            int size = iterator->data.size();

            T* result = new T[size];

            if (startIndex > endIndex) {
                //reverse_copy(iterator->data.begin() + endIndex, iterator->data.begin() + startIndex + 1, iterator->data.begin());
                int j = 0;
                for (int i = startIndex; i >= endIndex && j < size; i -= step, ++j) {
                    result[j] = iterator->data[i];
                }
            }
            else {
                int j = 0;
                for (int i = startIndex; i <= endIndex && j < size; i += step, ++j) {
                    result[j] = iterator->data[i];
                }
            }
            return result;
        }
        else {
            throw invalid_argument("Array not found");
        }
    }
    
    void reverse(string name) {
        auto it = find_if(arrays.begin(), arrays.end(), [name](const Array& arr) {
            return arr.name == name;
            });

        if (it != arrays.end()) {
            std::reverse(it->data.begin(), it->data.end());
        }
        else {
            throw invalid_argument("Array not found");
        }
    }
    
    void sort(string name) {
        auto iterator = find_if(arrays.begin(), arrays.end(), [name](const Array& arr) {
            return arr.name == name;
            });

        if (iterator != arrays.end()) {
            std::sort(iterator->data.begin(), iterator->data.end());
        }
        else {
            throw invalid_argument("Array not found");
        }
    }

    bool search(T item) {
        for (const auto& arr : arrays) {
            if (find(arr.data.begin(), arr.data.end(), item) != arr.data.end()) {
                return true;
            }
        }
        return false;
    }

    T& operator()(string name, int index) {
        auto iterator = find_if(arrays.begin(), arrays.end(), [name](const Array& arr) {
            return arr.name == name;
            });

        if (iterator != arrays.end()) {
            int size = iterator->data.size();
            if (index < 0) {
                index += size;
            }
            if (index >= 0 && index < size) {
                return iterator->data[index];
            }
            else {
                throw out_of_range("Index out of range");
            }
        }
        else {
            throw invalid_argument("Array not found");
        }
    }

    MultiArray<T> split(string name) {
        auto iterator = find_if(arrays.begin(), arrays.end(), [name](const Array& arr) {
            return arr.name == name;
            });

        if (iterator != arrays.end()) {
            int size = iterator->data.size();
            int mid = size / 2;

            MultiArray result;
            result.arrays.push_back({"first", vector<T>(iterator->data.begin(), iterator->data.begin() + mid)});
            result.arrays.push_back({"second", vector<T>(iterator->data.begin() + mid, iterator->data.end())});

            return result;
        }
        else {
            throw invalid_argument("Array not found");
        }
    }
    
    T* merge() {
        int totalSize = 0;
        for (const auto& arr : arrays) {
            totalSize += arr.data.size();
        }

        T* result=new T[totalSize];
        int offset = 0;

        for (const auto& arr : arrays) {
            for (const auto& value : arr.data) {
                //cout << value << endl;
                result[offset] = value;
                offset++;
            }
        }

        

        return result;
    }

    void applyToArray(string name, void (*func)(T&)) {
        auto iterator = find_if(arrays.begin(), arrays.end(), [name](const Array& arr) {
            return arr.name == name;
            });

        if (iterator != arrays.end()) {
            for (auto& value : iterator->data) {
                func(value);
            }
        }
        else {
            throw invalid_argument("Array not found");
        }
    }
   


    friend ostream& operator<<(ostream& os, const MultiArray& multiArray) {
        for (const auto& arr : multiArray.arrays) {
            os << arr.name << ": ";
            for (const auto& value : arr.data) {
                os << value << " ";
            }
            os << endl;
        }
        return os;
    }

    ~MultiArray() {}

};

template <typename T>
void printArray(const T* arr, int size) {

    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


template <typename T>
MultiArray<T> square(const MultiArray<T>& arr) {
    MultiArray<T> result = arr;
    result.applyToArray(result.getArrays().front().name, [](T& x) { x *= x; });
    return result;
}