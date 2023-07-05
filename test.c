#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(b + i) = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*sol;

	sol = malloc(size * count);
	if (sol == NULL)
		return (NULL);
	ft_bzero(sol, size * count);
	return (sol);
}

char	*ft_strdup(const char *s1)
{
	void		*cp_s1;
	size_t		len;

	len = ft_strlen(s1);
	cp_s1 = ft_calloc(len + 1, sizeof(*s1));
	if (cp_s1 == NULL)
		return (NULL);
	ft_memcpy(cp_s1, s1, len);
	return (cp_s1);
}

//malloc de 1000, comme ca c'est plus simple pour ajouter ou enlever des elem dans la copy

char **unset_var(char *flags, char **env_copy, int i)
{
	int		t;
	char	*temp;

	if (!ft_strncmp(env_copy[i], flags, ft_strlen(flags)))
	{
		if (env_copy[i])
			free(env_copy[i]);
		t = i;
		if (env_copy[++i])
		{
			while (env_copy[i])
			{
				temp = ft_strdup(env_copy[i]);
				if (env_copy[i])
					free(env_copy[i]);
				env_copy[t] = ft_strdup(temp);
				if (temp)
					free(temp);
				t++;
				i++;
			}
		}
		return (env_copy);
	}
	return (NULL);
}

char **ft_unset(char *cmd, char **flags, char **env_copy)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	while (flags[i])
	{
		j = 0;
		while (env_copy[j])
		{
			if (!ft_strncmp(env_copy[j], flags[i], ft_strlen(flags[i])))
			{
				env_copy = unset_var(flags[i], env_copy, j);
				break ;
			}
			j++;
		}
	i++;
	}
	return (env_copy);
}

char	**env_copy(char **env)
{
	char	**env_copy1;
	int		i;

	i = 0;
	env_copy1 = ft_calloc(sizeof(char **), 1000);
	if (!env_copy1)
		return (NULL);
	while (env[i])
	{
		env_copy1[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_copy1);
}

int	ft_isalnum1(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	is_equal_sign(char *str)
{
	int	i;
	int	b;
	int	a;

	i = 1;
	b = 0;
	a = 0;
	if (str[0] == '=')
		return (0);
	if (!ft_strncmp(str, "_=", 2))
		return (0);
	while (str[i])
	{
		if (str[i] == '=' && ft_isalnum1(str[i - 1]) == 1)
			b = 1;
		if (str[i - 1] == '=' && (str[i] != '<' || str[i] != '>'
				|| str[i] != '|'))
			a = 1;
		i++;
	}
	if (a && b)
		return (1);
	return (0);
}

char **add_new_var(char *flags, char **env_copy)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (ft_strncmp(env_copy[i], "_=", 2))
		i++;
	temp = ft_strdup(env_copy[i]);
	free(env_copy[i]);
	env_copy[i] = ft_strdup(flags);
	i++;
	env_copy[i] = ft_strdup(temp);
	free(temp);
	return (env_copy);
}

char **ft_export(char *cmd, char **flags, char **env_copy)
{
	int	i;

	i = 0;
	if (!flags[0])
	{
		while (env_copy[i])
		{
			printf("declare -x %s\n", env_copy[i]);
			i++;
		}
	}
	else if (flags[0])
	{
		while (flags[i])
		{
			if (is_equal_sign(flags[i]) == 1)
			{
				env_copy = add_new_var(flags[i], env_copy);
			}
			i++;
		}
	}
	return (env_copy);
}

int	main(int ac, char **av, char **env)
{
	char	**env_copy1;
	int		i;

	i = 0;
	env_copy1 = env_copy(env);
	while (env_copy1[i])
	{
		printf("%s\n", env_copy1[i]);
		i++;
	}
	printf("\n---------------------------------------------------\n\n");
	env_copy1 = ft_export("export", av + 1, env_copy1);
	i = 0;
	while (env_copy1[i])
	{
		printf("%s\n", env_copy1[i]);
		i++;
	}
	printf("\n---------------------------------------------------\n\n");
	env_copy1 = ft_unset("unset", av + 1, env_copy1);
	i = 0;
	while (env_copy1[i])
	{
		printf("%s\n", env_copy1[i]);
		i++;
	}
	exit(0);
}
