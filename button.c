#include "button.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>

SG_Button* SG_CreateButton(SDL_Renderer *renderer) {
    if (renderer == NULL) {
        return NULL;
    } 
    SG_Button* btn;
    btn = (SG_Button*)SDL_malloc(sizeof(SG_Button));
    btn->renderer = renderer;
    return btn;
}

void SG_ButtonProcessEvents(SDL_Event* event, SG_Button *btn) {
    if (SDL_GetMouseFocus() == SDL_GetRenderWindow(btn->renderer)) { //is the button in the same window as the mouse?
        float x, y;
        SDL_GetMouseState(&x, &y);
        if (x > btn->dst.x && x < btn->dst.x + btn->dst.w && y > btn->dst.y && y < btn->dst.y + btn->dst.h) {
            if (event->type == SDL_EVENT_MOUSE_BUTTON_UP && !event->button.down) {
                btn->state = SG_BUTTON_STATE_CLICKED;
                return;
            } else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                btn->state = SG_BUTTON_STATE_PRESSED;
            } else {
                btn->state = SG_BUTTON_STATE_HOVER;
            }
        } else {
            btn->state = SG_BUTTON_STATE_DEFAULT;
        }
    } else {
        btn->state = SG_BUTTON_STATE_DEFAULT;
    }
}

SG_BUTTON_STATE SG_RenderButton(SG_Button *btn, SDL_FRect* dst, SDL_Texture *def, SDL_Texture *hov, SDL_Texture *prsd) {
    btn->dst.x = dst->x;
    btn->dst.y = dst->y;
    btn->dst.w = dst->w;
    btn->dst.h = dst->h;

    switch (btn->state) {
        case SG_BUTTON_STATE_CLICKED:
            SDL_RenderTexture(btn->renderer, prsd, NULL, &btn->dst);
            btn->state = SG_BUTTON_STATE_HOVER;
            return SG_BUTTON_STATE_CLICKED;
            break;
        case SG_BUTTON_STATE_HOVER:
            SDL_RenderTexture(btn->renderer, hov, NULL, dst);
            break;
        case SG_BUTTON_STATE_PRESSED:
            SDL_RenderTexture(btn->renderer, prsd, NULL, &btn->dst);
            break;
        default:
            SDL_RenderTexture(btn->renderer, def, NULL, dst);    
            break;
    }
    
    return btn->state;
}
