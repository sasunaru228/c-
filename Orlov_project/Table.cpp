// Графика.cpp: определяет точку входа для консольного приложения.
//
#pragma warning (disable : 4996)

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "MyCrt.h"
#include "Table.h"


#define _CRT_SECURE_NO_WARNINGS

using namespace std;

char TabChars[][4][4] = {
	{
		{'\332','\304','\302','\277'},    // ┌-┬┐
		{'\263','\40','\263','\263'},     // │ ││
		{'\303','\304','\305','\264'},    // ├-┼┤
		{'\300','\304','\301','\331'}     // └-┴┘
	},
	{
		{'\311','\315','\313','\273'},    // ╔═╦╗
		{'\272','\40','\272','\272'},        
		{'\314','\315','\316','\271'},    
		{'\310','\315','\312','\274'}     
	},
	{
		{'\311','\315','\321','\273'},    // ╔═╤╗
		{'\272','\40','\263','\272'},     
		{'\307','\304','\305','\266'},    
		{'\310','\315','\317','\274'}     
	}
};

///////////////////////////////   ТАБЛИЦА   ///////////////////////////////

//struct Table
//{
//	short
//      X,					// Координата Х верхнего левого угла таблицы
//		Y,					// Координата Y верхнего левого угла таблицы
//		CCount,				// Количество столбцов таблицы
//		CWidth,				// Ширина столбцов таблицы без учета границ
//		RCount,				// Количество строк таблицы
//		RHeight,			// Высота строк таблицы без учета границ
//		TabType,			// Вид линий сетки таблицы (0 - одиночные; 1 - двойные; 2 - комбинированные)
//		Row,				// Индекс строки выбранной ячейки талицы (первая строка имеет индекс 0)
//      Col,				// Индекс столбца выбранной ячейки талицы (первый столбец имеет индекс 0)
//      Width,				// Полная широина таблицы
//      Height,				// Полная высота таблицы
//	    NormColors,			// Цветовые аттрибуты не выбранных ячеек (см. MyCrt)
//		SelectColors,		// Цветовые аттрибуты выбранной ячейки (см. MyCrt)
//		Precision;			// Количество разрядов после десятичной точки
//	TInf Value;				// Значение в выбранной ячейке талицы
//	union                   // Массив данных для заполнения ячеек таблицы 
//	{
//		TInf * Data;			
//		TInf ** Data1;
//	};
//	bool TypeData;          // Вид двумерного массива: true - Data[i][j]; false - Data[i * Col + j]
//	short DataRCount,		// Количество строк в массиве данных
//		  DataCCount,		// Количество столбцов в массиве данных
//		  DataRowTop,		// Индекс строки массива данных, находящейся в первой строке таблицы
//		  DataColLeft;		// Индекс столбца массива данных, находящегося в первом столбце таблицы
//	char *Buf;				// Указатель на буфер для сохранения изображения под таблицей
//  bool Headers;			// Рисовать нумераторы строк и столбцов
//  short RowHeaderWidth;   // Ширина столбца нумератора строк
//  bool Visible,			// Таблица на экране
//	     ViewerShow;	    // Показать строку со значением текущей ячейки
//  bool ReadOnly;          // Запретить редактирование
//  short EditorLen;		// Длина строки редактора
//};
//void InitTable(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType, short NormColors, 
//			   short SelectColors, TInf *Data, short DataCCount, short DataRCount, short Precision, bool ReadOnly, bool Viewer, bool Headers = true);      // Инициализация параметров таблицы Т
//void InitTable(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType, short NormColors, 
//			   short SelectColors, TInf **Data, short DataCCount, short DataRCount, short Precision, bool ReadOnly, bool Viewer, bool Headers = true);     // Инициализация параметров таблицы Т
//void HideTable(Table &T, short Colors);				// Стереть таблицу с экрана цветом Colors
//void ShowTable(Table &T);								// Показать таблицу на экране		
//void DrawEmptyTable(Table &T);						// Нарисовать таблицу без данных на экране
//void FillTable(Table &T);								// Заполнить таблицу данными из массива таблицы
//char CellChoice(Table &T);							// Выбор ячейки таблицы
//TInf GetValue(Table &T, int Row, int Col);			// Взять значение ячейки с индексами Row, Col
//TInf GetValue(Table &T);				                // Взять значение активной ячейки
//void SetValue(Table &T, int Row, int Col, TInf Val);	// Занести значение в ячейку с индексами Row, Col массива таблицы
//void SetValue(Table &T, TInf Val);		            // Занести значение в активную ячейку
//void DrawValue(Table &T, int Row, int Col, TInf Val);	// Занести значение в ячейку с индексами Row, Col массива таблицы и вывести на экран
//void DrawValue(Table &T, TInf Val);	                // Занести значение в активную ячейку массива таблицы и вывести на экран
//void FreeTable(Table &T);								// Стереть с экрана и освобождить память от таблицы
//void EditValue(Table &T, char Ch);					// Редактирование значения текущей ячейки

void Init(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType,	
		  short NormColors, short SelectColors, short DataCCount, short DataRCount,  short Precision, bool ReadOnly, bool Viewer,bool Headers)
{
	T.X = X;
	T.Y = Y;
	if (CCount <= DataCCount)
		T.CCount = CCount;
	else
		T.CCount = DataCCount;
	T.CWidth = CWidth;
	if (RCount <= DataRCount)
		T.RCount = RCount;
	else
		T.RCount = DataRCount;
	T.RHeight = RHeight;
	T.TabType = TabType;
	T.NormColors = NormColors;
	T.SelectColors = SelectColors;
	T.Row = 0;
	T.Col = 0;
	T.DataCCount = DataCCount;
	T.DataRCount = DataRCount;
	T.DataColLeft = 0;
	T.DataRowTop = 0;
	T.ViewerShow = Viewer;
	T.ReadOnly = ReadOnly;
	T.Precision = Precision;
	if (!T.ReadOnly)
		T.ViewerShow = true;
	T.Headers = Headers;
	char S[6];
	_itoa_s(T.DataRCount, S, 10);
	T.RowHeaderWidth = strlen(S) + 2;
	if (T.Headers)
	{
		T.Width = T.RowHeaderWidth + T.CCount * (T.CWidth + 1) + 2;
		T.Height = T.RCount * (T.RHeight + 1) + 3;
	}
	else
	{
		T.Width = T.CCount * (T.CWidth + 1) + 1;
		T.Height = T.RCount * (T.RHeight + 1) + 1;
	}
	if (T.ViewerShow)
		T.Height = T.Height + 2;
	T.Buf = new char[T.Width * T.Height * sizeof(CHAR_INFO)];
	T.Visible = false;
}

void InitTable(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType, 
			   short NormColors, short SelectColors, TInf *Data, short DataCCount, short DataRCount, short Precision, bool ReadOnly, bool Viewer, bool Headers)
{
	Init(T, X, Y, CCount, CWidth, RCount, RHeight, TabType,	NormColors, SelectColors, DataCCount, DataRCount, Precision, ReadOnly, Viewer, Headers);
	T.Data = Data;
	T.TypeData = false;
	T.Value = GetValue(T);
}

void InitTable(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType,
			   short NormColors, short SelectColors, TInf **Data, short DataCCount, short DataRCount, short Precision, bool ReadOnly, bool Viewer, bool Headers)
{
	Init(T, X, Y, CCount, CWidth, RCount, RHeight, TabType,	NormColors, SelectColors, DataCCount, DataRCount, Precision, ReadOnly, Viewer, Headers);
	T.Data1 = Data;
	T.TypeData = true;
	T.Value = GetValue(T);
}

void HideTable(Table &T, short Colors)
{
	PasteRect(T.X, T.Y, T.X + T.Width - 1, T.Y + T.Height - 1, T.Buf);
	T.Visible = false;
}

void FreeTable(Table &T)
{
	PasteRect(T.X, T.Y, T.X + T.Width - 1, T.Y + T.Height - 1, T.Buf);
	delete [] T.Buf;
}

void ShowTable(Table &T)
{
	T.Visible = true;
	CopyRect(T.X, T.Y, T.X + T.Width - 1, T.Y + T.Height - 1, T.Buf);
	DrawEmptyTable(T);
	FillTable(T);
}

void DrawTabLine(Table &T, int Y, int Line)
{
	short CCount = T.Headers ? T.CCount + 1 : T.CCount;
	GoToXY(T.X, Y);
	cout << TabChars[T.TabType][Line][0];
	for (int i = 1; i <= CCount; ++i)
	{
		short Len = T.Headers && (i == 1) ? T.RowHeaderWidth : T.CWidth; 
    	for (int j = 1; j <= Len; ++j)
			cout << TabChars[T.TabType][Line][1];
		if (i != CCount)
    		cout << TabChars[T.TabType][Line][2];
	}
	cout << TabChars[T.TabType][Line][3];
}

void FillChar1(int x, int y, int len, char c)
{
	GoToXY(x, y);
	for (int i = 0; i < len; ++i)
		cout << c;
}

void ViewerShow(Table &T)
{
	FillChar1(T.X, T.Y + T.Height - 3, 1, TabChars[T.TabType][2][0]);
	FillChar1(T.X + T.Width - 1, T.Y + T.Height - 3, 1, TabChars[T.TabType][2][3]);
	FillChar1(T.X, T.Y + T.Height - 2, 1, TabChars[T.TabType][1][0]);
	FillChar1(T.X + 1, T.Y + T.Height - 2, T.Width - 2, TabChars[T.TabType][1][1]);
	FillChar1(T.X + T.Width - 1 , T.Y + T.Height - 2, 1, TabChars[T.TabType][1][0]);
	FillChar1(T.X , T.Y + T.Height - 1, 1, TabChars[T.TabType][3][0]);
	FillChar1(T.X + 1, T.Y + T.Height - 1, T.Width - 2, TabChars[T.TabType][3][1]);
	FillChar1(T.X + T.Width - 1, T.Y + T.Height - 1, 1, TabChars[T.TabType][3][3]);
	WriteText(T.X + 2, T.Y + T.Height - 2, "  Cell");
}

void DrawEmptyTable(Table &T)
{
	short BColors = GetTextColors();
	TextColor(T.NormColors);
	SetConsoleCP(1251);
	int Y = T.Y;
	DrawTabLine(T, Y, 0);
	short RCount = T.Headers ? T.RCount + 1 : T.RCount;
	for (int i = 1; i <= RCount; ++i)
	{
		short Len = T.Headers && (i == 1) ? 1 : T.RHeight; 
    	for (int j = 1; j <= Len; ++j)
        	DrawTabLine(T, ++ Y, 1);
		if (i != RCount)
         	DrawTabLine(T, ++ Y, 2);
	}
	DrawTabLine(T, ++ Y, 3);
	if (T.ViewerShow)
		ViewerShow(T);
	cout << endl;
	SetConsoleCP(866);
	TextColor(BColors);
}

void ChangeCellAtr(Table &T, bool Select, int Row, int Col)
{
	short C, CH;
	if (Select)
	{
		C = T.SelectColors;
		CH = (T.NormColors & 0x00F0) | (T.SelectColors >> 4);
	}
	else
	{
		C = T.NormColors;
		CH = T.NormColors;
	}
	for (int i = 1; i <= T.RHeight; ++i)
		if (T.Headers)
		{
			ChangeTextAttribute(C, T.X + Col * (T.CWidth + 1) + T.RowHeaderWidth + 2, T.Y + Row * (T.RHeight + 1) + 3, T.CWidth);
			ChangeTextAttribute(CH, T.X + 1, T.Y + Row * (T.RHeight + 1) + 3, T.RowHeaderWidth);
			ChangeTextAttribute(CH, T.X + Col * (T.CWidth + 1) + T.RowHeaderWidth + 2, T.Y + 1, T.CWidth);
		}
		else
			ChangeTextAttribute(C, T.X + Col * (T.CWidth + 1) + 1, T.Y + Row * (T.RHeight + 1) + 1, T.CWidth);
}

void ViewVal(Table &T)
{
	if (T.ViewerShow)
	{
		GoToXY(T.X + 9, T.Y + T.Height - 2);
		char S[30] = "", S1[5];
		_itoa_s(T.DataRowTop + T.Row + 1, S1, 10);
		strcat_s(S, S1);
		strcat_s(S, "-");
		_itoa_s(T.DataColLeft + T.Col + 1, S1, 10);
		strcat_s(S, S1);
		strcat_s(S, ": ");
		cout << S;
		short L = strlen(S);
		ChangeTextAttribute(T.NormColors, T.X + 9, T.Y + T.Height - 2, L);
		GoToXY(T.X + L + 9, T.Y + T.Height - 2);
		cout << setw(T.Width - L - 11) << right << GetValue(T);
		T.EditorLen = T.Width - L - 11;
	}
}

char CellChoice(Table &T)
{
	char Ch;
	int BRow, BCol, BTopRow, BLeftCol;
	CursorVisible(false);
	do
	{
		ViewVal(T);
		ChangeCellAtr(T, true, T.Row, T.Col);
		BRow = T.Row;
		BCol = T.Col;
		BTopRow = T.DataRowTop;
		BLeftCol = T.DataColLeft;
		Ch = _getch();
		switch (Ch)
		{
		case 77: //Right
			if (T.Col < T.CCount - 1)
				++ T.Col;
			else
				if (T.Col + T.DataColLeft < T.DataCCount - 1)
					++ T.DataColLeft;
			break;
		case 75: //Left
			if (T.Col > 0)
				-- T.Col;
			else
				if (T.DataColLeft > 0)
					-- T.DataColLeft;
			break;
		case 72: //Up
			if (T.Row > 0)
				-- T.Row;
			else
				if (T.DataRowTop > 0)
					-- T.DataRowTop;
			break;
		case 80: //Down
			if (T.Row < T.RCount - 1)
				++ T.Row;
			else
				if (T.Row + T.DataRowTop < T.DataRCount - 1)
					++ T.DataRowTop;
			break;
		case 71: //Home
			T.Col = 0;
			T.DataColLeft = 0;
			break;
		case 79: //End
			T.Col = T.CCount - 1;
			T.DataColLeft = T.DataCCount - T.CCount;
			break;
		case 73: //PgUp
			T.Row = 0;
			T.DataRowTop = 0;
			break;
		case 81: //PgDn
			T.Row = T.RCount - 1;
			T.DataRowTop = T.DataRCount - T.RCount;
			break;
		case 27: //Esc
			break;
		case 13: //Enter
			break;
		};
		if ((T.DataRowTop != BTopRow) || (T.DataColLeft != BLeftCol))
			FillTable(T);
		else
			if ((T.Row != BRow) || (T.Col != BCol))
				ChangeCellAtr(T, false, BRow, BCol);
		T.Value = GetValue(T);
	}
	while ((Ch != 13) && (Ch != 27) && !strchr("01234567890+-.", Ch));
	CursorVisible(true);
	return Ch;
}

void ShowValue(Table &T, int Row, int Col, TInf Val)
{
	if (T.Visible)
	{
		if (T.Headers)
			GoToXY(T.X + (Col - T.DataColLeft) * (T.CWidth + 1) + T.RowHeaderWidth + 2, T.Y + (Row - T.DataRowTop) * (T.RHeight + 1) + 3);
		else
			GoToXY(T.X + (Col - T.DataColLeft) * (T.CWidth + 1) + 1, T.Y + (Row - T.DataRowTop) * (T.RHeight + 1) + 1);
		char S[20];
		_itoa_s(Val, S, 10);
		if ((sizeof(TInf) == sizeof(int) ? strlen(S) : strlen(S) + T.Precision + 1) > T.CWidth)
			cout << setw(T.CWidth) << "###";
		else
			cout << setw(T.CWidth) << fixed << setprecision(T.Precision) << Val;
	}
}

void FillHeaders(Table &T)
{ 
	short BColors = GetTextColors();
	TextColor(T.NormColors);
	for(int i = T.DataRowTop; i < T.DataRowTop + T.RCount; ++ i)
	{
		GoToXY(T.X + 1, T.Y + (i - T.DataRowTop) * (T.RHeight + 1) + 3);
		cout << setw(T.RowHeaderWidth - 2) << right << i + 1;
	}
	for(int i = T.DataColLeft; i < T.DataColLeft + T.CCount; ++ i)
	{
		GoToXY(T.X + T.RowHeaderWidth + (i - T.DataColLeft) * (T.CWidth + 1) + 3, T.Y + 1);
		cout << setw(T.CWidth - 2) << right << i + 1;
	}
    TextColor(BColors);
}

void FillTable(Table &T)
{ 
	int BX = WhereX(), BY = WhereY();
	if (T.Headers)
		FillHeaders(T);
	short BColors = GetTextColors();
	TextColor(T.NormColors);
	for(int i = 0; i < T.RCount; ++ i)
		for (int j = 0; j < T.CCount; ++ j)
			ShowValue(T, T.DataRowTop + i, T.DataColLeft + j, GetValue(T, T.DataRowTop + i, T.DataColLeft + j));
	ChangeCellAtr(T, true, T.Row, T.Col);
    TextColor(BColors);
	GoToXY(BX, BY);
}

TInf GetValue(Table &T, int Row, int Col)
{
	if (T.TypeData)
		return T.Data1[Row][Col];
	else
		return T.Data[Row * T.DataCCount  + Col];
}

TInf GetValue(Table &T)
{
	return GetValue(T, T.DataRowTop + T.Row, T.DataColLeft + T.Col);
}

void SetValue(Table &T, int Row, int Col, TInf Val)
{
	if (T.TypeData)
		T.Data1[Row][Col] = Val;
	else
		T.Data[Row * T.DataCCount  + Col] = Val;
}

void SetValue(Table &T, TInf Val)
{
	SetValue(T, T.DataRowTop + T.Row, T.DataColLeft + T.Col, Val);
}

void DrawValue(Table &T, int Row, int Col, TInf Val)
{
	SetValue(T, Row, Col, Val);
	ShowValue(T, Row, Col, Val);
}

void DrawValue(Table &T, TInf Val)
{
	DrawValue(T, T.DataRowTop + T.Row, T.DataColLeft + T.Col, Val);
}

char ReadStr(char *S, char &Ch)
{
	char C;
	S[0] = 0;
	int i = 0;
	do
	{
		if (Ch != 13)
		{
			C = Ch;
			Ch = 13;
		}
		else
			C = _getch();
		if ((C == 13) || (C == 27))
			S[i] = 0;
		else
			if (strchr("01234567890+-Ee.", C))
			{
				S[i] = C;
				cout << C;
				++ i;
			}
	}
	while ((!S[0] && ((C == 13) || (C != 27))) || (S[0] && (C != 13) && (C != 27)));
	return C;
}

void EditValue(Table &T, char Ch)
{
	if (!T.ReadOnly)
	{
		TInf Val;
		char S[200];
		char *C, c1;
		do
		{
			FillChar(T.X + T.Width - 2 - T.EditorLen, T.Y + T.Height - 2, T.EditorLen, ' ');
			GoToXY(T.X + T.Width - 2 - T.EditorLen, T.Y + T.Height - 2);
			c1 = ReadStr(S, Ch);
			Val = (TInf)strtod(S, &C);
			if ((c1 != 27) && (C[0]))
				MessageDlg("Invalid number format!", 0, 0x74);
		} while (C[0] && (c1 != 27));
		if (c1 != 27)
			DrawValue(T, Val);
	}
}

//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////   ОКНО    //////////////////////////////////

//struct Frame
//{
//	int X,					// Координата Х верхнего левого угла окна
//		Y,					// Координата Y верхнего левого угла окна
//		Height,				// Высота
//		Width,				// Ширина
//		TabType;			// Вид линий рамки (0 - одиночные; 1 - двойные)
//	short Colors;			// Цветовые аттрибуты (см. MyCrt)
//	char *Title;			// Текст заголовока окна
//	char *Buf;				// Указатель на буфер для сохранения изображения под окном
//};
//
//void InitFrame(Frame &T, int X, int Y, int Width, int Height, int TabType, short Colors); // Инициализация параметров окна
//void HideFrame(Frame &T);					// Убрать окно с экрана
//void ShowFrame(Frame &T);					// Показать окно на экране		
//void FreeFrame(Frame &T);					// Уничтожение окна на экране и в памяти

void InitFrame(Frame &T, int X, int Y, int Width, int Height, int Type, short Colors, const char *Title)
{
	T.X = X;
	T.Y = Y;
	T.Width = Width;
	T.Height = Height;
	T.Type = Type;
	T.Colors = Colors;
	int L = strlen(Title);
	T.Title =  new char[L + 1];
	strcpy(T.Title, Title);
	T.Buf = new char[T.Width * T.Height * sizeof(CHAR_INFO)];
}

void HideFrame(Frame &T)
{
	PasteRect(T.X, T.Y, T.X + T.Width - 1, T.Y + T.Height - 1, T.Buf);
}

void DrawLine(Frame &T, int Y, int Line)
{
	GoToXY(T.X, Y);
	cout << TabChars[T.Type][Line][0];
	for (int i = 1; i <= T.Width - 2; ++i)
		cout << TabChars[T.Type][Line][1];
	cout << TabChars[T.Type][Line][3];
}

void ShowFrame(Frame &T)
{
	CopyRect(T.X, T.Y, T.X + T.Width - 1, T.Y + T.Height - 1, T.Buf);
	short BColors = GetTextColors();
	TextColor(T.Colors);
	SetConsoleCP(1251);
	int Y = T.Y;
	DrawLine(T, Y, 0);
	for (int i = 1; i <= T.Height - 2; ++i)
       	DrawLine(T, ++ Y, 1);
	DrawLine(T, ++ Y, 3);
	cout << endl;
	SetConsoleCP(866);
	if (T.Title[0])
		WriteText(T.X + (T.Width - strlen(T.Title)) / 2, T.Y, T.Title, T.Colors);
	TextColor(BColors);
}

void FreeFrame(Frame &T)
{
	PasteRect(T.X, T.Y, T.X + T.Width - 1, T.Y + T.Height - 1, T.Buf);
	delete [] T.Title;
	delete [] T.Buf;
}

// Диалоговые функции

void MessageDlg(int X, int Y, const wchar_t *Text, int FrameType, short Colors)
	// Текст сообщения представлен в Юникоде
{
	int BX = WhereX(), BY = WhereY();
	CursorVisible(false);
	wchar_t S[] = L"Продолжение - любая клавиша";
	wchar_t S1[] = L"------------";
	Frame F;
	int LS = wcslen(S), LT = wcslen(Text);
	int L =  LT > LS ? LT + 4 : LS + 4;
	InitFrame(F, X, Y, L, 5, FrameType, Colors, "");
	ShowFrame(F);
	WriteText(F.X + (F.Width - LT) / 2, F.Y + 1, Text, Colors);
	WriteText(F.X + (F.Width - wcslen(S1)) / 2, F.Y + 2, S1, Colors);
	WriteText(F.X + (F.Width - LS) / 2, F.Y + 3, S, Colors);
	_getch();
	FreeFrame(F); 
	GoToXY(BX, BY);
	CursorVisible(false);
}

void MessageDlg(int X, int Y, const char *Text, int FrameType, short Colors)
	// Текст сообщения представлен однобайтными символами
{
	int BX = WhereX(), BY = WhereY();
	CursorVisible(false);
	char S[] = "Продолжение - любая клавиша";
	char S1[] = "------------";
	Frame F;
	int LS = strlen(S), LT = strlen(Text);
	int L =  LT > LS ? LT + 4 : LS + 4;
	InitFrame(F, X, Y, L, 5, FrameType, Colors, "");
	ShowFrame(F);
	WriteText(F.X + (F.Width - LT) / 2, F.Y + 1, Text, Colors);
	WriteText(F.X + (F.Width - strlen(S1)) / 2, F.Y + 2, S1, Colors);
	WriteText(F.X + (F.Width - LS) / 2, F.Y + 3, S, Colors);
	_getch();
	FreeFrame(F); 
	GoToXY(BX, BY);
	CursorVisible(false);
}

void MessageDlg(const wchar_t *Text, int FrameType, short Colors)
	// Текст сообщения представлен символами Юникода
	// Окно сообщения автоматически ценрируется в окне приложения
{
	int BX = WhereX(), BY = WhereY();
	CursorVisible(false);
	wchar_t S[] = L"Продолжение - любая клавиша";
	wchar_t S1[] = L"------------";
	Frame F;
	int LS = wcslen(S), LT = wcslen(Text);
	int L =  LT > LS ? LT + 4 : LS + 4;
	InitFrame(F, (GetScrWidth() - L) / 2, (GetScrHeight() - 5) / 2, L, 5, FrameType, Colors, "");
	ShowFrame(F);
	WriteText(F.X + (F.Width - LT) / 2, F.Y + 1, Text, Colors);
	WriteText(F.X + (F.Width - wcslen(S1)) / 2, F.Y + 2, S1, Colors);
	WriteText(F.X + (F.Width - LS) / 2, F.Y + 3, S, Colors);
	_getch();
	FreeFrame(F); 
	GoToXY(BX, BY);
	CursorVisible(false);
}

void MessageDlg(const char *Text, int FrameType, short Colors)
	// Текст сообщения представлен однобайтными символами
	// Окно сообщения автоматически ценрируется в окне приложения
{
	int BX = WhereX(), BY = WhereY();
	CursorVisible(false);
	char S[] = "Продолжение - любая клавиша";
	char S1[] = "------------";
	Frame F;
	int LS = strlen(S), LT = strlen(Text);
	int L =  LT > LS ? LT + 4 : LS + 4;
	InitFrame(F, (GetScrWidth() - L) / 2, (GetScrHeight() - 5) / 2, L, 5, FrameType, Colors, "");
	ShowFrame(F);
	WriteText(F.X + (F.Width - LT) / 2, F.Y + 1, Text, Colors);
	WriteText(F.X + (F.Width - strlen(S1)) / 2, F.Y + 2, S1, Colors);
	WriteText(F.X + (F.Width - LS) / 2, F.Y + 3, S, Colors);
	_getch();
	FreeFrame(F); 
	GoToXY(BX, BY);
	CursorVisible(false);
}

int StrCount(int L, const char *Text)
{
	int NS = 0, CCount = 0, PP = 0, TP = 0, SPP = 0;
	while (Text[TP])
	{
		if (Text[TP] != '\n')
		{
			if (Text[TP] == ' ')
			{
				PP = TP;
				SPP = CCount;
			}
			if (CCount == L - 5)
			{
				if (Text[TP + 1] != ' ')
				{
					TP = PP;
					CCount = SPP;
				}
				else
				{
					++TP;
					++CCount;
				}
				++NS;
				CCount = -1;
			}
			++CCount;
			++TP;
			if (!Text[TP])
				++NS;
		}
		else
		{
			++NS;
			CCount = 0;
			++TP;
			SPP = 0;
		}
	}
	return NS;
}

void DivStr(int L, const char *Text, char * MS)
{
	int NS = 0, CCount = 0, PP = 0, TP = 0, SPP = 0;
	while (Text[TP])
	{
		if (Text[TP] != '\n')
		{
 			*(MS + NS * (L - 3) + CCount) = Text[TP];
			if (Text[TP] == ' ')
			{
				PP = TP;
				SPP = CCount;
			}
			if (CCount == L - 5)
			{
				if (Text[TP + 1] != ' ')
				{
					TP = PP;
					CCount = SPP;
				}
				else
				{
					++TP;
					++CCount;
				}
				*(MS + NS * (L - 3) + CCount) = 0;
				++NS;
				CCount = -1;
			}
			++CCount;
			++TP;
			if (!Text[TP])
			{
				*(MS + NS * (L - 3) + CCount) = 0;
				++NS;
			}
		}
		else
		{
			*(MS + NS * (L - 3) + CCount) = 0;
			++NS;
			CCount = 0;
			++TP;
			SPP = 0;
		}
	}
}

void Message(Frame &F, int MaxLen, const char *Text, int FrameType, short Colors, const char *Prompt)
	// Сообщение Text выводится в окне, ширина которого равна MaxLen
	// Высота окна автоматически подстраивается под длину текста сообщения
	// Окно сообщения автоматически ценрируется в окне приложения
	// Текст сообщения представлен однобайтными символами
{
//	char S[] = "Продолжение - любая клавиша";
	char S1[] = "------------";
	int LS = strlen(Prompt), LT = strlen(Text);
	int L =  LS + 4 > MaxLen ? LS + 4 : MaxLen;
	int N = StrCount(L, Text);
	char *MS = new char [N * (L - 3)];
	DivStr(L, Text, MS);
	InitFrame(F, (GetScrWidth() - L) / 2, (GetScrHeight() - N - 4) / 2, L, N + 4, FrameType, Colors, "");
	ShowFrame(F);
	int Y = F.Y;
	for (int i = 0; i < N; ++ i)
		WriteText(F.X + (F.Width - strlen(MS + i * (L - 3))) / 2, ++Y, MS + i * (L - 3), Colors);
	delete [] MS;
	WriteText(F.X + (F.Width - strlen(S1)) / 2, ++Y, S1, Colors);
	WriteText(F.X + (F.Width - LS) / 2, ++Y, Prompt, Colors);
}

void MessageDlg(int MaxLen, const char *Text, int FrameType, short Colors)
	// Сообщение Text выводится в окне, ширина которого равна MaxLen
	// Высота окна автоматически подстраивается под длину текста сообщения
	// Окно сообщения автоматически ценрируется в окне приложения
	// Текст сообщения представлен однобайтными символами
{
	int BX = WhereX(), BY = WhereY();
	CursorVisible(false);
	Frame F;
	Message(F, MaxLen, Text, FrameType, Colors, "Продолжение - любая клавиша");
	_getch();
	FreeFrame(F); 
	GoToXY(BX, BY);
	CursorVisible(false);
}

bool YesNoDlg(int MaxLen, const char *Text, int FrameType, short Colors, bool Def, bool &Esc)
	// Вопрос Text выводится в окне, ширина которого равна MaxLen
	// Высота окна автоматически подстраивается под длину текста вопроса
	// Окно вопроса автоматически ценрируется в окне приложения
	// Текст вопроса представлен однобайтными символами
	// Возвращает результат ответа (true - false) и отказ от ответа Esc (клавиша Escape)
	// Def - исходное значение выбранного ответа
{
	int BX = WhereX(), BY = WhereY();
	CursorVisible(false);
	Frame F;
	Message(F, MaxLen, Text, FrameType, Colors, "Да   Нет");
	bool res = Def;
	char c;
	do
	{
		if (res)
		{
			ChangeTextAttribute(Colors, F.X + (F.Width - 8) / 2 + 4, F.Y + F.Height - 2, 5);
			ChangeTextAttribute(0x4E, F.X + (F.Width - 8) / 2 - 1, F.Y + F.Height - 2, 4);
		}
		else
		{
			ChangeTextAttribute(Colors, F.X + (F.Width - 8) / 2 - 1, F.Y + F.Height - 2, 4);
			ChangeTextAttribute(0x4E, F.X + (F.Width - 8) / 2 + 4, F.Y + F.Height - 2, 5);
		}
		c = _getch();
		switch (c)
		{
		case 77: //Right
			res = !res;
			break;
		case 75: //Left
			res = !res;
			break;
		}
	} while ((c != 13) && (c != 27));
	Esc = c == 27;
	FreeFrame(F); 
	GoToXY(BX, BY);
	CursorVisible(false);
	return res;
}
