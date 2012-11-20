#ifndef timer_h__
#define timer_h__

#include <ctime>

class timer
{
public:
	timer(){ startTime = std::clock();}
	void restart() { startTime = std::clock();}
	double elapsed() const
	{
		return double( std::clock() - startTime) / CLOCKS_PER_SEC;
	}
private:
	std::clock_t startTime;

};




#endif // timer_h__
