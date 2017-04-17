// Copyright ReGuider Team, 2016-2017
//
#include <librg/http/client.h>

void librg::network::http::set_data(request_t *req, void* data, uint64_t length)
{
    req->data = data;
    req->length = length;
}
