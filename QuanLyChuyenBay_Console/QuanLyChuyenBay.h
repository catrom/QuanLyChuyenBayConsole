#pragma once

#include "Objects.h"

struct node
{
	ChuyenBay data;
	node *next;
};

struct DanhSachChuyenBay
{
private:
	int SoLuongChuyenBay;
	node *head, *tail;

public:
	static DanhSachChuyenBay* _instance;
	DanhSachChuyenBay();

	static DanhSachChuyenBay * getinstance();
	int data_import();
	int data_export();

	void insert(ChuyenBay value);
	void delete_byposition(int pos);
};