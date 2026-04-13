# pragma once
# include <ESP_Music.h>

// Not Like Us - Kendrick Lamar (Main Riff)
const int bpm = 147; // Tempo for music playback (beats per minute)

Note melody[] = {
  // Bar 1: The "Mustard on the beat" bounce
  {NOTE_GS4,  N16},
  {NOTE_REST, N16},
  {NOTE_GS4,  N16},
  {NOTE_REST, N16},
  {NOTE_G4,   N16},
  {NOTE_REST, N16},
  {NOTE_G4,   N16},
  {NOTE_REST, N16},

  // Bar 2: The descending minor shift
  {NOTE_F4,   N16},
  {NOTE_REST, N16},
  {NOTE_F4,   N16},
  {NOTE_REST, N16},
  {NOTE_E4,   N16},
  {NOTE_REST, N16},
  {NOTE_E4,   N16},
  {NOTE_REST, N16},

  // Bar 3: The rapid rhythmic variation
  {NOTE_GS4,  N16},
  {NOTE_GS4,  N16},
  {NOTE_REST, N16},
  {NOTE_G4,   N16},
  {NOTE_G4,   N16},
  {NOTE_REST, N16},
  {NOTE_F4,   N16},
  {NOTE_F4,   N16},

  // Bar 4: Final resolution
  {NOTE_E4,   N8},
  {NOTE_REST, N8},
  {NOTE_E4,   N8},
  {NOTE_REST, N8},
};

const int melodyLength = sizeof(melody) / sizeof(Note);