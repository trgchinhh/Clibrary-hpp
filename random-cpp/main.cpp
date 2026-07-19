#include <iostream>
#include <vector>
#include <string>
#include <random.hpp>

using namespace std;
using namespace random;

int main() {
    seed(42); // có thể tạo seed hoặc không

    cout << "Số nguyên ngẫu nhiên: " << randint(1, 10) << endl;
    cout << "Khoảng ngẫu nhiên hai tham số: " << randrange(1, 10) << endl;
    cout << "Khoảng ngẫu nhiên một tham số: " << randrange(10) << endl;
    cout << "Số thực ngẫu nhiên: " << uniform(0.0, 1.0) << endl;
    cout << "Số thực từ 0 đến 1: " << random::random() << endl;
    cout << "Tỷ lệ phần trăm: " << (chance(0.5) ? "Thành công" : "Thất bại") << endl;

    vector<int> v = {1, 2, 3, 4, 5};
    int arr[] = {10, 20, 30};
    string s = "hello";

    cout << "Chọn từ vector: " << choice(v) << endl;
    cout << "Chọn từ mảng: " << choice(arr) << endl;
    cout << "Chọn từ chuỗi: " << choice(s) << endl;

    shuffle(v);
    cout << "Trộn vector: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    shuffle(s);
    cout << "Trộn chuỗi: " << s << endl;

    vector<int> sampled = sample(v, 3);
    cout << "Lấy mẫu vector: ";
    for (int x : sampled) cout << x << " ";
    cout << endl;

    return 0;
}