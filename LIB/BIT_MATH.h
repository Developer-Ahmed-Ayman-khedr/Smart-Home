/*
 * BIT_MATH.h
 *
 *  Created on: May 16, 2024
 *      Author: Abdo
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

/**************
INCLUDES
***************/


/**************
Global Data TYPES AND STRUCTURES
***************/


/**************
GLOBAL CONSTANT MACROS
***************/


/**************
GLOBAL FUNCTIONS MACROS
***************/

#define SET_BIT(var,shift)  var=(var|(1<<shift))
#define TOOGLE_BIT(var,shift)  var=(var^(1<<shift))
#define CLEAR_BIT(var,shift)  var=(var&(~(1<<shift)))
#define GET_BIT(var,shift)  ((var>>shift)&1)

/**************
GLOBAL FUNCTIONS Prototypes
****************/
#endif /* LIB_BIT_MATH_H_*/
