/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:28:20 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/30 11:42:01 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"


void HandleRequest::generateResponse()
{
	string e = "\r\n";
	Response = version + " " + code + " " + message + e;
	Response += "Date: lyoum" + e;
	Response += "Connection: " + headers["Connection"] + e;
	Response += "Content-Length: " + to_string(ResBody.length());
	Response += Spliter + ResBody + e;
}