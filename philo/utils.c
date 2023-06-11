/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:39:34 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/11 05:26:24 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_timestamp(t_philo *ph, size_t *time)
{
	gettimeofday(&ph->timer, NULL);
	*time = ((ph->timer.tv_sec - ph->table->rules.t_start.tv_sec) * 1000)
		+ ((ph->timer.tv_usec - ph->table->rules.t_start.tv_usec) / 1000);
}

void	msleep(t_philo *ph, size_t *time_output, int msec)
{
	int	begin;
	int	time;
	int	target;

	gettimeofday(&ph->timer, NULL);
	begin = ((ph->timer.tv_sec - ph->table->rules.t_start.tv_sec) * 1000)
		+ ((ph->timer.tv_usec - ph->table->rules.t_start.tv_usec) / 1000);
	time = begin;
	target = begin + msec;
	while (time < target)
	{
		usleep(20);
		gettimeofday(&ph->timer, NULL);
		time = ((ph->timer.tv_sec - ph->table->rules.t_start.tv_sec) * 1000)
			+ ((ph->timer.tv_usec - ph->table->rules.t_start.tv_usec) / 1000); 
	}
	*time_output = time;
}
