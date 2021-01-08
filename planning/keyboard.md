# Lovelace
## Keyboard

### Layout

- QWERTY
- Number row
 - Have numpad map to number row (?)
- Lowercase and uppercase
- Extended ASCII
 - Extra symbols (0x80-0xFF)
   - Typeable by holding down alt
     - OS will handle this
     - Not all characters will be typable due to limited keyboard keys


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
