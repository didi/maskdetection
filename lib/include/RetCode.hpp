#ifndef RET_CODE_HPP_
#define RET_CODE_HPP_

// Return code 
typedef enum _FM_RET_CODE_
{
  FM_SUCCESS = 0,
  FM_INIT_ERR = 1,
  FM_LOADIMG_ERR = 2,
  FM_IMG_INVALID = 3,
  FM_DETMASK_ERR = 4
} FM_RET_CODE;

#endif
