/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:04:45 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/02 15:07:07 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_finish(t_philo **philo)
{
	int			i;

	i = 0;
	while (i != -1)
	{
		i = 0;
		while (i < (*philo)->info.philo_num)
		{
			if (check_die(philo, &i))
				break ;
			if (check_enough_eat(philo, &i))
				break ;
			i++;
		}
	}
}

void	thread_init(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo->info.philo_num)
	{
		if (pthread_create(&philo[i].thread, 0, thread_ing, \
			(void *)&philo[i]) != 0)
		{
			while (j < i)
				pthread_join(philo[j++].thread, 0);
			return ;
		}
		i++;
	}
	check_finish(&philo);
	i = 0;
	while (i < philo->info.philo_num)
		pthread_join(philo[i++].thread, 0);
}

void	*thread_ing(void *data)
{
	t_philo	*philo;
	int		flag;

	flag = 0;
	philo = data;
	while (!flag)
	{
		if (philo->num % 2 == 0)
			even_fork(philo, philo->data);
		else
			odd_fork(philo, philo->data);
		if (philo->count_eat >= philo->info.must_eat \
			&& philo->finish_eat != 1 && philo->info.must_eat > 0)
		{
			pthread_mutex_lock(&(philo->data->flag));
			philo->data->end_eat -= 1;
			pthread_mutex_unlock(&(philo->data->flag));
			break ;
		}
		sleep_think(philo);
		pthread_mutex_lock(&(philo->data->flag));
		flag = philo->data->end;
		pthread_mutex_unlock(&(philo->data->flag));
	}
	return (0);
}

int	mutex_init(t_data *data)
{
	int	er;

	er = pthread_mutex_init(&data->flag, 0);
	if (er != 0)
	{
		pthread_mutex_destroy(&data->flag);
		return (1);
	}
	er = pthread_mutex_init(&data->print, 0);
	if (er != 0)
	{
		pthread_mutex_destroy(&data->flag);
		pthread_mutex_destroy(&data->print);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	t_info	info;
	int		er;

	if (info_init(argc, argv, &info))
		return (1);
	if (data_init_start(&data))
		return (1);
	er = data_init(&data, info);
	if (er == -1)
		return (free_philo_mutex(&data));
	if (er > 0)
		return (free_philo(&data, er));
	er = fork_init(&data, info);
	if (er == -1)
		return (free_philo(&data, info.philo_num));
	if (er > 0)
		return (free_fork(&data, er, info));
	if (philo_init(&philo, info, &data))
		return (free_fork(&data, info.philo_num, info));
	thread_init(philo);
	free(philo);
	free_fork(&data, info.philo_num, info);
	//system("leaks philo");
	return (0);
}
