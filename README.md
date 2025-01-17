# QuanLyChuyenBay: Simple C++ Console Application

## Quản lý các chuyến bay nội địa thuộc 1 hãng hàng không.

### Tổ chức các danh sách như sau:
- Máy bay : mảng con trỏ có tối đa 300 máy bay. Mỗi máy bay có các thông tin (Số hiệu MB (C15), loại máy bay (C40), số dãy , số dòng) ;  Mỗi máy bay có 1 số hiệu duy nhất;  
  Nếu số dãy = 5 nghĩa là máy bay có các dãy A, B, C, D, E; Nếu số dòng = 20 nghĩa là máy bay có các hàng ghế được đánh số từ 1 đến 20. Kết hợp dãy và hàng ghế ta sẽ có số vé.
Theo ví dụ trên, ta có 100 vé với các số vé A01, A02, ...., A19, A20, …, E19, E20.
- Chuyến bay : danh sách liên kết đơn ( Mã CB (C15),  Ngày giờ khởi hành, sân bay đến , trạng thái, Số hiệu MB, danh sách vé). Mỗi chuyến bay có 1 mã duy nhất; trạng thái chuyến bay bao gồm: 0: hủy chuyến, 1:còn vé, 2:hết vé, 3:hoàn tất ; danh sách vé cho biết thông tin vé trên chuyến bay, và số CMND của hành khách đã đặt vé đó. Danh sách chuyến bay luôn có sẵn thứ tự theo mã chuyến bay
- Hành khách: cây nhị phân tìm kiếm (Số CMND , Ho, Ten,  Phai ("Nam", "Nu"))

### Chương trình có các chức năng sau: 
- Cập nhập danh sách các máy bay (thêm / xóa / hiệu chỉnh)
- Cập nhật chuyến bay: cho phép thêm / xóa / hiệu chỉnh chuyến bay, hiệu chỉnh ngày giờ khởi hành của chuyến bay , hủy chuyến.
- Đặt vé: cho phép đặt vé trên 1 chuyến bay; nếu thông tin hành khách chưa có thì tự động cập nhật vào danh sách hành khách, nếu có rồi thì in ra màn hình để kiểm tra. Mỗi vé đều phải ghi nhận số CMND của hành khách; nếu hành khách chưa có số CMND thì yêu cầu nhập thông tin hành khách trước. Trên 1 chuyến bay, mỗi hành khách chỉ được mua 1 vé.
- Hủy vé: cho phép hủy vé đã đặt của hành khách.
- In danh sách các hành khách thuộc 1 chuyến bay dựa vào mã chuyến bay. Kết xuất.
- In danh sách các chuyến bay khởi hành trong ngày dd/mm/yyyy đến nơi XXXX mà còn vé (cho biết cụ thể số lượng các vé còn trống và giờ khởi hành)
- In danh sách các vé còn trống của 1 chuyến bay có mã chuyến bay là X. 
- Thống kê số lượt thực hiện chuyến bay của từng máy bay theo thứ tự  số lượt thực hiện giảm dần. Kết xuất.

### Lưu ý: 
Chương trình cho phép lưu các danh sách vào file; Kiểm tra các điều kiện khi nhập liệu làm dữ liệu bị sai.
