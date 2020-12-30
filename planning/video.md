# Harriet
## Video

### Graphics Modes

#### Shared
- Each byte in Draw Palette is in the form RRRGGGBB
- The screen is 0x1D4C (7500) bytes
 - Pixels go from left to right, top to bottom
   - If the byte is subdivided then the leftmost part comes first
- Screen resides at the bottom of bank memory
- Draw Palettes resides at bank offset + 0x1F30
- The 4 Draw Palettes are 4 bytes each
- Palette Tiles reside at bank offset + 0x1E00 and take up 300 bytes

#### Modes

- Hi-Color
 - 100 x 75 Resolution
 - Colors defined in form RRRGGGBB
 - 1 color per screen byte
- Hi-Res
 - 200 x 150 Resolution
 - 4 colors from a given section of the Draw Palette are accessible
  - Sections are specified in 5 by 5 tiles
 - 4 pixels per byte, 1 per dibit

### Text Modes

- Character tiles reside in video card ROM
 - Ascii character codes + 128 custom characters
 - Codes 0x00 through 0x01F and code 0x7F are not displayed as they are control characters
- Text resides at the bottom of bank memory
 - Text Buffer is 0x7D0 bytes long
- Colors for each character are determined by the corrosponding byte in the Color Buffer (I need a better name)
 - Color Buffer starts at bank offset + 0x800
 - Color Buffer is 0x7D0 bytes long
- The color buffer has bytes in the form AAAABBBB
 - AAAA is the foreground color picked from the Draw Palette (Picked as if all 4 palettes are 1 big palette)
 - BBBB is the background color picked from the Draw Palette (Picked as if all 4 palettes are 1 big palette)
- 80 Columns by 25 Rows
