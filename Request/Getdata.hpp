/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:06 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/15 02:16:39 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETDATA_HPP
# define GETDATA_HPP
#include "HandleRequest.hpp"
#include "Getdata.hpp"
# include <iostream>
# include <string>
using namespace std;
class Getdata
{
	private:
		string fileName;
		string ContnetType;
	public:
		// Constructors
		Getdata(string s);
		void getFileName(string Fpart);
		void CreatFill(string data);
};

#endif