#pragma once

namespace MOEB::Server
{
    class Core
    {
        private:
            Core* mInstance;
            bool mRunning;

        public:
            Core();
            ~Core();

            void Init();
            void Tick();
            Core* Instance();

            /**
             * Return if core is currently running
             * @return bool
             */
            bool IsRunning() {
                return mRunning;
            }
    };
}
