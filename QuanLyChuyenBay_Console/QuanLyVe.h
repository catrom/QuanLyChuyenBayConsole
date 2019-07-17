#pragma once
#include "Objects.h"

struct node_Ve // định nghĩa node của danh sách liên kết đơn
{
	Ve data;
	node_Ve *next;
};

struct QuanLyVe
{
private:
	int SoLuongVe; 
	node_Ve *head, *tail; // head, tail

public:
	static QuanLyVe* _instance; // biến thực thể toàn cục
	QuanLyVe(); // constructor

	static QuanLyVe * getinstance(); // lấy biến thực thể toàn cục
	int data_import(); // nhập dữ liệu từ file Ve.txt
	int data_export(); // xuất dữ liệu ra file Ve.txt

	void add(Ve value); // thêm dữ liệu (thêm đuối) 
	void remove(std::string machuyenbay, long soCMND); // xoá dữ liệu dựa vào mã chuyến bay và số CMND của hành khách
	Ve * find(std::string machuyenbay, long soCMND); // tìm kiếm thông tin vé dựa vào mã chuyến bay và số CMND của hành khách
	std::vector<Ve> getAll(std::string machuyenbay); // lấy danh sách vé đã đặt của chuyến bay dựa vào mã chuyến bay

	int KiemTraMaChuyenBay(std::string str); // kiểm tra input mã chuyến bay
	int KiemTraSoCMND(std::string str); // kiểm tra input số CMND
	int KiemTraDieuKienDatVe(std::string machuyenbay, long soCMND); // mỗi hành khách chỉ được đặt 1 vé trên chuyến bay
	int KiemTraViTriHopLe(int vitriday, int vitrihang); // kiểm tra số ghế có bị trùng lúc đặt hay không
	bool isHoTenHopLe(std::string str); // kiểm tra input họ tên 
	bool isPhaiHopLe(int phai); // kiểm tra input phái
	bool isViTriDayHopLe(std::string str, int soday); // kiểm tra vị trí dãy hợp lệ
	bool isViTriDongHopLe(std::string str, int sodong); // kiểm tra vị trí dòng hợp lệ


	// display
	int Menu(); // hiển thị menu và xử lý input
	int Add(); // hiển thị màn hình đặt vé và xử lý input
	int Remove(); // hiển thị màn hình huỷ vé và xử lý input
	int Export(); // thực hiện xuất danh sách vé ra file
	void ShowInfoChuyenBay(ChuyenBay * t); // hiển thị thông tin chuyến bay
	void ShowInfoHanhKhach(HanhKhach * t); // hiển thị thông tin của hành khách
	void ShowInfoVe(Ve * t); // hiển thị thông tin vé
};