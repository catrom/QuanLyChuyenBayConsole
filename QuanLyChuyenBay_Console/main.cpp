#include <iostream>
#include <ctime>
#include "Console.h"
#include "QuanLyMayBay.h"
#include "QuanLyChuyenBay.h"
using namespace std;

DanhSachMayBay * danhsachmaybay = DanhSachMayBay::getinstance();
DanhSachChuyenBay * danhsachchuyenbay = DanhSachChuyenBay::getinstance();

void MainMenu() {
	while (1) {
		int choose = -1;

		Clrscr();
		
		GotoXY(0, 0); SetColor(colorGreen); cout << "CHUONG TRINH QUAN LY CHUYEN BAY";
		GotoXY(5, 2); SetColor(colorCyan); cout << "1. Quan ly may bay";
		GotoXY(5, 3); SetColor(colorCyan); cout << "2. Quan ly chuyen bay";
		GotoXY(5, 4); SetColor(colorCyan); cout << "3. Quan ly ve";
		GotoXY(5, 5); SetColor(colorCyan); cout << "4. Thong ke - bao bieu";
		GotoXY(5, 6); SetColor(colorCyan); cout << "5. Thong tin";
		GotoXY(5, 7); SetColor(colorCyan); cout << "6. Thoat";

		while (1) {
			int rollBack = 0;

			SetCursorVisible(1);
			ClrLine(9); GotoXY(0, 9); SetColor(colorWhite); cout << "-> ";
			cin >> choose;

			switch (choose)
			{
			case 1:
				if (danhsachmaybay->Menu() == -1) {
					rollBack = 1;
					break;
				}
			case 2:
				if (danhsachchuyenbay->Menu() == -1) {
					rollBack = 1;
					break;
				}
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				return;
			default:
				SetColor(colorRed); cout << "ERROR: Input khong hop le!" << endl;
				break;
			}

			if (rollBack)
				break;
		}
	}
}

int main() {
	srand(time(NULL));
	SetCursorVisible(0);
	system("mode 100, 40");

	if (danhsachmaybay->data_import() == -1) {
		SetColor(colorRed); cout << "ERROR: Lay danh sach may bay that bai!" << endl;
		Sleep(2000);
	}

	if (danhsachchuyenbay->data_import() == -1) {
		SetColor(colorRed); cout << "ERROR: Lay danh sach chuyen bay that bai!" << endl;
		Sleep(2000);
	}


	MainMenu();
	return 1;
}