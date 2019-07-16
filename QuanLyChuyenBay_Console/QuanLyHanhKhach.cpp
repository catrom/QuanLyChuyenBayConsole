#include "QuanLyHanhKhach.h"

QuanLyHanhKhach * QuanLyHanhKhach::_instance = NULL;

QuanLyHanhKhach::QuanLyHanhKhach()
{
	SoLuongHanhKhach = 0;
	root = NULL;
}

QuanLyHanhKhach::~QuanLyHanhKhach()
{
	root = clear(root);
}

QuanLyHanhKhach * QuanLyHanhKhach::getinstance()
{
	if (_instance == NULL) _instance = new QuanLyHanhKhach();
	return _instance;
}

int QuanLyHanhKhach::data_import()
{
	std::ifstream in;
	in.open("data/HanhKhach.txt");

	if (in.fail()) {
		in.close();
		return -1;
	}

	std::string line;
	int soluong;

	in >> soluong;
	std::getline(in, line);

	for (int i = 0; i < soluong; i++) {
		HanhKhach * hanhkhach = new HanhKhach();

		std::getline(in, line);
		hanhkhach->SoCMND = StringToInteger(std::string(line));

		std::getline(in, line);
		hanhkhach->Ho = std::string(line);

		std::getline(in, line);
		hanhkhach->Ten = std::string(line);

		std::getline(in, line);
		hanhkhach->Phai = std::string(line);

		root = insert(*hanhkhach, root);
	}

	in.close();
	return 1;
}

int QuanLyHanhKhach::data_export()
{
	std::ofstream out;
	out.open("data/HanhKhach.txt", std::ios::trunc);

	if (out.fail()) {
		out.close();
		return -1;
	}

	out << SoLuongHanhKhach << std::endl;

	recursion_data_export(out, root);

	out.close();
	return 1;
}

void QuanLyHanhKhach::recursion_data_export(std::ofstream & out, node_HanhKhach * t)
{
	if (t == NULL)
		return;

	out << t->data.SoCMND << std::endl;
	out << t->data.Ho.c_str() << std::endl;
	out << t->data.Ten.c_str() << std::endl;
	out << t->data.Phai.c_str() << std::endl;
	
	recursion_data_export(out, t->left);
	recursion_data_export(out, t->right);
}

node_HanhKhach* QuanLyHanhKhach::clear(node_HanhKhach* t)
{
	if (t == NULL)
		return NULL;
	{
		clear(t->left);
		clear(t->right);
		delete t;
	}
	return NULL;
}

node_HanhKhach* QuanLyHanhKhach::insert(HanhKhach x, node_HanhKhach* t)
{
	if (t == NULL)
	{
		t = new node_HanhKhach;
		t->data = x;
		t->left = t->right = NULL;
		SoLuongHanhKhach++;
	}
	else if (x.SoCMND < t->data.SoCMND)
		t->left = insert(x, t->left);
	else if (x.SoCMND > t->data.SoCMND)
		t->right = insert(x, t->right);

	return t;
}

node_HanhKhach* QuanLyHanhKhach::findMin(node_HanhKhach* t)
{
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

node_HanhKhach* QuanLyHanhKhach::findMax(node_HanhKhach* t)
{
	if (t == NULL)
		return NULL;
	else if (t->right == NULL)
		return t;
	else
		return findMax(t->right);
}

node_HanhKhach* QuanLyHanhKhach::remove(HanhKhach x, node_HanhKhach* t)
{
	node_HanhKhach* temp;
	if (t == NULL)
		return NULL;
	else if (x.SoCMND < t->data.SoCMND)
		t->left = remove(x, t->left);
	else if (x.SoCMND > t->data.SoCMND)
		t->right = remove(x, t->right);
	else if (t->left && t->right)
	{
		temp = findMin(t->right);
		t->data = temp->data;
		t->right = remove(t->data, t->right);
	}
	else
	{
		temp = t;
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		delete temp;
	}

	return t;
}

node_HanhKhach* QuanLyHanhKhach::find(node_HanhKhach* t, long soCMND)
{
	if (t == NULL)
		return NULL;
	else if (soCMND < t->data.SoCMND)
		return find(t->left, soCMND);
	else if (soCMND > t->data.SoCMND)
		return find(t->right, soCMND);
	else
		return t;
}

HanhKhach * QuanLyHanhKhach::Find(long soCMND)
{
	node_HanhKhach * result = find(root, soCMND);

	if (result == NULL)
		return NULL;

	HanhKhach * hanhkhach = new HanhKhach;
	*hanhkhach = result->data;

	return hanhkhach;
}

void QuanLyHanhKhach::Insert(HanhKhach x)
{
	insert(x, root);
}

void QuanLyHanhKhach::Out()
{
	NLR(root);
}

void QuanLyHanhKhach::NLR(node_HanhKhach * t)
{
	if (t == NULL)
		return;

	std::cout << t->data.SoCMND << " ";
	NLR(t->left);
	NLR(t->right);
}
