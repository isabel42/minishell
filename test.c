#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (i < n && s11[i] == s22[i]
		&& s11[i] != '\0' && s22[i] != '\0')
		i++;
	if (n == i)
		return (0);
	else
		return (s11[i] - s22[i]);
}

void	ft_echo(char *cmd, char **flags)
{
	int	i;

	if (!ft_strncmp(flags[0], "-n", 2) && ft_strlen(flags[0]) == 2)
	{
		i = 2; //enlever 1
		while (flags[i])
		{
			printf("%s", flags[i]);
			i++;
		}
	}
	else
	{
		i = 1; //enlever 1
		while (flags[i])
		{
			printf("%s", flags[i]);
			i++;
		}
		write(1, "\n", 1);
	}
}

int	main(void)
{
	char	*flags[3] = {"-n", "salut"};

	ft_echo("echo", flags);
	return (0);
}
