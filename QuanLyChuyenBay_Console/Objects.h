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
	int ViTriDay;
	int ViTriHang;
};

struct ThoiGian
{
	int Ngay;
	int Thang;
	int Nam;
	int Gio;
	int Phut;
};

struct ChuyenBay
{
	std::string MaChuyenBay;
	std::string SoHieuMayBay;
	std::string SanBayDen;
	ThoiGian NgayKhoiHanh;
	int TrangThai; // 0: hủy chuyến, 1: còn vé, 2: hết vé, 3: hoàn tất 
};

struct HanhKhach
{
	long SoCMND;
	std::string Ho;
	std::string Ten;
	std::string Phai;
};
