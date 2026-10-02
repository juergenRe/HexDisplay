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