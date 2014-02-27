/* 
**    #   apache2.conf
**    LoadModule CXX_module modules/mod_CXX.so
**    <Location /CXX>
**    SetHandler CXX
**    </Location>
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "mod_CXX.h"
#include "content_manager.h"
#include <string>

C_DECLARE int CXX_handler(request_rec *r)
{
	if (strcasecmp(r->handler, "CXX")) {
		return DECLINED;
	}
	r->content_type = "text/html";

	ContentManager cm;
	std::string output = " hello! can you see me\n";

	if (!r->header_only) {
		ap_rputc(cm.findRemoteIP(), r);
		ap_rputs(output.c_str(), r);
	}
	return OK;
}

C_DECLARE void CXX_register_hooks(apr_pool_t *p)
{
	ap_hook_handler(CXX_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA CXX_module = {
	STANDARD20_MODULE_STUFF, 
	NULL,                  /* create per-dir    config structures */
	NULL,                  /* merge  per-dir    config structures */
	NULL,                  /* create per-server config structures */
	NULL,                  /* merge  per-server config structures */
	NULL,                  /* table of config file commands       */
	CXX_register_hooks  /* register hooks                      */
};
