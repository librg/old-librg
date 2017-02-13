#include "Filesystem.h"
#include <Core.h>

/**
 * Inner method
 * @param req [description]
 */
void FS::onRead(uv_fs_t *req)
{
    uv_fs_req_cleanup(req);

    if (req->result < 0) {
        Server::Core::Error("file reading: %s\n", uv_strerror(req->result));
    }

    fs_result_t* result = (fs_result_t*) req->data;

    if (req->result > 0) {
        // result
        // result->content[result->length] = '\0';
        result->callback(result);
    }

    // cleaning up
    uv_fs_close(uv_default_loop(), req, result->handle, NULL);

    // deleting
    delete req;
    delete result->content;
    delete result->filepath;
    delete result;
}

/**
 * Read file contents and pass result
 * of type FS:result_t to the callback
 * @param  filename
 * @param  callback
 * @return result of operation
 */
bool FS::Read(std::string filename, fs_callback callback)
{
    uv_fs_t* openReq = new uv_fs_t;

    // trying to open file
    int handle = uv_fs_open(uv_default_loop(), openReq, filename.c_str(), 0, 0, NULL);

    if (handle < 0) {
        Server::Core::Error("file reading: \"%s\" %s\n", filename.c_str(), uv_strerror(handle));
        return false;
    }

    // getting file size
    uv_fs_fstat(uv_default_loop(), openReq, handle, NULL);

    // create string
    char* str = new char[openReq->statbuf.st_size];

    // get the filename stuff
    char* filepath = new char[filename.size()];
    memcpy(filepath, filename.c_str(), filename.size());

    // creating content buffer
    fs_result_t* data = new fs_result_t;
    data->handle      = handle;
    data->length      = openReq->statbuf.st_size;
    data->content     = str;
    data->filepath    = filepath;
    data->fplength    = filename.size();
    data->callback    = callback;

    openReq->data = data;
    uv_buf_t uvBuf = uv_buf_init(str, openReq->statbuf.st_size);

    uv_fs_read(uv_default_loop(), openReq, handle, &uvBuf, 1, -1, onRead);
    return true;
}
