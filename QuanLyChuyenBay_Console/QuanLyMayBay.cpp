#include "QuanLyMayBay.h"

QuanLyMayBay * QuanLyMayBay::_instance = NULL;

QuanLyMayBay::QuanLyMayBay()
{
	SoLuongMayBay = 0;
}

QuanLyMayBay * QuanLyMayBay::getinstance()
{
	if (_instance == NULL) _instance = new QuanLyMayBay();
	return _instance;
}

int QuanLyMayBay::data_import()
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

int QuanLyMayBay::data_export()
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

void QuanLyMayBay::add(MayBay * value)
{
	DanhSach[SoLuongMayBay] = value;
	SoLuongMayBay++;
}

void QuanLyMayBay::delete_byposition(int i)
{
	for (int j = i; j < SoLuongMayBay - 1; j++)
	{
		DanhSach[j] = DanhSach[j + 1];
	}

	SoLuongMayBay--;
}

void QuanLyMayBay::update_byposition(int i, MayBay * value)
{
	DanhSach[i]->LoaiMayBay = value->LoaiMayBay;
	DanhSach[i]->SoDay = value->SoDay;
	DanhSach[i]->SoDong = value->SoDong;
}

std::string QuanLyMayBay::Build_SoHieuMayBay()
{
	string res = "MB";
	int max = 0;

	for (int i = 0; i < SoLuongMayBay; i++) {
		int id = StringToInteger(DanhSach[i]->SoHieuMayBay.substr(2, 14));

		if (id > max) max = id;
	}

	res = res + std::to_string(max + 1);
	return res;
}

bool QuanLyMayBay::isLoaiHopLe(string str)
{
	return str.size() > 0 && str.size() <= 40;
}

MayBay * QuanLyMayBay::getBy_SoHieuMayBay(std::string sohieu)
{
	for (int i = 0; i < SoLuongMayBay; i++) {
		if (DanhSach[i]->SoHieuMayBay == sohieu)
			return DanhSach[i];
	}

	return NULL;
}

std::vector<MayBay> QuanLyMayBay::getDanhSachMayBay()
{
	std::vector<MayBay> danhsach;
	for (int i = 0; i < SoLuongMayBay; i++)
		danhsach.push_back(*DanhSach[i]);

	return danhsach;
}

int QuanLyMayBay::Menu()
{
	while (1) {
		Clrscr();
		ShowList();

		GotoXY(0, 0); SetColor(colorHeader); cout << "QUAN LY MAY BAY";
		GotoXY(5, 2); SetColor(colorCyan); cout << "1. Them may bay";
		GotoXY(5, 3); SetColor(colorCyan); cout << "2. Hieu chinh may bay";
		GotoXY(5, 4); SetColor(colorCyan); cout << "3. Xoa may bay";
		GotoXY(5, 5); SetColor(colorCyan); cout << "4. Xuat danh sach";
		GotoXY(5, 6); SetColor(colorCyan); cout << "5. Tro ve" << endl << endl;

		int choose = -1;

		while (1) {
			int rollBack = 0;

			ClrLine(8); GotoXY(0, 8); SetColor(colorWhite); cout << "-> ";
			input->GetInput();

			if (!input->isInteger()) {
				ClrLine(9); GotoXY(0, 9); SetColor(colorRed); cout << "ERROR: Input khong hop le!";
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
					ClrLine(9); GotoXY(0, 9); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
					break;
				}

				if (rollBack == 1)
					break;
			}		
		}
	}
}

void QuanLyMayBay::ShowList()
{
	int lineStart = 12;
	GotoXY(5, lineStart); SetColor(colorYellow); cout << ">> Danh sach may bay:";

	// print header
	SetColor(colorDefault);
	for (int i = 0; i < 90; i++) { GotoXY(i + 5, lineStart + 1); putchar(196); }
	GotoXY(5, lineStart + 2); 
	cout << "| STT    | SO HIEU         | LOAI MAY BAY                           | SO DAY   | SO DONG |";
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

int QuanLyMayBay::Add()
{
	Clrscr();
	GotoXY(0, 0); SetColor(colorHeader); cout << "THEM MAY BAY";
	
	MayBay * maybay = new MayBay();

	maybay->SoHieuMayBay = Build_SoHieuMayBay();
	ClrLine(2); GotoXY(5, 2); SetColor(colorWhite); cout << "So hieu may bay: ";
	GotoXY(10, 3); SetColor(colorYellow); cout << maybay->SoHieuMayBay;

	// Nhap loai
	ClrLine(4); GotoXY(5, 4); SetColor(colorWhite); cout << "* Nhap loai may bay: ";
	while (1) {
		ClrLine(5);
		GotoXY(10, 5); SetColor(colorYellow);
		
		if (input->GetInput() == -1) return -1; 
		maybay->LoaiMayBay = input->GetResult();

		if (!isLoaiHopLe(maybay->LoaiMayBay)) {
			ClrLine(6); GotoXY(0, 6); SetColor(colorRed); cout << "ERROR: Loai khong hop le!";
		}
		else {
			LineStandardize(maybay->LoaiMayBay);
			break;
		}
	}

	// Nhap so day
	ClrLine(6); GotoXY(5, 6); SetColor(colorWhite); cout << "* Nhap so day: ";
	while (1) {
		ClrLine(7);
		GotoXY(10, 7); SetColor(colorYellow);
		
		if (input->GetInput() == -1) return -1;

		if (!input->isInteger()) {
			ClrLine(8); GotoXY(0, 8); SetColor(colorRed); cout << "ERROR: So day khong hop le!";
		}
		else {
			maybay->SoDay = StringToInteger(input->GetResult());
			break;
		}
	}

	// Nhap so dong
	ClrLine(8); GotoXY(5, 8); SetColor(colorWhite); cout << "* Nhap so dong: ";
	while (1) {
		ClrLine(9);
		GotoXY(10, 9); SetColor(colorYellow);

		if (input->GetInput() == -1) return -1;

		if (!input->isInteger()) {
			ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: So dong khong hop le!";
		}
		else {
			maybay->SoDong = StringToInteger(input->GetResult());
			break;
		}
	}

	ClrLine(10);
	GotoXY(5, 11); SetColor(colorCyan); cout << "1. Luu";
	GotoXY(25, 11); SetColor(colorCyan); cout << "2. Tro ve";

	int choose = -1;

	while (1) {
		ClrLine(13); GotoXY(0, 13); SetColor(colorWhite); cout << "-> ";
		
		if (input->GetInput() == -1) return -1;

		if (!input->isInteger()) {
			ClrLine(14); GotoXY(0, 14); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			switch (choose)
			{
			case 1:
				add(maybay);
				ClrLine(14); GotoXY(0, 14); SetColor(colorCyan); cout << "INFO: Them thanh cong!";
				Sleep(2000);
				return -1;
			case 2:
				return -1;
			default:
				ClrLine(14); GotoXY(0, 14); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}
		}
	}
}

int QuanLyMayBay::Modify()
{
	int choose = -1;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap so thu tu trong danh sach: ";
		SetColor(colorYellow);

		if (input->GetInput() == -1) return -1;
		if (!input->isInteger()) {
			ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			if (choose < 1 || choose > SoLuongMayBay) {
				ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
			}
			else {
				Clrscr();
				GotoXY(0, 0); SetColor(colorHeader); cout << "HIEU CHINH MAY BAY";
				int index = choose - 1;

				MayBay * maybay = new MayBay();
				maybay->SoHieuMayBay = DanhSach[index]->SoHieuMayBay;
				maybay->LoaiMayBay = DanhSach[index]->LoaiMayBay;
				maybay->SoDay = DanhSach[index]->SoDay;
				maybay->SoDong = DanhSach[index]->SoDong;

				ClrLine(2); GotoXY(5, 2); SetColor(colorWhite); cout << "So hieu may bay: " << maybay->SoHieuMayBay;

				// Nhap loai
				ClrLine(4); GotoXY(5, 4); SetColor(colorWhite); cout << "Loai may bay: " << maybay->LoaiMayBay;
				ClrLine(5); GotoXY(5, 5); SetColor(colorCyan); cout << "Hieu chinh Loai may bay? (Y/N) ";

				while (1) {
					char c = InputKey();
					bool ok = 0;

					if (c == 'Y' || c == 'y') {
						while (1) {
							ClrLine(5); GotoXY(5, 5); SetColor(colorWhite); cout << "* Nhap loai may bay: ";
							SetColor(colorYellow); 

							if (input->GetInput() == -1) return -1;

							if (!isLoaiHopLe(input->GetResult())) {
								ClrLine(6); GotoXY(0, 6); SetColor(colorRed); cout << "ERROR: Loai khong hop le!";
							}
							else {
								maybay->LoaiMayBay = LineStandardize(input->GetResult());
								ok = 1;
								break;
							}
						}
					}
					else if (c == 'N' || c == 'n') {
						ClrLine(5);
						//cin.ignore();
						break;
					}

					if (ok) break;
				}

				// Nhap so day
				ClrLine(6); GotoXY(5, 6); SetColor(colorWhite); cout << "So day: " << maybay->SoDay;
				ClrLine(7); GotoXY(5, 7); SetColor(colorCyan); cout << "Hieu chinh So day? (Y/N) ";

				while (1) {
					char c = InputKey();
					bool ok = 0;

					if (c == 'Y' || c == 'y') {
						while (1) {
							ClrLine(7); GotoXY(5, 7); SetColor(colorWhite); cout << "* Nhap so day: ";
							SetColor(colorYellow);

							if (input->GetInput() == -1) return -1;

							if (!input->isInteger()) {
								ClrLine(8); GotoXY(0, 8); SetColor(colorRed); cout << "ERROR: So day khong hop le!";
							}
							else {
								maybay->SoDay = StringToInteger(input->GetResult());
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
				ClrLine(8); GotoXY(5, 8); SetColor(colorWhite); cout << "So dong: " << maybay->SoDong;
				ClrLine(9); GotoXY(5, 9); SetColor(colorCyan); cout << "Hieu chinh So dong? (Y/N) ";

				while (1) {
					char c = InputKey();
					bool ok = 0;

					if (c == 'Y' || c == 'y') {
						while (1) {
							ClrLine(9); GotoXY(5, 9); SetColor(colorWhite); cout << "* Nhap so dong: ";
							SetColor(colorYellow); 
							if (input->GetInput() == -1) return -1;

							if (!input->isInteger()) {
								ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: So dong khong hop le!";
							}
							else {
								maybay->SoDong = StringToInteger(input->GetResult());
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
					ClrLine(13); GotoXY(0, 13); SetColor(colorWhite); cout << "-> ";
					
					if (input->GetInput() == -1) return -1;
					if (!input->isInteger()) {
						ClrLine(14); GotoXY(0, 14); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
					}
					else {
						choose = StringToInteger(input->GetResult());

						switch (choose)
						{
						case 1:
							update_byposition(index, maybay);
							ClrLine(14); GotoXY(0, 14); SetColor(colorCyan); cout << "INFO: Hieu chinh thanh cong!";
							Sleep(2000);
							return -1;
						case 2:
							return -1;
						default:
							ClrLine(14); GotoXY(0, 14); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
							break;
						}
					}
				}
			}
		}
	}
}

int QuanLyMayBay::Delete()
{
	int choose = -1;

	while (1) {
		ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "Nhap so thu tu trong danh sach: ";
		SetColor(colorYellow); 
		
		if (input->GetInput() == -1) return -1;

		if (!input->isInteger()) {
			ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
		}
		else {
			choose = StringToInteger(input->GetResult());

			if (choose < 1 || choose > SoLuongMayBay) {
				ClrLine(10); GotoXY(0, 10); SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
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
						//cin.ignore();
						return -1;
					}
				}
			}
		}
	}
}

int QuanLyMayBay::Export()
{
	if (data_export() == -1) {
		ClrLine(9); GotoXY(0, 9);
		SetColor(colorRed); cout << "ERROR: Loi xuat file!" << endl;
		Sleep(2000);
		return -1;
	}
	else {
		ClrLine(9); GotoXY(0, 9);
		SetColor(colorCyan); cout << "INFO: Xuat danh sach thanh cong ";
		SetColor(colorYellow); cout << "...data/MayBay.txt";
		Sleep(2000);
		return -1;
	}
}
