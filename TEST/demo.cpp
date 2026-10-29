// 1. Khai báo thư viện tổng hợp
#include <bits/stdc++.h>
using namespace std;

// Khai báo hằng, biến toàn cục, hàm phụ nếu cần

int main() {
    // Tăng tốc độ nhập, xuất
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. Khai báo biến
    int a, b;

    // 2. Nhập dữ liệu đúng thứ tự đề bài
    cin >> a >> b;

    // 3. Xử lí bài toán
    int tong = a + b;
    int hieu = a - b;

    // 4. Xuất đúng kết quả đề bài yêu cầu
    cout << tong << '\n';
    cout << hieu ;

    return 0;
}
