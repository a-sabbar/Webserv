/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:26 by zait-sli          #+#    #+#             */
/*   Updated: 2023/03/01 14:34:51 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


serv_d::serv_d() : backlog(SOMAXCONN)
{
}


serv_d::~serv_d()
{
}


serv_d & serv_d::operator=(const serv_d &assign)
{
	(void) assign;
	return *this;
}

