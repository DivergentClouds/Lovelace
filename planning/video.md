# Harriet
## Video

### Graphics Modes

#### Shared
- Each byte in Draw Palette is in the form RRRGGGBB
 - 0 for the first color in the Total Palette, 255 for the final one
- The screen is 0x3A98 bytes
 - Pixels go from right to left, top to bottom
   - If the pixel is subdivided then the leftmost part comes first
- Total Palette resides at the bottom of bank memory
 - Do not edit Total Palette
- Draw Palette directly above Total Palette
 - Draw Palette is 16 bytes
- Screen Memory Resides at the top of memory
- This leaves 0x458 (1112) bytes free

#### Modes

- Hi-Color
 - 100 x 75 Resolution
 - Colors come from Total Palette
 - 1 color per screen byte
- Mid-Color
 - 200 x 150 Resolution
 - Full Draw Palette is accessible
 - 2 colors per screen byte, 1 per nybble
- Hi-Res
 - 400 x 300 Resolution
 - First 4 colors in Draw Palette are accessible
 - 4 colors per screen byte, 1 per dibit

### Text Modes
