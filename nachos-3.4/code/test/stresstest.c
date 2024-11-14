#include "syscall.h"

int global_cnt = 0;

void toss() {
	int i;

	for (i = 0;i < 30;i++) {
		Yield();
	}

	Exit(global_cnt);
}

int main()
{
	int i;

	Fork(toss);
	global_cnt++;

	Fork(toss);
	global_cnt++;

	Fork(toss);
	global_cnt++;

	for (i = 0;i < 30;i++) {
		Yield();
	}

	Exit(global_cnt);
}

