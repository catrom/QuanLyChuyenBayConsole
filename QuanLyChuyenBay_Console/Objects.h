#pragma once
#include "Utilities.h"

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

	bool HopLe() {
		if (Nam < 1900) return 0;
		if (Gio < 0 || Gio > 23) return 0;
		if (Phut < 0 || Phut > 59) return 0;

		switch (Thang)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (Ngay < 0 || Ngay > 31) return 0;
			break;
		case 4: case 6: case 9: case 11:
			if (Ngay < 0 || Ngay > 30) return 0;
			break;
		case 2:
			if ((Nam % 4 == 0 && Nam % 100 != 0) || (Nam % 400 == 0)) {
				if (Ngay < 0 || Ngay > 29) return 0;
			}
			else {
				if (Ngay < 0 || Ngay > 28) return 0;
			}
		default:
			return 0;
		}

		return 1;
	}
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
