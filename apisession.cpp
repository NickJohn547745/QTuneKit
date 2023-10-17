#include "apisession.h"

APISession::APISession()
{

}
class APISession {
  get config() {
    return this._config;
  }
  request(e, n = {}, d = {}) {
    var h;
    return processMiddleware(this.middlewareStack, _objectSpreadProps$8(_objectSpread$e({}, this.config.defaultOptions, d), {baseUrl: this.config.url, path: e, fetchOptions: mergeFetchOptions(null === (h = this.config.defaultOptions) || void 0 === h ? void 0 : h.fetchOptions, d.fetchOptions), queryParameters: _objectSpread$e({}, this.config.defaultQueryParameters, n), urlParameters: _objectSpread$e({}, this.config.defaultUrlParameters, d.urlParameters)}));
  }
  reconfigure(e, n = Js.Replace) {
    n === Js.Merge && (e = deepmerge(this.config, e)), Xs.forEach(n => {
      if (void 0 === e[n]) throw new Error(`Session requires a valid SessionConfig, missing "${n}"`);
    }), this._config = e, this.middlewareStack = this.createMiddlewareStack();
  }
  createMiddlewareStack() {
    return Array.isArray(this.config.middleware) ? [constructUrlMiddleware, ...this.config.middleware, this.makeFetchMiddleware()] : [constructUrlMiddleware, this.makeFetchMiddleware()];
  }
  makeFetchMiddleware() {
    return "function" == typeof this.config.fetchFunction ? fetchMiddlewareFactory(this.config.fetchFunction) : Qs;
  }
  constructor(e) {
    this.reconfigure(e);
  }
}
