/* OCamlSDL2 - An OCaml interface to the SDL2 library
 Copyright (C) 2013 Florent Monnier
 
 This software is provided "AS-IS", without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from
 the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely.
*/
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>

#include <SDL_video.h>
#include "sdlwindow_stub.h"

/* TODO
int SDL_GL_LoadLibrary(const char *path);
void * SDL_GL_GetProcAddress(const char *proc);
*/

CAMLprim value
caml_SDL_GL_UnloadLibrary(value unit)
{
    SDL_GL_UnloadLibrary();
    return Val_unit;
}

CAMLprim value
caml_SDL_GL_ExtensionSupported(value extension)
{
    SDL_bool b = SDL_GL_ExtensionSupported(String_val(extension));
    return Val_bool(b);
}

/*
int SDL_GL_SetAttribute(SDL_GLattr attr, int value);
int SDL_GL_GetAttribute(SDL_GLattr attr, int *value);
*/

#define SDL_GLContext_val(ctx) ((SDL_GLContext)(ctx))
#define Val_SDL_GLContext(ctx) ((value)(ctx))

CAMLprim value
caml_SDL_GL_CreateContext(value window)
{
    SDL_GLContext ctx = SDL_GL_CreateContext(SDL_Window_val(window));
    return Val_SDL_GLContext(ctx);
}

CAMLprim value
caml_SDL_GL_MakeCurrent(value window, value context)
{
    int r = SDL_GL_MakeCurrent(
            SDL_Window_val(window), SDL_GLContext_val(context));
    return Val_int(r);
}

/*
int SDL_GL_SetSwapInterval(int interval);
*/

CAMLprim value
caml_SDL_GL_GetSwapInterval(value unit)
{
    int r = SDL_GL_GetSwapInterval();
    return Val_int(r);
}

CAMLprim value
caml_SDL_GL_SwapWindow(value window)
{
    SDL_GL_SwapWindow(SDL_Window_val(window));
    return Val_unit;
}

CAMLprim value
caml_SDL_GL_DeleteContext(value context)
{
    SDL_GL_DeleteContext(SDL_GLContext_val(context));
    return Val_unit;
}

/* vim: set ts=4 sw=4 et: */