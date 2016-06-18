#ifndef H83D722A4_3495_4C68_90A0_6CD2912FDEDC
#define H83D722A4_3495_4C68_90A0_6CD2912FDEDC

#define __FWD_DECL(ns, xlass, type) namespace ns { xlass type; }

#define FWD_DECL_CLASS(ns, type)  __FWD_DECL(ns, class,  type)
#define FWD_DECL_STRUCT(ns, type) __FWD_DECL(ns, struct, type)

#define FWD_DECL_STDCXX(type) FWD_DECL_CLASS(std, type)
#define FWD_DECL_STDC(tag, name) struct tag; typedef tag name;

#endif
