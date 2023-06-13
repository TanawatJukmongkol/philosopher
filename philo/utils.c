/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:39:34 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/12 17:22:36 by tjukmong         ###   ########.fr       */
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

void	philo_join(t_table *t)
{
	t_philo	*head;
	t_philo	*tmp;

	head = t->philo;
	while (1)
	{
		tmp = t->philo->right;
		if (pthread_join(tmp->thread, NULL))
			return (philo_purge(t->philo));
		if (tmp == head)
			return ;
		t->philo = tmp;
	}
}

void	philo_detatch(t_philo *ph)
{
	t_philo	*head;
	t_philo	*tmp;

	head = ph;
	while (1)
	{
		tmp = ph->right;
		if (tmp == head)
		{
			pthread_detach(tmp->thread);
			return ;
		}
		pthread_detach(tmp->thread);
		ph = tmp;
	}
}

void	philo_purge(t_philo *ph)
{
	t_philo	*head;
	t_philo	*tmp;

	head = ph;
	while (1)
	{
		tmp = ph->right;
		if (tmp == head)
		{
			free(ph);
			return ;
		}
		pthread_mutex_destroy(&ph->mutx);
		free(ph);
		ph = tmp;
	}
}

void	philo_take_fork(t_philo *ph, long time)
{
	if (!ph->state.holding && !ph->left->state.holding)
	{
		printf("%ld%8d has taken a fork\n", time, ph->id);
		ph->state.holding = 1;
		ph->left->state.holding = 1;
		ph->state.agenda = _eat;
	}
}

void	philo_free_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutx);
	ph->state.holding = 0;
	ph->left->state.holding = 0;
	pthread_mutex_unlock(&ph->mutx);
}

