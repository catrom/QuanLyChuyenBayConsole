#include "QuanLyMayBay.h"
#include "Funcs.h"
#include "Console.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;


DanhSachMayBay * DanhSachMayBay::_instance = NULL;

DanhSachMayBay::DanhSachMayBay()
{
	SoLuongMayBay = 0;
}

DanhSachMayBay * DanhSachMayBay::getinstance()
{
	if (_instance == NULL) _instance = new DanhSachMayBay();
	return _instance;
}

int DanhSachMayBay::data_import()
{
	std::ifstream in;
	in.open("data/MayBay.txt");

	if (in.fail()) {
		in.close();
		return -1;
	}

	std::string line;

	in >> SoLuongMayBay;
	std::getline(in, line);

	for (int i = 0; i < SoLuongMayBay; i++) {
		MayBay * maybay = new MayBay();

		std::getline(in, line);
		maybay->SoHieuMayBay = std::string(line);

		std::getline(in, line);
		maybay->LoaiMayBay = std::string(line);

		in >> maybay->SoDay >> maybay->SoDong;
		std::getline(in, line);

		DanhSach[i] = maybay;
	}

	in.close();
	return 1;
}

int DanhSachMayBay::data_export()
{
	std::ofstream out;
	out.open("data/MayBay.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << SoLuongMayBay << std::endl;

	for (int i = 0; i < SoLuongMayBay; i++) {
		out << DanhSach[i]->SoHieuMayBay.c_str() << std::endl;
		out << DanhSach[i]->LoaiMayBay.c_str() << std::endl;
		out << DanhSach[i]->SoDay << std::endl;
		out << DanhSach[i]->SoDong << std::endl;
	}

	out.close();
	return 1;
}

void DanhSachMayBay::add(MayBay * value)
{
	DanhSach[SoLuongMayBay] = value;
	SoLuongMayBay++;
}

void DanhSachMayBay::delete_byposition(int i)
{
	for (int j = i; j < SoLuongMayBay - 1; j++)
	{
		DanhSach[j] = DanhSach[j + 1];
	}

	SoLuongMayBay--;
}

void DanhSachMayBay::update_byposition(int i, MayBay * value)
{
	DanhSach[i]->LoaiMayBay = value->LoaiMayBay;
	DanhSach[i]->SoDay = value->SoDay;
	DanhSach[i]->SoDong = value->SoDong;
}

bool DanhSachMayBay::isSoHieuHopLe(string str)
{
	return str.size() > 0 && str.size() <= 15;
}

bool DanhSachMayBay::isLoaiHopLe(string str)
{
	return str.size() > 0 && str.size() <= 40;
}

bool DanhSachMayBay::isSoDayHopLe(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (!(str[i] >= '0' && str[i] <= '9'))
			return false;
	}

	return true;
}

bool DanhSachMayBay::isSoDongHopLe(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (!(str[i] >= '0' && str[i] <= '9'))
			return false;
	}

	return true;
}

int DanhSachMayBay::Menu()
{
	while (1) {
		Clrscr();
		ShowList();

		GotoXY(0, 0); SetColor(colorHeader1); cout << "QUAN LY MAY BAY";
		GotoXY(5, 2); SetColor(colorHeader2); cout << "1. Them may bay";
		GotoXY(5, 3); SetColor(colorHeader2); cout << "2. Sua may bay";
		GotoXY(5, 4); SetColor(colorHeader2); cout << "3. Xoa may bay";
		GotoXY(5, 5); SetColor(colorHeader2); cout << "4. Xuat danh sach";
		GotoXY(5, 6); SetColor(colorHeader2); cout << "5. Tro ve" << endl << endl;

		int choose = -1;

		while (1) {
			int rollBack = 0;

			SetCursorVisible(1);
			ClrLine(8); GotoXY(0, 8); SetColor(colorChoosen); cout << "-> ";
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
				SetColor(colorError); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}

			if (rollBack == 1)
				break;
		}
	}
}

void DanhSachMayBay::ShowList()
{
	int lineStart = 12;
	GotoXY(5, lineStart); SetColor(colorHeader3); cout << ">> Danh sach may bay:";

	// print header
	SetColor(colorDefault);
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 1); putchar(196); }
	GotoXY(5, lineStart + 2); 
	cout << "| STT    | So hieu         | Loai may bay                           | So day   | So dong |";
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 3); putchar(196); }

	// print data
	for (int i = 0; i < SoLuongMayBay; i++) {
		GotoXY(5, lineStart + 4 + 2 * i);
		cout << "|        |                 |                                        |          |         |";
		
		GotoXY(7, lineStart + 4 + 2 * i); cout << i + 1;	// STT;
		GotoXY(16, lineStart + 4 + 2 * i); cout << DanhSach[i]->SoHieuMayBay;	// So Hieu
		GotoXY(34, lineStart + 4 + 2 * i); cout << DanhSach[i]->LoaiMayBay;	// So loai
		GotoXY(75, lineStart + 4 + 2 * i); cout << DanhSach[i]->SoDay;	// So day
		GotoXY(86, lineStart + 4 + 2 * i); cout << DanhSach[i]->SoDong;	// So dong
		for (int j = 0; j < 90; j++) { GotoXY(j + 5, lineStart + 5 + 2 * i); putchar(196); }
	}
}

int DanhSachMayBay::Add()
{
	Clrscr();
	GotoXY(0, 0); SetColor(colorHeader1); cout << "THEM MAY BAY";
	
	MayBay * maybay = new MayBay();

	// Nhap so hieu
	ClrLine(2); GotoXY(5, 2); SetColor(colorChoosen); cout << "* Nhap so hieu may bay: ";
	while(1) {
		ClrLine(3);
		GotoXY(10, 3); SetColor(colorHeader3);
		cin.ignore(); getline(cin, maybay->SoHieuMayBay);

		if (!isSoHieuHopLe(maybay->SoHieuMayBay)) {
			SetColor(colorError); cout << "ERROR: So hieu khong hop le!";
		}
		else {
			LineStandardize(maybay->SoHieuMayBay);
			break;
		}
	}

	// Nhap loai
	ClrLine(4); GotoXY(5, 4); SetColor(colorChoosen); cout << "* Nhap loai may bay: ";
	while (1) {
		ClrLine(5);
		GotoXY(10, 5); SetColor(colorHeader3);
		getline(cin, maybay->LoaiMayBay);

		if (!isLoaiHopLe(maybay->LoaiMayBay)) {
			SetColor(colorError); cout << "ERROR: Loai khong hop le!";
		}
		else {
			LineStandardize(maybay->LoaiMayBay);
			break;
		}
	}

	// Nhap so day
	ClrLine(6); GotoXY(5, 6); SetColor(colorChoosen); cout << "* Nhap so day: ";
	while (1) {
		string soday;
		ClrLine(7);
		GotoXY(10, 7); SetColor(colorHeader3);
		getline(cin, soday);

		if (!isSoDayHopLe(soday)) {
			SetColor(colorError); cout << "ERROR: So day khong hop le!";
		}
		else {
			maybay->SoDay = StringToInteger(soday);
			break;
		}
	}

	// Nhap so dong
	ClrLine(8); GotoXY(5, 8); SetColor(colorChoosen); cout << "* Nhap so dong: ";
	while (1) {
		string sodong;
		ClrLine(9);
		GotoXY(10, 9); SetColor(colorHeader3);
		getline(cin, sodong);

		if (!isSoDongHopLe(sodong)) {
			SetColor(colorError); cout << "ERROR: So dong khong hop le!";
		}
		else {
			maybay->SoDong = StringToInteger(sodong);
			break;
		}
	}

	ClrLine(10);
	GotoXY(5, 11); SetColor(colorHeader2); cout << "1. Luu";
	GotoXY(25, 11); SetColor(colorHeader2); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		SetCursorVisible(1);
		ClrLine(13); GotoXY(0, 13); SetColor(colorChoosen); cout << "-> ";
		cin >> choose;

		switch (choose)
		{
		case 1:
			add(maybay);
			GotoXY(0, 14); SetColor(colorHeader2); cout << "INFO: Them thanh cong!";
			Sleep(2000);
			return -1;
		case 2:
			return -1;
		default:
			SetColor(colorError); cout << "ERROR: Input khong hop le!" << endl;
			break;
		}
	}
}

int DanhSachMayBay::Modify()
{
	int choose = -1;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorChoosen); cout << "Nhap so thu tu trong danh sach: ";
		SetColor(colorHeader3); cin >> choose;

		if (choose < 1 || choose > SoLuongMayBay) {
			SetColor(colorError); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			Clrscr();
			GotoXY(0, 0); SetColor(colorHeader1); cout << "HIEU CHINH MAY BAY";
			int index = choose - 1;

			MayBay * maybay = new MayBay();
			maybay->SoHieuMayBay = DanhSach[index]->SoHieuMayBay;
			maybay->LoaiMayBay = DanhSach[index]->LoaiMayBay;
			maybay->SoDay = DanhSach[index]->SoDay;
			maybay->SoDong = DanhSach[index]->SoDong;

			ClrLine(2); GotoXY(5, 2); SetColor(colorChoosen); cout << "So hieu may bay: " << maybay->SoHieuMayBay;

			// Nhap loai
			ClrLine(4); GotoXY(5, 4); SetColor(colorChoosen); cout << "Loai may bay: " << maybay->LoaiMayBay;
			ClrLine(5); GotoXY(5, 5); SetColor(colorHeader2); cout << "Hieu chinh Loai may bay? (Y/N) ";

			while (1) {
				char c = InputKey();
				bool ok = 0;

				if (c == 'Y' || c == 'y') {
					while (1) {
						ClrLine(5); GotoXY(5, 5); SetColor(colorChoosen); cout << "* Nhap loai may bay: ";
						SetColor(colorHeader3); getline(cin, maybay->LoaiMayBay);

						if (!isLoaiHopLe(maybay->LoaiMayBay)) {
							SetColor(colorError); cout << "ERROR: Loai khong hop le!";
						}
						else {
							LineStandardize(maybay->LoaiMayBay);
							ok = 1;
							break;
						}
					}
				}
				else if (c == 'N' || c == 'n') {
					ClrLine(5);
					cin.ignore();
					break;
				}
					
				if (ok) break;
			}

			// Nhap so day
			ClrLine(6); GotoXY(5, 6); SetColor(colorChoosen); cout << "So day: " << maybay->SoDay;
			ClrLine(7); GotoXY(5, 7); SetColor(colorHeader2); cout << "Hieu chinh So day? (Y/N) ";

			while (1) {
				char c = InputKey();
				bool ok = 0;

				if (c == 'Y' || c == 'y') {
					while (1) {
						string soday;

						ClrLine(7); GotoXY(5, 7); SetColor(colorChoosen); cout << "* Nhap so day: ";
						SetColor(colorHeader3); getline(cin, soday);

						if (!isSoDayHopLe(soday)) {
							SetColor(colorError); cout << "ERROR: So day khong hop le!";
						}
						else {
							maybay->SoDay = StringToInteger(soday);
							ok = 1;
							break;
						}
					}
				}
				else if (c == 'N' || c == 'n') {
					ClrLine(7);
					//cin.ignore();
					break;
				}

				if (ok) break;
			}

			// Nhap so dong
			ClrLine(8); GotoXY(5, 8); SetColor(colorChoosen); cout << "So dong: " << maybay->SoDong;
			ClrLine(9); GotoXY(5, 9); SetColor(colorHeader2); cout << "Hieu chinh So dong? (Y/N) ";

			while (1) {
				char c = InputKey();
				bool ok = 0;

				if (c == 'Y' || c == 'y') {
					while (1) {
						string sodong;

						ClrLine(9); GotoXY(5, 9); SetColor(colorChoosen); cout << "* Nhap so dong: ";
						SetColor(colorHeader3); getline(cin, sodong);

						if (!isSoDongHopLe(sodong)) {
							SetColor(colorError); cout << "ERROR: So dong khong hop le!";
						}
						else {
							maybay->SoDong = StringToInteger(sodong);
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
			GotoXY(5, 11); SetColor(colorHeader2); cout << "1. Luu";
			GotoXY(25, 11); SetColor(colorHeader2); cout << "2. Tro ve";

			while (1) {
				SetCursorVisible(1);
				ClrLine(13); GotoXY(0, 13); SetColor(colorChoosen); cout << "-> ";
				cin >> choose;

				switch (choose)
				{
				case 1:
					update_byposition(index, maybay);
					GotoXY(0, 14); SetColor(colorHeader2); cout << "INFO: Hieu chinh thanh cong!";
					Sleep(2000);
					return -1;
				case 2:
					return -1;
				default:
					SetColor(colorError); cout << "ERROR: Input khong hop le!" << endl;
					break;
				}
			}
		}
	}
}

int DanhSachMayBay::Delete()
{
	int choose = -1;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorChoosen); cout << "Nhap so thu tu trong danh sach: ";
		SetColor(colorHeader3); cin >> choose;

		if (choose < 1 || choose > SoLuongMayBay) {
			SetColor(colorError); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			int index = choose - 1;
			ClrLine(10); GotoXY(0, 10); SetColor(colorHeader2); cout << "Ban co chac chan xoa? (Y/N) ";

			while (1) {
				char c = InputKey();

				if (c == 'Y' || c == 'y') {
					delete_byposition(index);
					ClrLine(10); GotoXY(0, 10); SetColor(colorHeader2); cout << "INFO: Xoa thanh cong!";
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

int DanhSachMayBay::Export()
{
	if (data_export() == -1) {
		SetColor(colorError); cout << "ERROR: Loi xuat file!" << endl;
		Sleep(2000);
		return -1;
	}
	else {
		SetColor(colorHeader2); cout << "INFO: Xuat danh sach thanh cong ";
		SetColor(colorHeader3); cout << "...data/MayBay.txt";
		Sleep(2000);
		return -1;
	}
}
