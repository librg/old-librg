#ifndef __game_handler_h
#define __game_handler_h

namespace Server {
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
} // namespace Server

#endif // __game_handler_h
