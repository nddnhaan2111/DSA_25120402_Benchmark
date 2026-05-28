1.Cấu trúc dữ liệu giải thuật 2025-2026
MSSV: 25120402

Họ và tên: Nguyễn Đình Nhân

A:
2.Radix Sort kết hợp thao tác Bitwise.

Thuật toán chia nhỏ số nguyên 32-bit thành 4 byte riêng biệt và sắp xếp lần lượt từ byte thấp nhất đến byte cao nhất

Các thuật toán như Quick Sort hay Merge Sort là thuật toán "dựa trên so sánh" . Giới hạn tốc độ toán học của chúng luôn là O(Nlog N). Khi số lượng phần tử lên tới hàng triệu, CPU phải thực hiện hàng chục triệu phép so sánh rẽ nhánh. Radix Sort không hề so sánh hai số với nhau. Nó đếm và phân bổ các số theo từng chữ số/byte. Tốc độ của nó là nhanh hơn thuật toán so sánh khi tập dữ liệu đủ lớn.

Nếu bạn dùng vòng lặp chia dư cho 10 (% 10) để lấy từng chữ số, CPU phải thực hiện phép chia - một trong những lệnh tốn nhiều chu kỳ máy nhất. Việc tách số bằng hệ cơ số 256 (tương đương 1 byte) cho phép bạn dùng phép dịch bit (>>) và phép AND (&). Các phép toán bitwise này chạy trực tiếp ở cấp độ bóng bán dẫn của CPU, gần như tốn đúng 1 chu kỳ máy để hoàn thành, nhanh gấp hàng chục lần phép chia.

B:

IntroSort

Giới hạn chuỗi độ dài tối đa 100 cho phép std::sort vượt qua dễ dàng nếu biết cách tránh sao chép bộ nhớ dư thừa.

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