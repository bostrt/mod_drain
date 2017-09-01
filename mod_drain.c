/**
 * mod_drain for Apache HTTPD 2.4
 * Copyright (c) 2017 Robert Bost <bostrt at gmail dot com>
 *
 * All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the Apache License Version 2.0.
 *
 * You should have received a copy of the Apache License Version
 * 2.0 license with this file. If not, please write to:
 * bostrt at gmail dot com, or visit:
 * http://www.apache.org/licenses/LICENSE-2.0.html
 */

#include <httpd.h>
#include <http_config.h>
#include <http_log.h>
#include <stdlib.h>

static apr_pool_t *bad_pool = NULL;

static int drain_handler(request_rec *r)
{
    apr_table_t *GET;
    const char *amount_str = NULL;
    int amount = 10;

    if (!r->handler || strcmp(r->handler, "drain-handler")) {
        return(DECLINED);
    }

    ap_args_to_table(r, &GET);
    amount_str = apr_table_get(GET, "amount");

    if (amount_str) {
        amount = atoi(amount_str);
        if (amount == 0) amount = 10;
    }

    apr_palloc(bad_pool, (1024 * 1024 * amount));

    ap_set_content_type(r, "text/plain");
    ap_rprintf(r, "mod_drain\n%d MB drained\n", amount);

    return OK;
}

static void register_hooks(apr_pool_t *pool)
{
    apr_pool_create(&bad_pool, NULL);
    ap_hook_handler(drain_handler, NULL, NULL, APR_HOOK_LAST);
}

module AP_MODULE_DECLARE_DATA   drain_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks   /* Our hook registering function */
};
