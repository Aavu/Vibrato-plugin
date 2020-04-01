/*
  ==============================================================================

    ErrorDef.h
    Created: 1 Apr 2020 12:33:44pm
    Author:  Raghavasimhan Sankaranarayanan

  ==============================================================================
*/
  
#if !defined(__ErrorDef_hdr__)
#define __ErrorDef_hdr__

enum Error_t
{
    kNoError,

    kFileOpenError,
    kFileAccessError,

    kFunctionInvalidArgsError,

    kNotInitializedError,
    kFunctionIllegalCallError,
    kInvalidString,

    kMemError,

    kUnknownError,

    kNumErrors
};
#endif // #if !defined(__ErrorDef_hdr__)
