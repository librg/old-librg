#ifndef librg_network_bitstream_h
#define librg_network_bitstream_h

namespace librg
{
    namespace network
    {
        class bitstream_t {
            public:
                bitstream_t() : mBuffer(nullptr), mCurrentWritePos(0), mCurrentReadPos(0) {}

                template <typename T>
                void read(T & Var)
                {
                    unsigned int variableSize = sizeof(Var);
                    memcpy(&Var, reinterpret_cast<char*>(mBuffer) + mCurrentReadPos, variableSize);
                    mCurrentReadPos += variableSize;
                }

                template <typename T>
                void read(T * Var, unsigned int customSize = 0)
                {
                    if(Var == nullptr) return;

                    unsigned int variableSize = sizeof(*Var);
                    if(customSize != 0) variableSize = customSize;

                    memcpy(Var, reinterpret_cast<char*>(mBuffer) + mCurrentReadPos, variableSize);
                    mCurrentReadPos += variableSize;
                }

                template <typename T>
                void write(T * Var, unsigned int customSize = 0)
                {
                    if(Var == nullptr) return;

                    unsigned int variableSize = sizeof(*Var);
                    if(customSize != 0) variableSize = customSize;

                    mBuffer = realloc(mBuffer, mCurrentWritePos + variableSize);
                    memcpy(reinterpret_cast<char*>(mBuffer) + mCurrentWritePos, Var, variableSize);
                    mCurrentWritePos += variableSize;
                }

                template <typename T>
                void write(T Var)
                {
                    unsigned int variableSize = sizeof(Var);
                    mBuffer = realloc(mBuffer, mCurrentWritePos + variableSize);
                    memcpy(reinterpret_cast<char*>(mBuffer) + mCurrentWritePos, &Var, variableSize);
                    mCurrentWritePos += variableSize;
                }

                // TODO:
                // warning, potential crash if buffer < position
                template <typename T>
                void write_at(T Var, size_t position)
                {
                    memcpy(reinterpret_cast<char*>(mBuffer) + position, &Var, sizeof(Var));
                }

                void Flush()
                {
                    mCurrentReadPos = 0;
                    mCurrentWritePos = 0;

                    if(mBuffer != nullptr)
                        free(mBuffer);
                }

                void* raw() { return mBuffer; }
                unsigned int raw_size() { return mCurrentWritePos; }
                void set_raw(void * pRawBuffer) { mBuffer = pRawBuffer; }

            private:
                void * mBuffer;
                unsigned int mCurrentWritePos;
                unsigned int mCurrentReadPos;
        };
    }
}

#endif // librg_network_bitstream_h
