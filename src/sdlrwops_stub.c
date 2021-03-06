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
 
#include <SDL_rwops.h>
#include "sdlrwops_stub.h"

CAMLprim value
caml_SDL_RWFromMem(value str)
{
    SDL_RWops * rwo =
        SDL_RWFromMem(
                String_val(str),
                caml_string_length(str));
    return Val_SDL_RWops(rwo);
}

CAMLprim value
caml_SDL_RWFromFile(value file, value mode)
{
    SDL_RWops * rwo =
        SDL_RWFromFile(
                String_val(file),
                String_val(mode));
    if (rwo == NULL) caml_failwith("Sdlrwops.from_file");
    return Val_SDL_RWops(rwo);
}

CAMLprim value
caml_SDL_AllocRW(value unit)
{
    SDL_RWops * rwo = SDL_AllocRW();
    return Val_SDL_RWops(rwo);
}

CAMLprim value
caml_SDL_FreeRW(value rwo)
{
    SDL_FreeRW(SDL_RWops_val(rwo));
    return Val_unit;
}

#define Uint8_val(d) (Int_val(d))
#define Val_Uint8(d) (Val_int(d))

#define Uint16_val(d) (Int_val(d))
#define Val_Uint16(d) (Val_int(d))

#define Uint32_val(d) (Int32_val(d))
#define Val_Uint32(d) (caml_copy_int32(d))

#define Uint64_val(d) (Int64_val(d))
#define Val_Uint64(d) (caml_copy_int64(d))


#define read_int_stub(IntT, SDL_ReadT) \
  CAMLprim value \
  caml_##SDL_ReadT(value rwo) { \
      IntT d = SDL_ReadT(SDL_RWops_val(rwo)); \
      return Val_##IntT(d); \
  }

read_int_stub(Uint8, SDL_ReadU8)

read_int_stub(Uint16, SDL_ReadLE16)
read_int_stub(Uint16, SDL_ReadBE16)
read_int_stub(Uint32, SDL_ReadLE32)
read_int_stub(Uint32, SDL_ReadBE32)
read_int_stub(Uint64, SDL_ReadLE64)
read_int_stub(Uint64, SDL_ReadBE64)

#define Val_size_t  Val_int

#if 0
CAMLprim value
caml_SDL_WriteU8(value rwo, Uint8 d)
{
    return Val_size_t(
        SDL_WriteU8(SDL_RWops_val(rwo), Uint8_val(d)));
}
#endif

#define write_int_stub(IntT, SDL_WriteT) \
  CAMLprim value \
  caml_##SDL_WriteT(value rwo, value d) { \
      return Val_size_t( \
          SDL_WriteT(SDL_RWops_val(rwo), IntT##_val(d))); \
  }

write_int_stub(Uint8, SDL_WriteU8)

write_int_stub(Uint16, SDL_WriteLE16)
write_int_stub(Uint16, SDL_WriteBE16)
write_int_stub(Uint32, SDL_WriteLE32)
write_int_stub(Uint32, SDL_WriteBE32)
write_int_stub(Uint64, SDL_WriteLE64)
write_int_stub(Uint64, SDL_WriteBE64)

/* vim: set ts=4 sw=4 et: */
