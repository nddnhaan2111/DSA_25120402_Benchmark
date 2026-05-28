1.

Cấu trúc dữ liệu giải thuật 2025-2026

MSSV: 25120402

Họ và tên: Nguyễn Đình Nhân

2. 

A:
Radix Sort kết hợp thao tác Bitwise.

Thuật toán chia nhỏ số nguyên 32-bit thành 4 byte riêng biệt và sắp xếp lần lượt từ byte thấp nhất đến byte cao nhất

Lý do:

Các thuật toán như Quick Sort hay Merge Sort là thuật toán "dựa trên so sánh" . Giới hạn tốc độ toán học của chúng luôn là O(Nlog N). Khi số lượng phần tử lên tới hàng triệu, CPU phải thực hiện hàng chục triệu phép so sánh rẽ nhánh. Radix Sort không hề so sánh hai số với nhau. Nó đếm và phân bổ các số theo từng chữ số/byte. Tốc độ của nó là nhanh hơn thuật toán so sánh khi tập dữ liệu đủ lớn.

Nếu bạn dùng vòng lặp chia dư cho 10 (% 10) để lấy từng chữ số, CPU phải thực hiện phép chia - một trong những lệnh tốn nhiều chu kỳ máy nhất. Việc tách số bằng hệ cơ số 256 (tương đương 1 byte) cho phép bạn dùng phép dịch bit (>>) và phép AND (&). Các phép toán bitwise này chạy trực tiếp ở cấp độ bóng bán dẫn của CPU, gần như tốn đúng 1 chu kỳ máy để hoàn thành, nhanh gấp hàng chục lần phép chia.

B:

IntroSort

Thuật toán cài đặt tốt nhất: IntroSort (std::sort) kết hợp std::string_view và mảng đệm 1 chiều (Fast I/O 1D Buffer).

Các phương thức tối ưu hóa:

Memory Pool (Buffer 1D): Cấp phát một mảng char khổng lồ đủ chứa toàn bộ file input. Đọc file vào mảng này bằng một lệnh đọc duy nhất (ví dụ fread).

String View / Pointer Array: Thay vì tạo một mảng std::string, tạo một mảng std::string_view (hoặc con trỏ char* kèm độ dài). Mỗi phần tử chỉ trỏ đến địa chỉ bắt đầu của chuỗi nằm trong mảng đệm 1D.

Sắp xếp con trỏ: Gọi std::sort trực tiếp trên mảng std::string_view.

Lý do:Loại bỏ Memory Allocation (Cấp phát động): Lớp std::string mặc định sẽ gọi new để cấp phát bộ nhớ trên Heap khi độ dài vượt quá 15 ký tự (SSO - Small String Optimization). Với 10^5 chuỗi 100 ký tự, việc gọi lệnh cấp phát hệ điều hành 10^5 lần sẽ bóp nghẹt hiệu năng. Memory Pool xử lý việc này trong O(1) thời gian.

Tối ưu hóa Băng thông RAM (Memory Bandwidth): Một cấu trúc std::string_view chỉ nặng đúng 16 bytes (1 con trỏ 8 bytes + 1 số nguyên kích thước 8 bytes). Khi std::sort thực hiện lệnh hoán đổi, CPU chỉ hoán đổi 16 bytes thay vì copy mảng 100 bytes dữ liệu. Khối lượng dữ liệu trao đổi qua bus RAM giảm hơn 6 lần.

C:

 Bucket Sort (Sắp xếp theo thùng) phân hoạch độ dài + IntroSort nội bộ.

Các phương thức tối ưu hóa:Phân hoạch trực tiếp O(N): Khởi tạo một mảng gồm 91 vector<string_view> (đại diện cho chiều dài từ 10 đến 100). Đọc độ dài chuỗi L và đẩy thẳng string_view vào mảng con ở index L - 10.Loại bỏ Comparator hỗn hợp: Không viết hàm so sánh đo độ dài rồi mới đo ký tự. Các chuỗi trong cùng một bucket mặc định đã có cùng độ dài.Sắp xếp phân mảnh: Chạy vòng lặp từ 0 đến 90, gọi std::sort thông thường trên từng bucket một.

Lý do:

Giảm bậc độ phức tạp (Complexity Reduction): Việc dùng std::sort toàn cục đòi hỏi hàm so sánh phải tính toán độ dài O(N \log N) lần. Phân hoạch bằng Bucket Sort xử lý thuộc tính "độ dài" chỉ trong một vòng lặp O(N). 

Tối ưu hóa CPU Cache L1/L2 (Cache Locality): Dữ liệu 10^4 phần tử bị chia nhỏ thành 91 bucket. Các bucket này có kích thước dữ liệu cực nhỏ, dễ dàng được nạp vừa khít vào bộ nhớ đệm Cache L1 (tốc độ siêu nhanh, độ trễ ~1ns) của CPU. Thuật toán std::sort khi chạy trên đoạn dữ liệu đã nằm sẵn trong L1 sẽ đẩy tốc độ thực thi (Instructions Per Clock) lên mức cực hạn do hoàn toàn không gặp hiện tượng Cache Miss.

3.

Cách thức sinh test case:

A:

test001.in (Đã sắp xếp tăng dần): Mảng đã được sắp xếp sẵn. Nếu ai dùng Quick Sort mà luôn chọn phần tử đầu tiên làm chốt (pivot), thuật toán sẽ bị biến thành O(N^2) và chạy quá thời gian (TLE).

test002.in (Sắp xếp giảm dần): Tương tự Test 1, mảng ngược hoàn toàn sẽ làm khó các thuật toán thiếu tối ưu.

test003.in (Toàn số giống nhau): 10^5 phần tử có giá trị y hệt nhau. Nếu code Quick Sort phân chia mảng không khéo (không xử lý tốt dấu bằng), chương trình sẽ bị lặp vô hạn hoặc tràn bộ nhớ .

test004.in (Cực đại và Cực tiểu xen kẽ): Xen kẽ số lớn nhất (2147483647) và số nhỏ nhất (-2147483648) của kiểu int. Test này tránh những người dùng mảng đếm (Counting Sort) bị tràn RAM hoặc xử lý bit dấu bị sai.

test005.in (Ngẫu nhiên): Kiểm tra tổng thể với thuật toán.

B:

test001.in (100,000 chuỗi giống hệt nhau): Sinh ra 10^5 chuỗi toàn ký tự 'a' dài đúng 100 ký tự. Khi so sánh hai chuỗi giống nhau, máy tính bắt buộc phải chạy từ ký tự thứ 1 đến ký tự thứ 100 mới đưa ra kết luận. Thao tác so sánh chuỗi lúc này đạt độ phức tạp tối đa.

test002.in (Chỉ khác biệt ký tự cuối cùng): Tạo ra các chuỗi có 99 ký tự đầu hoàn toàn giống nhau, ký tự thứ 100 sẽ tăng dần theo vòng lặp từ a đến z. Thuật toán sắp xếp sẽ phải qua 99 ký tự đầu vô ích trước khi tìm thấy sự khác biệt ở ký tự cuối cùng.

test003.in (Chuỗi dài 100 ký tự, thứ tự giảm dần): Sinh ra các chuỗi dài tối đa 100 ký tự nhưng xếp ngược từ điển từ trước. Phá vỡ luồng phân chia của các thuật toán Quick Sort dùng chốt mặc định.

test004.in (Trùng tiền tố, độ dài tăng dần): Sinh các chuỗi dạng a, aa, aaa, aaaa... tăng dần độ dài lên tới 100 nhưng xếp lộn xộn hoặc giảm dần để test khả năng xử lý độ dài chuỗi của thuật toán.

test005.in (Ngẫu nhiên): Sinh ngẫu nhiên cả độ dài (10 - 100) và ký tự ngẫu nhiên để test tính ổn định.

C:

test001.in (Cùng độ dài tối đa 100, xếp ngược từ điển): Sinh ra 10000 chuỗi đều có chiều dài tối đa là 100 ký tự, nhưng các ký tự được xếp giảm dần. Test này triệt tiêu hoàn toàn lợi thế so sánh độ dài, ép thuật toán phải quay về bài toán so sánh chuỗi của những code không tối ưu.

test002.in (Xen kẽ độ dài cực ngắn và cực dài): Sinh ra các chuỗi xen kẽ liên tục: một chuỗi dài 10 ký tự aaaa... rồi đến một chuỗi dài 100 ký tự zzzz.... Test này ép các thuật toán phải liên tục hoán đổi các vùng nhớ có kích thước chênh lệch lớn, dễ làm lộ lỗi tràn bộ nhớ hoặc lỗi index mảng đệm.

test003.in (Độ dài giảm ): Sinh ra các chuỗi có độ dài giảm dần từ 100 xuống 10 (ngược hoàn toàn với yêu cầu đề bài là xếp tăng dần độ dài). Đây là cấu trúc dữ liệu tồi tệ nhất đối với những người sử dụng các thuật toán sắp xếp dựa trên phân hoạch.

test004.in (Tất cả chuỗi giống hệt nhau và dài tối đa): Sinh ra 10000 chuỗi zzzz... dài đúng 100 ký tự. Test này bẫy các hàm Quick Sort tự viết không xử lý tốt trường hợp các phần tử bằng nhau.

test005.in (Ngẫu nhiên): Sinh ngẫu nhiên cả độ dài (10 - 100) và ký tự ngẫu nhiên để test tính ổn định.

4.

Bài A: 

Nâng cấp Radix Sort từ Base-256 (8-bit) lên Base-65536 (16-bit)

Thay vì chia số nguyên 32-bit thành 4 khối 8-bit (cần 4 vòng lặp), ta cắt nó làm 2 khối 16-bit.Cách làm: Dùng mặt nạ & 65535 và dịch bit >> 16. Mảng tần số đếm (Count Array) lúc này sẽ có kích thước 2^{16} = 65536 phần tử.

Lý do: Bạn giảm được một nửa số lần duyệt mảng và số lần hoán đổi dữ liệu qua lại giữa hai mảng đệm (từ 4 vòng xuống 2 vòng). Kích thước mảng đếm là 65536 x 4  bytes = 256  KB, vừa khít để nằm trọn vẹn bên trong bộ nhớ đệm L2 Cache của CPU. Việc truy xuất mảng đếm này sẽ có độ trễ gần như bằng không.

Bài B: 

Ép kiểu chuỗi thành số nguyên 64-bit (SWAR - SIMD Within A Register)Hàm std::sort khi so sánh hai chuỗi sẽ dùng memcmp hoặc vòng lặp để đọ từng ký tự (1 byte/lần). Điều này là quá chậm chạp!Cách làm: Ép kiểu (cast) con trỏ của 8 ký tự đầu tiên trong chuỗi thành một số nguyên uint64_t (8 bytes). Thực hiện phép so sánh < hoặc == trên hai số nguyên khổng lồ này. Chỉ khi nào 8 ký tự đầu giống hệt nhau, ta mới lùi về đọ từng byte ở các ký tự tiếp theo.Lý do: CPU 64-bit sinh ra là để xử lý số 64-bit. Nó có thể so sánh 8 ký tự cùng một lúc chỉ trong đúng 1 chu kỳ máy (1 clock cycle) thay vì phải lặp 8 lần. Kỹ thuật này lập tức x8 tốc độ so sánh chuỗi ở các bộ test có chuỗi phân kỳ sớm.Kỹ thuật 2: MSD Radix Sort cho chuỗi (thay vì IntroSort)Lý do: Nếu gặp Test 001 (toàn bộ $10^5$ chuỗi giống hệt nhau và dài 100 ký tự), IntroSort sẽ phải liên tục so sánh toàn bộ 100 ký tự của các cặp chuỗi để nhận ra chúng bằng nhau. MSD (Most Significant Digit) Radix Sort sẽ gom tất cả các chuỗi có chung ký tự đầu vào một nhóm, sau đó duyệt tịnh tiến cột theo chiều dọc. Nó loại bỏ hoàn toàn việc phải so sánh lại các tiền tố (prefix) đã biết, biến độ phức tạp tồi tệ nhất từ $O(L \cdot N \log N)$ xuống $O(\sum L)$.Bài C: strlenlexiKỹ thuật 1: Trải phẳng Vector bằng Counting Sort (Flat 1D Bucket Placement)Trong giải pháp trước, ta dùng mảng các std::vector để gom nhóm theo độ dài. Tuy nhiên, lệnh push_back() của Vector có chi phí ngầm: nó thi thoảng phải dừng lại để xin hệ điều hành cấp thêm bộ nhớ, gây đứt gãy luồng thực thi.Cách làm: 1. Quét mảng lần 1: Đếm số lượng chuỗi cho mỗi độ dài (từ 10 đến 100).2. Cộng dồn (Prefix Sum): Tính ra chính xác vị trí bắt đầu (index) của từng độ dài trên một mảng tĩnh (Array) duy nhất.3. Quét mảng lần 2: Đẩy thẳng con trỏ chuỗi vào mảng tĩnh dựa trên index đã tính.Lý do: Triệt tiêu 100% các lệnh cấp phát bộ nhớ động (Dynamic Allocation). Toàn bộ dữ liệu nằm trên một khối nhớ liền kề duy nhất, giúp thuật toán sắp xếp phía sau chạy mượt mà theo đúng cơ chế dự đoán rẽ nhánh của CPU phần cứng.Kỹ thuật 2: Gắn độ dài vào chung với con trỏ (Pointer Tagging / Fat Pointer)Cách làm: Thay vì chỉ lưu địa chỉ chuỗi (char*), ta tạo một struct gồm 8-byte con trỏ và 2-byte lưu chiều dài thực tế của nó (vì chiều dài tối đa chỉ là 100).Lý do: Mặc dù Bucket Sort đã nhóm theo độ dài, trong một số pha xử lý, việc truy xuất lại chiều dài để cắt vòng lặp so sánh là cần thiết. Nếu bạn gọi hàm tính độ dài hoặc truy cập vào nội dung chuỗi chỉ để lấy độ trễ, CPU sẽ bị Cache Miss. Việc nhét sẵn chiều dài ngay sát bên cạnh con trỏ giúp CPU bốc 1 lần được cả 2 thông tin (Cache Locality cực tốt).
