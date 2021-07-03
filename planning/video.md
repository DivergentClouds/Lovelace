# Lovelace
## Video

- Bank offset + 1 specifies how many rows of character height
(starting from the top) are treated as graphics instead of text
	- 0 = Text Mode
	- 1
	- 2
	- 3
	- ...
	- 25 = Graphics Mode

### Text Mode

- Character tiles reside in non-memory mapped ROM
	- Starting at bottom of bank memory + 8
	- 8x8 characters with each row of pixels being a byte
	- Lasts for 0x37C0 (14272) bytes
- Ascii character codes + 128 custom characters
	- Codes 0x00 through 0x01F and code 0x7F are not displayed as they are
	control characters
- Text resides at the bottom of bank memory + 2
	- Text is specified in bytes in the order C F B
		- C = The character code of the current character
		- F = Foreground color of the current character
			- defined in form RRRGGGBB
		- B = Background color of the current character
			-  defined in form RRRGGGBB
- 40 Columns by 25 Rows
- Characters are offset horizontally by 3 effective pixels


### Graphics Modes

#### Graphics Mode
- 320x200 Resolution
- 4 pixels per byte, 1 per dibit
- Pixels go from left to right, top to bottom
- Each byte in Draw Palette is in the form RRRGGGBB
- Screen resides at the bottom of bank memory + 0x37D0
- Draw Palette resides at bank offset + 0x4390
- The Draw Palettes are 4 4-byte pallettes
- Palette Tiles reside at bank offset + 0xC00 and take up 0xBB8 (3000) bytes


- 4 colors from a given section of the Draw Palette are accessible
	- Sections are specified in 64 by 1 tiles
- Graphics buffer is 0xBB8 (3000) bytes long
