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

#include <SDL_audio.h>

CAMLprim value
caml_SDL_GetAudioDrivers(value unit)
{
    CAMLparam0();
    CAMLlocal1(ret);
    int i, num;
    num = SDL_GetNumAudioDrivers();
    ret = caml_alloc(num, 0);
    for (i = 0; i < num; i++) {
        const char *driver = SDL_GetAudioDriver(i);
        Store_field(ret, i, caml_copy_string(driver));
    }
    CAMLreturn(ret);
}

CAMLprim value
caml_SDL_AudioInit(value driver_name)
{
    int r = SDL_AudioInit(String_val(driver_name));
    if (r) caml_failwith("Sdlaudio.init");
    return Val_unit;
}

CAMLprim value
caml_SDL_AudioQuit(value unit)
{
    SDL_AudioQuit();
    return Val_unit;
}

CAMLprim value
caml_SDL_GetCurrentAudioDriver(value unit)
{
    const char * dr = SDL_GetCurrentAudioDriver();
    return caml_copy_string(dr);
}

static inline SDL_AudioStatus
SDL_AudioStatus_val(value v)
{
    switch (Int_val(v))
    {
        case 0: return SDL_AUDIO_STOPPED;
        case 1: return SDL_AUDIO_PLAYING;
        case 2: return SDL_AUDIO_PAUSED;
        default: caml_failwith("Sdlaudio.status");
    }
    caml_failwith("Sdlaudio.status");
}

static inline value
Val_SDL_AudioStatus(SDL_AudioStatus st)
{
    switch (st)
    {
        case SDL_AUDIO_STOPPED: return Val_int(0);
        case SDL_AUDIO_PLAYING: return Val_int(1);
        case SDL_AUDIO_PAUSED:  return Val_int(2);
        default: caml_failwith("Sdlaudio.status");
    }
    caml_failwith("Sdlaudio.status");
}

CAMLprim value
caml_SDL_GetAudioStatus(value unit)
{
    SDL_AudioStatus st = SDL_GetAudioStatus();
    return Val_SDL_AudioStatus(st);
}

CAMLprim value
caml_SDL_PauseAudio(value pause_on)
{
    SDL_PauseAudio(Int_val(pause_on));
    return Val_unit;
}

#if 0
int
SDL_OpenAudio(
            SDL_AudioSpec * desired,
            SDL_AudioSpec * obtained);
typedef Uint32 SDL_AudioDeviceID;
int SDL_GetNumAudioDevices(int iscapture);
const char *
SDL_GetAudioDeviceName(
            int index,
            int iscapture);

SDL_AudioDeviceID
SDL_OpenAudioDevice(
            const char *device,
            int iscapture,
            const SDL_AudioSpec * desired,
            SDL_AudioSpec * obtained,
            int allowed_changes);

SDL_AudioStatus
SDL_GetAudioDeviceStatus(SDL_AudioDeviceID dev);
void SDL_PauseAudioDevice(
            SDL_AudioDeviceID dev,
            int pause_on);
SDL_AudioSpec *
SDL_LoadWAV_RW(
            SDL_RWops * src,
            int freesrc,
            SDL_AudioSpec * spec,
            Uint8 ** audio_buf,
            Uint32 * audio_len);

#define SDL_LoadWAV(file, spec, audio_buf, audio_len) \
	SDL_LoadWAV_RW(SDL_RWFromFile(file, "rb"),1, spec,audio_buf,audio_len)

void SDL_FreeWAV(Uint8 * audio_buf);

int
SDL_BuildAudioCVT(
            SDL_AudioCVT * cvt,
            SDL_AudioFormat src_format,
            Uint8 src_channels,
            int src_rate,
            SDL_AudioFormat dst_format,
            Uint8 dst_channels,
            int dst_rate);

int SDL_ConvertAudio(SDL_AudioCVT * cvt);

#define SDL_MIX_MAXVOLUME 128
void
SDL_MixAudio(
            Uint8 * dst, const Uint8 * src,
            Uint32 len, int volume);

void
SDL_MixAudioFormat(
            Uint8 * dst,
            const Uint8 * src,
            SDL_AudioFormat format,
            Uint32 len, int volume);

void SDL_LockAudio();
void SDL_LockAudioDevice(SDL_AudioDeviceID dev);
void SDL_UnlockAudio();
void SDL_UnlockAudioDevice(SDL_AudioDeviceID dev);
void SDL_CloseAudio();
void SDL_CloseAudioDevice(SDL_AudioDeviceID dev);
int SDL_AudioDeviceConnected(SDL_AudioDeviceID dev);

#endif

/* vim: set ts=4 sw=4 et: */

