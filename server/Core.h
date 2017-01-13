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
            void Idle();
            void Tick(int64_t tick);
            void Log(const char* format, ...);

            /**
             * Return current isntance of the core
             * @return Core*
             */
            static Core* Instance()
            {
                return mInstance;
            }

            /**
             * Return if core is currently running
             * @return bool
             */
            bool IsRunning()
            {
                return mRunning;
            }
    };
}
