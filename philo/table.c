/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:26:50 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/09 17:04:22 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_timestamp(t_philo *ph, size_t *time)
{
	gettimeofday(&ph->timer, NULL);
	*time = ((ph->timer.tv_sec - ph->table->rules.t_start.tv_sec) * 1000)
		+ ((ph->timer.tv_usec - ph->table->rules.t_start.tv_usec) / 1000);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)ph;
	time = 0;
	while (philo->state.eaten < philo->table->rules.times_to_eat)
	{
		printf("[%ldms] Philosopher #%d\n", time, philo->id);
		usleep(100000);
		philo->state.eaten++;
		update_timestamp(ph, &time);
	}
	philo_died(ph);
	return (NULL);
}
