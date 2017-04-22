// Copyright ReGuider Team, 2016-2017
//
#include <librg/http/client.h>

librg::network::http::request_t librg::network::http::create(std::string host, std::string method, std::string uri, int port)
{
    request_t result = {};
    result.headers = method + " " + uri + " HTTP/1.1\r\n";
    add_header(&result, "Host", host);
    add_header(&result, "Connection", "keep-alive");
    return result;
}
