//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise
// Author: mmorise [at] meiji.ac.jp (Masanori Morise)
// Last update: 2021/02/15
//-----------------------------------------------------------------------------
#ifndef WORLD_CHEAPTRICK_H_
#define WORLD_CHEAPTRICK_H_

#include <stddef.h>
#include "world/macrodefinitions.h"

WORLD_BEGIN_C_DECLS

//-----------------------------------------------------------------------------
// Struct for CheapTrick
//-----------------------------------------------------------------------------
typedef struct {
  double q1;
  double f0_floor;
  unsigned int fft_size;
} CheapTrickOption;

//-----------------------------------------------------------------------------
// CheapTrick() calculates the spectrogram that consists of spectral envelopes
// estimated by CheapTrick.
//
// Input:
//   x                  : Input signal
//   x_length           : Length of x
//   fs                 : Sampling frequency
//   f0                 : F0 contour
//   f0_length          : Length of F0 contour
//   frame_period       : Temporal period used for the analysis
//   fft_size           : Size for FFT used by CheapTrick,
//   			  must be a power of 2 (e.g. 2048, 4096)
//
// Output:
//   spectrogram        : Spectrogram estimated by CheapTrick.
//-----------------------------------------------------------------------------
void CheapTrick(const double *x, size_t x_length, unsigned int fs,
    const double *f0, size_t f0_length, double frame_period,
    unsigned int fft_size, double *const *spectrogram);

//-----------------------------------------------------------------------------
// InitializeCheapTrickOption allocates the memory to the struct and sets the
// default parameters.
//
// Input:
//   fs : Sampling frequency
//
// Output:
//   option   : Struct for the optional parameter
//-----------------------------------------------------------------------------
void InitializeCheapTrickOption(unsigned int fs, CheapTrickOption *option);

//-----------------------------------------------------------------------------
// GetFFTSizeForCheapTrick() calculates the FFT size based on the sampling
// frequency and the lower limit of f0 (kFloorF0 defined in constantnumbers.h).
//
// Input:
//   fs : Sampling frequency
//   option : Option struct containing the lower f0 limit
//
// Output:
//   FFT size
//-----------------------------------------------------------------------------
unsigned int GetFFTSizeForCheapTrick(unsigned int fs, const CheapTrickOption *option);

//-----------------------------------------------------------------------------
// GetF0FloorForCheapTrick() calculates actual lower f0 limit for CheapTrick
// based on the sampling frequency and FFT size used. Whenever f0 is below
// this threshold the spectrum will be analyzed as if the frame is unvoiced
// (using kDefaultF0 defined in constantnumbers.h).
//
// Input:
//   fs : Sampling frequency
//   fft_size : FFT size
//
// Output:
//   Lower f0 limit (Hz)
//-----------------------------------------------------------------------------
double GetF0FloorForCheapTrick(unsigned int fs, unsigned int fft_size);

WORLD_END_C_DECLS

#endif  // WORLD_CHEAPTRICK_H_
