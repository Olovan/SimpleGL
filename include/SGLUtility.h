#ifndef SGLUTILITY_H_INCLUDED
#define SGLUTILITY_H_INCLUDED

static float radsToDegrees = 180/3.1415;
static float degreesToRads = 3.1415/180;

template <class T>
static const T& range(const T& a, const T& min, const T& max)
{
	if(a > max)
		return max;
	if(a < min)
		return min;
	return a;
	
}


#endif // SGLUTILITY_H_INCLUDED
