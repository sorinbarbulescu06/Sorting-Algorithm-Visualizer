#include "Sort_Core.h"

void Swap_Bars(Rectangle *a, Rectangle *b)
{
        int aux1 = a->y, aux2= a->height;
        a->y = b->y;
        b->y = aux1;
        a->height = b->height;
        b->height = aux2;
}

void Draw_Buttons(button *buttons)
{
    int i;
    for(i = 0 ; i < NB; i++){
        DrawRectangleRec(buttons[i].Coord, buttons[i].col);
        DrawRectangleLinesEx(buttons[i].Coord, 3, BLACK);
        DrawText(buttons[i].s, buttons[i].Coord.x + Button_Offset / 2, buttons[i].Coord.y + 12, 20, BLACK);
    }
}

void Draw_Bars(bar *bars)
{
    int i;
    for(i = 0 ; i < Bar_Number; i++){
        DrawRectangleRec(bars[i].Coord, bars[i].col);
    }
}

void Draw(button *buttons, int Array_exists, bar *bars)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    Draw_Buttons(buttons);
    if(Array_exists == 1){
        Draw_Bars(bars);
    }
    EndDrawing();
}

button* button_init()
{
    button *buttons = malloc(NB*sizeof(button));
    if(buttons == NULL){
        exit(1);
    }
    int i, Blank_L;
    Blank_L = (Width - NB * Button_L) / (NB + 1);
    for(i = 0; i < NB; i++){
        buttons[i].Coord.x = (i + 1) * Blank_L + i * Button_L;
        buttons[i].Coord.y = Height - Button_Offset - Button_H;
        buttons[i].Coord.height = Button_H;
        buttons[i].Coord.width = Button_L;
        buttons[i].s = malloc(16 * sizeof(char));
        if(buttons[i].s == NULL)
            exit(1);
    }
    strcpy(buttons[0].s , "Randomise");
    strcpy(buttons[1].s , "Bubble Sort");
    strcpy(buttons[2].s , "Quick Sort");
    buttons[0].col = RED;
    buttons[1].col = YELLOW;
    buttons[2].col = BLUE;
    return buttons;
}

button* Init()
{
    InitWindow(Width, Height, "Sorting Alg. Visualizer");
    SetTargetFPS(FPS);
    button *buttons = button_init();
    return buttons;
}

bar* generate()
{
    int i;
    int MaxBar_Height = Height - Button_Offset - Button_H - 2 * Bar_Offset;
    int Blank_Space = (Width - Bar_Number * Bar_Width) / 2;
    bar *bars = malloc(Bar_Number * sizeof(bar));
    for(i = 0; i < Bar_Number; i++){
        bars[i].Coord.height = (i + 1) * (MaxBar_Height / Bar_Number);
        bars[i].col = WHITE;
        bars[i].Coord.width = Bar_Width;
        bars[i].Coord.y = Bar_Offset + (MaxBar_Height - bars[i].Coord.height);
        bars[i].Coord.x = Blank_Space + i * Bar_Width;
    }
    for(i = Bar_Number - 1; i > 0; i--){
        int j = GetRandomValue(0, i);
        Swap_Bars(&bars[i].Coord, &bars[j].Coord);
    }
    return bars;
}

int StartBubbleSort(bar *bars, int Array_Exists, button *buttons)
{
    SetTargetFPS(720);
    int i,j;
    for(i = 0; i < Bar_Number - 1; i++){
        bars[i].col = RED;
        Draw(buttons, Array_Exists, bars);
        for(j = i + 1; j < Bar_Number; j++){
            if(WindowShouldClose() != 0)
                return 0;
            bars[j].col = RED;
            Draw(buttons, Array_Exists, bars);
            if(bars[i].Coord.height > bars[j].Coord.height){
                Swap_Bars(&bars[i].Coord, &bars[j].Coord);
            }
            Draw(buttons, Array_Exists, bars);
            bars[j].col = WHITE;
            
        }
        bars[i].col = GREEN;
        Draw(buttons, Array_Exists, bars);
    }
    bars[Bar_Number - 1].col = GREEN;
    Draw(buttons, Array_Exists, bars);
    SetTargetFPS(FPS);
    return 1;
}

void StartQuickSort(bar *bars, int Array_Exists, button *buttons, int pivot,int st)
{
    if(st >= pivot){
        bars[st].col = GREEN;
        Draw(buttons, Array_Exists, bars);
        if(WindowShouldClose() != 0)
            exit(1);
    }
    else{
        int i;
        int cnt = st;
        bars[pivot].col = RED;
        Draw(buttons, Array_Exists, bars);
        for(i = st; i < pivot; i++){
            bars[i].col = RED;
            Draw(buttons, Array_Exists, bars);
            if(WindowShouldClose() != 0)
                    exit(1);
            if(bars[i].Coord.height < bars[pivot].Coord.height){
                Swap_Bars(&bars[i].Coord, &bars[cnt].Coord);
                Draw(buttons, Array_Exists, bars);
                cnt++;
            }
            bars[i].col = WHITE;
        }
        bars[pivot].col = WHITE;
        Swap_Bars(&bars[cnt].Coord, &bars[pivot].Coord);
        bars[cnt].col = GREEN;
        Draw(buttons, Array_Exists, bars);
        StartQuickSort(bars, Array_Exists, buttons, cnt - 1, st);
        StartQuickSort(bars, Array_Exists, buttons, pivot, cnt + 1);
    }   
}

int CheckAndDo_Button_Pressed(button *buttons, int *Array_Exists, bar **bars)
{
    Vector2 Mouse_Pos = GetMousePosition();
    int i, ind = -1;
    bool Hover = false;
    for(i = 0; i < NB; i++){
        if(CheckCollisionPointRec(Mouse_Pos, buttons[i].Coord)){
            Hover = true;
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                ind = i;
            }
        }
    }
    if(Hover == true){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    int close = -1;
    if(ind == 0){
        if(*Array_Exists == 1){
            free(*bars);
        }
        *bars = generate();
        *Array_Exists = 1;
    }
    if(ind == 1 && *Array_Exists == 1){
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        close = StartBubbleSort(*bars, *Array_Exists, buttons);
        if(close == 0)
            return 0;
    }
    if(ind == 2 && *Array_Exists == 1){
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        StartQuickSort(*bars, *Array_Exists, buttons, Bar_Number - 1, 0);
    }
    return 1;
}