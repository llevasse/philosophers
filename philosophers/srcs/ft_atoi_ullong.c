/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ullong.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 06:58:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/30 10:33:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief Check if char is a space (commun separation between words).
/// @param c Char to check.
/// @return Return 1 if char is a space.
int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

/// @brief Parse *str as a unsigned long long.
/// @param *str *Str to pass as unsigned long long.
/// @return Return *str unsigned long long value if one is present in *str
/// , 0 if none.
unsigned long long	ft_atoi_ullong(const char *str)
{
	int					i;
	unsigned long long	res;

	i = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
		return (ft_atoi_ullong(str + i + 1));
	if (str[i] == '+')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		res = str[i] - '0';
	else
		return (0);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			res = res * 10 + str[i + 1] - '0';
		i++;
	}
	return (res);
}
