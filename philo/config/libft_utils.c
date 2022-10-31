/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/19 18:38:21 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

int	ft_atoi(const char *str)
{
	int				neg;
	long long int	res;

	res = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	if (res < 0)
		return (0);
	return (res * neg);
}

static int	bytes_to_allocate(int n)
{
	int	bytes;

	bytes = 0;
	if (n <= 0)
		bytes++;
	while (n)
	{
		n /= 10;
		bytes++;
	}
	bytes++;
	return (bytes);
}

static char	*cast_int_to_char(int bytes_fill, long num_to_convert, char *dest)
{
	int	check;

	check = 1;
	bytes_fill--;
	dest[bytes_fill] = '\0';
	bytes_fill--;
	if (num_to_convert < 0)
	{
		check = -1;
		dest[0] = '-';
		num_to_convert *= -1;
	}
	while (bytes_fill > 0)
	{
		dest[bytes_fill] = num_to_convert % 10 + '0';
		num_to_convert = num_to_convert / 10;
		bytes_fill--;
	}
	if (check > 0)
		dest[bytes_fill] = num_to_convert % 10 + '0';
	return (dest);
}

char	*ft_itoa(int n)
{
	int		bytes;
	int		test;
	char	*res;

	test = n;
	bytes = bytes_to_allocate(test);
	res = malloc(sizeof(char) * bytes);
	if (!res)
		return (NULL);
	res = cast_int_to_char(bytes, test, res);
	return (res);
}
