# Memory
Lib to manage allocation and free of multi level array

## Usage

Be care in the header you can comment this line `#include "../freeOnExit/freeOnExit.h"` to change the free management.
If this line is commented, the exit flag has no effect. And to free memory you ne need to do it yourselt using `free()` of `freeMemory()`. 
If this this line in uncommented, you can set exit flag to automaticaly free memory on normal termination, or yourself by calling  `free()` of `freeMemory()`. 
If tyou used exit flag don't use free function, you'll provoced double free.

```C
#include "memory.h"

if ( initMemory ( ( void ** ) &ptr, false, sizeof ( short ), 3, 2, 3, 4 ) )
{
	// error during allocation
}
else if ( freeMemory ( &ptr, 3 ) )
{
	// error during free
}

if ( initMemory ( ( void ** ) &ptr, true, sizeof ( short ), 3, 2, 3, 4 ) )
{
	// error
}

```