#pragma once

#include "Objects.h"

struct node
{
	ChuyenBay data;
	node *next;
};

struct DanhSachChuyenBay
{
private:
	int SoLuongChuyenBay;
	node *head, *tail;

public:
	static DanhSachChuyenBay* _instance;
	DanhSachChuyenBay();

	static DanhSachChuyenBay * getinstance();
	int data_import();
	int data_export();

	void insert(ChuyenBay value);
	void update_byposition(int pos, ChuyenBay value);
	void delete_byposition(int pos);
	ChuyenBay get_byposition(int pos);

	bool isMaHopLe(std::string str);
	bool isSoHieuMayBayHopLe(std::string str);
	bool isSanBayDenHopLe(std::string str);
	bool isNgayKhoiHanhHopLe(ThoiGian tg);
	bool isTrangThaiHopLe(std::string str);

	// display
	int Menu();
	void ShowList();
	void ShowTime(ThoiGian c);
	void ShowState(int state);
	int Add();
	int Modify();
	int Delete();
	int Export();
};