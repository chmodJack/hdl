#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>

extern "C" void dpic_init(uint8_t* in, uint8_t* out)
{
	printf("%s, in: %08x, out: %08x\n",__func__,in[0],out[0]);

	in[0]=0x11;
	out[0]=0x22;
}

extern "C" void dpic_tick(uint8_t* in, uint8_t* out)
{
	static uint32_t cnt = 0;
	cnt++;
	if((cnt % 1000000) == 0)
	{
		printf("%s, in: %08x, out: %08x\n",__func__,in[0],in[1]);
	}
}
