/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:31:34 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/27 20:00:56 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	checking_death(t_data *data, int i)
{
	print_message(&data->philos[i], "died");
	pthread_mutex_lock(&data->check_dead_m);
	data->check_dead = 1;
	pthread_mutex_unlock(&data->check_dead_m);
}

int	check_value_size(char *str)
{
	const char	*max_pos;
	const char	*max_neg;
	size_t		len;

	max_pos = "2147483647";
	max_neg = "-2147483648";
	len = ft_strlen(str);
	if (*str == '-')
	{
		if (len > ft_strlen(max_neg))
			return (1);
		if (len == ft_strlen(max_neg) && ft_strcmp(str, max_neg) > 0)
			return (1);
	}
	else
	{
		if (len > ft_strlen(max_pos))
			return (1);
		if (len == ft_strlen(max_pos) && ft_strcmp(str, max_pos) > 0)
			return (1);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *value)
{
	size_t	counter;

	counter = 0;
	while (*value != '\0')
	{
		counter += 1;
		value += 1;
	}
	return (counter);
}

void	clean_up(t_data *data)
{
	int			i;
	int			nbr_philos;

	i = 0;
	if (data->philos)
	{
		nbr_philos = data->nbr_of_philos;
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->check_dead_m);
		pthread_mutex_destroy(&data->snacks_m);
		pthread_mutex_destroy(&data->nbr_p_m);
		while (nbr_philos > i)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philos[i].meal);
			i++;
		}
		free(data->philos);
		free(data->forks);
	}
}
