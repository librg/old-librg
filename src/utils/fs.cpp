#include <librg/utils/fs.h>
#include <librg/core/shared.h>

using namespace librg;

/**
 * Inner method
 * @param req [description]
 */
void fs::private_onread(uv_fs_t *req)
{
    uv_fs_req_cleanup(req);

    if (req->result < 0) {
        core::error("file reading: %s\n", uv_strerror(req->result));
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
 * Makedir function
 * @param  filename
 * @return result code (uv/system status codes)
 */
int fs::mkdir(std::string filename)
{
    uv_fs_t req;
    return uv_fs_mkdir(uv_default_loop(), &req, filename.c_str(), 0755, NULL);
}

/**
 * Read file contents and pass result
 * of type fs:result_t to the callback
 * @param  filename
 * @param  callback
 * @return result of operation
 */
bool fs::read(std::string filename, fs::callback callback)
{
    uv_fs_t* req = new uv_fs_t;

    // trying to open file
    int handle = uv_fs_open(uv_default_loop(), req, filename.c_str(), 0, 0, NULL);

    if (handle < 0) {
        core::error("file reading: \"%s\" %s\n", filename.c_str(), uv_strerror(handle));
        return false;
    }

    // getting file size
    uv_fs_fstat(uv_default_loop(), req, handle, NULL);

    // create string
    char* str = new char[req->statbuf.st_size];

    // get the filename stuff
    char* filepath = new char[filename.size()];
    memcpy(filepath, filename.c_str(), filename.size());

    // creating content buffer
    fs_result_t* data = new fs_result_t;
    data->handle      = handle;
    data->length      = req->statbuf.st_size;
    data->content     = str;
    data->filepath    = filepath;
    data->fplength    = filename.size();
    data->callback    = callback;

    req->data = data;
    uv_buf_t uvBuf = uv_buf_init(str, req->statbuf.st_size);

    uv_fs_read(uv_default_loop(), req, handle, &uvBuf, 1, -1, private_onread);
    return true;
}

// bool fs:read(std::string filename, (void*)(entity*), fs_callback callback)
