﻿#pragma once
#include "Objects.h"

struct node_Ve
{
	Ve data;
	node_Ve *next;
};

struct QuanLyVe
{
private:
	int SoLuongVe;
	node_Ve *head, *tail;

public:
	static QuanLyVe* _instance;
	QuanLyVe();

	static QuanLyVe * getinstance();
	int data_import();
	int data_export();

	void add(Ve value);
	void remove(std::string machuyenbay, long soCMND);
	Ve * find(std::string machuyenbay, long soCMND);
	std::vector<Ve> getAll(std::string machuyenbay);

	int KiemTraMaChuyenBay(std::string str);
	int KiemTraSoCMND(std::string str);
	int KiemTraDieuKienDatVe(std::string machuyenbay, long soCMND); // mỗi hành khách chỉ được đặt 1 vé trên chuyến bay
	int KiemTraViTriHopLe(int vitriday, int vitrihang); // kiểm tra số ghế có bị trùng lúc đặt hay không
	bool isHoTenHopLe(std::string str);
	bool isPhaiHopLe(int phai);
	bool isViTriDayHopLe(std::string str, int soday);
	bool isViTriDongHopLe(std::string str, int sodong);


	// display
	int Menu();
	int Add();
	int Remove();
	int Export();
	void ShowInfoChuyenBay(ChuyenBay * t);
	void ShowInfoHanhKhach(HanhKhach * t);
	void ShowInfoVe(Ve * t);
};