/*
 * BIT_MATH.h
 *
 * Created: 5/6/2024 7:27:48 PM
 *  Author: Abdo
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

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
***************/

#endif /* BIT_MATH_H_ */