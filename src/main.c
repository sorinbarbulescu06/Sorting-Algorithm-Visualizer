#include "Sort_Core.h"

int main()
{
    int i;
    int Button_Pressed = 0;
    int Array_Exists = 0;
    bar *bars;
    button *buttons;
    buttons = Init();
    while(!WindowShouldClose()){
        int close = -1;
        close = CheckAndDo_Button_Pressed(buttons, &Array_Exists, &bars);
        if(close == 0)
            break;
        Draw(buttons, Array_Exists, 0, bars);
    }
    for(i = 0; i < NB; i++)
        free(buttons[i].s);
    free(bars);
    free(buttons);
    CloseWindow();
    return 0;
}