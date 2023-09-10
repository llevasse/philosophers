/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:54:18 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 16:56:12 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_mem_err(void)
{
	write (2, MEM_ERR, MEM_ERR_L);
}

void	write_mut_err(void)
{
	write (2, MUT_ERR, MUT_ERR_L);
}
