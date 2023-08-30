/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:49:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/30 22:18:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_args_valid(int argc, char **argv)
{	
	if (argc < 5)
		return ((void)write(2, TOO_SMALL, TOO_SMALL_L), 0);
	if (argc > 6)
		return ((void)write(2, TOO_MANY, TOO_MANY_L), 0);
	if (argv[1] && !is_only_digit(argv[1]))
		return ((void)write(2, BAD_NB_PHILO, BAD_NB_PHILO_L), 0);
	if (argv[2] && !is_only_digit(argv[2]))
		return ((void)write(2, BAD_TIME_DIE, BAD_TIME_DIE_L), 0);
	if (argv[3] && !is_only_digit(argv[3]))
		return ((void)write(2, BAD_TIME_EAT, BAD_TIME_EAT_L), 0);
	if (argv[4] && !is_only_digit(argv[4]))
		return ((void)write(2, BAD_TIME_SLEEP, BAD_TIME_SLEEP_L), 0);
	if (argv[5] && !is_only_digit(argv[5]))
		return ((void)write(2, BAD_NB_EAT, BAD_NB_EAT_L), 0);
	return (1);
}

int	is_only_digit(char	*s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	if (!s[i])
		return (1);
	return (0);
}
