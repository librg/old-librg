#pragma once

namespace MOServer
{
    class Core
    {
        private:
            static Core* mInstance;
            bool mRunning;

        public:
            Core();
            ~Core();

            void Init();
            void Tick();
            static Core* Instance();

            /**
             * Return if core is currently running
             * @return bool
             */
            bool IsRunning() {
                return mRunning;
            }
    };
}
