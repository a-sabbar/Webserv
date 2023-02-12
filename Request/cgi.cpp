// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:46:02 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/12 17:00:05 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"
#include <fcntl.h>



void HandleRequest::setEnv(string file)
{
    map<string, string > myEnv;
    myEnv["PATH_INFO"] = root;
    myEnv["REQUEST_METHOD"] = method;
    if (headers.find("Content-Length") != headers.end())
        myEnv["CONTENT_LENGTH"] = headers["Content-Length"];
    cout << "Content length is " << headers["Content-Length"] << endl;
    myEnv["REDIRECT_STATUS"] = "1";
    myEnv["CONTENT_TYPE"] = headers["Content-Type"];
    myEnv["SCRIPT_FILENAME"] = file;
    myEnv["QUERY_STRING"] = queryString;


    map<string, string>::iterator Mit;
    for (Mit = myEnv.begin(); Mit != myEnv.end(); ++Mit) {
        setenv(Mit->first.c_str() ,Mit->second.c_str(), 1);
    }
}

void HandleRequest::Exec(string f)
{
    ofstream out;
    ofstream in;
    int fd_in;


    out.open("/tmp/tmp.tmp");
    int fd = open("/tmp/tmp.tmp", O_RDWR);
    char *cmd[3];
    extern char **environ;
    
    cmd[0] = strdup("/Users/zait-sli/Desktop/Webser/Run_serv/php-cgi");
    cmd[1] = strdup(f.c_str());
    cmd[2] = NULL;

    int i = fork();
    if (method == "POST" && i == 0)
    {
        in.open("/tmp/in.tmp");
        in << body;
        in.close();
        fd_in = open("/tmp/in.tmp", O_RDONLY);
        dup2(fd_in,0);
        close(fd_in);
    }
    if (i == 0)
    {
        dup2(fd,1);
        cerr << execve(cmd[0],cmd,environ) << endl; 
    }
    else
    {
        waitpid(-1,NULL,0);
    }
    cout << "here4" << endl;
    close(fd);
    out.close();
}


string HandleRequest::handle_cgi(string f)
{
    stringstream ret;

    setEnv(f);
    Exec(f);

    fstream kk;
    kk.open("/tmp/tmp.tmp");
    ret << kk.rdbuf();
    // cerr << ret.str().substr(ret.str().find(Spliter) + SpliterLen) << endl;
    kk.close();

    remove("/tmp/tmp.tmp");
    remove("/tmp/in.tmp");
    return ret.str().substr(ret.str().find(Spliter) + SpliterLen);
}
 