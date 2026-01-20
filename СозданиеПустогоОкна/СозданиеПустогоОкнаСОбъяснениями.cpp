/*
~=~=~=~=~=~=*=~=~=~=~=~=~

Подробную информацию ищите в "Get Started with Win32 and C++"

~=~=~=~=~=~=*=~=~=~=~=~=~

Переменные:
1. HWND hwnd - дескриптор окна. Нужен, чтобы программа знала, с каким окном она работает (по сути номер окна). 
Создается функцией CreateWindowEx.

2. UINT uMsg - сообщение события (нажатие клавиши, мыши, закрытие окна и т.д.). 
Нужна, чтобы окно как-то реагировало на события. 
Формируется с помощью MSG msg внутри функции DispatchMessage(&msg).

3. WPARAM wParam и LPARAM lParam - параметры, которые бывают разные для разных событий.

4. HINSTANCE hInstance - дескриптор процесса, приложения в целом.

5. HINSTANCE hPrevInstance - не имеет смысла. Он использовался в 16-разрядной версии Windows, но теперь всегда равен нулю.

6. PWSTR pCmdLine - содержит аргументы командной строки в виде строки Юникода.

7. int nCmdShow - это флаг, указывающий, является ли основное окно приложения свернуто, развернуто или отображается в обычном режиме.

8. MSG msg - стурктура сообщения, которую формиует функция GetMessage(&msg, NULL, 0, 0), при этом сама функция возвращает числа, а не сообщение.

9. HDC hdc - дескриптор монитора. Нужен, чтобы программа знала, где она должна нарисовать окно.

10. PAINTSTRUCT ps - содержит сведения для приложения. 
Эти сведения можно использовать для рисования клиентской области окна, принадлежащей этому приложению.

~=~=~=~=~=~=*=~=~=~=~=~=~
*/
#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

//~=~=~=~=~=~=Предварительное объявление функции WindowProc=~=~=~=~=~=~
// 
//Предварительное объявление функции, чтоб использовать её в заполнении структуру WNDCLASS wc Она расписана дальше.
//Здесь пишется CALLBACK, потому что эту функцию вызывает другая функция DispatchMessage(&msg).
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//~=~=~=~=~=~=Начало wWinMain=~=~=~=~=~=~

//WINAPI пишется, чтоб заполнять стек аргументами в нужном порядке. Пишется wWinMain, а не WinMain, т.к. мы используем UNICODE, а не ANSI.
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine,
    int nCmdShow)
{

    //~=~=~=~=~=~=Создание класса окна=~=~=~=~=~=~

    //WNDCLASS wc - структура, по которой потом функция RegisterClass(&wc) зарегестрирует класс в операционной системе.
    //В дальнейшем CLASS_NAME[] будет представлять собой класс окна.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    //~=~=~=~=~=~=Создание окна=~=~=~=~=~=~

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              //                              1. Optional window styles.
        CLASS_NAME,                     //                              2. Window class
        L"Learn to Program Windows",    //                              3. Window text
        WS_OVERLAPPEDWINDOW,            //                              4. Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,     //5. x, y, width, height. Здесь можно было и числа указать
        NULL,       //                                                  6. Parent window    
        NULL,       //                                                  7. Menu
        hInstance,  //                                                  8. Instance handle
        NULL        //                                                  9. Additional application data
    );

    //hwnd чтоб знать, какое окно. nCmdShow чтоб знать, свернутое, развернутое или какое его делать.
    if (hwnd == NULL) { return 0; }
    ShowWindow(hwnd, nCmdShow);

    //~=~=~=~=~=~=Основной цикл работы приложения=~=~=~=~=~=~

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;

    //~=~=~=~=~=~=Здесь заканчивается приложение после срабатывания PostQuitMessage(0) в WindowProc=~=~=~=~=~=~
}

//~=~=~=~=~=~=Конец wWinMain=~=~=~=~=~=~


//~=~=~=~=~=~=Функция WindowProc=~=~=~=~=~=~
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        //&ps.rcPaint - Указатель на структуру RECT , содержащую логические координаты заполняемого прямоугольника.
        //hbr => (HBRUSH)(COLOR_BACKGROUND) - Маркер кисти, используемой для заполнения прямоугольника.
        //Если для параметра hbr указано значение цвета, оно должно быть одним из стандартных системных цветов
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));

        EndPaint(hwnd, &ps);
    }
    return 0;
    }

    /*
    1. При нажатии на крестик возникает событие WN_CLOSE.

    2. Можно сделать реацию на это событие в WindowProc, если, например, пользователь случайно туда нажал и хочет отменить действие.
    (Написать код среди case'ов, который обработает событие и отменит нажатие).

    3. Дальше событие WN_CLOSE попадает в DefWindowProc - стандартный обработчик всех событий. 
    Он стоит в конце всех case'ов и обрабатывает события, на которые программист своего ничего не написал.

    4. DefWindowProc вызывает функцию DestroyWindow, которая разрушает окно, ПОСЛЕ ЧЕГО кидает событие WM_DESTROY в очередь.

    5. PostQuitMessage реагирует на это событие и помещает сообщение WM_QUIT в очередь сообщений, что приводит к завершению цикла сообщений.
    
    6. Программа завершается
    */
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
