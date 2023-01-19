/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:06 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/18 00:40:17 by zait-sli         ###   ########.fr       */
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
		string ct;
	public:
		// Constructors
		Getdata(string s,string ct,bool);
		void getFileName(string Fpart);
		string getRandomName();
		void CreatFill(string data);
};

#endif