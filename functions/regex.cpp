/* 
  Copyright(C) 2014 Naoya Murakami <naoya@createfield.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; version 2
  of the License.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public
  License along with this library; if not, write to the Free
  Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
  MA 02110-1301, USA

*/

#include <groonga/plugin.h>

#include <iostream>
#include <string>
#include <re2/re2.h>

using namespace std;

#ifdef __GNUC__
# define GNUC_UNUSED __attribute__((__unused__))
#else
# define GNUC_UNUSED
#endif

static grn_obj *
func_regex_extract(grn_ctx *ctx, GNUC_UNUSED int nargs,
                   GNUC_UNUSED grn_obj **args,
                   grn_user_data *user_data)
{
  grn_obj *result;
  char *input = GRN_TEXT_VALUE(args[0]);
  char *pattern = GRN_TEXT_VALUE(args[1]);
  string s = input;
  bool ret_ext;
  if (args[2] == NULL) {
    ret_ext = RE2::Extract(input, pattern, "\\1", &s);
  } else {
    ret_ext = RE2::Extract(input, pattern, GRN_TEXT_VALUE(args[2]), &s);
  }
  
  if (ret_ext) {
    if ((result = grn_plugin_proc_alloc(ctx, user_data, GRN_DB_LONG_TEXT, 0))) {
      GRN_TEXT_SET(ctx, result, s.c_str(), strlen(s.c_str()));
    }
  } else {
    result = grn_plugin_proc_alloc(ctx, user_data, GRN_DB_VOID, 0);
  }
  return result;
}

static grn_obj *
func_regex_replace(grn_ctx *ctx, GNUC_UNUSED int nargs,
                   GNUC_UNUSED grn_obj **args,
                   grn_user_data *user_data)
{
  grn_obj *result;
  char *input = GRN_TEXT_VALUE(args[0]);
  char *pattern = GRN_TEXT_VALUE(args[1]);
  char *replace = GRN_TEXT_VALUE(args[2]);

  string s = input;
  RE2::GlobalReplace(&s, pattern, replace);

  if ((result = grn_plugin_proc_alloc(ctx, user_data, GRN_DB_LONG_TEXT, 0))) {
    GRN_TEXT_SET(ctx, result, s.c_str(), strlen(s.c_str()));
  }

  return result;
}

grn_rc
GRN_PLUGIN_INIT(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

grn_rc
GRN_PLUGIN_REGISTER(grn_ctx *ctx)
{
  grn_proc_create(ctx, "regex_extract", -1, GRN_PROC_FUNCTION,
                  func_regex_extract, NULL, NULL, 0, NULL);
  grn_proc_create(ctx, "regex_replace", -1, GRN_PROC_FUNCTION,
                  func_regex_replace, NULL, NULL, 0, NULL);

  return ctx->rc;
}

grn_rc
GRN_PLUGIN_FIN(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}
