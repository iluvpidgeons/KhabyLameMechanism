# pragma once
# include <ESP_Music.h>

const int bpm = 147;

Note melody[] = {
  {NOTE_GS4,  N16},
  {NOTE_REST, N16},
  {NOTE_GS4,  N16},
  {NOTE_REST, N16},
  {NOTE_G4,   N16},
  {NOTE_REST, N16},
  {NOTE_G4,   N16},
  {NOTE_REST, N16},

  {NOTE_F4,   N16},
  {NOTE_REST, N16},
  {NOTE_F4,   N16},
  {NOTE_REST, N16},
  {NOTE_E4,   N16},
  {NOTE_REST, N16},
  {NOTE_E4,   N16},
  {NOTE_REST, N16},

  {NOTE_GS4,  N16},
  {NOTE_GS4,  N16},
  {NOTE_REST, N16},
  {NOTE_G4,   N16},
  {NOTE_G4,   N16},
  {NOTE_REST, N16},
  {NOTE_F4,   N16},
  {NOTE_F4,   N16},

  {NOTE_E4,   N8},
  {NOTE_REST, N8},
  {NOTE_E4,   N8},
  {NOTE_REST, N8},
};

const int melodyLength = sizeof(melody) / sizeof(Note);