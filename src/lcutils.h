#ifndef _LCUTILS_H_
#define _LCUTILS_H_

#include "lcurl.h"

#define LCURL_MAKE_VERSION(MIN, MAJ, PAT) ((MIN<<16) + (MAJ<<8) + PAT)
#define LCURL_CURL_VER_GE(MIN, MAJ, PAT) (LIBCURL_VERSION_NUM >= LCURL_MAKE_VERSION(MIN, MAJ, PAT))

typedef struct lcurl_const_tag{
  const char *name;
  int value;
}lcurl_const_t;

typedef struct lcurl_callback_tag{
  int cb_ref;
  int ud_ref;
}lcurl_callback_t;

int lcurl_storage_init(lua_State *L);

void lcurl_storage_preserve_value(lua_State *L, int storage, int i);

int lcurl_storage_preserve_slist(lua_State *L, int storage, struct curl_slist * list);

struct curl_slist* lcurl_storage_remove_slist(lua_State *L, int storage, int idx);

void lcurl_storage_preserve_iv(lua_State *L, int storage, int i, int v);

void lcurl_storage_remove_i(lua_State *L, int storage, int i);

int lcurl_storage_free(lua_State *L, int storage);

struct curl_slist* lcurl_util_array_to_slist(lua_State *L, int t);

struct curl_slist* lcurl_util_to_slist(lua_State *L, int t);

void lcurl_util_slist_set(lua_State *L, int t, struct curl_slist* list);

void lcurl_util_slist_to_table(lua_State *L, struct curl_slist* list);

void lcurl_util_set_const(lua_State *L, const lcurl_const_t *reg);

int lcurl_util_push_cb(lua_State *L, lcurl_callback_t *c);

int lcurl_util_new_weak_table(lua_State*L, const char *mode);

int lcurl_util_pcall_method(lua_State *L, const char *name, int nargs, int nresults, int errfunc);

int lcurl_utils_apply_options(lua_State *L, int opt, int obj, int do_close,
                              int error_mode, int error_type, int error_code
                              );
#endif
