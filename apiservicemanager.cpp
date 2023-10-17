#include "apiservicemanager.h"

APIServiceManager::APIServiceManager()
{

}
class APIServiceManager {
  get api() {
    return this.getApiByType(this._defaultAPI);
  }
  get apiService() {
    if (void 0 !== this._defaultAPI) return this._apisByType[this._defaultAPI];
    Mt.error("There is no API instance configured");
  }
  get mediaAPI() {
    return this.getApiByType(_o.MEDIA_API);
  }
  get utsClient() {
    return this.getApiByType(_o.UTS_CLIENT);
  }
  getApiByType(e) {
    let n;
    if (void 0 !== e && (n = this._apisByType[e]), void 0 === n || void 0 === n.api) throw new MKError(MKError.CONFIGURATION_ERROR, "There is no API instance configured for the requested type: " + e);
    return n.api;
  }
  set defaultApiType (e) {
    this._defaultAPI = e;
  }
  registerAPIService(e) {
    var n, d = this;
    return (n = function* () {
      const {apiType: n, configureFn: h, options: p} = e, y = p.apiOptions || {};
      void 0 === d._defaultAPI && (d._defaultAPI = n), d._apisByType[n] = yield h.call(d, {apiOptions: y, store: d.store, dispatcher: d._dispatcher});
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$j(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$j(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  constructor(e, n) {
    this.store = e, this._dispatcher = n, this._apisByType = {};
  }
}
