
#ifndef MINITRACE_EXPORT_H
#define MINITRACE_EXPORT_H

#ifdef MINITRACE_STATIC_DEFINE
#  define MINITRACE_EXPORT
#  define MINITRACE_NO_EXPORT
#else
#  ifndef MINITRACE_EXPORT
#    ifdef minitrace_EXPORTS
        /* We are building this library */
#      define MINITRACE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MINITRACE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef MINITRACE_NO_EXPORT
#    define MINITRACE_NO_EXPORT 
#  endif
#endif

#ifndef MINITRACE_DEPRECATED
#  define MINITRACE_DEPRECATED __declspec(deprecated)
#endif

#ifndef MINITRACE_DEPRECATED_EXPORT
#  define MINITRACE_DEPRECATED_EXPORT MINITRACE_EXPORT MINITRACE_DEPRECATED
#endif

#ifndef MINITRACE_DEPRECATED_NO_EXPORT
#  define MINITRACE_DEPRECATED_NO_EXPORT MINITRACE_NO_EXPORT MINITRACE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MINITRACE_NO_DEPRECATED
#    define MINITRACE_NO_DEPRECATED
#  endif
#endif

#endif /* MINITRACE_EXPORT_H */
