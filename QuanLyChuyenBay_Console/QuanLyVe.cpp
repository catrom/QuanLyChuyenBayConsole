#include "QuanLyChuyenBay.h"
#include "QuanLyHanhKhach.h"
#include "QuanLyMayBay.h"
#include "QuanLyVe.h"

QuanLyVe * QuanLyVe::_instance = NULL;

QuanLyVe::QuanLyVe()
{
	SoLuongVe = 0;
	head = NULL;
	tail = NULL;
}

QuanLyVe * QuanLyVe::getinstance()
{
	if (_instance == NULL) _instance = new QuanLyVe();
	return _instance;
}

int QuanLyVe::data_import()
{
	std::ifstream in;
	in.open("data/Ve.txt");

	if (in.fail()) {
		in.close();
		return -1;
	}

	std::string line;
	int soluong;

	in >> soluong;
	std::getline(in, line);

	for (int i = 0; i < soluong; i++) {
		Ve * ve = new Ve();

		std::getline(in, line);
		ve->MaChuyenBay = std::string(line);

		in >> ve->SoCMND;
		in >> ve->ViTriDay;
		in >> ve->ViTriHang;

		std::getline(in, line);

		// Them vao linked list
		add(*ve);
	}

	in.close();
	return 1;
}

int QuanLyVe::data_export()
{
	std::ofstream out;
	out.open("data/Ve.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << SoLuongVe << std::endl;

	node_Ve *temp = new node_Ve;
	temp = head;

	while (temp != NULL)
	{
		out << temp->data.MaChuyenBay.c_str() << endl;
		out << temp->data.SoCMND << endl;
		out << temp->data.ViTriDay << endl;
		out << temp->data.ViTriHang << endl;

		temp = temp->next;
	}

	out.close();
	return 1;
}

void QuanLyVe::add(Ve value)
{
	SoLuongVe++;

	node_Ve *temp = new node_Ve;
	temp->data = value;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void QuanLyVe::remove(std::string machuyenbay, long soCMND)
{
	node_Ve *current = new node_Ve;
	node_Ve *previous = new node_Ve;

	current = head;

	while (current != NULL) {
		if (current->data.MaChuyenBay == machuyenbay && current->data.SoCMND == soCMND) {
			if (current == head) { // remove head
				head = head->next;
				delete current;
			}
			else {
				previous->next = current->next;
				delete current;
			}

			SoLuongVe--;
			return;
		}
		
		previous = current;
		current = current->next;
	}
}

Ve * QuanLyVe::find(std::string machuyenbay, long soCMND)
{
	node_Ve * temp = new node_Ve;
	temp = head;

	while (temp != NULL) {
		if (temp->data.MaChuyenBay == machuyenbay && temp->data.SoCMND == soCMND) {
			Ve * result = new Ve;
			*result = temp->data;
			return result;
		}

		temp = temp->next;
	}

	return NULL;
}

std::vector<Ve> QuanLyVe::getAll(std::string machuyenbay)
{
	vector<Ve> result;

	node_Ve * temp = new node_Ve;
	temp = head;

	while (temp != NULL) {
		if (temp->data.MaChuyenBay == machuyenbay) 
			result.push_back(temp->data);
		
		temp = temp->next;
	}

	return result;
}

int QuanLyVe::KiemTraMaChuyenBay(std::string str)
{
	if (!(str.size() > 0 && str.size() <= 15)) {
		ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Ma chuyen bay khong hop le!";
		return 0;
	}
	
	QuanLyChuyenBay * dschuyenbay = QuanLyChuyenBay::getinstance();
	ChuyenBay * chuyenbay = dschuyenbay->get_bymachuyenbay(str);

	if (chuyenbay == NULL) { 	// kiem tra ton tai
		ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "ERROR: Ma chuyen bay khong ton tai!";
		return 0;
	}

	// hien thi thong tin
	ShowInfoChuyenBay(chuyenbay);

	if (chuyenbay->TrangThai != 1) { // huy chuyen / het ve / hoan tat
		ClrLine(4); GotoXY(0, 4); SetColor(colorRed); cout << "INFO: Chuyen bay khong kha dung!";
		return -1;
	}

	return 1;
}

int QuanLyVe::KiemTraSoCMND(std::string str)
{
	if (str.size() == 0)
		return 0;

	for (int i = 0; i < str.size(); i++) {
		if (!(str[i] >= '0' && str[i] <= '9')) {
			ClrLine(7); GotoXY(0, 7); SetColor(colorRed); cout << "ERROR: So CMND khong hop le!";
			return 0;
		}
	}

	// kiem tra ton tai
	long soCMND = StringToInteger(str);
	QuanLyHanhKhach * dshanhkhach = QuanLyHanhKhach::getinstance();
	HanhKhach * hanhkhach = dshanhkhach->Find(soCMND);

	if (hanhkhach == NULL) {
		return -1;
	}
		
	// hien thi thong tin
	ShowInfoHanhKhach(hanhkhach);

	return 1;
}

int QuanLyVe::KiemTraDieuKienDatVe(std::string machuyenbay, long soCMND)
{
	node_Ve * temp = new node_Ve();
	temp = head;

	while (temp != NULL) {
		if (temp->data.MaChuyenBay == machuyenbay && temp->data.SoCMND == soCMND) { // da dat ve roi
			Ve * ve = new Ve;
			*ve = temp->data;
			ShowInfoVe(ve);

			return -1;
		}

		temp = temp->next;
	}

	return 1;
}

int QuanLyVe::KiemTraViTriHopLe(int vitriday, int vitrihang)
{
	node_Ve * temp = new node_Ve();
	temp = head;

	while (temp != NULL) {
		if (temp->data.ViTriDay == vitriday && temp->data.ViTriHang == vitrihang)
			return -1;

		temp = temp->next;
	}

	return 1;
}

bool QuanLyVe::isHoTenHopLe(std::string str)
{
	return str.size() > 0;
}

bool QuanLyVe::isPhaiHopLe(int phai)
{
	if (phai < 0 || phai > 1)
		return 0;

	return 1;
}

bool QuanLyVe::isViTriDayHopLe(std::string str, int soday)
{
	if (str.size() != 1)
		return 0;

	if (!(str[0] >= 'A' && str[0] - 'A' < soday))
		return 0;

	return 1;
}

bool QuanLyVe::isViTriDongHopLe(std::string str, int sodong)
{
	for (int i = 0; i < str.size(); i++) {
		if (!(str[i] >= '0' && str[i] <= '9'))
			return 0;
	}

	int vitri = StringToInteger(str);

	if (!(vitri >= 1 && vitri <= sodong))
		return 0;

	return 1;
}

int QuanLyVe::Menu()
{
	while (1) {
		Clrscr();

		GotoXY(0, 0); SetColor(colorHeader); cout << "QUAN LY VE";
		GotoXY(5, 2); SetColor(colorCyan); cout << "1. Dat ve";
		GotoXY(5, 3); SetColor(colorCyan); cout << "2. Huy ve";
		GotoXY(5, 4); SetColor(colorCyan); cout << "3. Xuat danh sach";
		GotoXY(5, 5); SetColor(colorCyan); cout << "4. Tro ve" << endl << endl;

		int choose = -1;

		while (1) {
			int rollBack = 0;

			SetCursorVisible(1);
			ClrLine(7); GotoXY(0, 7); SetColor(colorWhite); cout << "-> ";

			input->GetInput();
			if (!input->isInteger()) {
				ClrLine(8); GotoXY(0, 8); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
			}
			else {
				choose = StringToInteger(input->GetResult());

				switch (choose)
				{
				case 1:
					if (Add() == -1) {
						rollBack = 1;
						break;
					}
				case 2:
					if (Remove() == -1) {
						rollBack = 1;
						break;
					}
				case 3:
					if (Export() == -1) {
						rollBack = 1;
						break;
					}
				case 4:
					return -1;
				default:
					ClrLine(8); GotoXY(0, 8); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
					break;
				}

				if (rollBack == 1)
					break;
			}
		}
	}
}

int QuanLyVe::Add()
{
	Clrscr();
	GotoXY(0, 0); SetColor(colorHeader); cout << "DAT VE";

	Ve * ve = new Ve();
	int ketqua = 0;

	// Nhap ma chuyen bay
	ClrLine(2); GotoXY(5, 2); SetColor(colorWhite); cout << "* Nhap ma chuyen bay: ";
	while (1) {
		ClrLine(3);
		GotoXY(10, 3); SetColor(colorYellow);
		
		if (input->GetInput() == -1) return -1;
		ve->MaChuyenBay = input->GetResult();

		ketqua = KiemTraMaChuyenBay(ve->MaChuyenBay);
		
		if (ketqua == 1) {
			ClrLine(4);
			LineStandardize(ve->MaChuyenBay);
			break;
		}
	}

	// Nhap so CMND 
	GotoXY(5, 5); SetColor(colorWhite); cout << "* Nhap so CMND cua hanh khach: ";
	while (1) {
		ClrLine(6);
		string soCMND;
		GotoXY(10, 6); SetColor(colorYellow);
		
		if (input->GetInput() == -1) return -1;
		soCMND = input->GetResult();

		ketqua = KiemTraSoCMND(soCMND);

		if (ketqua) {
			ve->SoCMND = StringToInteger(soCMND);
			ClrLine(7);
			break;
		}
	}

	// Kiem tra dieu kien dat ve
	if (ketqua == 1) { // da co thong tin
		if (KiemTraDieuKienDatVe(ve->MaChuyenBay, ve->SoCMND) == -1) {
			ClrLine(8); GotoXY(0, 8); SetColor(colorRed); cout << "ERROR: Moi hanh khach chi duoc dat 1 ve!";
			getchar();
			return -1;
		}
	}

	// Nhap thong tin hanh khach
	if (ketqua == -1) { // chua co thong tin
		HanhKhach * hanhkhach = new HanhKhach();
		hanhkhach->SoCMND = ve->SoCMND;

		// Nhap ho
		while (1) {
			ClrLine(8);
			GotoXY(10, 8); SetColor(colorWhite); cout << "* Nhap ho: ";
			SetColor(colorYellow); 

			if (input->GetInput() == -1) return -1;
			hanhkhach->Ho = input->GetResult();

			if (!isHoTenHopLe(hanhkhach->Ho)) {
				ClrLine(9); GotoXY(0, 9); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
			}
			else {
				LineStandardize(hanhkhach->Ho);
				break;
			}
		}

		// Nhap ten
		while (1) {
			ClrLine(9);
			GotoXY(10, 9); SetColor(colorWhite); cout << "* Nhap ten: ";
			SetColor(colorYellow); 
			
			if (input->GetInput() == -1) return -1;
			hanhkhach->Ten = input->GetResult();

			if (!isHoTenHopLe(hanhkhach->Ten)) {
				ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
			}
			else {
				LineStandardize(hanhkhach->Ten);
				break;
			}
		}

		// Nhap phai
		while (1) {
			int iphai;
			ClrLine(10);
			GotoXY(10, 10); SetColor(colorWhite); cout << "* Nhap phai (0: Nam, 1: Nu): ";
			SetColor(colorYellow);

			if (input->GetInput() == -1) return -1;
			if (!input->isInteger()) {
				ClrLine(11); GotoXY(0, 11); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
			}
			else {
				iphai = StringToInteger(input->GetResult());

				if (!isPhaiHopLe(iphai)) {
					ClrLine(11); GotoXY(0, 11); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
				}
				else {
					hanhkhach->Phai = (iphai == 0 ? "Nam" : "Nu");
					ClrLine(11);
					break;
				}
			}
		}

		// Luu
		QuanLyHanhKhach * dshanhkhach = QuanLyHanhKhach::getinstance();
		dshanhkhach->Insert(*hanhkhach);
		ShowInfoHanhKhach(hanhkhach);
	}

	// Nhap thong tin vi tri day, vi tri dong
	// Lay thong tin may bay
	QuanLyChuyenBay * dschuyenbay = QuanLyChuyenBay::getinstance();
	MayBay * maybay = dschuyenbay->getMayBay_bymachuyenbay(ve->MaChuyenBay);

	int linestart = (ketqua == -1 ? 12 : 8);
	// Nhap day
	GotoXY(5, linestart); SetColor(colorWhite); cout << "* Nhap vi tri day (A - " << char(maybay->SoDay - 1 + 'A') << "):";

	while (1) {
		string day;
		ClrLine(linestart + 1);
		GotoXY(10, linestart + 1); 
		SetColor(colorYellow);

		if (input->GetInput() == -1) return -1;
		day = input->GetResult();

		if (!isViTriDayHopLe(day, maybay->SoDay)) {
			ClrLine(linestart + 2); GotoXY(0, linestart + 2); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
		}
		else {
			ve->ViTriDay = day[0] - 'A' + 1;
			ClrLine(linestart + 2);
			break;
		}
	}

	// Nhap dong
	GotoXY(5, linestart + 3); SetColor(colorWhite); cout << "* Nhap vi tri dong (1 - " << maybay->SoDong << "):";

	while (1) {
		string dong;
		ClrLine(linestart + 4);
		GotoXY(10, linestart + 4);
		SetColor(colorYellow); 

		if (input->GetInput() == -1) return -1;
		dong = input->GetResult();

		if (!isViTriDongHopLe(dong, maybay->SoDong)) {
			ClrLine(linestart + 5); GotoXY(0, linestart + 5); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
		}
		else {
			ve->ViTriHang = StringToInteger(dong);
			ClrLine(linestart + 5);
			break;
		}
	}

	// Kiem tra vi tri hop le
	if (KiemTraViTriHopLe(ve->ViTriDay, ve->ViTriHang) == -1) {
		ClrLine(linestart + 6); GotoXY(0, linestart + 6); SetColor(colorRed); cout << "ERROR: Vi tri trung!";
		getchar();
		return -1;
	}

	// hien thi thong tin ve
	ShowInfoVe(ve);

	// luu
	GotoXY(5, linestart + 7); SetColor(colorCyan); cout << "1. Luu";
	GotoXY(25, linestart + 7); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		SetCursorVisible(1);
		ClrLine(linestart + 9); GotoXY(0, linestart + 9); SetColor(colorWhite); cout << "-> ";
		
		if (input->GetInput() == -1) return -1;
		if (!input->isInteger()) {
			GotoXY(0, linestart + 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
		}
		else {
			choose = StringToInteger(input->GetResult());

			switch (choose)
			{
			case 1:
				add(*ve);
				GotoXY(0, linestart + 10); SetColor(colorCyan); cout << "INFO: Them thanh cong!";
				Sleep(2000);
				return -1;
			case 2:
				return -1;
			default:
				GotoXY(0, linestart + 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}
		}
	}
}

int QuanLyVe::Remove()
{
	Clrscr();
	GotoXY(0, 0); SetColor(colorHeader); cout << "HUY VE";

	string machuyenbay;
	string soCMND;
	int ketqua;

	// Nhap ma chuyen bay
	ClrLine(2); GotoXY(5, 2); SetColor(colorWhite); cout << "* Nhap ma chuyen bay: ";
	while (1) {
		ClrLine(3);
		GotoXY(10, 3); SetColor(colorYellow);
		
		if (input->GetInput() == -1) return -1;
		machuyenbay = input->GetResult();

		ketqua = KiemTraMaChuyenBay(machuyenbay);

		if (ketqua) {
			ClrLine(4);
			break;
		}
	}

	// Nhap so CMND 
	GotoXY(5, 5); SetColor(colorWhite); cout << "* Nhap so CMND cua hanh khach: ";
	while (1) {
		ClrLine(6);
		GotoXY(10, 6); SetColor(colorYellow);

		if (input->GetInput() == -1) return -1;
		soCMND = input->GetResult();

		ketqua = KiemTraSoCMND(soCMND);

		if (ketqua) {
			ClrLine(7);
			break;
		}
	}

	Ve * ve = find(machuyenbay, StringToInteger(soCMND));

	if (ve == NULL) { // ve khong ton tai
		ClrLine(7); GotoXY(0, 7); SetColor(colorRed); cout << "ERROR: Ve khong ton tai!";
		getchar();
		return -1;
	}
	else {
		ShowInfoVe(ve);
	}

	ClrLine(9); GotoXY(0, 9); SetColor(colorCyan); cout << "Xac nhan huy? (Y/N) ";

	while (1) {
		char c = InputKey();

		if (c == 'Y' || c == 'y') {
			remove(machuyenbay, StringToInteger(soCMND));
			ClrLine(10); GotoXY(0, 10); SetColor(colorCyan); cout << "INFO: Xoa thanh cong!";
			Sleep(2000);
			return -1;
		}
		else if (c == 'N' || c == 'n') {
			return -1;
		}
	}
}

int QuanLyVe::Export()
{
	QuanLyHanhKhach * dshanhkhach = QuanLyHanhKhach::getinstance();
	if (data_export() == -1 || dshanhkhach->data_export() == -1) {
		ClrLine(8); GotoXY(0, 8);
		SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
		Sleep(2000);
		return -1;
	}
	else {
		ClrLine(8); GotoXY(0, 8);
		SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
		SetColor(colorYellow); cout << "...data/Ve.txt";
		Sleep(2000);
		return -1;
	}
}

void QuanLyVe::ShowInfoChuyenBay(ChuyenBay * chuyenbay)
{
	for (int i = 5; i < 95; i++) {
		SetColor(colorDefault); GotoXY(i, 30); putchar(205);
	}

	QuanLyChuyenBay * dschuyenbay = QuanLyChuyenBay::getinstance();
	GotoXY(5, 31); SetColor(colorYellow); cout << "Thong tin chuyen bay: ";
	GotoXY(5, 32); SetColor(colorDefault); cout << "   Ma chuyen bay: " << chuyenbay->MaChuyenBay;
	GotoXY(5, 33); SetColor(colorDefault); cout << "   So hieu may bay: " << chuyenbay->SoHieuMayBay;
	GotoXY(5, 34); SetColor(colorDefault); cout << "   San bay den: " << chuyenbay->SanBayDen;
	GotoXY(5, 35); SetColor(colorDefault); cout << "   Ngay khoi hanh: "; dschuyenbay->ShowTime(chuyenbay->NgayKhoiHanh);
	GotoXY(5, 36); SetColor(colorDefault); cout << "   Trang thai: "; dschuyenbay->ShowState(chuyenbay->TrangThai);
}

void QuanLyVe::ShowInfoHanhKhach(HanhKhach * hanhkhach)
{
	for (int i = 5; i < 95; i++) {
		SetColor(colorDefault); GotoXY(i, 30); putchar(205);
	}

	GotoXY(50, 31); SetColor(colorYellow); cout << "Thong tin hanh khach: ";
	GotoXY(50, 32); SetColor(colorDefault); cout << "   So CMND: " << hanhkhach->SoCMND;
	GotoXY(50, 33); SetColor(colorDefault); cout << "   Ho: " << hanhkhach->Ho;
	GotoXY(50, 34); SetColor(colorDefault); cout << "   Ten: " << hanhkhach->Ten;
	GotoXY(50, 35); SetColor(colorDefault); cout << "   Phai: " << hanhkhach->Phai;
}

void QuanLyVe::ShowInfoVe(Ve * ve)
{
	for (int i = 5; i < 95; i++) {
		SetColor(colorDefault); GotoXY(i, 24); putchar(205);
	}

	GotoXY(5, 25); SetColor(colorYellow); cout << "Thong tin ve: ";
	GotoXY(5, 26); SetColor(colorDefault); cout << "   Ma chuyen bay: " << ve->MaChuyenBay;
	GotoXY(5, 27); SetColor(colorDefault); cout << "   So CMND: " << ve->SoCMND;
	GotoXY(5, 28); SetColor(colorDefault); cout << "   Vi tri: " << char(ve->ViTriDay - 1 + 'A') << ve->ViTriHang;
}
