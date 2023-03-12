/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runMyServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:30:41 by asabbar           #+#    #+#             */
/*   Updated: 2023/03/12 12:06:26 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef runMyServer_HPP
# define runMyServer_HPP
# include "../Webserv.hpp"
# include <iostream>
# include <string>
# include <algorithm>
using namespace std;

class runMyServer
{
    public:
        std::vector<serv_d> ::iterator             it;
        std::vector <int>                          serverSocket;
        std::vector <class client_d>               addNewFd;
        std::vector <struct pollfd>                fds;
        size_t                                     nfds;
        std::vector<class client_d> ::iterator     iterator_client;
        /* data */
    public:
        runMyServer(/* args */);
        runMyServer(std::vector<serv_d> &serv_data);
        struct pollfd                   Accept_read(int fd);
        int                             get_content_len(std::string request);
        std::string                     get_host(std::string request);
        void                            clearPollList(client_d client);
        std::string                     get_path(std::string request);
        void                            run(std::vector<serv_d> &serv_data);
        int                             readRequest(std::vector<serv_d> &serv_data, int fd);
        void                            binding(std::vector<serv_d> &serv_data);
        long long int	                get_time(void);
        ~runMyServer();      
};

#endif