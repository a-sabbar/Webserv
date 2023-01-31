/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:28:20 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/30 16:07:41 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"


string GetTime()
{
    string T;
    time_t givemetime = time(NULL);
    T = string(ctime(&givemetime));
    cout << T << endl;
    mytrim(T);
    T += " GMT+1";
    return T;
}

void HandleRequest::generateResponse()
{
	string e = "\r\n";
	Response = version + " " + code + " " + message + e;
	Response += "Date: " + GetTime() + e;
	Response += "Connection: " + headers["Connection"] + e;
	Response += "Content-Length: " + to_string(ResBody.length());
	Response += Spliter + ResBody + e;
}