/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:02 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/25 13:11:04 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Getdata.hpp"
#include <fstream>
#include <cstdio> 

// Constructors
Getdata::Getdata(string s,string ct ,bool i,map<string, vector<string> > rootLoc,string root)
{
	this->rootLoc = rootLoc;
	this->root = root;
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
		// RandomName();
		fileName = RandomName();
		if (ct == "application/pdf")
			fileName += ".pdf";
		else if(ct == "image/png")
			fileName += ".png";
		CreatFill(s);
	}
}

string Getdata::RandomName(void)
{
	char filename1[L_tmpnam];
	mkstemp(filename1);
	cout << "Temporary filenames:" << endl;
	cout << "1. " << filename1 << endl;
	// return(string(filename1));
	return("hhhh");
}

void Getdata::getFileName(string str)
{
	size_t t = str.find("filename=") + 10;
	fileName  = str.substr(t, str.find_first_of("\"", t) - t);
}

void Getdata::CreatFill(string data)
{
	ofstream out;
	string g;
	if (rootLoc["upload_store"].size() == 1)
		g = root + rootLoc["upload_store"].at(0) + "/" + fileName;
	else
		g = root + "/" + fileName;
	out.open(g);
	out << data;
	out.close();
}