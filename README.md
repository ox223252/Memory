
# Memory
Lib to manage allocation and free of multi level array

## Usage

You can use freeOnExit lib to freememory, to dot this you should define `MEM_WITH_FOE`, if you refuse to use freeOnExit lib don't define `MEM_WITH_FOE` or define `MEM_WITHOUT_FOE`.

If `MEM_WITH_FOE` is not defined or `MEM_WITHOUT_FOE` is deifned, the exit flag has no effect, to free memory you ne need to do it yourselt using `free()` or `freeMemory()`.

If `MEM_WITH_FOE` is defined and `MEM_WITHOUT_FOE` is not deifned, you can set exit flag to automaticaly free memory on normal termination, or yourself by calling  `free()` or `freeMemory()`.

If you set exit flag don't use free function, you're going to provoke double free.

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

Note : you can't use freeOnExit function to free memory set in dll, you should free it manually.