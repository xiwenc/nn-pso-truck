#ifndef _MATH_CLASS_
#define _MATH_CLASS_

/**
 * Math class
 */
class Math {
	
	public:
	
		//---------
		//functions
		//---------
		float uniformRandom(void);
		float uniformRandom(float, float);
		void seed(void);
		void swap(float &, float &);
		float approxEuclidean(float, float);
		
};//Math class

#endif

