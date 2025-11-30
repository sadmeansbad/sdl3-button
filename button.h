#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

typedef enum SG_BUTTON_STATE {
    SG_BUTTON_STATE_HOVER,   //Cursor is over the button but the mouse wasn't pressed
    SG_BUTTON_STATE_PRESSED, //Mouse button is down on the button
    SG_BUTTON_STATE_CLICKED, //Mouse button was pressed and released, mouse button down and up on the button
    SG_BUTTON_STATE_DEFAULT  //Nothing happens to the button
} SG_BUTTON_STATE;

typedef struct SG_Button {
    SDL_Renderer* renderer; 
    SDL_FRect dst; 
    SG_BUTTON_STATE state;
} SG_Button;

SG_Button* SG_CreateButton(SDL_Renderer* renderer); 

void SG_ButtonProcessEvents(SDL_Event* event, SG_Button* btn);

SG_BUTTON_STATE SG_RenderButton(SG_Button* btn, SDL_FRect* dst, SDL_Texture* def, SDL_Texture* hov, SDL_Texture* prsd);