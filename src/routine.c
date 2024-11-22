/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:11:00 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/22 19:01:07 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_threads(t_data *data)
{
	t_philos	*cur_ph;
	int			i;

	cur_ph = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_create(&cur_ph->thread, NULL, start_routine, (void *)cur_ph);
		cur_ph = cur_ph->next;
		i++;
	}
}

void	join_threads(t_data *data)
{
	t_philos	*cur_ph;
	int			i;

	cur_ph = data->philos;
	i = 0;
	while (data->nbr_of_philos > i)
	{
		pthread_join(cur_ph->thread, NULL);
		cur_ph = cur_ph->next;
		i++;
	}
}

void	*start_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (!philo->data->check_dead
		&& philo->has_eaten != philo->data->nbr_philo_eat)
	{
		thinking((void *) philo);
		eating((void *) philo);
	}
	return (NULL);
}
