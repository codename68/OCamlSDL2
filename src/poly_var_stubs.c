/* Copyright (C) 2013 Florent Monnier
 
 This software is provided "AS-IS", without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from
 the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely.
*/
#include <caml/mlvalues.h>

CAMLprim value
my_caml_hash_variant(value s)
{
    return Val_long(
        caml_hash_variant(String_val(s)));
}