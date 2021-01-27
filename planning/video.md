# Lovelace
## Video

### Graphics Modes

#### Shared
- Each byte in Draw Palette is in the form RRRGGGBB
- Pixels go from left to right, top to bottom
	- If the byte is subdivided then the leftmost part comes first
- Screen resides at the bottom of bank memory
- Draw Palette resides at bank offset + 0x1800
- The Draw Palettes are 4 4-byte pallettes
- Palette Tiles reside at bank offset + 0xC00 and take up 0xBB8 (3000) bytes

#### Graphics Mode

- 400 x 300 Resolution
- 4 colors from a given section of the Draw Palette are accessible
	- Sections are specified in 10 by 1 tiles
- 4 pixels per byte, 1 per dibit
- Graphics buffer is 0xBB8 (3000) bytes long

### Text Mode

- Character tiles reside in video card ROM
	- Ascii character codes + 128 custom characters
	- Codes 0x00 through 0x01F and code 0x7F are not displayed as they are control characters
- Text resides at the bottom of bank memory
	- Text Buffer is 0x3E8 (1000) bytes long
- Colors for each character are determined by the corrosponding byte in the Color Buffer (I need a better name)
	- Color Buffer starts at bank offset + 0x800
	- Color Buffer is 0x7D0 (2000) bytes long
- The color buffer has bytes in the form AAAAAAAA BBBBBBBB
	- AAAAAAAA is the foreground color defined in form RRRGGGBB
	- BBBBBBBB is the background color defined in form RRRGGGBB
- 40 Columns by 25 Rows
- 300 x 225 Effective resolution
- Characters are offset horizontally by 3 effective pixels
