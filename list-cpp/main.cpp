#include <iostream>
#include <list.hpp>

using namespace std;

struct Element {
    int id;
    double value;
    Element() : id(0), value(0.0) {}
    Element(int i, double v) : id(i), value(v) {}
};

ostream& operator<<(ostream& os, const Element& e) {
    os << "{" << e.id << "," << e.value << "}";
    return os;
}

int main() {
    List<int> list1 = {10, 20, 30, 40, 50};
    cout << "1. Khoi tao tu initializer_list: " << list1 << endl;

    list1.push(60);
    int x = 70;
    list1.push(x);
    cout << "2. Sau khi push: " << list1 << endl;

    list1.pop();
    cout << "3. Sau khi pop(): " << list1 << endl;

    cout << "4. Kich thuoc thuc te: " << list1.getsize() << " | Capacity: " << list1.capacity() << endl;
    cout << "5. Danh sach co trong hay khong? " << (list1.empty() ? "Co" : "Khong") << endl;

    cout << "6. Phan tu dau tien: " << list1.front() << " | Phan tu cuoi cung: " << list1.back() << endl;

    cout << "7. Truy cap qua operator[2]: " << list1[2] << endl;
    list1[2] = 99;
    cout << "8. Sau khi sua qua operator[2]: " << list1 << endl;

    cout << "9. Truy cap qua ham at(3): " << list1.at(3) << endl;

    list1.insert(1, 55);
    cout << "10. Sau khi insert(1, 55): " << list1 << endl;

    list1.erase(3);
    cout << "11. Sau khi erase(3): " << list1 << endl;

    cout << "12. Vi tri cua gia tri 55: " << list1.find(55) << endl;
    cout << "13. Danh sach co chua gia tri 40 khong? " << (list1.contains(40) ? "Co" : "Khong") << endl;

    list1.reverse();
    cout << "14. Sau khi reverse(): " << list1 << endl;

    list1.sort();
    cout << "15. Sau khi sort(): " << list1 << endl;

    cout << "16. Duyet qua vong lap Range-based for: ";
    for (const auto& val : list1) {
        cout << "[" << val << "] ";
    }
    cout << endl;

    cout << "17. Duyet nguoc qua rbegin va rend: ";
    for (auto it = list1.rbegin(); it != list1.rend(); ++it) {
        cout << "(" << *it << ") ";
    }
    cout << endl;

    List<int> list2 = list1;
    cout << "18. Danh sach copy_constructor (list2): " << list2 << endl;

    List<int> list3;
    list3 = list1;
    cout << "19. Danh sach dung toan tu gan copy (list3): " << list3 << endl;

    List<int> list4 = move(list2);
    cout << "20. Danh sach sau khi move_constructor (list4): " << list4 << endl;
    cout << "Kich thuoc list2 sau khi bi move: " << list2.getsize() << endl;

    List<Element> custom_list;
    custom_list.emplace_back(1, 1.5);
    custom_list.emplace_back(2, 2.5);
    cout << "21. Su dung emplace_back voi kieu cau truc: " << custom_list << endl;

    list1.resize(8, 100);
    cout << "22. Sau khi resize(8, 100): " << list1 << endl;
    list1.resize(4);
    cout << "23. Sau khi resize(4): " << list1 << endl;

    cout << "24. Capacity truoc khi shrink: " << list1.capacity() << endl;
    list1.shrink_to_fit();
    cout << "25. Capacity sau khi shrink_to_fit(): " << list1.capacity() << endl;

    list1.clear();
    cout << "26. Sau khi clear(), kich thuoc la: " << list1.getsize() << endl;

    return 0;
}