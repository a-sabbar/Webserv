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
    if (headers.find("Content-Length") != headers.end() && method == "POST")
        myEnv["CONTENT_LENGTH"] = headers["Content-Length"];
    myEnv["REDIRECT_STATUS"] = "1";
    myEnv["CONTENT_TYPE"] = headers["Content-Type"];
    myEnv["SCRIPT_FILENAME"] = file;
    if (headers.find("Cookie") != headers.end())
    {
        myEnv["HTTP_COOKIE"] = headers["Cookie"];
    }
    myEnv["QUERY_STRING"] = queryString;


    map<string, string>::iterator Mit;
    for (Mit = myEnv.begin(); Mit != myEnv.end(); ++Mit) {
        setenv(Mit->first.c_str() ,Mit->second.c_str(), 1);
    }
}

int g = 0;

void HandleRequest::Exec(string f)
{
    ofstream out;
    ofstream in;
    int fd_in;


    out.open("/tmp/tmp.tmp");
    int fd = open("/tmp/tmp.tmp", O_RDWR);
    char *cmd[3];
    extern char **environ;

    cmd[0] = strdup(loc["cgi_bin"].at(0).c_str());
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
        setEnv(f);

        dup2(fd,1);
        if (execve(cmd[0],cmd,environ) == -1)
        {
            g = 1;
            exit(1);
        } 
    }
    else if (i == -1)
        g = 256;
    else
        waitpid(-1,&g,0);
    free(cmd[0]);
    free(cmd[1]);
    close(fd);
    out.close();
}


string HandleRequest::handle_cgi(string f)
{
    stringstream ret;

    Exec(f);

    cgi = true;
    fstream kk;
    if (g == 256)
    {
        code = "500";
        message = "Internal Server Error";
    }
    else
    {
        kk.open("/tmp/tmp.tmp");
        ret << kk.rdbuf();
        kk.close();
    }
    remove("/tmp/tmp.tmp");
    remove("/tmp/in.tmp");
    cout <<ret.str() << endl;
    return ret.str();
}
 