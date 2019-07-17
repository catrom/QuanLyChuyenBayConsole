#include "ThongKeBaoBieu.h"
#include "QuanLyChuyenBay.h"
#include "QuanLyMayBay.h"
#include "QuanLyHanhKhach.h"
#include "QuanLyVe.h"

ChuyenBay * ThongKeBaoBieu::KiemTraMaChuyenBay(std::string machuyenbay)
{
	if (!(machuyenbay.size() > 0 && machuyenbay.size() <= 15)) {
		ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Ma chuyen bay khong hop le!";
		return NULL;
	}

	ChuyenBay * chuyenbay = QuanLyChuyenBay::getinstance()->get_bymachuyenbay(machuyenbay);

	if (chuyenbay == NULL) { 	// kiem tra ton tai
		ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Ma chuyen bay khong ton tai!";
		return NULL;
	}

	return chuyenbay;
}

int ThongKeBaoBieu::Menu()
{
	while (1) {
		Clrscr();

		GotoXY(0, 0); SetColor(colorHeader); cout << "THONG KE - BAO CAO";
		GotoXY(5, 2); SetColor(colorCyan); cout << "1. Danh sach hanh khach thuoc chuyen bay";
		GotoXY(5, 3); SetColor(colorCyan); cout << "2. Danh sach chuyen bay khoi hanh trong ngay";
		GotoXY(5, 4); SetColor(colorCyan); cout << "3. Danh sach ve trong cua chuyen bay";
		GotoXY(5, 5); SetColor(colorCyan); cout << "4. Thong ke so luot thuc hien chuyen bay";
		GotoXY(5, 6); SetColor(colorCyan); cout << "5. Tro ve";

		int choose = -1;

		while (1) {
			int rollBack = 0;

			ClrLine(8); GotoXY(0, 8); SetColor(colorWhite); cout << "-> ";
			
			input->GetInput();
			if (!input->isInteger()) {
				ClrLine(9); GotoXY(0, 9); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
			}
			else {
				choose = StringToInteger(input->GetResult());

				switch (choose)
				{
				case 1:
					if (QuanLyHanhKhach() == -1) {
						rollBack = 1;
						break;
					}
				case 2:
					if (QuanLyChuyenBay() == -1) {
						rollBack = 1;
						break;
					}
				case 3:
					if (QuanLyVeTrong() == -1) {
						rollBack = 1;
						break;
					}
				case 4:
					if (SoLuotThucHienChuyenBay() == -1) {
						rollBack = 1;
						break;
					}
				case 5:
					return -1;
				default:
					ClrLine(9); GotoXY(0, 9); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
					break;
				}

				if (rollBack == 1)
					break;
			}
		}
	}
}

int ThongKeBaoBieu::QuanLyHanhKhach()
{
	// Nhap ma chuyen bay
	string machuyenbay;
	ChuyenBay * chuyenbay;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap ma chuyen bay: ";
		SetColor(colorYellow); 

		if (input->GetInput() == -1) return -1;
		machuyenbay = input->GetResult();

		chuyenbay = KiemTraMaChuyenBay(machuyenbay);

		if (chuyenbay)
			break;
	}

	// lay danh sach ve
	std::vector<Ve> danhsachve = QuanLyVe::getinstance()->getAll(machuyenbay);
	
	//  lay danh sach hanh khach
	std::vector<HanhKhach> danhsachhanhkhach;
	HanhKhach * hanhkhach;
	for (unsigned int i = 0; i < danhsachve.size(); i++) {
		hanhkhach = QuanLyHanhKhach::getinstance()->Find(danhsachve[i].SoCMND);
		danhsachhanhkhach.push_back(*hanhkhach);
	}

	// hien thi danh sach
	Clrscr();
	ShowQuanLyHanhKhach(*chuyenbay, danhsachve, danhsachhanhkhach);

	// luu
	GotoXY(5, 1); SetColor(colorCyan); cout << "1. Xuat danh sach";
	GotoXY(35, 1); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		ClrLine(3); GotoXY(0, 3); SetColor(colorWhite); cout << "-> ";
		
		if (input->GetInput() == -1) return -1;
		if (!input->isInteger()) {
			ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			switch (choose)
			{
			case 1:
				if (ExportQuanLyHanhKhach(*chuyenbay, danhsachve, danhsachhanhkhach) == 1) {
					ClrLine(4); GotoXY(0, 4);
					SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
					SetColor(colorYellow); cout << "...thongke/DanhSachHanhKhach.txt";
				}
				else {
					ClrLine(4); GotoXY(0, 4);
					SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
				}
				Sleep(2000);
				return -1;
			case 2:
				return -1;
			default:
				ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}
		}
	}
}

int ThongKeBaoBieu::ExportQuanLyHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach)
{
	std::ofstream out;
	out.open("thongke/DanhSachHanhKhach.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	ThoiGian c = chuyenbay.NgayKhoiHanh;

	out << "DANH SACH HANH KHACH THUOC CHUYEN BAY #" << chuyenbay.MaChuyenBay << std::endl;
	out << "Ngay khoi hanh: " << c.Nam << "/" << c.Thang << "/" << c.Ngay << " " << c.Gio << ":" << c.Phut << endl;
	out << "Noi den: " << chuyenbay.SanBayDen << endl << endl;

	out << "STT\t" << "SOVE\t" << "SO CMND\t\t" << "HOTEN\t\t\t" << "PHAI" << endl;

	for (unsigned int i = 0; i < dsve.size(); i++) {
		out << i + 1 << '\t';
		out << char(dsve[i].ViTriDay - 1 + 'A') << dsve[i].ViTriHang << '\t';
		out << dshanhkhach[i].SoCMND << '\t';
		out << dshanhkhach[i].Ho << " " << dshanhkhach[i].Ten << "\t\t";
		out << dshanhkhach[i].Phai << endl;
	}

	out.close();
	return 1;
}

void ThongKeBaoBieu::ShowQuanLyHanhKhach(ChuyenBay chuyenbay, std::vector<Ve> dsve, std::vector<HanhKhach> dshanhkhach)
{
	GotoXY(5, 6); SetColor(colorYellow); cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY #" << chuyenbay.MaChuyenBay;
	GotoXY(5, 7); SetColor(colorWhite); cout << "Ngay khoi hanh: "; QuanLyChuyenBay::getinstance()->ShowTime(chuyenbay.NgayKhoiHanh);
	GotoXY(5, 8); SetColor(colorWhite); cout << "Noi den: " << chuyenbay.SanBayDen;

	int lineStart = 9;

	// print header
	SetColor(colorDefault);
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 1); putchar(196); }
	GotoXY(5, lineStart + 2);
	cout << "| STT    | SO VE           | SO CMND         | HO TEN                       | PHAI       |";
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 3); putchar(196); }

	// print data
	for (unsigned int i = 0; i < dsve.size(); i++) {
		GotoXY(5, lineStart + 4 + 2 * i);
		cout << "|        |                 |                 |                              |            |";

		GotoXY(7, lineStart + 4 + 2 * i); cout << i + 1;	// STT;
		GotoXY(16, lineStart + 4 + 2 * i); cout << char(dsve[i].ViTriDay - 1 + 'A') << dsve[i].ViTriHang;
		GotoXY(34, lineStart + 4 + 2 * i); cout << dshanhkhach[i].SoCMND;
		GotoXY(52, lineStart + 4 + 2 * i); cout << dshanhkhach[i].Ho << " " << dshanhkhach[i].Ten;	
		GotoXY(83, lineStart + 4 + 2 * i); cout << dshanhkhach[i].Phai;	
		for (int j = 0; j < 90; j++) { GotoXY(j + 5, lineStart + 5 + 2 * i); putchar(196); }
	}
}

int ThongKeBaoBieu::QuanLyChuyenBay()
{
	ThoiGian ngaykhoihanh;
	string sanbayden;

	ngaykhoihanh.Gio = 0;
	ngaykhoihanh.Phut = 0;

	// Nhap ngay
	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap ngay khoi hanh (yyyy mm dd): ";
		SetColor(colorYellow); 

		if (input->GetInput() == -1) return -1;
		if (!input->isListOfIntegers()) {
			ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Ngay khoi hanh khong hop le!";
		}
		else {
			std::vector<int> split = input->splitIntegers();
			if (split.size() != 3) {
				ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Ngay khoi hanh khong hop le!";
			}
			else {
				ngaykhoihanh.Nam = split[0];
				ngaykhoihanh.Thang = split[1];
				ngaykhoihanh.Ngay = split[2];

				if (!ngaykhoihanh.HopLe()) {
					ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Ngay khoi hanh khong hop le!";
				}
				else break;
			}
		}
	}

	// Nhap san bay den
	while (1) {
		ClrLine(10); GotoXY(0, 10); SetColor(colorWhite); cout << "Nhap san bay den: ";
		SetColor(colorYellow); 

		if (input->GetInput() == -1) return -1;
		sanbayden = input->GetResult();

		if (!QuanLyChuyenBay::getinstance()->isSanBayDenHopLe(sanbayden)) {
			ClrLine(11); GotoXY(0, 11); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
		}
		else break;
	}

	// lấy tất cả chuyến bay trong ngày, đến nơi x
	vector<ChuyenBay> danhsachchuyenbay = QuanLyChuyenBay::getinstance()->getAll(ngaykhoihanh, LineStandardize(sanbayden));

	// lọc ra còn vé
	for (unsigned int i = 0; i < danhsachchuyenbay.size(); i++) {
		MayBay * maybay = QuanLyMayBay::getinstance()->getBy_SoHieuMayBay(danhsachchuyenbay[i].SoHieuMayBay);
		int soLuongVeHienTai = QuanLyVe::getinstance()->getAll(danhsachchuyenbay[i].MaChuyenBay).size();

		if (soLuongVeHienTai == maybay->SoDay * maybay->SoDong) { // het ve
			danhsachchuyenbay.erase(danhsachchuyenbay.begin() + i); // xoa khoi danh sach
			i--;
		}
	}

	// hien thi
	Clrscr();
	ShowQuanLyChuyenBay(ngaykhoihanh, sanbayden, danhsachchuyenbay);

	// luu
	GotoXY(5, 1); SetColor(colorCyan); cout << "1. Xuat danh sach";
	GotoXY(35, 1); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		ClrLine(3); GotoXY(0, 3); SetColor(colorWhite); cout << "-> ";
		
		if (input->GetInput() == -1) return -1;
		if (!input->isInteger()) {
			ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			switch (choose)
			{
			case 1:
				if (ExportQuanLyChuyenBay(ngaykhoihanh, sanbayden, danhsachchuyenbay) == 1) {
					GotoXY(0, 4);
					SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
					SetColor(colorYellow); cout << "...thongke/DanhSachChuyenBay.txt";
				}
				else {
					GotoXY(0, 4);
					SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
				}
				Sleep(2000);
				return -1;
			case 2:
				return -1;
			default:
				ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}
		}
	}
}

int ThongKeBaoBieu::ExportQuanLyChuyenBay(ThoiGian ngaykhoihanh, std::string sanbayden, std::vector<ChuyenBay> dschuyenbay)
{
	std::ofstream out;
	out.open("thongke/DanhSachChuyenBay.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << "DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY" << std::endl;
	out << "Ngay khoi hanh: " << ngaykhoihanh.Nam << "/" << ngaykhoihanh.Thang << "/" << ngaykhoihanh.Ngay << endl;
	out << "Noi den: " << sanbayden << endl << endl;

	out << "STT\t" << "MA CHUYEN BAY\t" << "SO HIEU MAY BAY\t" << "GIO KHOI HANH\t" << "SO LUONG VE TRONG" << endl;

	for (unsigned int i = 0; i < dschuyenbay.size(); i++) {
		MayBay * maybay = QuanLyMayBay::getinstance()->getBy_SoHieuMayBay(dschuyenbay[i].SoHieuMayBay);
		int soLuongVeHienTai = QuanLyVe::getinstance()->getAll(dschuyenbay[i].MaChuyenBay).size();
		int soLuongVeConTrong = maybay->SoDay * maybay->SoDong - soLuongVeHienTai;

		out << i + 1 << "\t";	// STT;
		out << dschuyenbay[i].MaChuyenBay << "\t\t";
		out << dschuyenbay[i].SoHieuMayBay << "\t\t";
		out << dschuyenbay[i].NgayKhoiHanh.Gio << ":" << dschuyenbay[i].NgayKhoiHanh.Phut << "\t\t";
		out << soLuongVeConTrong << endl;
	}

	out.close();
	return 1;
}

void ThongKeBaoBieu::ShowQuanLyChuyenBay(ThoiGian ngaykhoihanh, std::string sanbayden, std::vector<ChuyenBay> dschuyenbay)
{
	GotoXY(5, 6); SetColor(colorYellow); cout << "DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY";
	GotoXY(5, 7); SetColor(colorWhite); cout << "Ngay khoi hanh: " << ngaykhoihanh.Nam << "/" << ngaykhoihanh.Thang << "/" << ngaykhoihanh.Ngay;
	GotoXY(5, 8); SetColor(colorWhite); cout << "Noi den: " << LineStandardize(sanbayden);

	int lineStart = 9;

	// print header
	SetColor(colorDefault);
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 1); putchar(196); }
	GotoXY(5, lineStart + 2);
	cout << "| STT    | MA CHUYEN BAY     | SO HIEU MAY BAY   | GIO KHOI HANH    | SO LUONG VE TRONG  |";
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 3); putchar(196); }

	// print data
	for (unsigned int i = 0; i < dschuyenbay.size(); i++) {
		MayBay * maybay = QuanLyMayBay::getinstance()->getBy_SoHieuMayBay(dschuyenbay[i].SoHieuMayBay);
		int soLuongVeHienTai = QuanLyVe::getinstance()->getAll(dschuyenbay[i].MaChuyenBay).size();
		int soLuongVeConTrong = maybay->SoDay * maybay->SoDong - soLuongVeHienTai;

		GotoXY(5, lineStart + 4 + 2 * i);
		cout << "|        |                   |                   |                  |                    |";

		GotoXY(7, lineStart + 4 + 2 * i); cout << i + 1;	// STT;
		GotoXY(16, lineStart + 4 + 2 * i); cout << dschuyenbay[i].MaChuyenBay;
		GotoXY(36, lineStart + 4 + 2 * i); cout << dschuyenbay[i].SoHieuMayBay;
		GotoXY(56, lineStart + 4 + 2 * i); cout << dschuyenbay[i].NgayKhoiHanh.Gio << ":" << dschuyenbay[i].NgayKhoiHanh.Phut;
		GotoXY(76, lineStart + 4 + 2 * i); cout << soLuongVeConTrong;
		for (int j = 0; j < 90; j++) { GotoXY(j + 5, lineStart + 5 + 2 * i); putchar(196); }
	}
}

int ThongKeBaoBieu::QuanLyVeTrong()
{
	// Nhap ma chuyen bay
	string machuyenbay;
	ChuyenBay * chuyenbay;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap ma chuyen bay: ";
		SetColor(colorYellow); 

		if (input->GetInput() == -1) return -1;
		machuyenbay = input->GetResult();

		chuyenbay = KiemTraMaChuyenBay(machuyenbay);

		if (chuyenbay)
			break;
	}

	// lay danh sach ve
	std::vector<Ve> danhsachve = QuanLyVe::getinstance()->getAll(machuyenbay);

	// lay thong tin may bay
	MayBay * maybay = QuanLyMayBay::getinstance()->getBy_SoHieuMayBay(chuyenbay->SoHieuMayBay);

	// ma trận vị trí
	std::vector<std::vector<bool>> vitri(maybay->SoDong, std::vector<bool>(maybay->SoDay, false));

	// true: đã đặt, false: chưa đặt
	for (unsigned int i = 0; i < danhsachve.size(); i++) {
		vitri[danhsachve[i].ViTriHang - 1][danhsachve[i].ViTriDay - 1] = true;
	}

	// hien thi
	Clrscr();
	ShowQuanLyVeTrong(*chuyenbay, vitri);

	// luu
	GotoXY(5, 1); SetColor(colorCyan); cout << "1. Xuat danh sach";
	GotoXY(35, 1); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		ClrLine(3); GotoXY(0, 3); SetColor(colorWhite); cout << "-> ";
		
		if (input->GetInput() == -1) return -1;
		if (!input->isInteger()) {
			ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			switch (choose)
			{
			case 1:
				if (ExportQuanLyVeTrong(*chuyenbay, vitri) == 1) {
					GotoXY(0, 4);
					SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
					SetColor(colorYellow); cout << "...thongke/DanhSachVeTrong.txt";
				}
				else {
					GotoXY(0, 4);
					SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
				}
				Sleep(2000);
				return -1;
			case 2:
				return -1;
			default:
				ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}
		}
	}
}

int ThongKeBaoBieu::ExportQuanLyVeTrong(ChuyenBay chuyenbay, std::vector<std::vector<bool>> vitri)
{
	MayBay * maybay = QuanLyMayBay::getinstance()->getBy_SoHieuMayBay(chuyenbay.SoHieuMayBay);
	int soLuongVeHienTai = QuanLyVe::getinstance()->getAll(chuyenbay.MaChuyenBay).size();
	int soLuongVeConTrong = maybay->SoDay * maybay->SoDong - soLuongVeHienTai;

	std::ofstream out;
	out.open("thongke/DanhSachVeTrong.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	ThoiGian c = chuyenbay.NgayKhoiHanh;

	out << "DANH SACH VE TRONG CHUYEN BAY #" << chuyenbay.MaChuyenBay << std::endl;
	out << "Ngay khoi hanh: " << c.Nam << "/" << c.Thang << "/" << c.Ngay << " " << c.Gio << ":" << c.Phut << endl;
	out << "Noi den: " << chuyenbay.SanBayDen << endl;
	out << "So luong ve da dat: " << soLuongVeHienTai << endl;
	out << "So luong ve trong: " << soLuongVeConTrong << endl << endl;
	out << "Danh sach ve trong: " << endl;

	for (int i = 0; i < maybay->SoDong; i++) {
		for (int j = 0; j < maybay->SoDay; j++) {
			if (!vitri[i][j])
				out << char(j + 'A') << i + 1 << ", ";
		}
	}

	out.close();
	return 1;
}

void ThongKeBaoBieu::ShowQuanLyVeTrong(ChuyenBay chuyenbay, std::vector<std::vector<bool>> vitri)
{
	MayBay * maybay = QuanLyMayBay::getinstance()->getBy_SoHieuMayBay(chuyenbay.SoHieuMayBay);
	int soLuongVeHienTai = QuanLyVe::getinstance()->getAll(chuyenbay.MaChuyenBay).size();
	int soLuongVeConTrong = maybay->SoDay * maybay->SoDong - soLuongVeHienTai;

	int linestart = 11;
	int colstart = 8;

	GotoXY(5, 6); SetColor(colorYellow); cout << "DANH SACH DAT VE CHUYEN BAY #" << chuyenbay.MaChuyenBay;
	GotoXY(5, 7); SetColor(colorWhite); cout << "Ngay khoi hanh: "; QuanLyChuyenBay::getinstance()->ShowTime(chuyenbay.NgayKhoiHanh);
	GotoXY(5, 8); SetColor(colorWhite); cout << "Noi den: " << chuyenbay.SanBayDen;
	GotoXY(5, 8); SetColor(colorWhite); cout << "Ve da dat: ";
	SetColor(colorRed); putchar(254); 
	SetColor(colorWhite); cout << " So luong: " << soLuongVeHienTai;
	GotoXY(5, 9); SetColor(colorWhite); cout << "Ve trong:  ";
	SetColor(colorGreen); putchar(254);
	SetColor(colorWhite); cout << " So luong: " << soLuongVeConTrong;
	

	// print header
	for (int i = 0; i < maybay->SoDay; i++) {
		GotoXY(colstart + 2 * i, linestart); SetColor(colorWhite); cout << char(i + 'A');
	}

	for (int i = 0; i < maybay->SoDong; i++) {
		GotoXY(colstart - 1 - std::to_string(i + 1).size(), linestart + 1 + i); SetColor(colorWhite); cout << i + 1;
	}

	// print vi tri
	for (int i = 0; i < maybay->SoDong; i++) {
		for (int j = 0; j < maybay->SoDay; j++) {
			if (vitri[i][j]) // da dat ve
				SetColor(colorRed);
			else // ve trong
				SetColor(colorGreen);
			
			GotoXY(colstart + 2 * j, linestart + 1 + i); 
			putchar(254);
		}
	}

	GotoXY(5, linestart + maybay->SoDong + 2); SetColor(colorWhite); cout << "Danh sach ve con trong: ";
	// in thu tu
	GotoXY(5, linestart + maybay->SoDong + 3); SetColor(colorYellow);

	for (int i = 0; i < maybay->SoDong; i++) {
		for (int j = 0; j < maybay->SoDay; j++) {
			if (!vitri[i][j]) 
				cout << char(j + 'A') << i + 1 << ", ";
		}
	}
	
	GotoXY(WhereX() - 2, WhereY()); cout << ' ';
}

int ThongKeBaoBieu::SoLuotThucHienChuyenBay()
{
	std::vector<MayBay> dsmaybay = QuanLyMayBay::getinstance()->getDanhSachMayBay();
	std::vector<ChuyenBay> dschuyenbay = QuanLyChuyenBay::getinstance()->getAll();
	std::vector<int> soluotthuchien(dsmaybay.size());

	// counting
	for (unsigned int i = 0; i < dsmaybay.size(); i++) {
		int cnt = 0;
		for (unsigned int j = 0; j < dschuyenbay.size(); j++) {
			if (dsmaybay[i].SoHieuMayBay == dschuyenbay[j].SoHieuMayBay)
				cnt++;
		}
		soluotthuchien[i] = cnt;
	}

	// sorting
	for (unsigned int i = 0; i < soluotthuchien.size(); i++) {
		for (unsigned int j = i + 1; j < soluotthuchien.size(); j++) {
			if (soluotthuchien[i] < soluotthuchien[j]) {
				int itemp = soluotthuchien[i];
				soluotthuchien[i] = soluotthuchien[j];
				soluotthuchien[j] = itemp;

				MayBay mbtemp = dsmaybay[i];
				dsmaybay[i] = dsmaybay[j];
				dsmaybay[j] = mbtemp;
			}
		}
	}

	// show
	Clrscr();
	ShowSoLuotThucHienChuyenBay(dsmaybay, soluotthuchien);

	// luu
	GotoXY(5, 1); SetColor(colorCyan); cout << "1. Xuat danh sach";
	GotoXY(35, 1); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		ClrLine(3); GotoXY(0, 3); SetColor(colorWhite); cout << "-> ";
		
		if (input->GetInput() == -1) return -1;
		if (!input->isInteger()) {
			ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			switch (choose)
			{
			case 1:
				if (ExportSoLuotThucHienChuyenBay(dsmaybay, soluotthuchien) == 1) {
					GotoXY(0, 4);
					SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
					SetColor(colorYellow); cout << "...thongke/SoLuotThucHienChuyenBay.txt";
				}
				else {
					GotoXY(0, 4);
					SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
				}
				Sleep(2000);
				return -1;
			case 2:
				return -1;
			default:
				ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}
		}
	}
}

int ThongKeBaoBieu::ExportSoLuotThucHienChuyenBay(std::vector<MayBay> dsmaybay, std::vector<int> soluotthuchien)
{
	std::ofstream out;
	out.open("thongke/SoLuotThucHienChuyenBay.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << "THONG KE SO LUOT THUC HIEN CHUYEN BAY" << endl << endl;

	out << "STT\t" << "SO HIEU MAY BAY\t" << "LOAI MAY BAY\t" << "SO LUOT THUC HIEN CHUYEN BAY" << endl;

	for (unsigned int i = 0; i < dsmaybay.size(); i++) {
		out << i + 1 << "\t";	// STT;
		out << dsmaybay[i].SoHieuMayBay << "\t\t";
		out << dsmaybay[i].LoaiMayBay << "\t\t";
		out << soluotthuchien[i] << endl;
	}

	out.close();
	return 1;
}

void ThongKeBaoBieu::ShowSoLuotThucHienChuyenBay(std::vector<MayBay> dsmaybay, std::vector<int> soluotthuchien)
{
	GotoXY(5, 6); SetColor(colorYellow); cout << "THONG KE SO LUOT THUC HIEN CHUYEN BAY";

	int lineStart = 7;

	// print header
	SetColor(colorDefault);
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 1); putchar(196); }
	GotoXY(5, lineStart + 2);
	cout << "| STT    | SO HIEU MAY BAY        | LOAI MAY BAY          | SO LUOT THUC HIEN CHUYEN BAY |";
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 3); putchar(196); }

	// print data
	for (unsigned int i = 0; i < dsmaybay.size(); i++) {
		GotoXY(5, lineStart + 4 + 2 * i);
		cout << "|        |                        |                       |                              |";

		GotoXY(7, lineStart + 4 + 2 * i); cout << i + 1;	// STT;
		GotoXY(16, lineStart + 4 + 2 * i); cout << dsmaybay[i].SoHieuMayBay;
		GotoXY(41, lineStart + 4 + 2 * i); cout << dsmaybay[i].LoaiMayBay;
		GotoXY(65, lineStart + 4 + 2 * i); cout << soluotthuchien[i];
		for (int j = 0; j < 90; j++) { GotoXY(j + 5, lineStart + 5 + 2 * i); putchar(196); }
	}
}
