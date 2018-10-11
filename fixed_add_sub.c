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
	float actual_a , actual_b , float_added , actual_added, float_sub,actual_sub;
	int fixed_a , fixed_b , operation, bits, int_bits, deci_bits , fixed_added,fixed_sub , temp;

	printf("Enter two floating point numbers\n");
	printf("a = ");
	scanf("%f",&actual_a);
	printf("b = ");
	scanf("%f",&actual_b);
	printf("no of bits(from 0 to 31 excluding sign bit): ");
	scanf("%d",&bits);

	if(abs(actual_a)>abs(actual_b))
	{
		temp = abs(actual_a);
	}
	else
	{
		temp = abs(actual_b);
	}

	int_bits = bits_required(temp) + 1;
	printf("bits allocated for integer: %d\n",int_bits);
	deci_bits = bits - int_bits;
	printf("bits allocated for decimal: %d\n",deci_bits);

	if(deci_bits > 0)
	{
		fixed_a = rounded(actual_a * (1 << deci_bits));
		printf("fixed_a: %d\n",fixed_a);
		fixed_b = rounded(actual_b * (1 << deci_bits));
		printf("fixed_b: %d\n\n", fixed_b);

		
		fixed_added = fixed_a + fixed_b;
		printf("Addition\nfixed_added: %d\n",fixed_added);
		float_added = (fixed_added / (float)(1 << deci_bits));
		printf("float_added: %f\n",float_added);
		actual_added = actual_a + actual_b;
		printf("actual_added: %f\n",actual_added);
		printf("error: %.8f\n\n",actual_added - float_added);

		fixed_sub = fixed_a - fixed_b;
		printf("subtracion\nfixed_subtracted: %d\n",fixed_sub);
		float_sub = (fixed_sub / (float)(1 << deci_bits));
		printf("float_subtracted: %f\n",float_sub);
		actual_sub = actual_a - actual_b;
		printf("actual_subtracted: %f\n",actual_sub);
		printf("error: %.8f\n",actual_sub - float_sub);
	}
	else	printf("cannot be computed\n");
}