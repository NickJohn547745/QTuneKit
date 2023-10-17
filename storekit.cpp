#include "storekit.h"

StoreKit::StoreKit()
{

}
class StoreKit extends Notifications {
  updateUserTokenFromStorage() {
    const e = this._getStorageItem(ve.USER_TOKEN);
    this.userToken = e || void 0;
  }
  get authorizationStatus() {
    return this._authorizationStatus;
  }
  set authorizationStatus (e) {
    this._authorizationStatus !== e && (this._getIsActiveSubscription.updateCache(void 0), this.dispatchEvent(xe.authorizationStatusWillChange, {authorizationStatus: this._authorizationStatus, newAuthorizationStatus: e}), this._authorizationStatus = e, this.dispatchEvent(xe.authorizationStatusDidChange, {authorizationStatus: e}));
  }
  get cid() {
    if (!this._cids[this.cidNamespace]) {
      const e = this._getStorageItem(this.cidNamespace);
      this._cids[this.cidNamespace] = e || void 0;
    }
    return this._cids[this.cidNamespace];
  }
  set cid (e) {
    e ? this._setStorageItem(this.cidNamespace, e) : this._removeStorageItem(this.cidNamespace), this._cids[this.cidNamespace] = e;
  }
  eligibleForSubscribeView() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      const n = yield e.hasMusicSubscription();
      return (!e.hasAuthorized || e.hasAuthorized && !n) && !e._dispatchedSubscribeView;
    })();
  }
  get hasAuthorized() {
    return this.authorizationStatus > Ie.DENIED;
  }
  get logoutURL() {
    if (!this._disableLogoutURL) return this.playBase + "/webPlayerLogout";
  }
  get _pldfltcid() {
    return this._cids[ve.DEFAULT_CID];
  }
  set _pldfltcid (e) {
    this._cids[ve.DEFAULT_CID] = e;
  }
  get restrictedEnabled() {
    if (this.userToken && "boolean" != typeof this._restrictedEnabled) {
      const e = this._getStorageItem(ve.RESTRICTIONS_ENABLED);
      if (e) this._restrictedEnabled = "0" !== e; else if (this._storefrontCountryCode) {
        const e = ["br", "ch", "gt", "hu", "id", "in", "it", "kr", "la", "lt", "my", "ru", "sg", "tr"];
        this._restrictedEnabled = -1 !== e.indexOf(this._storefrontCountryCode) || void 0;
      }
    }
    return this._restrictedEnabled;
  }
  set restrictedEnabled (e) {
    this._restrictedEnabledOverridden || (this.userToken && void 0 !== e && this._setStorageItem(ve.RESTRICTIONS_ENABLED, e ? "1" : "0"), this._restrictedEnabled = e, e && (this.authorizationStatus = Ie.RESTRICTED));
  }
  overrideRestrictEnabled(e) {
    this._restrictedEnabledOverridden = false, this.restrictedEnabled = e, this._restrictedEnabledOverridden = true;
  }
  get storefrontCountryCode() {
    if (!this._storefrontCountryCode) {
      const e = this._getStorageItem(ve.STOREFRONT_COUNTRY_CODE);
      this._storefrontCountryCode = (null == e ? void 0 : e.toLowerCase()) || Me.ID;
    }
    return this._storefrontCountryCode;
  }
  set storefrontCountryCode (e) {
    e && this.userToken ? this._setStorageItem(ve.STOREFRONT_COUNTRY_CODE, e) : this._removeStorageItem(ve.STOREFRONT_COUNTRY_CODE), e !== this._storefrontCountryCode && (this._storefrontCountryCode = e, this.dispatchEvent(xe.storefrontCountryCodeDidChange, {storefrontCountryCode: e}));
  }
  get storefrontIdentifier() {
    return this._storefrontIdentifier;
  }
  set storefrontIdentifier (e) {
    this._storefrontIdentifier = e, this.dispatchEvent(xe.storefrontIdentifierDidChange, {storefrontIdentifier: e});
  }
  runTokenValidations(e, n = true) {
    e && validateToken(e) ? (n && this._setStorageItem(ve.USER_TOKEN, e), this.authorizationStatus = this.restrictedEnabled ? Ie.RESTRICTED : Ie.AUTHORIZED) : (this._removeStorageItem(ve.USER_TOKEN), this.authorizationStatus = Ie.NOT_DETERMINED);
  }
  wrapDynamicUserTokenForChanges(e, n = invoke(e)) {
    if ("function" != typeof e) return e;
    let d = n;
    return () => {
      const n = invoke(e);
      return d !== n && (d = n, this.runTokenValidations(n, false), this.dispatchEvent(xe.userTokenDidChange, {userToken: n})), n || "";
    };
  }
  get dynamicUserToken() {
    return this._dynamicUserToken;
  }
  set dynamicUserToken (e) {
    const n = invoke(e);
    this._dynamicUserToken = this.wrapDynamicUserTokenForChanges(e, n), this.runTokenValidations(n, "function" != typeof e), this.dispatchEvent(xe.userTokenDidChange, {userToken: n});
  }
  get userToken() {
    return invoke(this.dynamicUserToken);
  }
  set userToken (e) {
    this.dynamicUserToken = e;
  }
  get userTokenIsValid() {
    return validateToken(this.userToken);
  }
  deeplinkURL(e = {}) {
    return "https://finance-app.itunes.apple.com/deeplink?" + buildQueryParams(e = _objectSpread$H({}, this.deeplinkParameters || {}, e));
  }
  itunesDeeplinkURL(e = {p: "browse"}) {
    return "https://itunes.apple.com/deeplink?" + buildQueryParams(e = _objectSpread$H({}, this.deeplinkParameters || {}, e));
  }
  pldfltcid() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      if (!e._cids[ve.DEFAULT_CID]) try {
        yield e.infoRefresh();
      } catch (Mr) {
        return;
      }
      return e._cids[ve.DEFAULT_CID];
    })();
  }
  renewUserToken() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      if (!e.userToken) return e.requestUserToken();
      const n = new Headers({Authorization: "Bearer " + e.developerToken, Accept: "application/json", "Content-Type": "application/json", "X-Apple-Music-User-Token": "" + e.userToken}), d = yield fetch(e.playBase + "/renewMusicToken", {method: "POST", headers: n});
      if (401 === d.status) return yield e.revokeUserToken(), Promise.reject(new Error("Renew token"));
      const h = yield d.json();
      return h["music-token"] && (e.userToken = h["music-token"]), e.userToken;
    })();
  }
  requestStorefrontCountryCode() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      if (e.authorizationStatus <= Ie.DENIED) return Promise.reject("Not authorized: " + e.authorizationStatus);
      const n = new Headers({Authorization: "Bearer " + e.developerToken, "Music-User-Token": e.userToken || ""}), d = yield fetch(e.apiBase + "/me/storefront", {headers: n});
      if (d && !d.ok) return e._reset(), Promise.reject("Storefront Country Code error.");
      const h = yield d.json();
      if (h.errors) return Promise.reject(h.errors);
      const [p] = h.data;
      return p && p.id ? (e.storefrontCountryCode = p.id, e.storefrontCountryCode) : Promise.reject("Storefront Country Code error.");
    })();
  }
  requestStorefrontIdentifier() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      if (!e.storefrontIdentifier) {
        const n = yield class {
          static inferFromLanguages(e, n = function () {
            if ("undefined" == typeof navigator) return [];
            if (navigator.languages) return navigator.languages;
            const e = navigator.language || navigator.userLanguage;
            return e ? [e] : [];
          }()) {
            return _asyncToGenerator$15(function* () {
              const d = yield function (e) {
                return _fetchStorefronts.apply(this, arguments);
              }(e), h = d.map(e => e.id), p = n[0] || "en-US", [y, m] = p.toLowerCase().split(/-|_/), g = h.includes(m) ? m : "us";
              return d.find(e => e.id === g);
            })();
          }
          constructor(e, n, d) {
            this.id = e, this.attributes = n, this.type = "storefronts", this.href = d || `/v1/${this.type}/${e}`;
          }
        }.inferFromLanguages(e.developerToken);
        e.storefrontIdentifier = n.id;
      }
      return e.storefrontIdentifier;
    })();
  }
  requestUserToken() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      if (e._serviceSetupView.isServiceView) return e.userToken || "";
      try {
        const n = yield e._serviceSetupView.load({action: De.AUTHORIZE});
        e.cid = n.cid, e.userToken = n.userToken, e.restrictedEnabled = n.restricted;
      } catch (n) {
        return e._reset(), e.authorizationStatus = n, Promise.reject(n);
      }
      return e.userToken;
    })();
  }
  revokeUserToken() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      var n;
      try {
        yield e._webPlayerLogout();
      } catch (Mr) {}
      null === (n = e.authBridgeApp) || void 0 === n || n.clearAuth(), e.dispatchEvent(xe.authorizationStatusWillChange, {authorizationStatus: e.authorizationStatus, newAuthorizationStatus: Ie.NOT_DETERMINED}), e._reset(), e.dispatchEvent(xe.authorizationStatusDidChange, {authorizationStatus: e.authorizationStatus}), e.dispatchEvent(xe.userTokenDidChange, {userToken: e.userToken});
    })();
  }
  setCids(e) {
    this._cids = _objectSpread$H({}, this._cids, e), Object.keys(this._cids).forEach(e => {
      this._setStorageItem(e, this._cids[e]);
    });
  }
  hasMusicSubscription() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      return !!e.hasAuthorized && e._getIsActiveSubscription();
    })();
  }
  _getIsActiveSubscription() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      var n;
      return !!(null === (n = (yield e.me()).subscription) || void 0 === n ? void 0 : n.active);
    })();
  }
  resetSubscribeViewEligibility() {
    this._dispatchedSubscribeView = false;
  }
  presentSubscribeViewForEligibleUsers(e = {}, n = true) {
    var d = this;
    return _asyncToGenerator$14(function* () {
      const h = yield d.eligibleForSubscribeView();
      if (!d._serviceSetupView.isServiceView && h) {
        if (!n) return d.dispatchEvent(xe.eligibleForSubscribeView, e), void (d._dispatchedSubscribeView = true);
        try {
          const e = yield d._serviceSetupView.load({action: De.SUBSCRIBE});
          return d._dispatchedSubscribeView = true, e;
        } catch (p) {
          return d.revokeUserToken();
        }
      }
    })();
  }
  infoRefresh() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      if (e.authorizationStatus <= Ie.DENIED) return Promise.reject("Not authorized: " + e.authorizationStatus);
      const n = new Headers({Authorization: "Bearer " + e.developerToken, "Music-User-Token": e.userToken || ""});
      try {
        const d = yield fetch(e.iTunesBuyBase + "/account/web/infoRefresh", {credentials: "include", headers: n}), h = yield d.json();
        e.setCids(h);
      } catch (Mr) {}
    })();
  }
  me() {
    if (this.authorizationStatus <= Ie.DENIED) return Promise.reject("Not authorized: " + this.authorizationStatus);
    if (!this._me) {
      var n = this;
      this._me = new Promise(function () {
        var d = _asyncToGenerator$14(function* (d, h) {
          const p = new Headers({Authorization: "Bearer " + n.developerToken, "Music-User-Token": n.userToken || ""}), y = addQueryParamsToURL(n.apiBase + "/me/account", _objectSpread$H({meta: "subscription"}, n.meParameters));
          let m;
          try {
            m = yield fetch(y, {headers: p});
          } catch (Mr) {
            return h(new MKError(MKError.NETWORK_ERROR, "Failed to fetch /me/account"));
          }
          if (m && !m.ok) return n.realm !== e.SKRealm.TV && n._reset(), h("Account error.");
          let g = yield m.json();
          if (g.errors) return h(g.errors);
          const {data: b, meta: _} = g;
          if (!_ || !_.subscription) return h("Account error.");
          n.storefrontCountryCode = _.subscription.storefront;
          const T = {meta: _, subscription: _.subscription};
          return b && b.length && (T.attributes = b[0].attributes), d(T);
        });
        return function (e, n) {
          return d.apply(this, arguments);
        };
      }()).then(e => {
        var n;
        return this._getIsActiveSubscription.updateCache((null === (n = e.subscription) || void 0 === n ? void 0 : n.active) || false), this._me = null, e;
      }).catch(e => (this._me = null, Promise.reject(e)));
    }
    return this._me;
  }
  _getStorageItem(e) {
    var n;
    if (e) return "cookie" === this.persist ? getCookie(e) : "localstorage" === this.persist ? null === (n = this.storage) || void 0 === n ? void 0 : n.getItem(`${this.storagePrefix}.${e}`) : void 0;
  }
  _processLocationHash(e) {
    const n = /^\#([a-zA-Z0-9+\/]{200,}={0,2})$/;
    if (n.test(e)) {
      const d = e.replace(n, "$1");
      try {
        const {itre: e, musicUserToken: n, cid: h} = JSON.parse(atob(d));
        this.restrictedEnabled = e && "1" === e, this.userToken = n, this.cid = h;
      } catch (Mr) {}
      history.replaceState(null, document.title, " ");
    }
  }
  _removeStorageItem(e) {
    if ("cookie" === this.persist) this._removeCookieFromDomains(e); else if ("localstorage" === this.persist) {
      var n;
      return null === (n = this.storage) || void 0 === n ? void 0 : n.removeItem(`${this.storagePrefix}.${e}`);
    }
  }
  _removeCookieFromDomains(e, n = window) {
    removeCookie(e);
    const {hostname: d} = n.location, h = d.split(".");
    if (h.length && (h.shift(), h.length > 2)) for (let p = h.length; p > 2; p--) {
      const d = h.join(".");
      h.shift(), removeCookie(e, n, d);
    }
  }
  _reset(e = Ie.NOT_DETERMINED) {
    this._authorizationStatus = e, this._cids = {}, this._dispatchedSubscribeView = false, this._restrictedEnabled = void 0, this._storefrontCountryCode = void 0, this._getIsActiveSubscription.updateCache(void 0), Object.keys(Te).forEach(e => {
      this._removeStorageItem(Te[e]);
    }), this._removeStorageItem(ve.RESTRICTIONS_ENABLED), this._removeStorageItem(ve.USER_TOKEN), this._removeStorageItem(ve.STOREFRONT_COUNTRY_CODE), this._dynamicUserToken = void 0, this._me = null;
  }
  _setStorageItem(e, n) {
    var d, h;
    return "cookie" === this.persist ? (null === (d = this.authBridgeApp) || void 0 === d || d.setCookieItem(e, n), setCookie(e, n, "/", 180)) : "localstorage" === this.persist ? null === (h = this.storage) || void 0 === h ? void 0 : h.setItem(`${this.storagePrefix}.${e}`, n) : void 0;
  }
  _webPlayerLogout() {
    var e = this;
    return _asyncToGenerator$14(function* () {
      const n = e.logoutURL;
      if (!n) return;
      const d = new Headers({Authorization: "Bearer " + e.developerToken, Accept: "application/json", "Content-Type": "application/json", "X-Apple-Music-User-Token": "" + e.userToken}), h = yield fetch(n, {method: "POST", headers: d, credentials: "same-origin"});
      return h && !h.ok ? Promise.reject(h.status) : h.json();
    })();
  }
  constructor(n, d) {
    super([xe.authorizationStatusDidChange, xe.authorizationStatusWillChange, xe.eligibleForSubscribeView, xe.storefrontCountryCodeDidChange, xe.userTokenDidChange, xe.storefrontIdentifierDidChange]), this.developerToken = n, this.apiBase = "https://api.music.apple.com/v1", this.iTunesBuyBase = je, this.meParameters = {}, this.persist = "localstorage", this.playBase = Ue, this.prefix = "music", this.realm = e.SKRealm.MUSIC, this.storage = getLocalStorage(), this._authorizationStatus = Ie.NOT_DETERMINED, this._disableLogoutURL = false, this._dispatchedSubscribeView = false, this._me = null, this._cids = {}, this._restrictedEnabledOverridden = false, this._dynamicUserToken = getCookie(ve.USER_TOKEN), pe.info("StoreKit initialized"), d && (d.apiBase && (this.apiBase = d.apiBase), d.deeplink && (this.deeplinkParameters = d.deeplink), d.meParameters && (this.meParameters = d.meParameters), d.persist && (this.persist = d.persist), d.prefix && (this.prefix = d.prefix), void 0 !== d.realm && (this.realm = d.realm), this.bundleId = _e[this.realm]), this.cidNamespace = Te[this.realm], this._developerToken = new DeveloperToken(n), this._serviceSetupView = new ServiceSetupView(n, {authenticateMethod: d && d.authenticateMethod, iconURL: d && d.iconURL, deeplinkParameters: this.deeplinkParameters}), this.storagePrefix = `${this.prefix}.${this._developerToken.teamId}`.toLocaleLowerCase(), this.updateUserTokenFromStorage(), this.developerToken && this.userTokenIsValid && (this._restrictedEnabled = this.restrictedEnabled), this._storefrontCountryCode = this.storefrontCountryCode, this.whenAuthCompleted = Promise.resolve(), isNodeEnvironment$1() || (this._processLocationHash(window.location.hash), "cookie" !== this.persist || (null == d ? void 0 : d.disableAuthBridge) || (this.authBridgeApp = new AuthBridgeApp, this.authBridgeApp.authClearedFromOtherFrame = this.revokeUserToken.bind(this), this.whenAuthCompleted = this.authBridgeApp.whenAuthCompleted.then(() => {
      this.updateUserTokenFromStorage();
    })));
  }
}
