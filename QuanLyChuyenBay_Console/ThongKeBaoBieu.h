#pragma once
#include "Objects.h"

struct ThongKeBaoBieu 
{
public:
	ChuyenBay * KiemTraMaChuyenBay(std::string machuyenbay); // kiểm tra input mã chuyến bay

	int Menu(); // hiển thị menu và xử lý input

	int QuanLyHanhKhach(); // hiển thị màn hình xử lý danh sách hành khách thuộc chuyến bay
	int ExportQuanLyHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach); // Xuất danh sách ra file DanhSachHanhKhach.txt
	void ShowQuanLyHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach); // Hiển thị danh sách ra màn hình

	int QuanLyChuyenBay(); // hiển thị màn hình xử lý danh sách chuyến bay trong ngày + nơi đến
	int ExportQuanLyChuyenBay(ThoiGian ngaykhoihanh, std::string sanbayden, std::vector<ChuyenBay> dschuyenbay); // Xuất DanhSachChuyenBay.txt
	void ShowQuanLyChuyenBay(ThoiGian ngaykhoihanh, std::string sanbayden, std::vector<ChuyenBay> dschuyenbay); // Hiển thị

	int QuanLyVeTrong(); // hiển thị màn hình xử lý danh sách vé trống của chuyến bay
	int ExportQuanLyVeTrong(ChuyenBay chuyenbay, std::vector<std::vector<bool>> vitri); // Xuất  DanhSachVeTrong.txt
	void ShowQuanLyVeTrong(ChuyenBay chuyenbay, std::vector<std::vector<bool>> vitri); // Hiển thị

	int SoLuotThucHienChuyenBay(); // hiển thị màn hình xử lý số lượt thực hiện của máy bay
	int ExportSoLuotThucHienChuyenBay(std::vector<MayBay> dsmaybay, std::vector<int> soluotthuchien); // Xuất SoLuotThucHienChuyenBay.txt
	void ShowSoLuotThucHienChuyenBay(std::vector<MayBay> dsmaybay, std::vector<int> soluotthuchien); // Hiển thị
};