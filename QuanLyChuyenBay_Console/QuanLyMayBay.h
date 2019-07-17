#pragma once
#include "Objects.h"

struct QuanLyMayBay
{
private:
	int SoLuongMayBay;
	MayBay* DanhSach[300];	// mảng tuyến tính con trỏ chứa các đối tượng

public:
	static QuanLyMayBay* _instance; // biến thực thể toàn cục
	QuanLyMayBay();	// constructor

	static QuanLyMayBay * getinstance(); // lấy biến thực thể toàn cục
	int data_import(); // nhập dữ liệu từ file MayBay.txt
	int data_export(); // xuất dữ liệu ra file MayBay.txt

	void add(MayBay * value); // thêm máy bay vào danh sách 
	void delete_byposition(int i); // xoá máy bay khỏi danh sách dựa vào vị trí
	void update_byposition(int i, MayBay * value);	// cập nhật giá trị máy bay dựa vào vị trí

	std::string Build_SoHieuMayBay();	// tự động tạo mới số hiệu máy bay

	bool isLoaiHopLe(std::string str);	// kiểm tra chuỗi nhập vào cho Loại máy bay

	MayBay * getBy_SoHieuMayBay(std::string sohieu); // tìm kiếm máy bay dựa vào số hiệu
	std::vector<MayBay> getDanhSachMayBay(); // lấy danh sách máy bay, trả về dưới dạng vector

	// display
	int Menu();		 // hiển thị menu và xử lí input
	void ShowList(); // hiển thị danh sách máy bay
	int Add();	     // hiển thị màn hình thêm máy bay và xử lý input
	int Modify();    // hiển thị màn hình hiệu chỉnh máy bay và xử lý input
	int Delete();    // hiển thị màn hình xoá máy bay và xử lý input
	int Export();    // thực hiện xuất dữ liệu
};

