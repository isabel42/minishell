#include <stdio.h>
#include <stdlib.h>

char	*all_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
		i++;
	}
	return (str);
}

int	main(int ac, char **av)
{
	printf("%s\n", all_lower(av[1]));
	return (0);
}
