// Copyright ReGuider Team, 2016-2017
//
#include <librg/http/client.h>

void librg::network::http::send(request_t *req, request_callback_t callback)
{
    std::string output = req->headers;
    
    if (req->data) {
        output.append("Content-Length", req->length);
    }

    output.append("\r\n\r\n");

    if (req->data) {
        char *data = new char[req->length+1];
        strncpy(data, (char *)req->data, req->length);
        data[req->length] = 0;
        output.append(data);
    }

    // TODO: send data and make sure callback gets called on response...
}
