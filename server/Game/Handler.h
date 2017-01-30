#ifndef _m2o_game_handler_h
#define _m2o_game_handler_h

namespace M2OServer {
namespace Game     {

const short EVENT_LIMIT = 255;

class Handler
{
public:
    Handler();
    ~Handler();

    void Dispatch(short eventId, void* data);
private:
    void OnTest(void* data);

    void (Handler::*mRegistry[EVENT_LIMIT])(void* data);
};


} // namespace Game
} // namespace M2OServer

#endif // _m2o_game_handler_h
