/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:49:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/30 10:57:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_args_valid(int argc, char **argv)
{	
	if (argc < 5)
		return ((void)write(2, TOO_SMALL, TOO_SMALL_L), 0);
	if (argc > 6)
		return ((void)write(2, TOO_MANY, TOO_MANY_L), 0);
	(void)argv;
	return (1);
}
