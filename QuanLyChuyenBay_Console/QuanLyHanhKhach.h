#pragma once
#include "Objects.h"

struct node_HanhKhach // định nghĩa node của cây tìm kiếm nhị phân
{
	HanhKhach data;
	node_HanhKhach* left;
	node_HanhKhach* right;
};

struct QuanLyHanhKhach
{
private:
	int SoLuongHanhKhach; 
	node_HanhKhach* root; // root

public:
	static QuanLyHanhKhach* _instance; // biến thực thể toàn cục

	QuanLyHanhKhach(); // constructor
	~QuanLyHanhKhach(); // destructor

	static QuanLyHanhKhach * getinstance(); // lấy biến thực thể toàn cục
	int data_import(); // nhập dữ liệu từ file HanhKhach.txt
	int data_export(); // xuất dữ liệu ra file HanhKhach.txt
	void recursion_data_export(std::ofstream &out, node_HanhKhach* t); // vì cây tìm kiếm nhị phân hiện theo thuật toán đệ quy, do đó việc duyệt từng node để xuất ra file cũng phải thực hiện theo đệ quy

	node_HanhKhach* clear(node_HanhKhach* t); // huỷ cây nhị phân
	node_HanhKhach* insert(HanhKhach x, node_HanhKhach* t); // thêm dữ liệu (đệ quy)
	node_HanhKhach* findMin(node_HanhKhach* t); // tìm kiếm giá trị nhỏ nhất
	node_HanhKhach* findMax(node_HanhKhach* t); // tìm kiếm giá trị lớn nhất
	node_HanhKhach* remove(HanhKhach x, node_HanhKhach* t); // huỷ liên kết giá trị trong cây nhị phân
	node_HanhKhach* find(node_HanhKhach* t, long soCMND); // tìm kiếm hành khách dựa vào số CMND (đệ quy)

	HanhKhach* Find(long soCMND); // tìm kiếm hành khách dựa vào số CMND
	void Insert(HanhKhach x); // thêm dữ liệu
};
