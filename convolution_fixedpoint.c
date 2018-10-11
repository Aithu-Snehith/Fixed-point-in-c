#include <stdio.h>
#include <stdlib.h>

int bits_required(int x)
{
	int count = 0;
	while(x/2 != 0)
	{
		count++;
		x = x/2;
	}
	return count + 1;
}

int rounded(float x)
{
	if(x > 0)
	{
		if(x - (int)x < 0.5)	return (int)x;
		else	return (int)x + 1;
	}
	else
	{
		if(x - (int)x > 0.5)	return (int)x;
		else	return (int)x - 1;
	}
	
}

int main()
{
	int i;
	double float_conv[25] = {0} , actual_conv[25] = {0};
	int fixed_a[16]={878} , fixed_b[16]={0} , fixed_conv[25] = {0}, bits=0, int_bits=0, deci_bits=0,temp=0;

	//inputs
	double actual_a[16] = { 0.256258710002038,	0.963365491187825,	-0.743741290000000	,0.963365491190122,	0.256258709998790,	-0.450848071183266,	1.25625871000000,	-0.450848071189536	,0.256258710000382,	0.963365491183852,	-0.743741290000000,	0.963365491188951,	0.256258710000446,	-0.450848071184437,	1.25625871000000,	-0.450848071188365};

	double actual_b[10] = { 0.256258710000824,	-0.299311523023751,	1.18013824251201,	-0.724526570403471,	0.963365491184473,	0.0611683879836982,	-0.126424722362053,	1.08772832230303,	-0.743741290000000,	1.08772832230147};

	bits = 16;

	//finding the bits reqired
	temp = actual_a[0];
	for(int i = 1; i < 16;i++)	if(abs(actual_a[i])>temp)	temp = abs(actual_a[i]);
	if(abs(actual_b[0])>abs(temp))	temp = abs(actual_b[0]);
	for(int i = 1; i < 10;i++)	if(abs(actual_b[i])>temp)	temp = abs(actual_b[i]);

	int_bits = bits_required(temp) + 1;
	printf("bits allocated for integer: %d\n",int_bits);
	deci_bits = bits - int_bits;
	printf("bits allocated for decimal: %d\n",deci_bits);

	//converting to fixed point
	for(int i = 0; i < 16; i++)
	{
		fixed_a[i] = rounded(actual_a[i] * (1 << deci_bits));
		// printf("%d 	",fixed_a[i]);
	}
	// printf("\n");
	for(int i = 0; i < 10; i++)
	{
		fixed_b[i] = rounded(actual_b[i] * (1 << deci_bits));
		// printf("%d 	",fixed_b[i]);
	}

	//convolving in fixed point
	for(int i = 0; i < 25 ; i++)
	{
		for(int j = 0; j <= i ; j++)
		{
			if(j<16 && i-j<10)
			{
				fixed_conv[i] = fixed_conv[i] + fixed_a[j] * fixed_b[i-j];
				actual_conv[i] = actual_conv[i] + actual_a[j] * actual_b[i-j];
			}	
		}
	}
	
	for(int i = 0; i < 25; i++)	float_conv[i] = (fixed_conv[i] / (double)(1 << deci_bits*2));


	printf("\nArray_index		fixed_conv 		float_conv 		actual_conv		error\n\n");
	for(int i = 0 ; i < 25 ; i++)
	{
		printf("conv[%2d]		%d 		%f 		%f		%f\n",i, fixed_conv[i],float_conv[i],actual_conv[i],float_conv[i]-actual_conv[i]);
	}
	printf("\n");
}