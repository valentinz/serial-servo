serial-servo
============

## Serial commands

| Command		| Result		| Description								|
| --------------------- | --------------------- | --------------------------------------------------------------------- |
| 01[NUM][POS][CS]00	| [POS][CS]00		| Write [POS] 200 = C8 oder 100 = 64 to servo [NUM] 1 = pin PC0.	|
| e.g. 0101c83600	| e.g. c83800		|									|
| e.g. 0101649a00	| e.g. 649c00		|									|
| 02[NUM][CS]00		| [POS][CS]00		| Read servo position [POS] from servo [NUM] 1 = Pin PC0.		|
| e.g. 0201fd00		| e.g. c83800		|									|

