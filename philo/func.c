/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:09:35 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/01 19:32:52 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long long wait_time)
{
	long long	start;
	long long	now;

	if (wait_time < 0)
		return ;
	start = ft_gettime();
	while (1)
	{
		now = ft_gettime();
		if ((now - start) >= wait_time)
			break ;
		usleep(100);
	}
}

long long	ft_gettime(void)
{
	struct timeval	time;
	long long		now;

	gettimeofday(&time, 0);
	now = time.tv_sec * 1000 + time.tv_usec * 0.001;
	return (now);
}

void	print_state(t_philo philo, char *msg)
{
	long long		now;

	pthread_mutex_lock(&(philo.data->print));
	now = ft_gettime();
	pthread_mutex_lock(&(philo.data->flag));
	if (!(philo.data->end))
		printf("%lld %d %s\n", now - philo.info.start_time, philo.num + 1, msg);
	pthread_mutex_unlock(&(philo.data->flag));
	pthread_mutex_unlock(&(philo.data->print));
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	pm;
	long long	sum;

	sum = 0;
	pm = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pm = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + str[i] - 48;
		i++;
	}
	if (i > 18)
		return (-1);
	return (sum * pm);
}
