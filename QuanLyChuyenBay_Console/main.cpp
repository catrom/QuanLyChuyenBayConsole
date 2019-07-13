#include <iostream>
#include <ctime>
#include "Console.h"
#include "QuanLyMayBay.h"

using namespace std;

DanhSachMayBay * danhsachmaybay = DanhSachMayBay::getinstance();

void MainMenu() {
	while (1) {
		int choose = -1;

		Clrscr();
		
		GotoXY(0, 0); SetColor(colorHeader1); cout << "CHUONG TRINH QUAN LY CHUYEN BAY";
		GotoXY(5, 2); SetColor(colorHeader2); cout << "1. Quan ly may bay";
		GotoXY(5, 3); SetColor(colorHeader2); cout << "2. Quan ly chuyen bay";
		GotoXY(5, 4); SetColor(colorHeader2); cout << "3. Quan ly ve";
		GotoXY(5, 5); SetColor(colorHeader2); cout << "4. Thong ke - bao bieu";
		GotoXY(5, 6); SetColor(colorHeader2); cout << "5. Thong tin";
		GotoXY(5, 7); SetColor(colorHeader2); cout << "6. Thoat";

		while (1) {
			int rollBack = 0;

			SetCursorVisible(1);
			ClrLine(9); GotoXY(0, 9); SetColor(colorChoosen); cout << "-> ";
			cin >> choose;

			switch (choose)
			{
			case 1:
				if (danhsachmaybay->Menu() == -1) {
					rollBack = 1;
					break;
				}
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				return;
			default:
				SetColor(colorError); cout << "ERROR: Input khong hop le!" << endl;
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
		SetColor(colorError); cout << "ERROR: Lay danh sach may bay that bai!" << endl;
	}


	MainMenu();
	return 1;
}