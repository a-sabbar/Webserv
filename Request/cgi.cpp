/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:46:02 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/11 23:38:04 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"



void HandleRequest::setEnv(string file)
{
    
    map<string, string > myEnv;
    myEnv["SCRIPT_NAME"] = file.substr(file.find_last_of("/") + 1);
    cout << file.substr(file.find_last_of("/") + 1) << endl;
    myEnv["REDIRECT_STATUS"] = code;
    myEnv["REQUEST_METHOD"] = method;
    if(!queryString.empty())
        myEnv["QUERY_STRING"] = queryString;
        
    myEnv["CONTENT_TYPE"] = headers["Content-Type"];






    
    map<string, string>::iterator Mit;
    for (Mit = myEnv.begin(); Mit != myEnv.end(); ++Mit) {
        setenv(Mit->first.c_str() ,Mit->second.c_str(), 1);
    }
}

void HandleRequest::Exec(string f)
{
    
    ofstream out;
    // fstream test;

    out.open("/tmp/tmp.tmp");
    FILE * h = fopen("/tmp/tmp.tmp", "w+");
    int fd = fileno(h);    
    // int tt = dup(1);
    char *cmd[3];
    extern char **environ;
    
    cmd[0] = strdup("/Users/zait-sli/Desktop/Webser/php-cgi");
    cmd[1] = strdup(f.c_str());
    cmd[2] = NULL;

    int i = fork();
    if (i == 0)
    {
        dup2(fd,1);
        cerr << execve(cmd[0],cmd,environ) << endl; 
    }
    else
    {
        waitpid(-1,NULL,0);
    }
    // dup(tt);
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
    cerr << ret.str().length() << endl;
    kk.close();
    return ret.str();
}
 