#include "store.h"

Store::Store()
{

}
class Store {
  get authorizationStatus() {
    return this.storekit.authorizationStatus;
  }
  get cid() {
    return this.storekit.cid;
  }
  get developerToken() {
    return this.storekit.developerToken;
  }
  get hasAuthorized() {
    return this._hasAuthorized;
  }
  get isAuthorized() {
    return this.storekit.hasAuthorized;
  }
  get isRestricted() {
    return this.storekit.authorizationStatus === Ie.RESTRICTED;
  }
  get metricsClientId() {
    return this._metricsClientId;
  }
  set metricsClientId (e) {
    this._metricsClientId = e;
  }
  get musicUserToken() {
    return this.storekit.userToken;
  }
  set musicUserToken (e) {
    this.storekit.userToken = e;
  }
  set dynamicMusicUserToken (e) {
    this.storekit.dynamicUserToken = e;
  }
  get realm() {
    return this.storekit.realm;
  }
  set requestUserToken (e) {
    this._providedRequestUserToken = true, this.storekit.requestUserToken = e;
  }
  get restrictedEnabled() {
    return this.storekit.restrictedEnabled;
  }
  set restrictedEnabled (e) {
    this.storekit.overrideRestrictEnabled(e);
  }
  get storefrontCountryCode() {
    var e;
    return this.isAuthorized ? this.storekit.storefrontCountryCode : null !== (e = this._defaultStorefrontCountryCode) && void 0 !== e ? e : this.storekit.storefrontCountryCode;
  }
  get storefrontId() {
    return this._apiStorefrontId || this.storekit.storefrontCountryCode;
  }
  set storefrontId (e) {
    e && (e = e.toLowerCase()), e !== this._apiStorefrontId && (this._apiStorefrontId = e, this._dispatcher.publish(lr.apiStorefrontChanged, {storefrontId: e}));
  }
  get subscribeURL() {
    return this.storekit.deeplinkURL({p: "subscribe"});
  }
  get subscribeFamilyURL() {
    return this.storekit.deeplinkURL({p: "subscribe-family"});
  }
  get subscribeIndividualURL() {
    return this.storekit.deeplinkURL({p: "subscribe-individual"});
  }
  get subscribeStudentURL() {
    return this.storekit.deeplinkURL({p: "subscribe-student"});
  }
  get userToken() {
    return this.musicUserToken;
  }
  authorize() {
    var e = this;
    return _asyncToGenerator$v(function* () {
      if (e.storekit.userTokenIsValid) return e.storekit.userToken;
      let n;
      try {
        n = yield e.storekit.requestUserToken();
      } catch (z) {
        try {
          yield e.unauthorize();
        } catch (Mr) {}
        throw new MKError(MKError.AUTHORIZATION_ERROR, "Unauthorized");
      }
      return e._providedRequestUserToken && (e.storekit.userToken = n), e.storekit.userTokenIsValid ? (yield e.storekit.requestStorefrontCountryCode().catch(function () {
        var n = _asyncToGenerator$v(function* (n) {
          return yield e.unauthorize(), Promise.reject(n);
        });
        return function (e) {
          return n.apply(this, arguments);
        };
      }()), n) : void 0;
    })();
  }
  unauthorize() {
    var e = this;
    return _asyncToGenerator$v(function* () {
      return e.storekit.revokeUserToken();
    })();
  }
  constructor(n, d = {}) {
    this._hasAuthorized = false, this._providedRequestUserToken = false, this._ageVerificationRequired = (e, n) => true, this._dispatcher = d.services.dispatcher, d.precache && (this.precache = d.precache), d.storefrontId && (this.storefrontId = d.storefrontId), this._defaultStorefrontCountryCode = d.storefrontCountryCode, (d.affiliateToken || d.campaignToken) && (d.linkParameters = _objectSpreadProps$f(function (e) {
      for (var n = 1; n < arguments.length; n++) {
        var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
        "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
          return Object.getOwnPropertyDescriptor(d, e).enumerable;
        }))), h.forEach(function (n) {
          n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
        });
      }
      return e;
    }({}, d.linkParameters || {}), {at: d.affiliateToken, ct: d.campaignToken})), this.storekit = new StoreKit(n, {apiBase: bs.urls.mediaApi, authenticateMethod: bs.features["legacy-authenticate-method"] ? "POST" : "GET", deeplink: d.linkParameters, disableAuthBridge: d.disableAuthBridge, iconURL: bs.app.icon, meParameters: d.meParameters, persist: d.persist, realm: d.realm || e.SKRealm.MUSIC}), this.storekit.addEventListener(ss.authorizationStatusDidChange, e => {
      const {authorizationStatus: n} = e;
      this._hasAuthorized = [Ie.AUTHORIZED, Ie.RESTRICTED].includes(n);
    });
  }
}
