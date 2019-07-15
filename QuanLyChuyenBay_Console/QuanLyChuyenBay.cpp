#include "QuanLyChuyenBay.h"
#include "QuanLyMayBay.h"

DanhSachChuyenBay * DanhSachChuyenBay::_instance = NULL;

DanhSachChuyenBay::DanhSachChuyenBay()
{
	SoLuongChuyenBay = 0;
	head = NULL;
	tail = NULL;
}

DanhSachChuyenBay * DanhSachChuyenBay::getinstance()
{
	if (_instance == NULL) _instance = new DanhSachChuyenBay();
	return _instance;
}

int DanhSachChuyenBay::data_import()
{
	std::ifstream in;
	in.open("data/ChuyenBay.txt");

	if (in.fail()) {
		in.close();
		return -1;
	}

	std::string line;
	int soluong;

	in >> soluong;
	std::getline(in, line);

	for (int i = 0; i < soluong; i++) {
		ChuyenBay * chuyenbay = new ChuyenBay();

		std::getline(in, line);
		chuyenbay->MaChuyenBay = std::string(line);

		std::getline(in, line);
		chuyenbay->SoHieuMayBay = std::string(line);

		std::getline(in, line);
		chuyenbay->SanBayDen = std::string(line);

		in >> chuyenbay->NgayKhoiHanh.Nam >> chuyenbay->NgayKhoiHanh.Thang >> chuyenbay->NgayKhoiHanh.Ngay
			>> chuyenbay->NgayKhoiHanh.Gio >> chuyenbay->NgayKhoiHanh.Phut;
		in >> chuyenbay->TrangThai;
		std::getline(in, line);

		// Them vao linked list
		insert(*chuyenbay);
	}

	in.close();
	return 1;
}

int DanhSachChuyenBay::data_export()
{
	std::ofstream out;
	out.open("data/ChuyenBay.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << SoLuongChuyenBay << std::endl;

	node_ChuyenBay *temp = new node_ChuyenBay;
	temp = head;

	while (temp != NULL)
	{
		out << temp->data.MaChuyenBay.c_str() << endl;
		out << temp->data.SoHieuMayBay.c_str() << endl;
		out << temp->data.SanBayDen.c_str() << endl;
		out << temp->data.NgayKhoiHanh.Nam << " ";
		out << temp->data.NgayKhoiHanh.Thang << " ";
		out << temp->data.NgayKhoiHanh.Ngay << " ";
		out << temp->data.NgayKhoiHanh.Gio << " ";
		out << temp->data.NgayKhoiHanh.Phut << endl;
		out << temp->data.TrangThai << endl;

		temp = temp->next;
	}

	out.close();
	return 1;
}

void DanhSachChuyenBay::insert(ChuyenBay value)
{
	SoLuongChuyenBay++;

	node_ChuyenBay *temp = new node_ChuyenBay;
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

void DanhSachChuyenBay::update_byposition(int pos, ChuyenBay value)
{
	node_ChuyenBay * current = new node_ChuyenBay;
	current = head;

	for (int i = 0; i < pos; i++)
		current = current->next;

	current->data = value;
}

void DanhSachChuyenBay::delete_byposition(int pos)
{
	SoLuongChuyenBay--;

	node_ChuyenBay *current = new node_ChuyenBay;
	node_ChuyenBay *previous = new node_ChuyenBay;
	current = head;

	if (pos == 0) { // delete head
		head = head->next;
		delete current;
		return;
	}

	for (int i = 0; i < pos; i++)
	{
		previous = current;
		current = current->next;
	}

	previous->next = current->next;
}

ChuyenBay DanhSachChuyenBay::get_byposition(int pos)
{
	node_ChuyenBay *current = new node_ChuyenBay;
	current = head;

	for (int i = 0; i < pos; i++)
		current = current->next;

	return current->data;
}

ChuyenBay * DanhSachChuyenBay::get_bymachuyenbay(std::string machuyenbay)
{
	ChuyenBay * res = new ChuyenBay();

	node_ChuyenBay * temp = new node_ChuyenBay();
	temp = head;

	while (temp != NULL) {
		if (temp->data.MaChuyenBay == machuyenbay) {
			*res = temp->data;
			return res;
		}
		temp = temp->next;
	}

	return NULL;
}

MayBay * DanhSachChuyenBay::getMayBay_bymachuyenbay(std::string machuyenbay)
{
	ChuyenBay * chuyenbay = get_bymachuyenbay(machuyenbay);

	if (chuyenbay == NULL)
		return NULL;

	DanhSachMayBay * dsmaybay = DanhSachMayBay::getinstance();
	MayBay * maybay = dsmaybay->getBy_SoHieuMayBay(chuyenbay->SoHieuMayBay);

	return maybay;
}

bool DanhSachChuyenBay::isMaHopLe(string str)
{
	return str.size() > 0 && str.size() <= 15;
}

bool DanhSachChuyenBay::isSoHieuMayBayHopLe(std::string str)
{
	if (!(str.size() > 0 && str.size() <= 15))
		return 0;

	// kiểm tra ma máy bay có tồn tại hay không
	DanhSachMayBay * dsmaybay = DanhSachMayBay::getinstance();
	if (!dsmaybay->getBy_SoHieuMayBay(str))
		return 0;

	return 1;
}

bool DanhSachChuyenBay::isSanBayDenHopLe(std::string str)
{
	return str.size() > 0;
}

bool DanhSachChuyenBay::isNgayKhoiHanhHopLe(ThoiGian tg)
{
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);

	if (tg.Nam < now->tm_year + 1900) return 0;
	if (tg.Thang < now->tm_mon + 1) return 0;
	if ((tg.Thang == now->tm_mon + 1 && tg.Ngay < now->tm_mday)) return 0;
	if (tg.Gio < 0 || tg.Gio > 23) return 0;
	if (tg.Phut < 0 || tg.Phut > 59) return 0;
	
	return 1;
}

bool DanhSachChuyenBay::isTrangThaiHopLe(std::string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (!(str[i] >= '0' && str[i] <= '9'))
			return 0;
	}

	if (StringToInteger(str) < 0 || StringToInteger(str) > 3)
		return 0;

	return 1;
}

int DanhSachChuyenBay::Menu()
{
	while (1) {
		Clrscr();
		ShowList();

		GotoXY(0, 0); SetColor(colorGreen); cout << "QUAN LY CHUYEN BAY";
		GotoXY(5, 2); SetColor(colorCyan); cout << "1. Them chuyen bay";
		GotoXY(5, 3); SetColor(colorCyan); cout << "2. Hieu chinh chuyen bay";
		GotoXY(5, 4); SetColor(colorCyan); cout << "3. Xoa chuyen bay";
		GotoXY(5, 5); SetColor(colorCyan); cout << "4. Xuat danh sach";
		GotoXY(5, 6); SetColor(colorCyan); cout << "5. Tro ve" << endl << endl;

		int choose = -1;

		while (1) {
			int rollBack = 0;

			SetCursorVisible(1);
			ClrLine(8); GotoXY(0, 8); SetColor(colorWhite); cout << "-> ";
			cin >> choose;

			switch (choose)
			{
			case 1:
				if (Add() == -1) {
					rollBack = 1;
					break;
				}
			case 2:
				if (Modify() == -1) {
					rollBack = 1;
					break;
				}
			case 3:
				if (Delete() == -1) {
					rollBack = 1;
					break;
				}
			case 4:
				if (Export() == -1) {
					rollBack = 1;
					break;
				}
			case 5:
				return -1;
			default:
				SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}

			if (rollBack == 1)
				break;
		}
	}
}

void DanhSachChuyenBay::ShowList()
{
	int lineStart = 12;
	GotoXY(5, lineStart); SetColor(colorYellow); cout << ">> Danh sach chuyen bay:";

	// print header
	SetColor(colorDefault);
	for (int i = 0; i < 100; i++) { GotoXY(i, lineStart + 1); putchar(196); }
	GotoXY(0, lineStart + 2);
	cout << "| STT  | Ma chuyen bay    | So hieu may bay  | San bay den        | Ngay khoi hanh   | Trang thai  |";
	for (int i = 0; i < 100; i++) { GotoXY(i, lineStart + 3); putchar(196); }

	// print data
	node_ChuyenBay * current = new node_ChuyenBay;
	current = head;
	for (int i = 0; i < SoLuongChuyenBay; i++, current = current->next) {
		GotoXY(0, lineStart + 4 + 2 * i);
		cout << "|      |                  |                  |                    |                  |             |";

		GotoXY(2, lineStart + 4 + 2 * i); cout << i + 1;	// STT;
		GotoXY(9, lineStart + 4 + 2 * i); cout << current->data.MaChuyenBay;	// So Hieu
		GotoXY(28, lineStart + 4 + 2 * i); cout << current->data.SoHieuMayBay;	// So loai
		GotoXY(47, lineStart + 4 + 2 * i); cout << current->data.SanBayDen;	// So day
		GotoXY(68, lineStart + 4 + 2 * i); ShowTime(current->data.NgayKhoiHanh);
		GotoXY(87, lineStart + 4 + 2 * i); ShowState(current->data.TrangThai);
		for (int j = 0; j < 100; j++) { GotoXY(j, lineStart + 5 + 2 * i); putchar(196); }
	}
}

void DanhSachChuyenBay::ShowTime(ThoiGian c)
{
	cout << c.Nam << "/" << c.Thang << "/" << c.Ngay << " " << c.Gio << ":" << c.Phut;
}

void DanhSachChuyenBay::ShowState(int state)
{
	switch (state)
	{
	case 0: cout << "Huy chuyen"; break;
	case 1: cout << "Con ve"; break;
	case 2: cout << "Het ve"; break;
	case 3: cout << "Hoan tat"; break;
	default:
		break;
	}
}

int DanhSachChuyenBay::Add()
{
	Clrscr();
	GotoXY(0, 0); SetColor(colorGreen); cout << "THEM CHUYEN BAY";

	ChuyenBay * chuyenbay = new ChuyenBay();

	// Nhap ma chuyen bay
	ClrLine(2); GotoXY(5, 2); SetColor(colorWhite); cout << "* Nhap ma chuyen bay: ";
	while (1) {
		ClrLine(3);
		GotoXY(10, 3); SetColor(colorYellow);
		cin.ignore(); getline(cin, chuyenbay->MaChuyenBay);

		if (!isMaHopLe(chuyenbay->MaChuyenBay)) {
			SetColor(colorRed); cout << "ERROR: Ma chuyen bay khong hop le!";
		}
		else {
			LineStandardize(chuyenbay->MaChuyenBay);
			break;
		}
	}

	// Nhap so hieu may bay
	ClrLine(4); GotoXY(5, 4); SetColor(colorWhite); cout << "* Nhap so hieu may bay: ";
	while (1) {
		ClrLine(5);
		GotoXY(10, 5); SetColor(colorYellow);
		getline(cin, chuyenbay->SoHieuMayBay);

		if (!isSoHieuMayBayHopLe(chuyenbay->SoHieuMayBay)) {
			SetColor(colorRed); cout << "ERROR: So hieu may bay khong hop le hoac khong ton tai!";
		}
		else {
			LineStandardize(chuyenbay->SoHieuMayBay);
			break;
		}
	}

	// Nhap san bay den
	ClrLine(6); GotoXY(5, 6); SetColor(colorWhite); cout << "* Nhap san bay den: ";
	while (1) {
		ClrLine(7);
		GotoXY(10, 7); SetColor(colorYellow);
		getline(cin, chuyenbay->SanBayDen);

		if (!isSanBayDenHopLe(chuyenbay->SanBayDen)) {
			SetColor(colorRed); cout << "ERROR: San bay den khong hop le!";
		}
		else {
			LineStandardize(chuyenbay->SanBayDen);
			break;
		}
	}

	// Nhap ngay khoi hanh
	ClrLine(8); GotoXY(5, 8); SetColor(colorWhite); cout << "* Nhap thoi gian khoi hanh (yyyy mm dd hh mm): ";
	while (1) {
		string soday;
		ClrLine(9);
		GotoXY(10, 9); SetColor(colorYellow);
		cin >> chuyenbay->NgayKhoiHanh.Nam >> chuyenbay->NgayKhoiHanh.Thang >> chuyenbay->NgayKhoiHanh.Ngay
			>> chuyenbay->NgayKhoiHanh.Gio >> chuyenbay->NgayKhoiHanh.Phut;

		if (!isNgayKhoiHanhHopLe(chuyenbay->NgayKhoiHanh)) {
			SetColor(colorRed); cout << "ERROR: Ngay khoi hanh khong hop le!";
		}
		else {
			break;
		}
	}

	// Nhap trang thai
	ClrLine(10); GotoXY(5, 10); SetColor(colorWhite); cout << "* Nhap trang thai (0: huy chuyen, 1: con ve, 2: het ve, 3: hoan tat): ";
	while (1) {
		string trangthai;
		ClrLine(11);
		GotoXY(10, 11); SetColor(colorYellow);
		getline(cin, trangthai);

		if (!isTrangThaiHopLe(trangthai)) {
			SetColor(colorRed); cout << "ERROR: Trang thai khong hop le!";
		}
		else {
			chuyenbay->TrangThai = StringToInteger(trangthai);
			break;
		}
	}

	ClrLine(12);
	GotoXY(5, 13); SetColor(colorCyan); cout << "1. Luu";
	GotoXY(25, 13); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		SetCursorVisible(1);
		ClrLine(15); GotoXY(0, 15); SetColor(colorWhite); cout << "-> ";
		cin >> choose;

		switch (choose)
		{
		case 1:
			insert(*chuyenbay);
			GotoXY(0, 16); SetColor(colorCyan); cout << "INFO: Them thanh cong!";
			Sleep(2000);
			return -1;
		case 2:
			return -1;
		default:
			SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
			break;
		}
	}
}

int DanhSachChuyenBay::Modify()
{
	int choose = -1;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap so thu tu trong danh sach: ";
		SetColor(colorYellow); cin >> choose;

		if (choose < 1 || choose > SoLuongChuyenBay) {
			SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			Clrscr();
			GotoXY(0, 0); SetColor(colorGreen); cout << "HIEU CHINH MAY BAY";
			int index = choose - 1;

			ChuyenBay * chuyenbay = new ChuyenBay();
			*chuyenbay = get_byposition(index);

			ClrLine(2); GotoXY(5, 2); SetColor(colorWhite); cout << "Ma chuyen bay: " << chuyenbay->MaChuyenBay;
			ClrLine(3); GotoXY(5, 3); SetColor(colorWhite); cout << "So hieu may bay: " << chuyenbay->SoHieuMayBay;
			ClrLine(4); GotoXY(5, 4); SetColor(colorWhite); cout << "San bay den: " << chuyenbay->SanBayDen;

			// Nhap ngay khoi hanh
			ClrLine(6); GotoXY(5, 6); SetColor(colorWhite); cout << "Ngay khoi hanh: "; ShowTime(chuyenbay->NgayKhoiHanh);
			ClrLine(7); GotoXY(5, 7); SetColor(colorCyan); cout << "Hieu chinh Ngay khoi hanh? (Y/N) ";

			while (1) {
				char c = InputKey();
				bool ok = 0;

				if (c == 'Y' || c == 'y') {
					while (1) {
						ClrLine(7); GotoXY(5, 7); SetColor(colorWhite); cout << "* Nhap thoi gian khoi hanh (yyyy mm dd hh mm): ";
						SetColor(colorYellow); 
						cin >> chuyenbay->NgayKhoiHanh.Nam >> chuyenbay->NgayKhoiHanh.Thang >> chuyenbay->NgayKhoiHanh.Ngay
							>> chuyenbay->NgayKhoiHanh.Gio >> chuyenbay->NgayKhoiHanh.Phut;
						cin.ignore();

						if (!isNgayKhoiHanhHopLe(chuyenbay->NgayKhoiHanh)) {
							SetColor(colorRed); cout << "ERROR: Ngay khoi hanh khong hop le!";
						}
						else {
							ok = 1;
							break;
						}
					}
				}
				else if (c == 'N' || c == 'n') {
					ClrLine(7);
					cin.ignore();
					break;
				}

				if (ok) break;
			}

			// Nhap trang thai
			ClrLine(8); GotoXY(5, 8); SetColor(colorWhite); cout << "Trang thai: "; ShowState(chuyenbay->TrangThai);
			ClrLine(9); GotoXY(5, 9); SetColor(colorCyan); cout << "Hieu chinh Trang thai? (Y/N) ";

			while (1) {
				char c = InputKey();
				bool ok = 0;
				string trangthai;

				if (c == 'Y' || c == 'y') {
					while (1) {
						ClrLine(9); GotoXY(5, 9); SetColor(colorWhite); cout << "* Nhap trang thai (0: huy chuyen, 1: con ve, 2: het ve, 3: hoan tat): ";
						SetColor(colorYellow);
						getline(cin, trangthai);

						if (!isTrangThaiHopLe(trangthai)) {
							SetColor(colorRed); cout << "ERROR: Trang thai khong hop le!";
						}
						else {
							chuyenbay->TrangThai = StringToInteger(trangthai);
							ok = 1;
							break;
						}
					}
				}
				else if (c == 'N' || c == 'n') {
					ClrLine(9);
					//cin.ignore();
					break;
				}

				if (ok) break;
			}

			ClrLine(10);
			GotoXY(5, 11); SetColor(colorCyan); cout << "1. Luu";
			GotoXY(25, 11); SetColor(colorCyan); cout << "2. Tro ve";

			while (1) {
				SetCursorVisible(1);
				ClrLine(13); GotoXY(0, 13); SetColor(colorWhite); cout << "-> ";
				cin >> choose;

				switch (choose)
				{
				case 1:
					update_byposition(index, *chuyenbay);
					GotoXY(0, 14); SetColor(colorCyan); cout << "INFO: Hieu chinh thanh cong!";
					Sleep(2000);
					return -1;
				case 2:
					return -1;
				default:
					SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
					break;
				}
			}
		}
	}
}

int DanhSachChuyenBay::Delete()
{
	int choose = -1;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap so thu tu trong danh sach: ";
		SetColor(colorYellow); cin >> choose;

		if (choose < 1 || choose > SoLuongChuyenBay) {
			SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			int index = choose - 1;
			ClrLine(10); GotoXY(0, 10); SetColor(colorCyan); cout << "Ban co chac chan xoa? (Y/N) ";

			while (1) {
				char c = InputKey();

				if (c == 'Y' || c == 'y') {
					delete_byposition(index);
					ClrLine(10); GotoXY(0, 10); SetColor(colorCyan); cout << "INFO: Xoa thanh cong!";
					Sleep(2000);
					return -1;
				}
				else if (c == 'N' || c == 'n') {
					cin.ignore();
					return -1;
				}
			}
		}
	}
}

int DanhSachChuyenBay::Export()
{
	if (data_export() == -1) {
		SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
		Sleep(2000);
		return -1;
	}
	else {
		SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
		SetColor(colorYellow); cout << "...data/ChuyenBay.txt";
		Sleep(2000);
		return -1;
	}
}

