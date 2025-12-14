#include <SDL3/SDL.h>

typedef enum SG_ELEMENT_STATE {
    SG_ELEMENT_STATE_HOVER,     //Cursor is over the button but the mouse wasn't pressed
    SG_ELEMENT_STATE_PRESSED,   //Mouse button is down on the button
    SG_ELEMENT_STATE_CLICKED,   //Mouse button was pressed and released, mouse button down and up on the button
    SG_ELEMENT_STATE_DEFAULT    //Nothing happens to the button
} SG_ELEMENT_STATE;

typedef struct SG_ELEMENT_DATA {
    SG_ELEMENT_STATE state;     
    float x, y;                 //where the element is being interacted with
} SG_ELEMENT_DATA;

typedef struct SG_Context {
    bool active;
    float mouse_x, mouse_y;
    SG_ELEMENT_STATE state;
} SG_Context;

SG_ELEMENT_DATA SG_Button(SG_Context* ctx, SDL_FRect* dst);

void SG_ContextProcessEvents(SDL_Window* window, SG_Context* ctx, SDL_Event* event);