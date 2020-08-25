# Harriet
## Video

### Graphics Modes

#### Shared
- Each byte in Draw Palette is in the form RRRGGGBB
- The screen is 0x3A98 bytes
 - Pixels go from right to left, top to bottom
   - If the pixel is subdivided then the leftmost part comes first
- Screen resides at the bottom of bank memory
- Draw Palette resides at bank offset + 0x3AA0
- Draw Palette is 16 bytes

#### Modes

- Hi-Color
 - 100 x 75 Resolution
 - Colors defined in form RRRGGGBB
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

- Character tiles reside at bank offset to bank offset + 0x4000
 - Ascii character codes + 128 custom characters
 - Codes 0x00 through 0x01F and code 0x7F are not displayed as they are control characters
- Text resides at 0xF730 through 0xFF00
- Foreground colors reside at 0xEF5F through 0xF72F
- Background colors reside at 0xE78E through 0xEF5E
- 80 Column
