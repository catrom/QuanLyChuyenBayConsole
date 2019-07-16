#pragma once
#include "Objects.h"

struct node_ChuyenBay
{
	ChuyenBay data;
	node_ChuyenBay *next;
};

struct QuanLyChuyenBay
{
private:
	int SoLuongChuyenBay;
	node_ChuyenBay *head, *tail;

public:
	static QuanLyChuyenBay* _instance;
	QuanLyChuyenBay();

	static QuanLyChuyenBay * getinstance();
	int data_import();
	int data_export();

	void insert(ChuyenBay value);
	void update_byposition(int pos, ChuyenBay value);
	void delete_byposition(int pos);

	ChuyenBay get_byposition(int pos);
	ChuyenBay * get_bymachuyenbay(std::string machuyenbay);
	MayBay * getMayBay_bymachuyenbay(std::string machuyenbay);
	std::vector<ChuyenBay> getAll(ThoiGian t, std::string sanbayden);

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