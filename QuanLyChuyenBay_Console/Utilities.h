#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;

// Console
#define colorHeader 224
#define colorGreen   10
#define colorCyan   11
#define colorYellow   14
#define colorDefault   7
#define colorWhite 15
#define colorRed 12

#define keyNone			-1

int InputKey();		// lấy giá trị ASCII của phím vừa được nhập
void Clrscr();      // xoá toàn bộ màn hình
void ClrLine(int line); // xoá dòng
void GotoXY(int column, int line); // di chuyển con trỏ tới vị trí col, row
int WhereX(); // lấy vị trí cột hiện tại của con trỏ
int WhereY(); // lấy vị trí dòng hiện tại của con trỏ
void SetColor(int color); // thiết lập màu cho text

// 
using namespace std;
int StringToInteger(std::string s); // chuyển đổi giá trị kiểu string qua kiểu integer
std::string LineStandardize(std::string s); // chuẩn hoá chuỗi

// input
struct Input {
private:
	std::string result;	// chuỗi kết quả của input từ người dùng

public:
	int GetInput();	    // hàm xử lí lấy input từ người dùng, nếu người dùng ấn ESC thì return -1.
	std::string GetResult();	// trả về chuỗi đã nhập

	bool isInteger(); // kiểm tra chuỗi đã nhập chỉ bao gồm các kí tự số
	bool isListOfIntegers();	// kiểm tra chuỗi đã nhập là một dòng chứa các số tách biệt 
								// (dùng trong lúc nhập liệu ngày khởi hành: yyyy mm dd hh mm)
	bool isString();	// kiểm tra chuỗi đã nhập không rỗng, có thể mở rộng
		
	std::vector<int> splitIntegers();	// tách các số từ chuỗi thành std::vector để xử lý
};

static Input * input = new Input; // khai báo đối tượng toàn cục