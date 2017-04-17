// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_http_client_h
#define librg_network_http_client_h

#include <librg/core.h>
#include <librg/entities.h>
#include <librg/components/client.h>

namespace librg
{
    namespace network
    {
        namespace http
        {
            struct request_t {
                std::string headers;
                void* data;
                uint64_t length;
            };

            using response_t = std::string;
            using request_callback_t = std::function<void(response_t* res)>;

            request_t create(std::string host, std::string method, std::string uri, int port);

            void add_header(request_t *req, std::string head, std::string text);

            void set_data(request_t *req, void* data, uint64_t length);

            void send(request_t *req, request_callback_t callback);
        }
    }
}

#endif // librg_network_http_client_h
