# HƯỚNG DẪN GIẢI BÀI TOÁN: CHIA TÚI QUÀ (LUYEN01)

---

### Bước 1: Phân tích đề bài & Mô hình hóa toán học

* **Tóm tắt bài toán:**
  * Có $A$ quyển vở và $B$ cây bút.
  * Cần chia đều vào $K$ túi quà sao cho mỗi túi có số lượng vở như nhau, số lượng bút như nhau, và không thừa lại đồ vật nào.
  * **Yêu cầu:** Tìm số túi quà nhiều nhất ($K$), cùng số vở ($A / K$) và số bút ($B / K$) trong mỗi túi.

* **Bản chất toán học:**
  * Để chia đều toàn bộ số vở: $A \ \vdots \ K$ ($K$ là ước của $A$).
  * Để chia đều toàn bộ số bút: $B \ \vdots \ K$ ($K$ là ước của $B$).
  * Do đó, $K$ là **ước chung** của cả $A$ và $B$.
  * Để số túi quà $K$ đạt giá trị **lớn nhất**, $K$ chính là **Ước chung lớn nhất (UCLN)** của $A$ và $B$:
    $$K = \text{UCLN}(A, B) = \gcd(A, B)$$
  * Khi đó:
    * Số vở trong mỗi túi: $\text{vở} = \frac{A}{K}$
    * Số bút trong mỗi túi: $\text{bút} = \frac{B}{K}$

* **Ràng buộc & Lưu ý kiểu dữ liệu:**
  * Giới hạn: $1 \le A, B \le 10^{18}$.
  * **Quan trọng:** Giá trị $10^{18}$ vượt quá phạm vi của kiểu số nguyên `int` thông thường (chỉ chứa tối đa $\approx 2 \times 10^9$). Bắt buộc phải khai báo bằng kiểu số nguyên 64-bit: **`long long`** trong C++.

---

### Bước 2: Dẫn dắt & Hình thành thuật toán

#### 1. Vì sao không dùng cách chạy vòng lặp (Vét cạn)?
* **Ý tưởng vét cạn:** Cho biến chạy $i$ từ $\min(A, B)$ lùi dần về $1$, hễ gặp số nào chia hết cho cả $A$ và $B$ thì dừng.
* **Hạn chế:** Khi $A, B \approx 10^{18}$, vòng lặp cần duyệt hàng tỷ tỷ phép tính, chương trình sẽ chạy mất hàng triệu năm $\rightarrow$ **Quá thời gian (Time Limit Exceeded - TLE)**.

#### 2. Thuật toán Euclid tối ưu
* **Nguyên lý:** 
  $$\gcd(A, B) = \gcd(B, A \pmod B)$$
  Thay vì trừ liên tục, ta lấy phần dư của phép chia $A$ cho $B$, sau đó lặp lại quy trình với cặp số mới cho đến khi số dư bằng $0$.
* **Độ phức tạp:** $O(\log(\min(A, B)))$. Với số lớn tới $10^{18}$, máy tính thực hiện tối đa khoảng $90$ phép chia $\rightarrow$ Hoàn thành trong **chưa tới $0.0001$ giây**, đạt trọn vẹn điểm tối đa.

---

### Bước 3: Lời giải C++ chuẩn

```cpp
#include <iostream>

using namespace std;

// Ham tim Uoc chung lon nhat bang thuat toan Euclid
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b; // Lay so du
        a = b;               // Gan so chia thanh so bi chia
        b = r;               // Gan so du thanh so chia moi
    }
    return a;
}

// Ham tim Boi chung nho nhat (chia truoc roi moi nhan de tranh tran so long long)
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int main() {
    // Toi uu toc do nhap xuat
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Doc va ghi file theo yeu cau de bai
    freopen("LUYEN01.INP", "r", stdin);
    freopen("LUYEN01.OUT", "w", stdout);

    long long A, B;
    if (cin >> A >> B) {
        // So tui qua nhieu nhat la UCLN cua A va B
        long long K = gcd(A, B);

        long long so_vo = A / K;
        long long so_but = B / K;

        // Xuat ket qua
        cout << K << "\n";
        cout << so_vo << " " << so_but << "\n";
    }

    return 0;
}
```

---

### Bước 4: Bảng mô phỏng từng bước (Dry Run)

Ví dụ với bộ test mẫu: **$A = 84$**, **$B = 126$**.

#### Bảng chạy hàm `gcd(84, 126)`:

| Bước thực hiện | Giá trị `a` | Giá trị `b` | Điều kiện (`b != 0`) | Phép chia dư `r = a % b` | Cập nhật `a = b` | Cập nhật `b = r` | Ý nghĩa sư phạm |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| **Bắt đầu** | $84$ | $126$ | Đúng ($126 \ne 0$) | $84 \pmod{126} = 84$ | $a = 126$ | $b = 84$ | Tự động đảo số lớn lên trước |
| **Vòng 1** | $126$ | $84$ | Đúng ($84 \ne 0$) | $126 \pmod{84} = 42$ | $a = 84$ | $b = 42$ | Còn dư $42$, tiếp tục chia |
| **Vòng 2** | $84$ | $42$ | Đúng ($42 \ne 0$) | $84 \pmod{42} = 0$ | $a = 42$ | $b = 0$ | Chia hết (dư $0$) |
| **Kết thúc** | $42$ | $0$ | **Sai** ($b == 0$) | — | — | — | Dừng vòng lặp, trả về $a = 42$ |

* Kết quả UCLN ($K$): **$42$**
* Số vở trong mỗi túi: $84 / 42 = \mathbf{2}$
* Số bút trong mỗi túi: $126 / 42 = \mathbf{3}$