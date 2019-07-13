#include "Objects.h"

struct DanhSachMayBay
{
private:
	int SoLuongMayBay;
	MayBay* DanhSach[300];

public:
	static DanhSachMayBay* _instance;
	DanhSachMayBay();

	static DanhSachMayBay * getinstance();
	int data_import();
	int data_export();

	void add(MayBay * value);
	void delete_byposition(int i);
	void update_byposition(int i, MayBay * value);

	bool isSoHieuHopLe(std::string str);
	bool isLoaiHopLe(std::string str);
	bool isSoDayHopLe(std::string str);
	bool isSoDongHopLe(std::string str);

	// display
	int Menu();
	void ShowList();
	int Add();
	int Modify();
	int Delete();
	int Export();
};

