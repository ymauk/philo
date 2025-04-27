/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:11:00 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/27 16:30:46 by ymauk            ###   ########.fr       */
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
		data->philos[i].last_meal = get_current_time();
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

void	print_message(t_philos *philo, const char *status)
{
	pthread_mutex_lock(&philo->data->print);
	if (check_mutex_var(philo, 1) != 1)
		printf("%zu %d %s\n", get_current_time()
			- philo->data->start_time, philo->id_philo, status);
	pthread_mutex_unlock(&philo->data->print);
}

void	*start_routine(void *arg)
{
	t_philos	*philo;

	philo = arg;
	thinking((void *) philo);
	if (philo->data->nbr_of_philos == 1)
		one_philo((void *) philo);
	if (philo->id_philo % 2 != 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!check_mutex_var(philo, 2)
		&& check_mutex_var(philo, 1) != 1)
	{
		if (philo->has_eaten != 0)
			thinking((void *) philo);
		take_forks((void *) philo);
		eating((void *) philo);
		putdown_forks((void *) philo);
		go_sleep((void *) philo);
	}
	return (NULL);
}

void	*monitoring_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		if (all_eaten(data) == 1)
			break ;
		i = 0;
		while (data->nbr_of_philos > i)
		{
			pthread_mutex_lock(&data->philos[i].meal);
			if (get_current_time() - data->philos[i].last_meal
				> data->time_to_die)
			{
				checking_death(data, i);
				pthread_mutex_unlock(&data->philos[i].meal);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal);
			i++;
		}
	}
	return (NULL);
}
