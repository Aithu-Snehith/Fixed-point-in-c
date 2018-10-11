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
	double float_correl[20] = {0} , actual_correl[20] = {0};
	int fixed_a[10]={0} , fixed_b[10]={0} , fixed_correl[20] = {0}, bits=0, int_bits=0, deci_bits=0,temp=0;

	//inputs
	double actual_a[10] = { -8.31662009587695e-13, 0.634029328751641, -0.767445067471676, 1.21423064425930, -0.398089786809545, 0.577773754381422, 0.836673932101677, -0.308971047587158, 1.58778525229245, -0.182021563971272   };

	double actual_b[10] = { 0.256258710000824, -0.299311523023751,  1.18013824251201, -0.724526570403471, 0.963365491184473   , 0.0611683879836982,     -0.126424722362053,  1.08772832230303, -0.743741290000000,   1.08772832230147};

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
	for(int i = 0; i < 10; i++)
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

	for(int i = 0; i < 10 ; i++)
	{
		for(int j = 0; j <= i ; j++)
		{
				fixed_correl[i] = fixed_correl[i] + fixed_a[j] * fixed_b[j+9-i];
				actual_correl[i] = actual_correl[i] + actual_a[j] * actual_b[j+9-i];
		}
	}

	//correlation in fixed point
	for(int i = 1; i < 10 ; i++)
	{
		for(int j = 0; j < 10 ; j++)
		{
			if(0 <= j-i)
			{
				fixed_correl[i+9] = fixed_correl[i+9] + fixed_a[j] * fixed_b[j-i];
				actual_correl[i+9] = actual_correl[i+9] + actual_a[j] * actual_b[j-i];
			}	
		}
	}
	
	for(int i = 0; i < 20; i++)	float_correl[i] = (fixed_correl[i] / (double)(1 << deci_bits*2));


	printf("\nArray_index		fixed_correl 		float_correl 		actual_correl		error\n\n");
	for(int i = 0 ; i < 19 ; i++)
	{
		printf("correl[%2d]		%10d 		%f 		%f		%f\n",i, fixed_correl[i],float_correl[i],actual_correl[i],float_correl[i]-actual_correl[i]);
	}
	printf("\n");
}