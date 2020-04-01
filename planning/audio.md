# Audio

# Harriet

- 3 oscillators
 - 2 filters
   - Highpass
     - `cccccccc`
     - 256 cutoffs
   - Lowpass
     - `cccccccc`
     - 256 cutoffs
 - ADSR
   - `aaaaaaaa dddddddd`
   - `ssssssss rrrrrrrr`
   - 256 different length options for each
 - Waveform
   - `000000aa` `bbbbbbbb`
   - a is waveform selection, 4 waveforms
   - b is pulse width
 - Note/pitch
   - `0nnnnnnn`
   - 128 notes; note 0 is 0hz, notes 1 - 127 are a0 - c8
   - `bbbbbbbb`
   - 256 pitch bend levels
 - Phase
   - `pppppppp`
   - 256 phases
 - Volume
   - `vvvvvvvv`
   - 256 volume levels
