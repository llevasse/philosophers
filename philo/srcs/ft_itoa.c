/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:12:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/14 21:41:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_strcat(char *dst, const char *src);
char	*set_minus(char *s, int len);
void	*ft_memset(void *b, int c, size_t len);
int		get_long_len(long n);
void	fill_res(char *res, int len_int, long n);

char	*ft_itoa(int n)
{
	char	*res;
	int		len_int;
	int		is_neg;
	long	long_n;

	long_n = (long)n;
	is_neg = 0;
	if (long_n < 0)
	{
		is_neg = 1;
		long_n = long_n * -1;
	}
	len_int = get_long_len(long_n);
	res = malloc((len_int + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len_int] = '\0';
	fill_res(res, len_int, long_n);
	if (is_neg == 0)
		return (res);
	else
		return (set_minus(res, len_int));
}

void	fill_res(char *res, int len_int, long n)
{
	int	i;

	i = len_int - 1;
	while (i > 0 && n > 9)
	{
		res[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	res[0] = n + '0';
}

char	*set_minus(char *s, int len)
{
	char	*res;

	res = malloc(len * sizeof(char) + 2);
	if (!res)
		return (NULL);
	memset(res, 0, len + 2);
	res[0] = '-';
	ft_strcat(res, s);
	free(s);
	return (res);
}

int	get_long_len(long n)
{
	if (n < 10)
		return (1);
	return (1 + (get_long_len(n / 10)));
}

void	ft_strcat(char *dst, const char *src)
{
	while (*dst)
		dst++;
	while (*src)
	{
		*dst++ = *src;
		src++;
	}
	*dst = '\0';
}
