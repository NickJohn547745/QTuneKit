#include "mediaapiservice.h"

MediaAPIService::MediaAPIService()
{

}
class MediaAPIService {
  get isConfigured() {
    return void 0 !== this._api;
  }
  get api() {
    if (void 0 === this._api) throw new MKError(MKError.CONFIGURATION_ERROR, "The API cannot be accessed before it is configured.");
    return this._api;
  }
  get storefrontId() {
    return this.store && this.store.storefrontId;
  }
  configure(e) {
    var n = this;
    return _asyncToGenerator$5(function* () {
      void 0 !== e.store && (n.store = e.store, [ss.authorizationStatusDidChange, ss.userTokenDidChange, ss.storefrontIdentifierDidChange, ss.storefrontCountryCodeDidChange].forEach(e => {
        n.store.storekit.addEventListener(e, () => n.resetAPI());
      }), n._initializeAPI(e));
    })();
  }
  clear() {
    this.api && this.api.clearNetworkCache && this.api.clearNetworkCache();
  }
  getAPIForItem(e) {
    var n = this;
    return _asyncToGenerator$5(function* () {
      return P(e) ? (yield n.store.authorize(), n.api.library || n.api) : n.api;
    })();
  }
  resetAPI() {
    var e = this;
    return _asyncToGenerator$5(function* () {
      e.clear(), e._initializeAPI();
    })();
  }
  _initializeAPI(e) {
    if (void 0 !== (null == e ? void 0 : e.api)) return void (this._api = e.api);
    const n = e && e.store || this.store;
    if (void 0 === n) return;
    const d = bs.features["api-session-storage"] ? getSessionStorage() : void 0, h = e && e.storefrontId || n.storefrontId, p = new API(this.url, n.developerToken, h, n.storekit.userToken, n.storekit.storefrontCountryCode, d, bs, e && e.apiOptions && e.apiOptions.sessionOptions);
    this._api = p.v3;
  }
  _updateStorefrontId(e) {
    var n = this;
    return _asyncToGenerator$5(function* () {
      n.api && e === n.api.storefrontId || (yield n.configure({dispatcher: n._dispatcher, store: n.store, storefrontId: e}));
    })();
  }
  constructor(e) {
    if (this._dispatcher = e, !bs.urls.mediaApi) throw new Error("bag.urls.mediaApi is not configured");
    this.url = bs.urls.mediaApi, this.namedQueueOptions = Ec;
    var n = this;
    this._dispatcher.subscribe(lr.apiStorefrontChanged, function () {
      var e = _asyncToGenerator$5(function* (e, {storefrontId: d}) {
        yield n._updateStorefrontId(d);
      });
      return function (n, d) {
        return e.apply(this, arguments);
      };
    }());
  }
}
