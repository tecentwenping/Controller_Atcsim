#ifndef _UNCOPYABLE_H_
#define _UNCOPYABLE_H_

class WUncopyable
{
protected:
	WUncopyable() {}
	~WUncopyable() {}

private:
	WUncopyable(const WUncopyable&);
	WUncopyable& operator=(const WUncopyable&);
};

#endif