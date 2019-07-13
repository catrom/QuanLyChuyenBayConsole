#pragma once

#include "Objects.h"
#include <fstream>
#include <string>

struct DanhSachChuyenBay
{
	struct node
	{
		ChuyenBay data;
		node *next;
	};

	node *head, *tail;

	DanhSachChuyenBay()
	{
		head = NULL;
		tail = NULL;
	}

	void insert(ChuyenBay value)
	{
		node *temp = new node;
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
	
	void delete_byposition(int pos)
	{
		node *current = new node;
		node *previous = new node;
		current = head;
		for (int i = 1; i < pos; i++)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
	}
};

struct DanhSachHanhKhach
{
	struct node
	{
		HanhKhach data;
		node* left;
		node* right;
	};

	node* root;

	DanhSachHanhKhach()
	{
		root = NULL;
	}

	~DanhSachHanhKhach()
	{
		root = clear(root);
	}

	node* clear(node* t)
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

	node* insert(HanhKhach x, node* t)
	{
		if (t == NULL)
		{
			t = new node;
			t->data = x;
			t->left = t->right = NULL;
		}
		else if (x.SoCMND < t->data.SoCMND)
			t->left = insert(x, t->left);
		else if (x.SoCMND > t->data.SoCMND)
			t->right = insert(x, t->right);
		return t;
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(HanhKhach x, node* t)
	{
		node* temp;
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

	node* find(node* t, HanhKhach x)
	{
		if (t == NULL)
			return NULL;
		else if (x.SoCMND < t->data.SoCMND)
			return find(t->left, x);
		else if (x.SoCMND > t->data.SoCMND)
			return find(t->right, x);
		else
			return t;
	}
};
