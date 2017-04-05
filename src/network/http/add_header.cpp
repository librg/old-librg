// Copyright ReGuider Team, 2016-2017
//
#include <librg/network/http/client.h>

void librg::network::http::add_header(request_t *req, std::string head, std::string text)
{
    std::string line = head + ":" + text + "\r\n";
    req->headers.append(line);
}