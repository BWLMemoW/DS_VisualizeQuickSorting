#ifdef __MINGW32__
#include <stdio.h>
extern "C" {
    FILE* __imp___iob_func(void) {
        static FILE iob[3];
        iob[0] = *stdin;
        iob[1] = *stdout;
        iob[2] = *stderr;
        return iob;
    }
}
#endif

#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>  // 添加头文件
#include <cwchar>   // 添加头文件

using namespace std;

// 结构体定义：用于表示数组元素
struct Object
{
    int val, type = 0;  // val: 元素值, type: 元素类型(0=未排序,1=比较中,2=已排序)
};

// 辅助函数：将char数组转换为TCHAR数组
void charToTCHAR(const char* src, TCHAR* dest, int maxSize) {
#ifdef _UNICODE
    mbstowcs(dest, src, maxSize);
#else
    strncpy(dest, src, maxSize);
    dest[maxSize - 1] = '\0';
#endif
}

// 显示开始界面
void ShowStartScreen() {
    int width = getwidth();
    int height = getheight();
    
    // 设置背景颜色
    setbkcolor(BLACK);
    cleardevice();
    
    // 绘制标题
    settextstyle(36, 0, _T("Arial"));
    settextcolor(LIGHTGREEN);
    
    TCHAR titleText[] = _T("Quick Sort Visualization");
    int titleWidth = textwidth(titleText);
    outtextxy((width - titleWidth) / 2, height / 4, titleText);
    
    // 绘制副标题
    settextstyle(24, 0, _T("Arial"));
    settextcolor(LIGHTCYAN);
    
    TCHAR subtitleText[] = _T("Interactive Sorting Demo");
    int subtitleWidth = textwidth(subtitleText);
    outtextxy((width - subtitleWidth) / 2, height / 4 + 50, subtitleText);
    
    // 绘制分隔线
    setlinecolor(LIGHTGRAY);
    setlinestyle(PS_SOLID, 2);
    line(width / 4, height / 2, width * 3 / 4, height / 2);
    
    // 绘制说明文字
    settextstyle(16, 0, _T("Arial"));
    settextcolor(YELLOW);
    
    TCHAR instructions[][100] = {
        _T("White: Unsorted elements"),
        _T("Yellow: Pivot or comparing elements"),
        _T("Green: Sorted elements"),
        _T("Shows current array state during sorting"),
        _T("Press any key to start the visualization")
    };
    
    int startY = height / 2 + 30;
    for (int i = 0; i < 5; i++) {
        outtextxy(width / 4, startY + i * 30, instructions[i]);
    }
    
    // 绘制开始提示
    settextstyle(22, 0, _T("Arial"));
    settextcolor(LIGHTMAGENTA);
    
    TCHAR startPrompt[] = _T("Press any key to start...");
    int promptWidth = textwidth(startPrompt);
    outtextxy((width - promptWidth) / 2, height * 3 / 4, startPrompt);
    
    // 绘制版本信息
    settextstyle(12, 0, _T("Arial"));
    settextcolor(DARKGRAY);
    
    TCHAR versionText[] = _T("Version 1.0 | Using EasyX Graphics Library");
    outtextxy(width - textwidth(versionText) - 10, height - 25, versionText);
    
    // 等待用户按下任意键
    getch();
    
    // 添加一个简单的动画效果（闪烁提示文字）
    for (int i = 0; i < 3; i++) {
        settextcolor(i % 2 == 0 ? LIGHTRED : LIGHTMAGENTA);
        outtextxy((width - promptWidth) / 2, height * 3 / 4, startPrompt);
        Sleep(200);
    }
    
    // 清屏准备开始排序
    cleardevice();
}

// 绘制函数：可视化当前数组状态
void Draw(Object Arr[10]) {
    // 获取画布尺寸
    int width = getwidth();
    int height = getheight();
    
    // 计算柱状图的宽度和间距
    int barWidth = width / 15;
    int spacing = width / 30;
    int maxVal = Arr[0].val;
    
    // 找到最大值以便进行缩放
    for (int i = 1; i < 10; i++) {
        if (Arr[i].val > maxVal) {
            maxVal = Arr[i].val;
        }
    }
    
    // 计算缩放因子
    float scale = (height * 0.8) / maxVal;
    
    // 清除背景
    setbkcolor(BLACK);
    cleardevice();
    
    // 绘制标题
    settextstyle(24, 0, _T("Arial"));
    settextcolor(LIGHTGRAY);
    
    TCHAR titleText[] = _T("Quick Sort Visualization");
    outtextxy(width/2 - textwidth(titleText)/2, 5, titleText);
    
    // 绘制操作提示
    settextstyle(12, 0, _T("Arial"));
    TCHAR instructionText[] = _T("Press 'R' to restart, 'E' to exit");
    outtextxy(10, 40, instructionText);
    
    // 设置文本属性
    settextstyle(14, 0, _T("Arial"));
    setbkmode(TRANSPARENT);
    
    // 绘制每个数组元素
    for (int i = 0; i < 10; i++) {
        int x = spacing + i * (barWidth + spacing);
        int barHeight = Arr[i].val * scale;
        int y = height - barHeight - 60;  // 为底部的文本留出空间
        
        // 根据元素类型设置不同的颜色
        if(Arr[i].type == 0) setfillcolor(WHITE);
        else if(Arr[i].type == 1) setfillcolor(YELLOW);
        else setfillcolor(GREEN);
        
        // 绘制带边框的柱状图
        setlinecolor(DARKGRAY);
        setlinestyle(PS_SOLID, 2);
        fillrectangle(x, y, x + barWidth, height - 60);
        
        // 在柱状图上方绘制数值
        char valueText[20];
        sprintf(valueText, "%d", Arr[i].val);
        
        // 转换为TCHAR类型
        TCHAR tValueText[20];
        charToTCHAR(valueText, tValueText, 20);
        
        settextcolor(LIGHTGRAY);
        int textWidth = textwidth(tValueText);
        outtextxy(x + (barWidth - textWidth)/2, y - 25, tValueText);
        
        // 在柱状图下方绘制索引
        char indexText[10];
        sprintf(indexText, "%d", i);
        
        TCHAR tIndexText[10];
        charToTCHAR(indexText, tIndexText, 10);
        
        int indexTextWidth = textwidth(tIndexText);
        outtextxy(x + (barWidth - indexTextWidth)/2, height - 45, tIndexText);
    }
    
    // 绘制当前数组的文本表示
    settextstyle(16, 0, _T("Courier New"));
    
    char arrayText[256];
    sprintf(arrayText, "Current Array: [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", 
            Arr[0].val, Arr[1].val, Arr[2].val, Arr[3].val, Arr[4].val, 
            Arr[5].val, Arr[6].val, Arr[7].val, Arr[8].val, Arr[9].val);
    
    TCHAR tArrayText[256];
    charToTCHAR(arrayText, tArrayText, 256);
    
    int textY = height - 25;
    outtextxy(20, textY, tArrayText);
    
    // 绘制图例
    settextstyle(12, 0, _T("Arial"));
    setfillcolor(WHITE);
    fillrectangle(10, 70, 25, 85);
    TCHAR unsortedText[] = _T("Unsorted");
    outtextxy(30, 70, unsortedText);
    
    setfillcolor(YELLOW);
    fillrectangle(120, 70, 135, 85);
    TCHAR comparingText[] = _T("Pivot/Comparing");
    outtextxy(140, 70, comparingText);
    
    setfillcolor(GREEN);
    fillrectangle(280, 70, 295, 85);
    TCHAR sortedText[] = _T("Sorted");
    outtextxy(300, 70, sortedText);
}

// 等待R键或E键的函数
void WaitForRKey() {
    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'r' || ch == 'R') {
                cleardevice();
                return;
            }
            if (ch == 'e' || ch == 'E') {
                closegraph();
                exit(0);
            }
        }
        // 短暂延迟以防止CPU过度使用
        Sleep(10);
    }
}

// 可视化排序过程
void VisualizeSort(Object Arr[]) {
    // 在开始前重置所有元素类型
    for (int i = 0; i < 10; i++) {
        Arr[i].type = 0;
    }
    
    stack<pair<int, int>> stk;
    stk.push({0, 9});
    
    while (!stk.empty()) {
        auto [low, high] = stk.top();
        stk.pop();
        
        if (low >= high) {
            if (low == high) {
                Arr[low].type = 2;
                Draw(Arr);
                Sleep(500);
            }
            continue;
        }
        
        // 分区操作
        Object pivot = Arr[low];
        pivot.type = 1;
        Arr[low].type = 1;
        
        int i = low, j = high;
        
        // 可视化分区前的状态
        Draw(Arr);
        Sleep(500);
        
        while (i < j) {
            // 移动j指针
            Arr[j].type = 1;
            while (i < j && Arr[j].val >= pivot.val) {
                Arr[j].type = 0;
                j--;
                if (i < j) Arr[j].type = 1;
                Draw(Arr);
                Sleep(300);
            }
            if (i < j) {
                Arr[i] = Arr[j];
                i++;
            }
            
            // 移动i指针
            if (i < j) Arr[i].type = 1;
            while (i < j && Arr[i].val <= pivot.val) {
                Arr[i].type = 0;
                i++;
                if (i < j) Arr[i].type = 1;
                Draw(Arr);
                Sleep(300);
            }
            if (i < j) {
                Arr[j] = Arr[i];
                j--;
            }
        }
        
        Arr[i] = pivot;
        Arr[i].type = 2;
        
        // 可视化分区后的状态
        Draw(Arr);
        Sleep(500);
        
        // 重置下一个分区的元素类型
        for (int k = low; k <= high; k++) {
            if (k != i) Arr[k].type = 0;
        }
        
        // 将子数组压入栈
        if (i + 1 < high) stk.push({i + 1, high});
        if (low < i - 1) stk.push({low, i - 1});
    }
    
    // 最终可视化 - 所有元素已排序
    for (int i = 0; i < 10; i++) {
        Arr[i].type = 2;
    }
    Draw(Arr);
    
    // 显示完成信息
    settextstyle(20, 0, _T("Arial"));
    settextcolor(LIGHTGREEN);
    
    TCHAR completeText[] = _T("Sorting Complete!");
    TCHAR restartText[] = _T("Press R to restart or E to exit");
    
    outtextxy(getwidth()/2 - textwidth(completeText)/2, 
              getheight()/2 - 100, completeText);
    outtextxy(getwidth()/2 - textwidth(restartText)/2,
              getheight()/2 - 70, restartText);
}

bool isNumber(const std::string& str)
{
    std::stringstream ss(str);
    int d;
    ss >> d;
    return ss.eof(); // 成功解析且没有剩余字符

}

int GetRand(int min, int max)
{
    int num = (double)rand()/(RAND_MAX+1) * (max-min) + min;
    return num;
}

int main()
{
    srand(time(0));
    int testArray[10];
    int t1[10] = {10,7,6,8,1,2,4,9,5,3};
    int t2[10] = {10,9,8,7,6,5,4,3,2,1};
    int t3[10] = {1,2,3,4,5,6,7,8,9,10};

    HWND hwnd = initgraph(1000, 700, EX_NOCLOSE); //初始化图形窗口
    setbkcolor(BLACK);
    SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE); //保持窗口始终置顶
    
    ShowStartScreen(); //显示开始界面

    printf("========================\n");
    printf("Quick Sort Visualization\n");
    printf("========================\n");
    printf("Use Examples? y/n(Default):");
    
    string inp;
    getline(cin,inp);

    char c = inp[0];

    if(c == 'y')
    {
        printf("#1(Default) - [10,7,6,8,1,2,4,9,5,3]\n");
        printf("#2 - [10,9,8,7,6,5,4,3,2,1]\n");
        printf("#3 - [1,2,3,4,5,6,7,8,9,10]\n");
        printf("#4 - 10 random ones in [1,20]\n");
        printf("Input example id: #");

        
        getline(cin,inp);
        if(!isNumber(inp))
        {
            inp = "1";
        }
        
        int id;
        std::stringstream ss(inp);
        ss >> id;

        if(id == 2) for(int i = 0; i < 10; i++) testArray[i] = t2[i];
        else if(id == 3) for(int i = 0; i < 10; i++) testArray[i] = t3[i];
        else if(id == 4) for(int i = 0; i < 10; i++) testArray[i] = GetRand(1,20);
        else for(int i = 0; i < 10; i++) testArray[i] = t1[i];
    }
    else
    {
        printf("Please input 10 integers separated by spaces:\n");

        
        for(int i = 0; i < 10; i++)
        {
            printf("Element %d: ", i+1);
            
            getline(cin,inp);
            if(!isNumber(inp))
            {
                printf("[ERROR] Not a number\n");
                i--;
                continue;
            }
            
            int t;
            std::stringstream ss(inp);
            ss >> t;

            if(t <= 0) 
            {
                printf("[ERROR] Element should be greater than 0\n");
                i--;
            }
            else testArray[i] = t;
        }
    }
    
    while (true)
    {
        Object objects[10];
        for(int i = 0; i < 10; i++) //设置排序数组
        {
            objects[i].val = testArray[i];
            objects[i].type = 0;
        }
        
        VisualizeSort(objects); //排序并可视化
        
        WaitForRKey(); //等待用户输入以重新开始或退出
        
        //如果用户按了R键，获取新数组
        printf("\nUse Examples?(or press Ctrl+C to exit) y/n(Default):");
        getline(cin,inp);
        char c = inp[0];

        if(c == 'y')
        {
            printf("#1(Default) - [10,7,6,8,1,2,4,9,5,3]\n");
            printf("#2 - [10,9,8,7,6,5,4,3,2,1]\n");
            printf("#3 - [1,2,3,4,5,6,7,8,9,10]\n");
            printf("#4 - 10 random ones in [1,20]\n");
            printf("Input example id: #");

            
            getline(cin,inp);
            if(!isNumber(inp))
            {
                inp = "1";
            }
            
            int id;
            std::stringstream ss(inp);
            ss >> id;

            if(id == 2) for(int i = 0; i < 10; i++) testArray[i] = t2[i];
            else if(id == 3) for(int i = 0; i < 10; i++) testArray[i] = t3[i];
            else if(id == 4) for(int i = 0; i < 10; i++) testArray[i] = GetRand(1,20);
            else for(int i = 0; i < 10; i++) testArray[i] = t1[i];
        }
        else
        {
            printf("Please input 10 integers separated by spaces:\n");

        
            for(int i = 0; i < 10; i++)
            {
                printf("Element %d: ", i+1);
                
                getline(cin,inp);
                if(!isNumber(inp))
                {
                    printf("[ERROR] Not a number\n");
                    i--;
                    continue;
                }
                
                int t;
                std::stringstream ss(inp);
                ss >> t;

                if(t <= 0) 
                {
                    printf("[ERROR] Element should be greater than 0\n");
                    i--;
                }
                else testArray[i] = t;
            }
        }
        cleardevice();
    }
    
    closegraph();
    return 0;
}