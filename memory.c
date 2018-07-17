////////////////////////////////////////////////////////////////////////////////
/// \copiright ox223252, 2017
///
/// This program is free software: you can redistribute it and/or modify it
///     under the terms of the GNU General Public License published by the Free
///     Software Foundation, either version 2 of the License, or (at your
///     option) any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
///     ANY WARRANTY; without even the implied of MERCHANTABILITY or FITNESS FOR
///     A PARTICULAR PURPOSE. See the GNU General Public License for more
///     details.
///
/// You should have received a copy of the GNU General Public License along with
///     this program. If not, see <http://www.gnu.org/licenses/>
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "memory.h"

static int initSubMem ( void ** const ptr, const bool exit, const uint32_t size, const uint32_t length )
{
	*ptr = malloc ( size * length );
	if ( !*ptr )
	{
		return ( __LINE__ );
	}
#if defined(MEM_WITH_FOE) && !defined(MEM_WITHOUT_FOE)
	else if ( exit &&
		setFreeOnExit ( *ptr ) )
	{
		free ( *ptr );
		*ptr = NULL;
		return ( __LINE__ );
	}
#endif
	return ( 0 );
}

int initMemory ( void ** const ptr, const bool exit, uint32_t size, const uint32_t depth, ... )
{
	uint32_t *tabSize = NULL;
	va_list list;
	uint32_t i = 0, j = 0; // loop counters
	uint32_t length = 1;
	void * tmp = NULL;
	void ** tmp2 = NULL;

	if ( !ptr ||
		*ptr ||
		!size ||
		!depth )
	{
		errno = EINVAL;
		return ( __LINE__ );
	}


	va_start ( list, depth );

#if defined(MEM_WITH_FOE) && !defined(MEM_WITHOUT_FOE)
	initFreeOnExit ( );
#endif
	
	// init tab of length for each dimention
	tabSize = malloc ( sizeof ( uint32_t ) * depth );
	if ( !tabSize )
	{
		va_end ( list );
		return ( __LINE__ );
	}

	// calc and store global size
	for ( i = 0; i < depth; i++ )
	{
		tabSize[ i ] = va_arg ( list, uint32_t );
		length *= tabSize[ i ];

		if ( !length )
		{
			free ( tabSize );
			va_end ( list );

			return ( __LINE__ );
		}
	}

	// allocate first pointer level
	if ( initSubMem ( ( void ** ) &tmp, exit, size, length ) )
	{
		free ( tabSize );
		va_end ( list );
		return ( __LINE__ );
	}

	// allocate second, third, and other pointer level
	for ( i = depth - 1; i > 0; i-- )
	{
		length /= tabSize[ i ];

		if ( initSubMem ( ( void ** ) &tmp2, exit, sizeof ( void * ), length ) )
		{
			free ( tabSize );
			va_end ( list );
			return ( __LINE__ );
		}

		for ( j = 0; j < length; j++)
		{
			tmp2[ j ] = &(( uint8_t * )tmp)[ tabSize[ i ] * j * size ];
		}

		// change the original size to sizeof of ptr
		// nex we will malloc pointer over pointers
		size = sizeof ( void * );

		tmp = tmp2;
	}

	*ptr = tmp;
	
	free ( tabSize );
	va_end ( list );

	return ( 0 );
}

int freeMemory ( void ** const ptr, const uint32_t depth )
{
	if ( !ptr ||
		!depth )
	{
		errno = EINVAL;
		return ( __LINE__ );
	}

	if ( depth > 1 )
	{
		freeMemory ( *ptr, depth - 1 );
	}

	free ( *ptr );
	*ptr = NULL;
	return ( 0 );
}

#ifdef TEST_MEM_INIT

int main ( void )
{
	short ***ptr = NULL;
	short *ptr2 = NULL;
	int i, j, k;

	initMemory ( ( void ** ) &ptr, true, sizeof ( short ), 3, 2, 3, 4 );
	initMemory ( ( void ** ) &ptr2, false, sizeof ( short ), 1, 4 );
	
	for ( i = 0; i < 2; i++ )
	{
		for ( j = 0; j < 3; j++ )
		{
			for ( k = 0; k < 4; k++ )
			{
				ptr[ i ][ j ][ k ] = i * 12 + j * 4 + k;
			}
		}
	}

	for ( i = 0; i < 2; i++ )
	{
		for ( j = 0; j < 3; j++ )
		{
			for ( k = 0; k < 4; k++ )
			{
				printf ( "%d %d %d : %d -- @ %p\n", i, j, k, ptr [ i ][ j ][ k ], &ptr [ i ][ j ][ k ] );
			}
		}
	}

	freeMemory ( ( void ** ) &ptr, 3 );
	freeMemory ( ( void ** ) &ptr2, 1 );

	return ( 0 );
}

#endif