#include "syscall.h"

void infinity() {
	int i = 0;
	for (; ;) Yield();
}

void self() {
	Kill(1);
}

int main()
{
	int ret;
	int id = Fork(infinity);
	Yield();
	ret = Kill(id);

	id = Fork(infinity);
	Yield();
	ret = Kill(id);

	id = Fork(infinity);
	Yield();
	ret = Kill(id);

	Fork(self);
	Yield();

	Kill(100);

	Exit(ret);
	return ret;
}
