/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:26:47 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/16 18:31:58 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(t_table *t, t_philo	*ph, void *(*routine)(void *))
{
	ph->table = t;
	ph->state.eaten = 0;
	ph->state.hunger = ph->table->rules.time_to_live;
	ph->state.agenda = _think;
	ph->state.holding = 0;
	ph->id = t->nbr_philo;
	if (pthread_create(&ph->thread, NULL, routine, ph))
	{
		philo_purge(ph);
		return (NULL);
	}
	gettimeofday(&t->rules.t_start, NULL);
	return (ph);
}

t_philo	*philo_spawn(t_table *t, void *(*routine)(void *))
{
	t_philo	*tmp;

	if (t->nbr_philo == 0)
	{
		t->nbr_philo = 1;
		t->philo = malloc(sizeof(t_philo));
		if (!t->philo)
			return (NULL);
		t->philo->left = t->philo;
		t->philo->right = t->philo;
		t->philo->id = 1;
		return (philo_init(t, t->philo, routine));
	}
	tmp = t->philo->left;
	(t->philo->left)->right = malloc(sizeof(t_philo));
	if (!(t->philo->left)->right)
		return (NULL);
	(t->philo->left)->right->right = t->philo;
	(t->philo->left)->right->left = tmp;
	t->philo->left = (t->philo->left)->right;
	t->nbr_philo++;
	t->philo->left->id = t->nbr_philo;
	return (philo_init(t, t->philo->left, routine));
}

void	philo_died(t_philo *ph)
{
	size_t	time;

	time = 0;
	update_timestamp(ph, &time);
	printf("%ld%8d died\n", time, ph->id);
	pthread_mutex_destroy(&ph->table->mutx);
}
