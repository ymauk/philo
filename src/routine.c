/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:11:00 by ymauk             #+#    #+#             */
/*   Updated: 2024/12/03 12:20:16 by ymauk            ###   ########.fr       */
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
	printf("%zu %d %s\n", get_current_time()
		- philo->data->start_time, philo->id_philo, status);
	pthread_mutex_unlock(&philo->data->print);
}

void	*start_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	//die ungeraden warten lasse eine milisekunde
	while (philo->has_eaten != philo->data->nbr_philo_eat && philo->data->check_dead != 1)
	{
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

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		if (all_eaten(data) == 1)
			break ;
		printf("arrived\n");
		while (data->nbr_of_philos > i)
		{
			pthread_mutex_lock(&data->philos[i].meal);
			if (get_current_time() - data->philos[i].last_meal
				> data->time_to_die)
			{
				print_message(data->philos, "died");
				data->check_dead = 1;
				pthread_mutex_unlock(&data->philos[i].meal);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal);
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}

int	all_eaten(t_data *data)
{
	int	i;

	i = 0;
	while (data->nbr_of_philos > i)
	{
		if (data->philos[i].has_eaten != data->nbr_philo_eat)
			return (0);
		i++;
	}
	printf("all eaten return 1\n");
	return (1);
}
