# Harriet
## Keyboard

### Layout

- QWERTY
- Number row
	- Have numpad map to number row (?)
- Lowercase and uppercase
- Extended ASCII
	- Extra symbols (0x80-0xFE)
		- Extended language support is priority
			- Diacritic characters
				- Combining pseudo-character (0xFF) that activates subroutine from drivers that moves cursor back one space
					- Subroutine stored in keyboard bank
				- Low and high versions of diacritics for lowercase and uppercase letters
		- Boxes, lines, and borders for remaining characters

### Interrupts

- Interrupts signal that a change has happened in the mapping of which keys are pressed.
- It's up to the driver to determine the differences.

### Scancodes

- Control, alt, shift, backspace, enter, escape
- Arrow keys (Left, Right, Up, Down)
- Space
- `A` - `Z`
- `0` - `9`
- `-`, `=`
- `,`, `.`, `/`
- `;`, `'`, `\`
- `[`, `]`
