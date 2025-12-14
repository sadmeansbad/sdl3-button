#include "button.h"
#include <SDL3/SDL.h>

SG_ELEMENT_DATA SG_Button(SG_Context* ctx, SDL_FRect* dst) {
    SG_ELEMENT_DATA data;
    if (ctx->active) {
        if (ctx->mouse_x > dst->x && 
            ctx->mouse_x < dst->x + dst->w && 
            ctx->mouse_y > dst->y && 
            ctx->mouse_y < dst->y + dst->h) {
            data.x = ctx->mouse_x - dst->x;
            data.y = ctx->mouse_y - dst->y;
            data.state = ctx->state;
            if (ctx->state == SG_ELEMENT_STATE_CLICKED) {
                ctx->state = SG_ELEMENT_STATE_HOVER;
            }
        } else {
            data.state = SG_ELEMENT_STATE_DEFAULT;
        }
    } else {
        data.state = SG_ELEMENT_STATE_DEFAULT;
    }
    return data;
}

void SG_ContextProcessEvents(SDL_Window* window, SG_Context* ctx, SDL_Event *event) {
    ctx->active = true;

    if (SDL_GetWindowFromID(event->button.windowID) != window) ctx->active = false;

    ctx->mouse_x = event->button.x;
    ctx->mouse_y = event->button.y;

    if (ctx->active) {
        if (ctx->state == SG_ELEMENT_STATE_PRESSED) {
            if (event->type == SDL_EVENT_MOUSE_BUTTON_UP && event->button.button == SDL_BUTTON_LEFT) {
                ctx->state = SG_ELEMENT_STATE_CLICKED;
            }
        } else if (ctx->state == SG_ELEMENT_STATE_HOVER && event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT) {
            ctx->state = SG_ELEMENT_STATE_PRESSED;
        } else {
            ctx->state = SG_ELEMENT_STATE_HOVER;
        }
    } else {
        ctx->state = SG_ELEMENT_STATE_DEFAULT;
    }
}