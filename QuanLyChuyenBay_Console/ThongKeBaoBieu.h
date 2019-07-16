#pragma once
#include "Objects.h"

struct ThongKeBaoBieu 
{
public:
	ChuyenBay * KiemTraMaChuyenBay(std::string machuyenbay);

	int Menu();

	int QuanLyHanhKhach();
	int ExportQuanLyHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach);
	void ShowQuanLyHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach);

	int QuanLyChuyenBay();
	int ExportQuanLyChuyenBay(ThoiGian ngaykhoihanh, std::string sanbayden, std::vector<ChuyenBay> dschuyenbay);
	void ShowQuanLyChuyenBay(ThoiGian ngaykhoihanh, std::string sanbayden, std::vector<ChuyenBay> dschuyenbay);

	int QuanLyVeTrong();
	int ExportQuanLyVeTrong(ChuyenBay chuyenbay, std::vector<std::vector<bool>> vitri);
	void ShowQuanLyVeTrong(ChuyenBay chuyenbay, std::vector<std::vector<bool>> vitri);

	int SoLuotThucHienChuyenBay();
	int ExportSoLuotThucHienChuyenBay();
	void ShowSoLuotThucHienChuyenBay();
};