/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:41 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/22 19:18:40 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(void *arg)
{
	t_philos	*philo;
	size_t		time;

	philo = (t_philos *)arg;
	time = get_current_time() - philo->data->start_time;
	printf("%zu Philosopher %d is thinking\n", time, philo->id_philo);
}

void	eating(void *arg)
{
	t_philos	*philo;
	size_t		time_r;
	size_t		time_l;

	time_r = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->forks[philo->id_philo - 1]);
	printf("%zu Philosopher %d has taken a fork\n", time_r, philo->id_philo);
	time_l = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->forks[philo->id_philo
		% philo->data->nbr_of_philos]);
	printf("%zu Philosopher %d has taken a fork\n", time_r, philo->id_philo);
}
