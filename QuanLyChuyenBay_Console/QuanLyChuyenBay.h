#pragma once
#include "Objects.h"

struct node_ChuyenBay	// khai báo cấu trúc node của danh sách liên kết đơn
{
	ChuyenBay data;
	node_ChuyenBay *next;
};

struct QuanLyChuyenBay
{
private:
	int SoLuongChuyenBay; 
	node_ChuyenBay *head, *tail; // head, tail của danh sách liên kết đơn

public:
	static QuanLyChuyenBay* _instance;	// biến thực thể toàn cục
	QuanLyChuyenBay(); // constructor

	static QuanLyChuyenBay * getinstance();	// lấy biến thực thể toàn cục
	int data_import(); // nhập dữ liệu từ ChuyenBay.txt
	int data_export(); // xuất dữ liệu ra ChuyenBay.txt

	void insert(ChuyenBay value); // thêm dữ liệu vào danh sách liên kết (thêm đuôi)
	void update_byposition(int pos, ChuyenBay value); // cập nhật dựa vào số thứ tự trong danh sách
	void delete_byposition(int pos); // xoá dựa vào số thứ tự trong danh sách

	ChuyenBay get_byposition(int pos); // lấy thông tin dựa vào số thứ tự trong danh sách
	ChuyenBay * get_bymachuyenbay(std::string machuyenbay); // tìm kiếm chuyến bay dựa vào mã chuyến bay
	MayBay * getMayBay_bymachuyenbay(std::string machuyenbay); // lấy thông tin của máy bay dựa vào mã chuyến bay
	std::vector<ChuyenBay> getAll(); // lấy danh sách chuyến bay, trả về kiểu vector
	std::vector<ChuyenBay> getAll(ThoiGian t, std::string sanbayden); // lấy danh sách chuyến bay dựa vào ngày khởi hành và sân bay đến, trả về kiểu vector

	std::string Build_MaChuyenBay(); // tự động tạo mới mã chuyến bay

	bool isSoHieuMayBayHopLe(std::string str); // kiểm tra số hiệu hợp lệ
	bool isSanBayDenHopLe(std::string str); // kiểm tra sân bay đến hợp lệ
	bool isNgayKhoiHanhHopLe(ThoiGian tg); // kiểm tra ngày khởi hành hợp lệ
	bool isTrangThaiHopLe(int trangthai); // kiểm tra trạng thái hợp lệ

	// display
	int Menu(); // hiển thị menu và xử lý input
	void ShowList(); // hiển thị danh sách chuyến bay
	void ShowTime(ThoiGian c); // định dạng in ra của giá trị thời gian
	void ShowState(int state); // định dạng in ra của giá trị trạng thái 
	int Add(); // hiển thị màn hình thêm chuyến bay và xử lý input
	int Modify(); // hiển thị màn hình hiệu chỉnh chuyến bay và xử lý input
	int Delete(); // hiển thị màn hình xoá chuyến bay và xử lý input
	int Export(); // thực hiện xuất dữ liệu
};