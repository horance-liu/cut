#ifndef H83D722A4_3495_4C68_90A0_6CD2912FDEDC
#define H83D722A4_3495_4C68_90A0_6CD2912FDEDC

#define FWD_DECL(ns, type) namespace ns { class type; }

#define FWD_DECL_STDCPP(type) FWD_DECL(std, type)
#define FWD_DECL_STDC(tag, name) struct tag; typedef tag name;

#endif
