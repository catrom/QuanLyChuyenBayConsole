#pragma once

#include <time.h>
#include <iostream>

struct MayBay
{
	std::string SoHieuMayBay;
	std::string LoaiMayBay;
	int SoDay;
	int SoDong;
};

struct Ve
{
	std::string MaChuyenBay;
	long SoCMND;
};

struct ChuyenBay
{
	std::string MaChuyenBay;
	time_t GioKhoiHanh;
	std::string SanBayDen;
	int TrangThai;
	std::string SoHieuMayBay;
	Ve* DanhSachVe[1000];
};

struct HanhKhach
{
	long SoCMND;
	std::string Ho;
	std::string Ten;
	std::string Phai;
};
