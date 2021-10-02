#include "MainServer.h"
#include <iostream>
#include <muduo/base/Logging.h>
#include "request.pb.h"

MainServer::MainServer(EventLoop *base_loop, InetAddress &addr, const string &chat_name):server_(base_loop,addr,chat_name)
{
    maps_.insert({"UpFile", bind(&MainServer::UpFile, this, _1, _2, _3)});
    maps_.insert({"DownLoadFile", bind(&MainServer::DownLoadFile, this, _1, _2, _3)});
    maps_.insert({"SearchFile", bind(&MainServer::SearchFile, this, _1, _2, _3)});
    maps_.insert({"DeleteFile", bind(&MainServer::DeleteFile, this, _1, _2, _3)});
}

//读写事件回调
void MainServer::msg_callback(TcpConnectionPtr &conn, Buffer *buff, Timestamp stamp)
{
    string recv = buff->retrieveAllAsString();
    //反序列化
    ik::Request request;
    request.ParseFromString(recv);
    LOG_INFO << "Recv request: " << recv;

    //获取处理器
    string request_type = request.request_type();
    auto handler = get_handler(request_type);
    handler(conn, buff, stamp);
}

void MainServer::conn_callback(TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        LOG_INFO << "client: " << conn->getTcpInfoString() << " login!";
    }
}

void MainServer::UpFile(TcpConnectionPtr &conn, Buffer *buff, Timestamp stamp)
{
    
}

//搜寻文件
void MainServer::SearchFile(TcpConnectionPtr &conn, Buffer *buff, Timestamp stamp)
{

}

//下载文件
void MainServer::DownLoadFile(TcpConnectionPtr &conn, Buffer *buff, Timestamp stamp)
{}

//删除文件
void MainServer::DeleteFile(TcpConnectionPtr &conn, Buffer *buff, Timestamp stamp)
{}

DealFunc MainServer::get_handler(string &type)
{
    return maps_[type];
}