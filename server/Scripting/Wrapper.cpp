/*

   PROJECT: Bully Multiplayer
   FILE: Server/Server.Core/CLuaFuncArguments.h
   DEVELOPERS: MyU

   Copyright 2014-2015 Bully Multiplayer Team

*/

#pragma once

class CLuaFuncArguments
{
private:
    lua_State *m_pVM;
    int m_iIndex;
    bool m_bErrorOccured;
    BYTE m_byteReturnCount;

public:
    CLuaFuncArguments(lua_State *pVM);

    template < typename T >
    void Read ( T& outVal )
    {
        int iArgType = lua_type(m_pVM, m_iIndex);

        if ( typeid(T) == typeid(bool) )
        { // boolean / byte
            if ( iArgType == LUA_TBOOLEAN && typeid(T) == typeid(bool) )
            {
                outVal = lua_toboolean(m_pVM, m_iIndex++)?true:false;
                return;
            }
            ArgErr(m_iIndex, LUA_TBOOLEAN);
        }
        else
        { // float / int / byte
            //printlnf("CLuaFuncArguments::Read(Number, %i)", m_iIndex);
            if ( iArgType == LUA_TNUMBER )
            { // no need for tointeger
                outVal = static_cast<T>(lua_tonumber(m_pVM, m_iIndex++));
                return;
            }
            ArgErr(m_iIndex, LUA_TNUMBER);
        }


        //m_iArgErrIndex = m_iIndex;
        // report arg error?
        outVal = NULL;
        m_iIndex++;
    }
    void Read ( const char* &outVal )
    {
        int iArgType = lua_type(m_pVM, m_iIndex);

        if ( iArgType == LUA_TSTRING || iArgType == LUA_TNUMBER ) // support only number's also
        {
            outVal = lua_tostring(m_pVM, m_iIndex++);
            return;
        }//tnone, tnil handling?

        ArgErr(m_iIndex, LUA_TSTRING);
        // report arg error?
        outVal = NULL;
        m_iIndex++;
    }

    inline int ReadFuncRef()
    {
        int iArgType = lua_type(m_pVM, m_iIndex);
        if (iArgType != LUA_TFUNCTION)
        {
            ArgErr(m_iIndex, LUA_TFUNCTION);
            return -1;
        }

        lua_pushvalue(m_pVM, m_iIndex++);
        return luaL_ref(m_pVM, LUA_REGISTRYINDEX);
    }

    // Read overload's
    inline void Read(Color& outVal)
    {
        // TODO: Support own type: Color
        Read<BYTE>(outVal.r);
        Read<BYTE>(outVal.g);
        Read<BYTE>(outVal.b);
    }

    inline void Read(CVector3& outVal)
    {
        // TODO: Support own type: Vector3
        Read<float>(outVal.fX);
        Read<float>(outVal.fY);
        Read<float>(outVal.fZ);
    }

    //byteReturnCount
    template < typename T >
    void WriteReturn(T inVal)
    {
        if (typeid(T) == typeid(bool))
        { // bool
            lua_pushboolean(m_pVM, inVal?true:false);
        }
        else
        { // float / int / byte / shiet
            lua_pushnumber(m_pVM, static_cast<T>(inVal));
        }
        m_byteReturnCount++;
    }

    // WriteReturn overload's
    void WriteReturn(const char* inVal)
    {

        if (inVal != NULL)
            lua_pushstring(m_pVM, inVal);
        else
            lua_pushnil(m_pVM);
        m_byteReturnCount++;
    }
    inline void WriteReturn(char* inVal) { WriteReturn((const char*)inVal); } // hue

    inline void WriteReturn(CVector3 inVal)
    {
        // TODO: Support own type: Vector3
        WriteReturn<float>(inVal.fX);
        WriteReturn<float>(inVal.fY);
        WriteReturn<float>(inVal.fZ);
    }

    inline void ArgErr(int iIndex, int iExpectedType)
    {
        luaL_typerror(m_pVM, iIndex, lua_typename(m_pVM, iExpectedType));
        printf("%s, ", lua_typename(m_pVM, iExpectedType));

        m_bErrorOccured = true;
    }

    inline bool Cancel() { return lua_pushinteger(m_pVM, 0), 1; }
    inline BYTE GetReturnCount() { return m_byteReturnCount; }
    inline bool Failed() {
        //printf(")\n");
        return m_bErrorOccured;
    }

    ~CLuaFuncArguments();
};
