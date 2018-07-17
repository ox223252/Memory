#ifndef __MEMORY_H__
#define __MEMORY_H__
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
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
/// \file memory.h
/// \brief lib to init multiple array
/// \author ox223252
/// \date 2018-07
/// \copyright GPLv2
/// \version 0.1
/// \depend freeOnExit
////////////////////////////////////////////////////////////////////////////////

#ifndef MEM_WITH_FOE
#define MEM_WITHOUT_FOE
#endif

#if defined(MEM_WITH_FOE) && !defined(MEM_WITHOUT_FOE)
#include "../freeOnExit/freeOnExit.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// \fn int initMemory ( void ** const ptr, const bool exit, uint32_t size, 
///     const uint32_t depth, ... );
/// \param [ out ] ptr : out pointer address
/// \perma [ in ] exit : use or not freeOnExit
/// \perma [ in ] size : data type size ( sizeof ( type ) )
/// \param [ in ] depth : number of array depth level
/// \param [ in ] ... : level length ( only uint32_t / in )
/// \brief this funcion is used to allocate multi level array
/// \return if 0 the ok else see errno to more details
////////////////////////////////////////////////////////////////////////////////
int initMemory ( void ** const ptr, const bool exit, uint32_t size, 
	const uint32_t depth, ... );

////////////////////////////////////////////////////////////////////////////////
/// \fn int freeMemory ( void ** const ptr, const uint32_t depth );
/// \param [ in/out ] ptr : pointer address
/// \param [ in ] depth : number of array depth level
/// \breif this function is used to free memory allocated with initMemory()
///     without exit flag set or without freeOnExit lib.
////////////////////////////////////////////////////////////////////////////////
int freeMemory ( void ** const ptr, const uint32_t depth );

#endif