#pragma once

///////////////////////////////   ТАБЛИЦА   ///////////////////////////////

typedef double TInf;        // Тип данных для таблицы (для целых чисел заменить double на int)

struct Table
{
	short
		X,					// Координата Х верхнего левого угла таблицы
		Y,					// Координата Y верхнего левого угла таблицы
		CCount,				// Количество столбцов таблицы
		CWidth,				// Ширина столбцов таблицы без учета границ
		RCount,				// Количество строк таблицы
		RHeight,			// Высота строк таблицы без учета границ
		TabType,			// Вид линий сетки таблицы (0 - одиночные; 1 - двойные; 2 - комбинированные)
		Row,				// Индекс строки выбранной ячейки талицы (первая строка имеет индекс 0)
		Col,				// Индекс столбца выбранной ячейки талицы (первый столбец имеет индекс 0)
		Width,				// Полная широина таблицы
		Height,				// Полная высота таблицы
	    NormColors,		    // Цветовые аттрибуты не выбранных ячеек (см. MyCrt)
		SelectColors,		// Цветовые аттрибуты выбранной ячейки (см. MyCrt)
		Precision;			// Количество разрядов после десятичной точки
	TInf Value;				// Значение в выбранной ячейке талицы
	union					// Массив данных для заполнения ячеек таблицы 
	{
		TInf * Data;		
		TInf ** Data1;
	};
	bool TypeData;          // Вид двумерного массива: true - Data[i][j]; false - Data[i * Col + j]
	short DataRCount,		// Количество строк в массиве данных
		  DataCCount,		// Количество столбцов в массиве данных
		  DataRowTop,		// Индекс строки массива данных, находящейся в первой строке таблицы
		  DataColLeft;		// Индекс столбца массива данных, находящегося в первом столбце таблицы
	char *Buf;				// Указатель на буфер для сохранения изображения под таблицей
    bool Headers;			// Рисовать нумераторы строк и столбцов
    short RowHeaderWidth;   // Ширина столбца нумератора строк
	bool Visible,			// Таблица на экране
	     ViewerShow;	    // Показать просмотрщик значений ячеек
	bool ReadOnly;          // Запретить редактирование
    short EditorLen;		// Длина строки редактора
};
void InitTable(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType, short NormColors, short SelectColors, TInf *Data, 
			   short DataCCount, short DataRCount, short Precision, bool ReadOnly, bool Viewer, bool Headers = true);      // Инициализация параметров таблицы Т
void InitTable(Table &T, int X, int Y, int CCount, int CWidth, int RCount, int RHeight, int TabType, short NormColors, short SelectColors, TInf **Data, 
			   short DataCCount, short DataRCount, short Precision, bool ReadOnly, bool Viewer, bool Headers = true);     // Инициализация параметров таблицы Т
void HideTable(Table &T, short Colors);					// Стереть таблицу с экрана цветом Colors
void ShowTable(Table &T);								// Показать таблицу на экране		
void DrawEmptyTable(Table &T);							// Нарисовать таблицу без данных на экране
void FillTable(Table &T);								// Заполнить таблицу данными из массива таблицы
char CellChoice(Table &T);								// Выбор ячейки таблицы
TInf GetValue(Table &T, int Row, int Col);				// Взять значение ячейки с индексами Row, Col
TInf GetValue(Table &T);				                // Взять значение активной ячейки
void SetValue(Table &T, int Row, int Col, TInf Val);	// Занести значение в ячейку с индексами Row, Col массива таблицы
void SetValue(Table &T, TInf Val);		                // Занести значение в активную ячейку
void DrawValue(Table &T, int Row, int Col, TInf Val);	// Занести значение в ячейку с индексами Row, Col массива таблицы и вывести на экран
void DrawValue(Table &T, TInf Val);	                    // Занести значение в активную ячейку массива таблицы и вывести на экран
void FreeTable(Table &T);								// Стереть с экрана и освобождить память от таблицы
void EditValue(Table &T, char Ch);						// Редактирование значения текущей ячейки

/////////////////////////////////   ОКНО    //////////////////////////////////

struct Frame
{
	int X,					// Координата Х верхнего левого угла окна
		Y,					// Координата Y верхнего левого угла окна
		Height,				// Высота
		Width,				// Ширина
		Type;				// Вид линий рамки (-1 - без рамки; 0 - одиночные; 1 - двойные)
	short Colors;			// Цветовые аттрибуты (см. MyCrt)
	char *Title;			// Текст заголовока окна
	char *Buf;				// Указатель на буфер для сохранения изображения под окном
};

void InitFrame(Frame &T, int X, int Y, int Width, int Height, int TabType, short Colors, const char *Title); // Инициализация параметров окна
void HideFrame(Frame &T);					// Убрать окно с экрана
void ShowFrame(Frame &T);					// Показать окно на экране		
void FreeFrame(Frame &T);					// Уничтожение окна на экране и в памяти

//////////////////////////// Диалоговые функции //////////////////////////

void MessageDlg(int X, int Y, const wchar_t *Text, int FrameType, short Colors);
	// Однострочное текстовое сообщение Text выводится в окне с координатами X и Y.
	// Ширина окна автоматически подстраивается под длину текста сообщения
	// Текст сообщения представлен символами Юникода
void MessageDlg(int X, int Y, const char *Text, int FrameType, short Colors);
	// Однострочное текстовое сообщение Text выводится в окне с координатами X и Y.
	// Ширина окна автоматически подстраивается под длину текста сообщения
	// Текст сообщения представлен однобайтными символами 
void MessageDlg(const char *Text, int FrameType, short Colors);
	// Окно сообщения автоматически ценрируется в окне приложения
	// Ширина окна автоматически подстраивается под длину текста сообщения
	// Текст сообщения представлен однобайтными символами
void MessageDlg(const wchar_t *Text, int FrameType, short Colors);
	// Текст сообщения представлен символами Юникода
	// Ширина окна автоматически подстраивается под длину текста сообщения
	// Окно сообщения автоматически ценрируется в окне приложения
void MessageDlg(int MaxLen, const char *Text, int FrameType, short Colors);
	// Сообщение Text выводится в окне, ширина которого равна MaxLen
	// Высота окна автоматически подстраивается под длину текста сообщения
	// Окно сообщения автоматически центрируется в окне приложения
	// Текст сообщения представлен однобайтными символами
bool YesNoDlg(int MaxLen, const char *Text, int FrameType, short Colors, bool Def, bool &Esc);
	// Вопрос Text выводится в окне, ширина которого равна MaxLen
	// Высота окна автоматически подстраивается под длину текста вопроса
	// Окно вопроса автоматически ценрируется в окне приложения
	// Текст вопроса представлен однобайтными символами
	// Возвращает результат ответа (true - false) и отказ от ответа Esc (клавиша Escape) 
	// Def - исходное значение выбранного ответа
