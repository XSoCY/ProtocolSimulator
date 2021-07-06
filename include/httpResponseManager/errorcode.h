/*
 * 主要定义http请求错误码
 * 创建者：xuejh
 * 创建日期：2021-01-06
 */
#ifndef ERRORCODE_H
#define ERRORCODE_H

namespace HTTP_ERROR_CODE {
    enum errorCode
    {
        ERROR_CODE_REQUEST_SUCCESS  = 200,
        ERROR_CODE_SAVE_SUCCESS     = 201,
        ERROR_CODE_UPDATE_SUCCESS   = 202,
        ERROR_CODE_SAVE_DEL_SUCCESS = 203,

        ERROR_CODE_DATA_EMPTY       = 401,
        ERROR_CODE_DATA_FORMAT      = 402,
        ERROR_CODE_REQUEST_ERROR    = 403,

        ERROR_CODE_SAVE_FAIL        = 501,
        ERROR_CODE_UPDATE_FAIL      = 502,
        ERROR_CODE_DEL_FAIL         = 503,
    };
}

#endif // ERRORCODE_H
