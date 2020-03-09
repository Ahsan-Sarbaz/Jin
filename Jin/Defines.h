#pragma once


//TODO: more compiler checks
#if defined(_MSC_VER)
	#define JIN_INLINE __forceinline
#elif defined(__GNUC__)
	#define JIN_INLINE inline
#endif // _MSVC_
