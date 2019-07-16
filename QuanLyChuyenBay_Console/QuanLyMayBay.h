#pragma once
#include "Objects.h"

struct QuanLyMayBay
{
private:
	int SoLuongMayBay;
	MayBay* DanhSach[300];

public:
	static QuanLyMayBay* _instance;
	QuanLyMayBay();

	static QuanLyMayBay * getinstance();
	int data_import();
	int data_export();

	void add(MayBay * value);
	void delete_byposition(int i);
	void update_byposition(int i, MayBay * value);

	std::string Build_SoHieuMayBay();

	bool isLoaiHopLe(std::string str);

	MayBay * getBy_SoHieuMayBay(std::string sohieu);
	int getSoLuongMayBay();
	std::vector<MayBay> getDanhSachMayBay();

	// display
	int Menu();
	void ShowList();
	int Add();
	int Modify();
	int Delete();
	int Export();
};

