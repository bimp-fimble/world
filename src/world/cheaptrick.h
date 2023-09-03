//-----------------------------------------------------------------------------
// Copyright 2012 Masanori Morise
// Author: mmorise [at] meiji.ac.jp (Masanori Morise)
// Last update: 2021/02/15
//-----------------------------------------------------------------------------
#ifndef WORLD_CHEAPTRICK_H_
#define WORLD_CHEAPTRICK_H_

#include "world/macrodefinitions.h"

WORLD_BEGIN_C_DECLS

//-----------------------------------------------------------------------------
// Struct for CheapTrick
//-----------------------------------------------------------------------------
typedef struct {
  double q1;
  double f0_floor;
  int fft_size;
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
//   option             : Struct to order the parameter for CheapTrick
//
// Output:
//   spectrogram        : Spectrogram estimated by CheapTrick.
//-----------------------------------------------------------------------------
void CheapTrick(const double *x, int x_length, int fs,
    const double *f0, int f0_length, double frame_period,
    const CheapTrickOption *option, double *const *spectrogram);

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
void InitializeCheapTrickOption(int fs, CheapTrickOption *option);

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
int GetFFTSizeForCheapTrick(int fs, const CheapTrickOption *option);

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
double GetF0FloorForCheapTrick(int fs, int fft_size);

WORLD_END_C_DECLS

#endif  // WORLD_CHEAPTRICK_H_
