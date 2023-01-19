/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:02 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/19 23:38:58 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Getdata.hpp"
#include "fstream"

// Constructors
Getdata::Getdata(string s,string ct ,bool i)
{
	this->ct = ct;
	if (i == 0)
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
	else
	{
		fileName = "ttttttt";
		if (ct == "application/pdf")
			fileName += ".pdf";
		CreatFill(s);
	}
}


void Getdata::getFileName(string str)
{
	size_t t = str.find("filename=") + 10;
	fileName  = str.substr(t, str.find_first_of("\"", t) - t);
}

void Getdata::CreatFill(string data)
{
	ofstream out;
	string g = "./upload/" + fileName;
	out.open(g);
	out << data;
	out.close();
}