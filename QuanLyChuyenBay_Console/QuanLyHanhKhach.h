#pragma once
#include "Objects.h"

struct node_HanhKhach
{
	HanhKhach data;
	node_HanhKhach* left;
	node_HanhKhach* right;
};

struct QuanLyHanhKhach
{
private:
	int SoLuongHanhKhach;
	node_HanhKhach* root;

public:
	static QuanLyHanhKhach* _instance;

	QuanLyHanhKhach();
	~QuanLyHanhKhach();

	static QuanLyHanhKhach * getinstance();
	int data_import();
	int data_export();
	void recursion_data_export(std::ofstream &out, node_HanhKhach* t);

	node_HanhKhach* clear(node_HanhKhach* t);
	node_HanhKhach* insert(HanhKhach x, node_HanhKhach* t);
	node_HanhKhach* findMin(node_HanhKhach* t);
	node_HanhKhach* findMax(node_HanhKhach* t);
	node_HanhKhach* remove(HanhKhach x, node_HanhKhach* t);
	node_HanhKhach* find(node_HanhKhach* t, long soCMND);

	HanhKhach* Find(long soCMND);
	void Insert(HanhKhach x);

	void Out();
	void NLR(node_HanhKhach * t);
};
