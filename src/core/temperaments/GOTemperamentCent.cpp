/*
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
 * License GPL-2.0 or later
 * (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
 */

#include "GOTemperamentCent.h"

#include <math.h>

GOTemperamentCent::GOTemperamentCent(wxString name, wxString title,
                                     wxString group)
    : GOTemperament(name, title, group) {
  m_Tuning[0] = 0;
  m_Tuning[1] = 0;
  m_Tuning[2] = 0;
  m_Tuning[3] = 0;
  m_Tuning[4] = 0;
  m_Tuning[5] = 0;
  m_Tuning[6] = 0;
  m_Tuning[7] = 0;
  m_Tuning[8] = 0;
  m_Tuning[9] = 0;
  m_Tuning[10] = 0;
  m_Tuning[11] = 0;
}

GOTemperamentCent::GOTemperamentCent(wxString name, float i1, float i2,
                                     float i3, float i4, float i5, float i6,
                                     float i7, float i8, float i9, float i10,
                                     float i11, float i12)
    : GOTemperament(name) {
  m_Tuning[0] = i1;
  m_Tuning[1] = i2;
  m_Tuning[2] = i3;
  m_Tuning[3] = i4;
  m_Tuning[4] = i5;
  m_Tuning[5] = i6;
  m_Tuning[6] = i7;
  m_Tuning[7] = i8;
  m_Tuning[8] = i9;
  m_Tuning[9] = i10;
  m_Tuning[10] = i11;
  m_Tuning[11] = i12;
}

GOTemperamentCent::GOTemperamentCent(wxString name, wxString group, float i1,
                                     float i2, float i3, float i4, float i5,
                                     float i6, float i7, float i8, float i9,
                                     float i10, float i11, float i12)
    : GOTemperament(name, group) {
  m_Tuning[0] = i1;
  m_Tuning[1] = i2;
  m_Tuning[2] = i3;
  m_Tuning[3] = i4;
  m_Tuning[4] = i5;
  m_Tuning[5] = i6;
  m_Tuning[6] = i7;
  m_Tuning[7] = i8;
  m_Tuning[8] = i9;
  m_Tuning[9] = i10;
  m_Tuning[10] = i11;
  m_Tuning[11] = i12;
}

float GOTemperamentCent::GetOffset(bool ignorePitch, unsigned midi_number,
                                   unsigned wav_midi_number,
                                   float wav_pitch_fract, float harmonic_number,
                                   float pitch_correction,
                                   float default_tuning) const {
  double concert_pitch_correction = 0;

  if (!ignorePitch && wav_midi_number) {
    concert_pitch_correction = (100.0 * wav_midi_number - 100.0 * midi_number +
                                log(8.0 / harmonic_number) / log(2) * 1200) +
                               wav_pitch_fract;
  }
  return m_Tuning[midi_number % 12] - default_tuning -
         concert_pitch_correction + pitch_correction;
}
