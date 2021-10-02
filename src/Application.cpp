#include "Application.h"

#include <muduo/base/Logging.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace muduo;
using namespace std;

Configure Application::configure_;

void Application::init(int argc, char **argv)
{
    //加载配置文件
    configure_.load_configure("../conf/MainServer.conf");
}

Application::Application()
{
}