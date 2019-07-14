#include "QuanLyChuyenBay.h"
#include "Console.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

DanhSachChuyenBay * DanhSachChuyenBay::_instance = NULL;

DanhSachChuyenBay::DanhSachChuyenBay()
{
	SoLuongChuyenBay = 0;
	head = NULL;
	tail = NULL;
}

DanhSachChuyenBay * DanhSachChuyenBay::getinstance()
{
	if (_instance == NULL) _instance = new DanhSachChuyenBay();
	return _instance;
}

int DanhSachChuyenBay::data_import()
{
	std::ifstream in;
	in.open("data/ChuyenBay.txt");

	if (in.fail()) {
		in.close();
		return -1;
	}

	std::string line;

	in >> SoLuongChuyenBay;
	std::getline(in, line);

	for (int i = 0; i < SoLuongChuyenBay; i++) {
		ChuyenBay * chuyenbay = new ChuyenBay();

		std::getline(in, line);
		chuyenbay->MaChuyenBay = std::string(line);

		std::getline(in, line);
		chuyenbay->SoHieuMayBay = std::string(line);

		std::getline(in, line);
		chuyenbay->SanBayDen = std::string(line);

		in >> chuyenbay->NgayKhoiHanh.Nam >> chuyenbay->NgayKhoiHanh.Thang >> chuyenbay->NgayKhoiHanh.Ngay
			>> chuyenbay->NgayKhoiHanh.Gio >> chuyenbay->NgayKhoiHanh.Phut;
		in >> chuyenbay->TrangThai;
		std::getline(in, line);

		// Them vao linked list
		insert(*chuyenbay);
	}

	in.close();
	return 1;
}

int DanhSachChuyenBay::data_export()
{
	std::ofstream out;
	out.open("data/ChuyenBay.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << SoLuongChuyenBay << std::endl;

	node *temp = new node;
	temp = head;

	while (temp != NULL)
	{
		out << temp->data.MaChuyenBay.c_str() << endl;
		out << temp->data.SoHieuMayBay.c_str() << endl;
		out << temp->data.SanBayDen.c_str() << endl;
		out << temp->data.NgayKhoiHanh.Nam << temp->data.NgayKhoiHanh.Thang << temp->data.NgayKhoiHanh.Ngay
			<< temp->data.NgayKhoiHanh.Gio << temp->data.NgayKhoiHanh.Phut << endl;
		out << temp->data.TrangThai << endl;

		temp = temp->next;
	}

	out.close();
	return 1;
}

void DanhSachChuyenBay::insert(ChuyenBay value)
{
	SoLuongChuyenBay++;

	node *temp = new node;
	temp->data = value;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void DanhSachChuyenBay::delete_byposition(int pos)
{
	SoLuongChuyenBay--;

	node *current = new node;
	node *previous = new node;
	current = head;
	for (int i = 1; i < pos; i++)
	{
		previous = current;
		current = current->next;
	}
	previous->next = current->next;
}
