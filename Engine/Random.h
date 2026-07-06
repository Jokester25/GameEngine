#pragma once

#include <stdlib.h>

namespace nu 
{
	inline int RandomInt() {

		return rand();
	}
	//<summary>
	//Get Ramdom Int value [0, max)
	//</summary>
	//<param name  ="max"> Exclusive max value</param>
	//<returns> Exclusive max value example: RandomInt(10) will return values 0-9 </returns>
	inline int RandomInt(int max) {

		return rand() % max;
	}
	//<summary>
	// Get random int value [min, max]
	// </summary>
	// <param name ="min"> Inclusive min value</param>
	// <param name ="max"> Inclusive max value</param>
	// <returns> Inclusive max value example: RandomInt(10, 20) will return values 10-20 </returns>
	inline int RandomInt(int min, int max) {
		return min + RandomInt((max - min) + 1);
	}
	//<summary>
	// Get random float value [0, 1)
	//</summary>
	inline float RandomFloat() {
		// rand() = 0 <- RAND_MAX
		return rand() / (float)RAND_MAX;
	}

	//<summary>
	//Get random float value [0, max)
	//</summary>
	//<param name = "max"> Exclusive? max value</param>
	//<returns> Exclusive max value example: RandomFloat(10) will return values
	inline float RandomFloat(float max) {
		// 0 <--> 1 * max
		return RandomFloat() * max;
	}


	inline float RandomFloat(float min, float max) {
		// min + (0 <--> 1 ) * (max - min)

		return min + RandomFloat() * (max - min);
	}


}	