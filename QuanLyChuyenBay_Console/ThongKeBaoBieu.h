#pragma once
#include "Objects.h"

struct ThongKeBaoBieu 
{
public:
	ChuyenBay * KiemTraMaChuyenBay(std::string machuyenbay);

	int Menu();
	int DanhSachHanhKhach();
	int ExportDanhSachHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach);
	void ShowDanhSachHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach);

	int DanhSachChuyenBay();
	int ExportDanhSachChuyenBay();

	int DanhSachVeTrong();
	int ExportDanhSachVeTrong();

	int SoLuotThucHienChuyenBay();
	int ExportSoLuotThucHienChuyenBay();
};