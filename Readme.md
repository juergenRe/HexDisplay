# Notes for HexDisplay Project

## Programming USERID memory 

When compiling for debugging, those values can be directly programmed via 
    Window --> Target Memory Views --> User ID memory.

When having compiled for production, those values will be automatically reset to 0xFF and cannot altered from the IDE. You need to use MPLAB IPE for this.

### First start
- Be sure to have the ICE connected and MPLAB X closed
- Select the right processor and click "Connect"

### Setting the USER ID value
- enter the advanced mode (Settings --> Advanced Mode)
- Open the Target Memory View and change the value
- Go back to "Operate"

### Programming the device
- select the hex file created by MPLAB X IDE. It located in the "dist" folder, take the production code.
- Click on "Program" to program it, then "Verify" to validate the device programming.

## input bits reordering

To have more flexibility in routing data lines, bit numbers on J2 can be programmed freely and selected from predefined sets.

Selection is done via User ID memory, Byte 0. If kept unprogrammed, a test program is running, skipping through all segments.

### Set 0 (Standard):

| Pin | Signal |
|-----|--------|
|  1  | Vdd    |
|  2  | GND    |
|  3  | db0    |
|  4  | db1    |
|  5  | db2    |
|  6  | db3    |
|  7  | db4    |
|  8  | db5    |
|  9  | db6    |
| 10  | db7    |

### Set 1:

| Pin | Signal |
|-----|--------|
|  1  | Vdd    |
|  2  | GND    |
|  3  | db6    |
|  4  | db7    |
|  5  | db4    |
|  6  | db5    |
|  7  | db2    |
|  8  | db3    |
|  9  | db0    |
| 10  | db1    |

## segment driving

### data bit to address which segment
0 - -
1 D DP
2 C G
4 B F
8 A E

### Encoding of each segment and resulting hex code for table
0 -- A B C D E F    0xcf
1 -- B C            0x06
2 -- A B D E G      0xad
3 -- A B C D G      0x2f
4 -- B C F G        0x66
5 -- A C D F G      0x6b
6 -- A C D E F G    0xeb
7 -- A B C          0x0e
8 -- A B C D E F G  0xef
9 -- A B C D F G    0x6f
A -- A B C E F G    0xee
B -- C D E F G      0xe3
C -- A D E F        0xc9
D -- B C D E G      0xa7
E -- A D E F G      0xe9
F -- A E F G        0xe8