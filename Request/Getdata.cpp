/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:02 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/15 02:22:21 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Getdata.hpp"
#include "fstream"

// Constructors
Getdata::Getdata(string s)
{
	string firstPart;
	string data;
	int sp = s.find(Spliter);
	firstPart = s.substr(0,sp);
	data = s.substr(sp + SpliterLen);
	if (firstPart.find("filename=") != string::npos && firstPart.find("filename=\"\"") == string::npos)
	{
		getFileName(firstPart);
		CreatFill(data);
	}
}


void Getdata::getFileName(string str)
{
	int t = str.find("filename=") + 10;
	fileName  = str.substr(t, str.find_first_of("\"", t) - t);
	cout << fileName << endl;
}

void Getdata::CreatFill(string data)
{
	ofstream out;
	out.open(fileName);
	out << data;
	out.close();
}