/* Avalanche
 * (c) 2022 Chris Young
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

#include <proto/dos.h>

#include <exec/types.h>

#ifdef __amigaos4__
#include <proto/zip.h>
#include <libraries/zip.h>
#endif

#include "libs.h"
#include "locale.h"
#include "module.h"
#include "req.h"

static void mod_zip_show_error(void *awin, zip_t *zip)
{
	open_error_req(zip_error_strerror(zip_get_error(zip)), locale_get_string(MSG_OK), awin);
}

static BOOL mod_zip_del(void *awin, char *archive, char **files, ULONG count)
{
#ifdef __amigaos4__
	int err = 0;
	zip_t *zip = zip_open(archive, 0, &err);

	if(zip) {
		for(int i = 0; i < count; i++) {
			zip_int64_t index = zip_name_locate(zip, files[i], 0);
			if(index == -1) {
				mod_zip_show_error(awin, zip);
				zip_discard(zip);
				return FALSE;
			}

			err = zip_delete(zip, index);
			if(err == -1) {
				mod_zip_show_error(awin, zip);
				zip_discard(zip);
				return FALSE;
			}
		}

		err = zip_close(zip);
		if(err == -1) {
			mod_zip_show_error(awin, zip);
			zip_discard(zip);
			return FALSE;
		}
		return TRUE;
	} else {
		open_error_req(zip_error_strerror(&err), locale_get_string(MSG_OK), awin);
	}

	return FALSE;
#endif
}

static BOOL mod_zip_add(void *awin, char *archive, char *file)
{
#ifdef __amigaos4__
	int err = 0;
	zip_t *zip = zip_open(archive, 0, &err);

	if(zip) {
		zip_source_t *src = zip_source_file(zip, file, 0, -1);
		if(zip == NULL) {
			mod_zip_show_error(awin, zip);
			zip_discard(zip);
			return FALSE;
		}

		err = zip_file_add(zip, FilePart(file), src, 0);
		if(err == -1) {
			mod_zip_show_error(awin, zip);
			zip_discard(zip);
			return FALSE;
		}

		err = zip_close(zip);
		if(err == -1) {
			mod_zip_show_error(awin, zip);
			zip_discard(zip);
			return FALSE;
		}
		return TRUE;
	} else {
		open_error_req(zip_error_strerror(&err), locale_get_string(MSG_OK), awin);
	}

	return FALSE;
#endif
}

void mod_zip_register(struct module_functions *funcs)
{
	if(libs_zip_init()) {
		funcs->add = mod_zip_add;
		funcs->del = mod_zip_del;
	}
}
