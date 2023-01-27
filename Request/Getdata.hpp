/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:06 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/27 15:27:27 by asabbar          ###   ########.fr       */
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
		string root;
		map<string, vector<string> > rootLoc;
	public:
		// Constructors
		Getdata(string s,string ct,bool,map<string, vector<string> > rootLoc,string root);
		void getFileName(string Fpart);
		string getRandomName();
		void CreatFill(string data);
		string RandomName(void);
};

#endif
